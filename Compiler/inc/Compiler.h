//
// Created by aleksey on 21.04.2020.
//

#ifndef COMPILER_COMPILER_H
#define COMPILER_COMPILER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>

enum class HeaderType {
    DEFAULT = 0,

};

enum class Commands {
    #define DEF(name) name,
    #include "../../processor/commands_name.h"
    NumberOfCommands
};
enum class TypeArg {
    REG         = 1 << 0,
    LABEL       = 1 << 1,
    NO_ARG      = 1 << 2,
    RAM         = 1 << 3,
    ELEM_T      = 1 << 4,
    COMMENT     = 1 << 5,
};

enum class RegNumber {
    #define STR_COMMANDS(reg, name) reg,
    #include "../../processor/string_define.h"
};

class GenerateBinary {
private:
    std::vector<std::pair<int, int>> command_array;
    std::string binary_file;
    std::string filename;
    std::set<std::pair<int, int>> label_arr;
    long long ReadInt(std::ifstream &input);
    double ReadDouble(std::ifstream &input);
    void ReserveVariables();
    long long FindBinPosInOutput(int inp_file_pos) {};
    void PrintDouble() {};
    void ScanDouble() {};
    void WriteJmp(std::ifstream &input, std::string jmp_opcode);
    void AddLabel(std::ifstream &input);
    void UpdateJmpList();
    void ArithmeticOperations(std::string opcode, int type);
public:
    explicit GenerateBinary(const std::string &input_filename);
    explicit operator std::string() {
        return binary_file;
    }
};

class Compiler {
private:
    std::string GetElfHeader(HeaderType type = HeaderType::DEFAULT);
public:
    explicit Compiler(const std::string& input = "assembler.bin", const std::string& commands_file = "command_list.txt") {
        std::ofstream out("output");
        out << GetElfHeader() << std::string(GenerateBinary(input));
    }
    enum class Error {
        Commands_not_found,
        BadOpcodeSize,
    };
};

std::string StrToHex(std::string hex_str) {
    std::string res;
    unsigned char tmp = 0;
    for (int i = 0; i < hex_str.size(); i++) {
        if (hex_str[i] >= '0' && hex_str[i] <= '9') {
            tmp += (1 + 15 * (i % 2 == 0)) * (hex_str[i] - '0');
        } else {
            tmp += (1 + 15 * (i % 2 == 0)) * (hex_str[i] - 'a' + 10);
        }
        if (i % 2 == 1) {
            res.append(1, tmp);
            tmp = 0;
        }
    }
    return res;
};

std::string Compiler::GetElfHeader(HeaderType type) {
    if (type == HeaderType::DEFAULT) {
        std::string res;
        res += StrToHex("7f454c46");         //ELF start
        res += StrToHex("02");               //64bit
        res += StrToHex("01");               //little endian
        res += StrToHex("01");               //elf_ver
        res += StrToHex("00");               //ABI type
        res += StrToHex("0000000000000000"); //reserved
        res += StrToHex("0200");             //executable
        res += StrToHex("3e00");             //x86-64
        res += StrToHex("01000000");         //elf_format, only 1
        res += StrToHex("7802400000000000"); //virtual entry address
        res += StrToHex("4000000000000000"); //program header table offset
        res += StrToHex("0000000000000000"); //section header table offset
        res += StrToHex("00000000");         //elf flag
        res += StrToHex("3800");             //sizeof header
        res += StrToHex("3800");             //sizeof program table
        res += StrToHex("0100");             //number of program headers
        res += StrToHex("4000");             //sizeof section header
        res += StrToHex("00000000");         //number of section header and shstrndx
        res += StrToHex("01000000");         //text segment?

        //We use write in IN and OUT instructions to avoid other section
        res += StrToHex("07000000");         //r+x+w

        res += StrToHex("0000000000000000"); //offset from start of file
        res += StrToHex("0000400000000000"); //virtual segment address
        res += StrToHex("0000400000000000"); //physical address
        res += StrToHex("3e00000000000000"); //size of program in file
        res += StrToHex("3e00000000000000"); //size of program in memory
        res += StrToHex("0100000000000000"); //align power of two
        return res;
    }
}

