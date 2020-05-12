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
#include <deque>

enum class HeaderType {
    DEFAULT = 0,

};

enum class Commands {
    #define DEF(name) name,
    #include "../../compiler/inc/commands_name.h"
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
    #include "../../compiler/inc/string_define.h"
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
    void WriteBinInt(int val);
    void PushXMM(int n);
    void PopXMM(int n);
    void WritePow();
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
    explicit Compiler(const std::string& input = "assembler.bin", const std::string &output_file = "output") {
        std::ofstream out(output_file);
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
        res += StrToHex("8802400000000000"); //virtual entry address
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
        res += StrToHex("3e11000000000000"); //size of program in file
        res += StrToHex("3e11000000000000"); //size of program in memory
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
    std::deque<unsigned char> buff_optimization;
    ReserveVariables();
    while (!input.eof()) {
        char tmp_cmd;
        char type;
        command_array.emplace_back(input.tellg(), binary_file.size());
        if (!input.read(&tmp_cmd, 1)) {
            break;
        }
        if (!input.read(&type, 1)) {
            throw "Error extra byte at the end of file";
        }
        auto cmd = static_cast<Commands>(tmp_cmd);
        if (cmd == Commands::JMP) {
            binary_file += StrToHex("e9");           //jmp near opcode
            AddLabel(input);
        } else if (cmd == Commands::ADD) {
            ArithmeticOperations("f20f58c1", type);                 //add xmm0, xmm1
        } else if (cmd == Commands::SUB) {
            ArithmeticOperations("f20f5cc1", type);                 //sub xmm0, xmm1
        } else if (cmd == Commands::MUL) {
            ArithmeticOperations("f20f59c1", type);               //mul xmm0, xmm1
        } else if (cmd == Commands::DIV) {
            ArithmeticOperations("f20f5ec1", type);   //div xmm0, xmm1
        } else if (cmd == Commands::PUSH) {
            int cur_num = ReadInt(input);
            if (type == static_cast<int>(TypeArg::REG)) {
                PushXMM(cur_num);
            } else if (type == static_cast<int>(TypeArg::RAM)) {
                binary_file += StrToHex("ffb5");         //push [bp - 8 * cur_num]
                WriteBinInt(-1 * 8 * cur_num);
            } else if (type == (static_cast<int>(TypeArg::RAM) | static_cast<int>(TypeArg::REG))) {
                binary_file += StrToHex("ff");
                binary_file += static_cast<unsigned char>(cur_num + 0x30);
            } else if (type == static_cast<int>(TypeArg::ELEM_T)) {
                binary_file += StrToHex("48b8");         //mov rax, ...
                long long tmplong = cur_num;
                char* tmp = static_cast<char *>(static_cast<void *>(&tmplong));
                std::string tmp_str(tmp, 8);
                //std::reverse(tmp_str.begin(), tmp_str.end());  //depend on little endian
                binary_file += tmp_str;
                binary_file += StrToHex("f2480f2ac8");   //cvtsi2sd xmm1, rax
                PushXMM(1);
            }
        } else if (cmd == Commands::POP) {
            int cur_num = ReadInt(input);
            if (type == static_cast<int>(TypeArg::REG)) {
                PopXMM(cur_num);
            } else if (type == static_cast<int>(TypeArg::RAM)) {
                binary_file += StrToHex("8f85");         //pop [bp + 8 * cur_num]
                WriteBinInt(-1 * 8 * cur_num);
            } else if (type == (static_cast<int>(TypeArg::RAM) | static_cast<int>(TypeArg::REG))) {
                binary_file += StrToHex("8f");
                binary_file += static_cast<unsigned char>(cur_num);
            }
        } else if (cmd == Commands::IN) {
            binary_file += StrToHex("e8");            //jmp ...
            int pos = -1 * binary_file.size() - 2 + 0x80;
            char* tmp = static_cast<char *>(static_cast<void *>(&pos));
            binary_file += std::string(tmp, 4);
            binary_file += StrToHex("f2490f2ac8");      //cvtsi2sd xmm1,r8
            PushXMM(1);                                     //push xmm1
        } else if (cmd == Commands::OUT) {
            PopXMM(0);
            binary_file += StrToHex("f2480f2cc0");    //cvttsd2si rax, xmm0
            binary_file += StrToHex("e8");            //jmp ...
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
            WriteJmp(input, "0f86");
        } else if (cmd == Commands::JL) {
            WriteJmp(input, "0f82");
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
        } else if (cmd == Commands::POW) {
            if (type != static_cast<int>(TypeArg::NO_ARG)) {
                throw "Bad Type of argument in pow, expected NO_ARG";
            } else {
                WritePow();
            }
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
    PopXMM(1);
    PopXMM(0);
    //binary_file += StrToHex("5b58");      //pop rbx; pop rax
    binary_file += StrToHex("660f2fc1");    //comisd xmm0,xmm1
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
            for (int i = 0; i < jmp_near_size; i++) {
                binary_file[label_arr.begin()->second - jmp_near_size + i] = bin_label[i];
            }
            label_arr.erase(label_arr.begin());
        }
    }
}

void GenerateBinary::ArithmeticOperations(std::string opcode, int type) {
//    if (type != static_cast<int>(TypeArg::NO_ARG)) {
//        throw "Bad type in Arithmetic operation, expected NO_ARG, get " + std::to_string(static_cast<int>(type));
//    }
//  binary_file += StrToHex("5b58");     //pop rbx; pop rax
    PopXMM(1);
    PopXMM(0);
    binary_file += StrToHex(opcode);
    PushXMM(0);
}

void GenerateBinary::WriteBinInt(int val) {
    char* tmp = static_cast<char *>(static_cast<void *>(&val));
    std::string tmp_str(tmp, 4);
    //std::reverse(tmp_str.begin(), tmp_str.end());     //depend on little endian
    binary_file += tmp_str;
}

void GenerateBinary::PopXMM(int n) {
    switch (n) {                                            //movsd  xmm0, [rsp]
        case 0:
            binary_file += StrToHex("f20f100424");
            break;
        case 1:
            binary_file += StrToHex("f20f100c24");
            break;
        case 2:
            binary_file += StrToHex("f20f101424");
            break;
        case 3:
            binary_file += StrToHex("f20f101c24");
            break;
        default:
            throw "Bad number of xmm register in pop XMM";
    }
    binary_file += StrToHex("4883c408");       //sub rsp, 8
}

void GenerateBinary::PushXMM(int n) {
    binary_file += StrToHex("4883ec08");        //add rsp, 8
    switch (n) {                                        //movsd  [rsp], xmm0
        case 0:
            binary_file += StrToHex("f20f110424");
            break;
        case 1:
            binary_file += StrToHex("f20f110c24");
            break;
        case 2:
            binary_file += StrToHex("f20f111424");
            break;
        case 3:
            binary_file += StrToHex("f20f111c24");
            break;
        default:
            throw "Bad number of xmm register in push XMM";
    }
}

void GenerateBinary::WritePow() {
    PopXMM(1);  //degree of pow
    PopXMM(1);
    binary_file += StrToHex("f20f51c1");
    PushXMM(0);
}

#endif //COMPILER_COMPILER_H