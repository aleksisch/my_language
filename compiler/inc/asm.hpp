#include "main_proc.h"
#include <cstdlib>
#include <string>

int make_binary_file(const char* input_name, const char* assembler)
{
    pointer_on_line* lineptr = nullptr;
    char*               text = nullptr;
    int                 size = 0;
    int            countline = 0;
    int               writed = 0;
    int                error = OK;

    work_file(&size, &lineptr, &text, input_name, &countline);

    int size_buf = countline + (int) sizeof(elem_t);

    char* asm_text = (char*) calloc(size_buf, sizeof(char));

    Data_labels data_lable;

    #define DEF(num, elements, code)                                                        \
    else if (cur_cmd.cmd_num == num && cur_cmd.type_arg == elements)                        \
    {                                                                                       \
        asm_text[writed++] = (char) num;                                                    \
        asm_text[writed++] = (char) elements;                                               \
                                                                                            \
        if ( (elements & NO_ARG) != NO_ARG)                                                 \
        {                                                                                   \
            elem_t* ptr = (elem_t*) (asm_text + writed);                                    \
            *ptr        = cur_cmd.arg_num;                                                  \
            writed     += (int) sizeof(elem_t);                                             \
        }                                                                                   \
    }

    for (int line = 0; line < countline; line++)
    {
        Commands cur_cmd = {};

        error = split_line(lineptr[line], &cur_cmd);

        realloc_buffer(&size_buf, &asm_text, writed, countline + (int) sizeof(elem_t));

        if (get_lable (&data_lable, &cur_cmd, &writed, &error, asm_text) == 0);

        else if ((cur_cmd.type_arg & COMMENT) == COMMENT);

        #include "proc_commands.h"

        else
            printf("BAD COMMAND %d name, %d type skipped it line is %d\n", cur_cmd.cmd_num, cur_cmd.type_arg, line);

        if (error != 0)
            printf("something goes wrong error code: %d", error);

    }

    #undef DEF

    update_label(data_lable, asm_text);

    FILE *asm_file = fopen(assembler, "w+b");

    if (asm_file == nullptr)
        return 1;

    fwrite(asm_text, sizeof(char), writed, asm_file);
    free(asm_text);
    fclose(asm_file);

    return error;
}

int update_label(Data_labels data_lable, char* asm_text)
{
    for (int i = 0; i < data_lable.jump_num; i++)

        for (int l = 0; l < LABELS_LENGTH; l++)
        {
            if (strcmp(data_lable.jump_bytes[i].name, data_lable.labels_arr[l].name) == 0)

                *((elem_t*) (asm_text + data_lable.jump_bytes[i].byte)) = (elem_t) data_lable.labels_arr[l].byte;
        }
    return 0;
}

int get_lable(Data_labels* data_label, Commands* cur_cmd, int* writed, int *error, char* asm_text)
{
    if (cur_cmd->label_name[0] == ':' && (cur_cmd->type_arg == LABEL))
    {
        bool label_exist = false;

        for (int i = 0; i < LABELS_LENGTH; i++)

            if (strcmp(cur_cmd->label_name, data_label->labels_arr[i].name) == 0)
            {
                data_label->labels_arr[i].byte = *writed;
                label_exist = true;
            }

        int* l_number = &(data_label->labels_num);

        if (label_exist == 0 && ++(*l_number) < LABELS_LENGTH)
        {
                   data_label -> labels_arr[*l_number].byte = *writed;
            strcpy(data_label -> labels_arr[*l_number].name, cur_cmd->label_name+1);    //+1 to avoid ':'
        }

        if (LABELS_LENGTH < *l_number) *error |= OVERFLOW_LABELS;
    }
    else if (cur_cmd->type_arg == LABEL)
    {
        #define DEF(num, elements, code)                                                                \
        if (cur_cmd->cmd_num == num && elements == cur_cmd->type_arg)                                   \
        {                                                                                               \
            asm_text[(*writed)++] = (char) num;                                                         \
            asm_text[(*writed)++] = (char) elements;                                                    \
                                                                                                        \
                   data_label -> jump_bytes[ data_label -> jump_num ].byte = *writed;                   \
            strcpy(data_label -> jump_bytes[(data_label -> jump_num)++].name, cur_cmd->label_name);     \
            *writed += (int) sizeof(elem_t);                                                            \
        }                                                                          // for label

        #include "proc_commands.h"

        #undef DEF
    }
    else return 1;

    return 0;
}

int disassembler(const char* disasm_file, const char* assembler_file)
{
    char* result_txt = nullptr;

    bin_to_txt(assembler_file, result_txt);

    FILE *output_file = fopen(disasm_file, "w");

    if (output_file == nullptr)
        return 1;

    fprintf(output_file, "%s", result_txt);

    fclose(output_file);

    free(result_txt);

    return 0;
}