GenerateBinary::GenerateBinary(const std::string &input_filename) {
    filename = input_filename;
    std::ifstream input(input_filename, std::ios::binary);
    std::vector<int> vec;
    std::multiset<std::pair<int, int>> label_arr;
    std::stringstream tmpsstream;
    tmpsstream << std::fstream("src/IOlib.s").rdbuf();
    binary_file += tmpsstream.str();

    ReserveVariables();
    while (!input.eof()) {
        char tmp_cmd;
        char type;
        command_array.emplace_back(input.tellg(), binary_file.size());
        input.read(&tmp_cmd, 1);
        input.read(&type, 1);
        Commands cmd = static_cast<Commands>(tmp_cmd);
        if (cmd == Commands::JMP) {
            binary_file += StrToHex("e9");           //jmp near opcode
            AddLabel(input);
        } else if (cmd == Commands::ADD) {
            ArithmeticOperations("4801d8", type);                 //add rax, rbx
        } else if (cmd == Commands::SUB) {
            ArithmeticOperations("4829d8", type);                 //sub rax, rbx
        } else if (cmd == Commands::MUL) {
            ArithmeticOperations("480fafc3", type);               //imul rax, rbx
        } else if (cmd == Commands::DIV) {
            ArithmeticOperations("48f7fb", type);   //idiv rax, rbx
        } else if (cmd == Commands::PUSH) {
            long long cur_num = ReadInt(input);
            if (type == static_cast<int>(TypeArg::REG)) {
                binary_file += static_cast<unsigned char>(cur_num + 0x50);  //80?
            } else if (type == static_cast<int>(TypeArg::RAM)) {
                binary_file += StrToHex("ff75");         //push [bp + 8 * cur_num]
                binary_file += static_cast<unsigned char>(-1 * 8 * cur_num);
            } else if (type == (static_cast<int>(TypeArg::RAM) | static_cast<int>(TypeArg::REG))) {
                binary_file += StrToHex("ff");
                binary_file += static_cast<unsigned char>(cur_num + 0x30);
            } else if (type == static_cast<int>(TypeArg::ELEM_T)) {
                binary_file += StrToHex("49bf");         //mov r15, ...
                char* tmp = static_cast<char *>(static_cast<void *>(&cur_num));
                std::string tmp_str(tmp, 8);
                //std::reverse(tmp_str.begin(), tmp_str.end());     //depend on little endian
                binary_file += tmp_str;
                binary_file += StrToHex("4157");         //push r15
            }
        } else if (cmd == Commands::POP) {
            int cur_num = ReadInt(input);
            if (type == static_cast<int>(TypeArg::REG)) {
                binary_file += static_cast<unsigned char>(cur_num + 0x58);
            } else if (type == static_cast<int>(TypeArg::RAM)) {
                binary_file += StrToHex("8f45");         //pop [bp + 8 * cur_num]
                binary_file += static_cast<unsigned char>(-1 * 8 * cur_num);
            } else if (type == (static_cast<int>(TypeArg::RAM) | static_cast<int>(TypeArg::REG))) {
                binary_file += StrToHex("8f");
                binary_file += static_cast<unsigned char>(cur_num);
            }
        } else if (cmd == Commands::IN) {
            binary_file += StrToHex("e8");            //jmp ...
            int pos = -1 * binary_file.size() - 2 + 0x80;
            char* tmp = static_cast<char *>(static_cast<void *>(&pos));
            binary_file += std::string(tmp, 4);
            binary_file += StrToHex("4150");            //push r8
        } else if (cmd == Commands::OUT) {
            binary_file += StrToHex("58e8");            //pop rax; jmp ...
            int pos = -1 * binary_file.size() - 4 + 0x80;
            char* tmp = static_cast<char *>(static_cast<void *>(&pos));
            binary_file += std::string(tmp, 4);
        } else if (cmd == Commands::JA) {
            WriteJmp(input, "0f87");
        } else if (cmd == Commands::JAE) {
            WriteJmp(input, "0f83");
        } else if (cmd == Commands::JNE) {
            WriteJmp(input, "0f85");
        } else if (cmd == Commands::JE) {
            WriteJmp(input, "0f84");
        } else if (cmd == Commands::JLE) {
            WriteJmp(input, "0f8e");
        } else if (cmd == Commands::JL) {
            WriteJmp(input, "0f8c");
        } else if (cmd == Commands::JME) {
            WriteJmp(input, "0f83");
        } else if (cmd == Commands::JM) {
            WriteJmp(input, "0f87");
        } else if (cmd == Commands::CALL) {
            binary_file += StrToHex("e8");
            AddLabel(input);
            binary_file += StrToHex("50");          //push rax
        } else if (cmd == Commands::RET) {
            binary_file += StrToHex("58");          //pop rax
            binary_file += StrToHex("c3");          //ret
        } else if (cmd == Commands::END) {
            binary_file += StrToHex("b801000000bb00000000cd80");    //end of program
        }
    }
    UpdateJmpList();
    binary_file += StrToHex("b801000000bb00000000cd80");    //end of program to avoid seg fault in program without end
}

