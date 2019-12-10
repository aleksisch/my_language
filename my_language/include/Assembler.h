#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "MainHeader.h"

template <typename type_t>
struct VarNumber
{
    int number = 0;
    int hash_str = 0;
    TreeNode<type_t>* ptr_func = 0;
};

template <typename type_t>
class Assembler
{
    public:

        /*!
        @brief Init Write all Tree to assembler file asm.txt
        @param cur_node Start write drom this node
        */
        static int GraphToAsm(TreeNode<type_t>* cur_node, const char* filename = assembler_file);

    private:

        /*!
        @brief Call other function to write graph
        */
        static int WriteGraph(TreeNode<type_t>* cur_node);

        /*!
        @brief Write while to assembler file
        */
        static int WhileToAsm (TreeNode<type_t>* cur_node);

        /*!
        @brief Write if to assembler file
        */
        static int IfToAsm(TreeNode<type_t>* cur_node);

        /*!
        @brief Write assign to assembler file
        */
        static int AssignToAsm(TreeNode<type_t>* cur_node);

        /*!
        @brief Write expression to assembler file
        */
        static int ExprToAsm(TreeNode<type_t>* cur_node);

        /*!
        @brief Get variable number in array (not value)
        */
        static int GetVarNumber(TreeNode<type_t>* cur_node, TreeNode<type_t>** ptr_on_func = nullptr);

        /*!
        @brief Add function to variable array if needed
        */
        static void AddFunc(TreeNode<type_t>*& cur_node);

        /*!
        @brief Add variable to variable array if needed
        */
        static void VarToAsm(TreeNode<type_t>* cur_node);

        /*!
        @brief Write all condition to file "< > <= >= == "
        */
        static int WriteCond(TreeNode<type_t>* cur_node);

        /*!
        @brief Write function to file
        */
        static int FuncToAsm(TreeNode<type_t>* cur_node);

        /*!
        @brief Push All variable to stac    k.
        @brief Use it when call some function, to create local variable
        */
        static void PushAllVar();

        /*!
        @brief Pop all variable from stack.
        @brief Use it when return from function, to restore variable
        */
        static void PopAllVar();

        static void PushVariable(int num);

        static void PopVariable(int num);

        static FILE* output_file;

        static VarNumber<type_t>* variable;

        static int cur_size;

        static int last_push;

};

template <typename type_t>
int Assembler<type_t>::last_push = 0;

template <typename type_t>
int Assembler<type_t>::cur_size = 0;

template <typename type_t>
VarNumber<type_t>* Assembler<type_t>::variable = new VarNumber<type_t>[MAX_VARIABLE];

template <typename type_t>
FILE* Assembler<type_t>::output_file = nullptr;

template <typename type_t>
int Assembler<type_t>::GraphToAsm(TreeNode<type_t>* cur_node, const char* filename)
{
    output_file = fopen(filename, "w");

    WriteGraph(cur_node);
    fclose (output_file);

    return 0;
}

template <typename type_t>
int Assembler<type_t>::WriteGraph(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    switch (cur_node->type_node)
    {
        using namespace NodeType;

        case QUOTE:
            WriteGraph(cur_node->left_child);
            WriteGraph(cur_node->right_child);
            return 0;

        case VARIABLE:
            ExprToAsm(cur_node->left_child);
            VarToAsm(cur_node);
            return 0;

        case FUNCTION:
            FuncToAsm(cur_node);
            return 0;
    }

    switch (MyRound(cur_node->number))
    {
        using namespace Operands;

        case IF:
            IfToAsm(cur_node);
            return 0;

        case ASSIGN:
            AssignToAsm(cur_node);
            return 0;

        case WHILE:
            WhileToAsm(cur_node);
            return 0;

        case PRINTF:
            ExprToAsm(cur_node->left_child);
            fprintf(output_file, "OUT\n");
            return 0;

        case SCANF:
            fprintf(output_file, "IN \n");
            PopVariable(GetVarNumber(cur_node->left_child));
            return 0;

        case RET:
            ExprToAsm(cur_node->left_child);
            fprintf(output_file, "RET\n");
            return 0;

        case 0:
            return 0;

        default:
            printf("UNKNOWN_OPERATTON number %d\n", cur_node->type_node);
            return NodeType::UNKNOWN;
    }
}

template <typename type_t>
void Assembler<type_t>::PushVariable(int num)
{
    fprintf(output_file, "PUSH [%d]\n", num);
}

template <typename type_t>
void Assembler<type_t>::PopVariable(int num)
{
    fprintf(output_file, "POP [%d]\n", num);
}

template <typename type_t>
void Assembler<type_t>::PushAllVar()
{
    for (int i = MAX_VARIABLE - 2; i >= 0; i--)
        PushVariable(i);
}

template <typename type_t>
void Assembler<type_t>::PopAllVar()
{
    PopVariable(MAX_VARIABLE - 1);  //To Save return value

    for (int i = 0; i < MAX_VARIABLE - 1; i++)
        PopVariable(i);

    PushVariable(MAX_VARIABLE - 1);
}


