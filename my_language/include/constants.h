#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

static const char* input_graph_file  = "input.txt";
static const char* output_graph_file = "out_graph.txt";
static const char* output_graphviz   = "tmp_dump.dt";
static const char* output_latex      = "node_latex.txt";
static const char* log_filename      = "log.txt";
static const char* assembler_file    = "../asm.txt";
static const int MAX_VARIABLE        = 30;
static const int MAX_HASH            = 1000;
static const int STR_LENGTH = 255;

namespace Priority
{
    enum
    {
        SKIP,
        FUNC,
        ASSIGN,
        COMPARE,
        ADDSUB,
        MULDIV,
        MATH,
        VAR,
    };
}

namespace Operands
{
    enum
    {
        FUNC,
        SUB,
        ADD,
        DIV,
        MUL,
        SIN,
        COS,
        LN,
        TAN,
        POW,
        SINH,
        COSH,
        TANH,
        RET,
        WHILE,
        IF,
        MORE,
        MOREEQ,
        LESSEQ,
        LESS,
        EOLINE,
        ASSIGN,
        VAR,
        EQUAL,
        NEQUAL,
        PRINTF,
        SCANF,
        DIFF,
        NUM,
    };
}

namespace NodeType
{
    enum
    {
        OK = 0,
        QUOTE,
        MATH,
        VALUE,
        VARIABLE,
        OPERATION,
        STATEMENT,
        FUNCTION,
        UNKNOWN,
    };
}

#endif // CONSTANTS_H_INCLUDED
