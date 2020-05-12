#ifndef MAIN_PROC_H_INCLUDED
#define MAIN_PROC_H_INCLUDED

#include <iostream>
#include <cmath>

#include "onegin.h"
#include "stack.h"
#include "constants.h"

enum commands_number
{
    #define DEF(name) name,

    #include "commands_name.h"

    #undef DEF
};

enum str_to_i
{
    #define STR_COMMANDS(str, name) str,

    #include "string_define.h"

    #undef STR_COMMANDS
};
enum Errors
{
    OK = 0,
    EXTRA_ARG,
    OVERFLOW_LABELS,
    UNKNOWN_CMD
};
enum Type_arg
{
    REG         = 1 << 0,
    LABEL       = 1 << 1,
    NO_ARG      = 1 << 2,
    RAM         = 1 << 3,
    ELEM_T      = 1 << 4,
    COMMENT     = 1 << 5,
};

struct cpu_struct
{
    stack_t cpu_stack;
    stack_t func_stack;
    elem_t reg_a = 0;
    elem_t reg_b = 0;
    elem_t reg_c = 0;
    elem_t reg_d = 0;
    elem_t RAM[RAM_LENGTH] = {};             //alloc 1mb array to ram
};

struct labels
{
    int byte;
    char name[S_LENGTH];
};

struct Data_labels
{
    labels labels_arr[LABELS_LENGTH] = {};
    labels jump_bytes[LABELS_LENGTH] = {};
    int labels_num = 0;
    int jump_num = 0;
};

struct Commands
{
    int cmd_num = 0;
    elem_t arg_num = 0;
    int type_arg = 0;
    char label_name[S_LENGTH] = {};
};


void unit_tests();

int update_label(Data_labels data_lable, char* asm_text);

int get_lable(Data_labels* data_label, Commands* cur_cmd, int* writed, int *error, char* asm_text);

int get_type_str_arg(char* arg_name, Commands* cmd);

int split_line(pointer_on_line pointer, Commands* cmd);

int make_binary_file                   (const char* input_name     = INPUT_FILE,
                                        const char* assembler      = ASSEMBLER_FILE);
int disassembler                       (const char* disasm_file    = DISASSEMBLER_FILE,
                                        const char* assembler_file = ASSEMBLER_FILE);

int CPU (cpu_struct *processor,         const char* binary_file    = ASSEMBLER_FILE,
                                        const char* result_file    = OUTPUT_FILE);

int bin_to_txt                         (const char* assembler_file, char* &result_txt);

int realloc_buffer(int* size_buf, char** asm_text, int writed, int resize_b);

const char* get_reg_name(int n);

elem_t* get_reg_num(int cmd, cpu_struct* processor);

#include "asm.hpp"
#include "read_file.hpp"
#include "stack.hpp"
#include "cpu.hpp"
//#include "unit_tests.hpp"




#endif // MAIN_PROC_H_INCLUDED
