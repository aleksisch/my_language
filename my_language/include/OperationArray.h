#ifndef OPERATIONARRAY_H_INCLUDED
#define OPERATIONARRAY_H_INCLUDED

template <typename type_t>
struct Operators
{
    int num;
    int type;
    char name[STR_LENGTH];
    int priority;
};


template <typename type_t>
const Operators<type_t> Operation[] = {
                                        {Operands::EOLINE, NodeType::QUOTE,      ";",       Priority::SKIP},
                                        {Operands::EQUAL,  NodeType::OPERATION,  "==",      Priority::COMPARE},
                                        {Operands::NEQUAL, NodeType::OPERATION,  "!=",      Priority::COMPARE},
                                        {Operands::MOREEQ, NodeType::OPERATION,  ">=",      Priority::COMPARE},
                                        {Operands::LESSEQ, NodeType::OPERATION,  "<=",      Priority::COMPARE},
                                        {Operands::MORE,   NodeType::OPERATION,  ">",       Priority::COMPARE},
                                        {Operands::LESS,   NodeType::OPERATION,  "<",       Priority::COMPARE},
                                        {Operands::ASSIGN, NodeType::STATEMENT,  "=",       Priority::ASSIGN},
                                        {Operands::SUB,    NodeType::OPERATION,  "-",       Priority::ADDSUB},
                                        {Operands::ADD,    NodeType::OPERATION,  "+",       Priority::ADDSUB},
                                        {Operands::DIV,    NodeType::OPERATION,  "/",       Priority::MULDIV},
                                        {Operands::MUL,    NodeType::OPERATION,  "*",       Priority::MULDIV},
                                        {Operands::POW,    NodeType::OPERATION,  "^",       Priority::MULDIV},
                                        {Operands::SIN,    NodeType::MATH,       "sin",     Priority::MATH},
                                        {Operands::COS,    NodeType::MATH,       "cos",     Priority::MATH},
                                        {Operands::LN,     NodeType::MATH,       "ln",      Priority::MATH},
                                        {Operands::TAN,    NodeType::MATH,       "tan",     Priority::MATH},
                                        {Operands::SINH,   NodeType::MATH,       "sh",      Priority::MATH},
                                        {Operands::COSH,   NodeType::MATH,       "ch",      Priority::MATH},
                                        {Operands::TANH,   NodeType::MATH,       "th",      Priority::MATH},
                                        {Operands::PRINTF, NodeType::MATH,       "print",   Priority::MATH},
                                        {Operands::SCANF,  NodeType::MATH,       "scan",    Priority::MATH},
                                        {Operands::DIFF,   NodeType::MATH,       "diff",    Priority::MATH},
                                        {Operands::FUNC,   NodeType::FUNCTION,   "func",    Priority::FUNC},
                                        {Operands::WHILE,  NodeType::STATEMENT,  "while",   Priority::FUNC},
                                        {Operands::IF,     NodeType::STATEMENT,  "if",      Priority::FUNC},
                                        {Operands::ELSE,   NodeType::STATEMENT,  "else",    Priority::FUNC},
                                        {Operands::RET,    NodeType::STATEMENT,  "return",  Priority::FUNC},
                                        {Operands::VAR,    NodeType::VARIABLE,   "x",       Priority::VAR}
                                     };

#endif // OPERATIONARRAY_H_INCLUDED