double GenerateBinary::ReadDouble(std::ifstream &input) {
    double tmp;
    input.readsome(static_cast<char *>(static_cast<void *>(&tmp)), 8);
    return tmp;
}

long long GenerateBinary::ReadInt(std::ifstream &input) {
    double tmp;
    input.readsome(static_cast<char *>(static_cast<void *>(&tmp)), 8);
    return static_cast<long long>(tmp);
    return *static_cast<long long *>(static_cast<void*>(&tmp));
}

void GenerateBinary::ReserveVariables() {
    binary_file += StrToHex("4889e5");   //mov rbp, rsp
    binary_file += StrToHex("4881ecf0000000");   //reserve space to 20 variables of type double
}

void GenerateBinary::WriteJmp(std::ifstream &input, std::string jmp_opcode) {
    binary_file += StrToHex("585b");      //pop rax; pop rbx
    binary_file += StrToHex("4839D8");    //cmp rax, rbx
    binary_file += StrToHex(jmp_opcode);         //jmp ...
    AddLabel(input);                          //add addr
}

void GenerateBinary::AddLabel(std::ifstream &input) {
    long long label = ReadInt(input);
    binary_file += "1111";                              //reserve 32bit for address (we use jmp near)
    label_arr.emplace(static_cast<int>(label), binary_file.size());
}

void GenerateBinary::UpdateJmpList() {
    for (auto &elem : command_array) {
        while (!label_arr.empty() && elem.first == label_arr.begin()->first) {
            const int jmp_near_size = 4;
            int jmp_src = elem.second - label_arr.begin()->second;
            char* bin_label = static_cast<char *>(static_cast<void *>(&jmp_src));
            std::cout << elem.second << " " << label_arr.begin()->second;
            for (int i = 0; i < jmp_near_size; i++) {
                binary_file[label_arr.begin()->second - jmp_near_size + i] = bin_label[i];
            }
            //binary_file.replace(label_arr.begin()->second - jmp_near_size, jmp_near_size, bin_label);
            label_arr.erase(label_arr.begin());
        }
    }
}

void GenerateBinary::ArithmeticOperations(std::string opcode, int type) {
//    if (type != static_cast<int>(TypeArg::NO_ARG)) {
//        throw "Bad type in Arithmetic operation, expected NO_ARG, get " + std::to_string(static_cast<int>(type));
//    }
    binary_file += StrToHex("585b");     //pop rax; pop rbx
    binary_file += StrToHex(opcode);
    binary_file += StrToHex("50");       //push rax
}

#endif //COMPILER_COMPILER_H