template <typename type_t>
int Assembler<type_t>::GetVarNumber(TreeNode<type_t>* cur_node, TreeNode<type_t>** ptr_on_func)
{
    assert(cur_node);

    VarNumber<type_t>*& var = Assembler<type_t>::variable;

    int int_num = (int) cur_node->number;

    for (int i = 0; i < Assembler<type_t>::cur_size; i++)
        if (int_num == variable[i].hash_str || int_num + MAX_VARIABLE == var[i].hash_str)
        {
            if (ptr_on_func != nullptr)
                *ptr_on_func = var[i].ptr_func;

            return i;
        }

    int var_num = (Assembler<type_t>::cur_size)++;

    var[var_num].hash_str = int_num;

    if (ptr_on_func != nullptr)
        var[var_num].ptr_func = *ptr_on_func;

    else
        var[var_num].ptr_func = nullptr;

    return var_num;
}

template <typename type_t>
void Assembler<type_t>::AddFunc(TreeNode<type_t>*& cur_node)
{
    assert(cur_node);

    GetVarNumber(cur_node, &cur_node);
    cur_node->left_child->number += MAX_VARIABLE; //Make local number variable
    GetVarNumber(cur_node->left_child);
}

template <typename type_t>
void Assembler<type_t>::VarToAsm(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    TreeNode<type_t>* ptr_on_func = nullptr;

    int num = GetVarNumber(cur_node, &ptr_on_func);

    if (ptr_on_func != nullptr)
    {
        PopVariable(MAX_VARIABLE - 1);
        PushAllVar();

        PushVariable(MAX_VARIABLE - 1);
        PopVariable(num + 1);

        fprintf(output_file, "CALL func%p\n", ptr_on_func);
        PopAllVar();
    }

    else
        PushVariable(num);
}

template <typename type_t>
int Assembler<type_t>::AssignToAsm(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    if (cur_node->type_node != NodeType::STATEMENT || MyRound(cur_node->number) != Operands::ASSIGN)
        return -1;

    ExprToAsm(cur_node->right_child);

    PopVariable(GetVarNumber(cur_node->left_child));

    return 0;
}

template <typename type_t>
int Assembler<type_t>::ExprToAsm(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    if (cur_node->left_child != nullptr)
        ExprToAsm(cur_node->left_child);

    if (cur_node->right_child != nullptr)
        ExprToAsm(cur_node->right_child);

    switch (cur_node->type_node)
    {
        case NodeType::VARIABLE:
            VarToAsm(cur_node);
            break;

        case NodeType::VALUE:
            fprintf(output_file, "PUSH %s\n", NodeDataToStr(cur_node));
            break;

        case NodeType::OPERATION:
            fprintf(output_file, "%s\n", FuncToStr(cur_node));
            break;

        default:
            fprintf(output_file, "UNKNOWN number %s type %d\n", NodeDataToStr(cur_node), cur_node->type_node);
            return NodeType::UNKNOWN;
    }

    return 0;
}

template <typename type_t>
int Assembler<type_t>::WriteCond(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    switch (MyRound(cur_node->left_child->number))
    {
        using namespace Operands;
        case EQUAL:
            fprintf(output_file, "JNE");
            break;

        case MORE:
            fprintf(output_file, "JLE");
            break;

        case MOREEQ:
            fprintf(output_file, "JL");
            break;

        case LESS:
            fprintf(output_file, "JME");
            break;

        case LESSEQ:
            fprintf(output_file, "JM");
            break;

        case NEQUAL:
            fprintf(output_file, "JE");
            break;

        default:
            perror("Bad condition");
            return NodeType::UNKNOWN;
    }

    fprintf(output_file, " l%p\n", cur_node);

    return 0;
}
template <typename type_t>
int Assembler<type_t>::IfToAsm(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    if (cur_node->type_node != NodeType::STATEMENT || MyRound(cur_node->number) != Operands::IF)
    {
        perror("IfToAsm bad node");
        return -1;
    }

    ExprToAsm(cur_node->left_child->left_child);
    ExprToAsm(cur_node->left_child->right_child);

    WriteCond(cur_node);

    WriteGraph(cur_node->right_child);

    fprintf(output_file, ":l%p\n", cur_node);

    return 0;
}

template <typename type_t>
int Assembler<type_t>::WhileToAsm(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    if (cur_node->type_node != NodeType::STATEMENT || MyRound(cur_node->number) != Operands::WHILE)
    {
        perror("WhileToAsm bad node");
        return -1;
    }

    fprintf(output_file, ":st%p\n", cur_node);

    ExprToAsm(cur_node->left_child->left_child);
    ExprToAsm(cur_node->left_child->right_child);

    WriteCond(cur_node);

    WriteGraph(cur_node->right_child);

    fprintf(output_file, "JMP st%p\n:l%p\n", cur_node, cur_node);

    return 0;
}

template <typename type_t>
int Assembler<type_t>::FuncToAsm(TreeNode<type_t>* cur_node)
{
    assert(cur_node);

    if (cur_node->type_node != NodeType::FUNCTION)
        return -1;

    fprintf(output_file, "JMP endfunc%p\n", cur_node->left_child);

    AddFunc(cur_node->left_child);

    fprintf(output_file, ":func%p\n", cur_node->left_child);

    WriteGraph(cur_node->right_child);

    fprintf(output_file, "PUSH 6666\nRET\n");

    fprintf(output_file, ":endfunc%p\n", cur_node->left_child);

    return 0;
}

#endif // ASSEMBLER_H