int get_type_str_arg(char* arg_name, Commands* cmd)
{
    if (arg_name[0] == ';')         //if comment
    {
        cmd->type_arg |= NO_ARG;
        return 0;
    }
    if (arg_name[0] == '[')         //if ram
    {
        cmd->type_arg |= RAM;

        if (sscanf(arg_name + 1, CONST_FOR_ELEM_T, &(cmd->arg_num)) == 1)   //scanf array index
            return 0;

        else
            arg_name++;             //to skip '['
    }
    #define STR_COMMANDS(name, letter) if ((#name)[0] == arg_name[0] && \
                                           (#name)[1] == arg_name[1])   \
                                           {                            \
                                               cmd->arg_num = name;     \
                                               cmd->type_arg |= REG;    \
                                           }
    #include "string_define.h"

    #undef STR_COMMANDS

    if ((cmd->type_arg & REG) == REG)
        return 0;

    cmd->type_arg |= LABEL;

    strcpy(cmd->label_name, arg_name);

    return 0;
}

int split_line(pointer_on_line pointer, Commands* cmd)
{
    char* cur_txt          = pointer.start;
    int readed             = 0;
    int error              = 0;
    int cur_cmd_type       = 0;
    char arg_str[S_LENGTH] = {};
    char cmd_str[S_LENGTH] = {};

    sscanf(cur_txt, "%s %n", cmd_str, &readed);

    if (cmd_str[0] == ':')
    {
        strcpy(cmd->label_name, cmd_str);
        cmd->type_arg |= LABEL;
    }

    else if (cmd_str[0] == ';') cmd->type_arg |= COMMENT;


    #define DEF(name, num, code)\
                                                \
        else if (strcmp(#name, cmd_str) == 0)   \
        {                                       \
                cmd->cmd_num = name;            \
                cur_cmd_type = num;             \
        }

    #include "proc_commands.h"

    #undef DEF

    else error |= UNKNOWN_CMD;

    int cur_elem_read = 0;

    char next_char = 0;

    sscanf(cur_txt + readed,  "%*s%c", &next_char);

    int last_elem = sscanf(cur_txt + readed, CONST_FOR_ELEM_T " %n", &cmd->arg_num, &cur_elem_read);

    if (last_elem == 0) cur_elem_read = 0;

    if (next_char == ';')
        cmd->type_arg |= COMMENT;

    else if (last_elem == -1 || (cur_cmd_type & NO_ARG) == NO_ARG)                                //end of file
    {
        if (cmd->type_arg != LABEL)
            cmd->type_arg |= NO_ARG;
    }

    else if (last_elem == 0)
    {
        sscanf(cur_txt + readed, "%s %n", arg_str, &cur_elem_read);

        error |= get_type_str_arg(arg_str, cmd);                        //getting cmd->type_arg && cmd->arg_num
    }

    else if (last_elem == 1)
        cmd->type_arg |= ELEM_T;

    if (sscanf(cur_txt + readed + cur_elem_read, "%s", arg_str) == 1 && arg_str[0] != ';')
        error |= EXTRA_ARG;

    return error;
}


int bin_to_txt(const char* assembler_file, char* &result_txt)
{
    int readed    = 0;
    int size_asm  = 0;
    int writed    = 0;
    int error     = OK;

    char *assembler  = (char*) readFile (assembler_file, &size_asm, "r+b");

    int size_buf = size_asm + 100;                                         //to not often use realloc on small asm file

    result_txt = (char*) calloc(size_buf, sizeof(char));

    #define DEF(name, elements, code)                                                       \
    else if ((int) assembler[readed]     == name &&                                         \
             (int) assembler[readed + 1] == elements)                                       \
    {                                                                                       \
        readed += 2;                                                                        \
        int cur_write = 0;                                                                  \
        sprintf(result_txt + writed, "%s%n", #name, &cur_write);                            \
        writed += cur_write;                                                                \
        elem_t next = *((elem_t*) (assembler + readed));                                    \
                                                                                            \
        if (((int)elements & NO_ARG) == 0)                                                  \
        {                                                                                   \
            if ( elements == (RAM | REG))                                                   \
                sprintf(result_txt + writed, " [%s]%n", get_reg_name((int) next), &cur_write);\
                                                                                            \
            else if (elements == REG)                                                       \
                sprintf(result_txt + writed, " %s%n", get_reg_name((int) next), &cur_write);\
                                                                                            \
            else if (elements == RAM)                                                       \
                sprintf(result_txt + writed, " [%d]%n", (int) next, &cur_write);            \
                                                                                            \
            else sprintf(result_txt + writed, " " CONST_FOR_ELEM_T "%n", next, &cur_write); \
                                                                                            \
            writed += cur_write;                                                            \
            readed += (int) sizeof(elem_t);                                                 \
        }                                                                                   \
        sprintf(result_txt + writed++, "\n");                                               \
    }
    while (readed < size_asm)
    {
        realloc_buffer (&size_buf, &result_txt, writed, size_asm + 100); // + 100 to avoid overflow array on small size_asm

        if (0) ;

        #include "proc_commands.h"

        else
        {
            printf("ERROR elem in asm file: %d %d \n",  assembler[readed], readed);
            error |= UNKNOWN_CMD;
        }
    }
    #undef DEF

    free(assembler);

    return error;
}


int realloc_buffer(int* size_buf, char** asm_text, int writed, int resize_b)
{
    if (writed * 2  > *size_buf)
        {
            int temp = *size_buf;
            *size_buf += resize_b ;
            *asm_text = (char*) realloc(*asm_text, *size_buf);

            if (asm_text == nullptr)
                return REALLOC_ERROR;

            memset(*asm_text + temp, 0, *size_buf - temp);
        }
    return OK;
}

const char* get_reg_name(int n)
{
    #define STR_COMMANDS(name, letter) if (name == n) return #name;

    #include "string_define.h"

    #undef STR_COMMANDS

    return "Unknown register";
}
