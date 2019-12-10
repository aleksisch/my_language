#ifndef WORK_STRING_HEADER
#define WORK_STRING_HEADER

#include "../include/MainHeader.h"

template <typename type_t>
const char* NodeDataToStr(TreeNode<type_t>* current)
{

    if (current->type_node == NodeType::VARIABLE)
    {
        std::string res = std::to_string(((int) current->number) % MAX_HASH);
        res = "var" + res;
        return res.c_str();
    }

    else if (current->left_child != nullptr)    //keep func arg in left child
    {
        for (int op = 0; op < Operands::NUM; op++)
            if (MyRound(current->number) == Operation<type_t>[op].num)
                return Operation<type_t>[op].name;

        return "Unknown cmd";
    }

    else
    {
        std::string res = std::to_string(current->number);
        return res.c_str();
    }
}

template <typename type_t>
const char* FuncToStr(TreeNode<type_t>* current)
{
    assert(current);

    using namespace Operands;
    switch (MyRound(current->number))
    {
        case ADD:
            return "ADD";
        case SUB:
            return "SUB";
        case MUL:
            return "MUL";
        case DIV:
            return "DIV";
        case SIN:
            return "SIN";
        case COS:
            return "COS";
        case POW:
            return "POW";
        default:
            return "UNKNOWN";
    }
}

FILE* BeginLatexFile(const char* output)
{
    FILE* file = fopen (output, "w");
    fprintf(file,    "\\documentclass{article}\n\
                        \\usepackage{hyperref}\n\
                        \\begin{document}\n $$");
    return file;
}

void CloseLatexFile(FILE*& file)
{
    if (file == nullptr)
        return;

    fprintf(file, "$$\n\\end{document}");

    fclose(file);

    char s[STR_LENGTH] = "";

    sprintf(s, "pdflatex %s >/dev/null", log_filename);

    system(s);

    file = nullptr;
}

char* ReadFile (const char* str, size_t *size, const char* chmod)
{
    FILE *fp = NULL;

    if ((fp = fopen(str, chmod)) == NULL)
    {
        printf("Cannot find text\n");
        system("pause");
        exit(0);
    }

    fseek (fp, 0L, SEEK_END);

    *size = ftell(fp);

    char *text = (char *) calloc(*size + 1, sizeof(char));

    fseek (fp, 0L, SEEK_SET);

    fread (text, sizeof(char), *size, fp);

    text[*size] = '\0';

    fclose (fp);

    return text;
}

#endif
