    #ifndef PARSER_H
#define PARSER_H

#include "MainHeader.h"
/*!
@brief Skip spaces Enter (\n)
@return skipped lines
*/
int SkipToBrace(const char*& ptr_on_text);

/*!
@brief Search next command int string
@param command Pointer to string to search command
@param *number Pointer to number of command. Change in function
@param *type_cmd Pointer to type of command. Change in function
@param length Pointer to int variale. Put there length of readed command
@return priority command, -1 if command not found
*/
template <typename type_t>
int StrCmdToNum(const char*& command, type_t* number = nullptr, int* type_cmd = nullptr, int* length = nullptr);

/*!
@brief Get Hash of string
@param pointer on str
@return Hash number
*/
template <typename type_t>
type_t GetStrHash(const char* str);


template <typename type_t>
class Parser
{
    public:
        Parser()  {}
        ~Parser() {}

        static TreeNode<type_t>* CreateTree(const char* file = input_graph_file);

        static int read_lines;

    private:

        /*!
        @brief Check for token ";"
        @param str Pointer to current text
        @return ptr on Node
        */
        static TreeNode<type_t>* GetLine(const char*& str);

        static TreeNode<type_t>* GetG(const char*& str);

        /*!
        @brief Check for token "="
        @param str Pointer to current text
        @return ptr on Node
        */
        static TreeNode<type_t>* GetEqual(const char*& str);

        /*!
        @brief Check for token ">< >= <="
        @param str Pointer to current text
        @return ptr on Node
        */
        static TreeNode<type_t>* GetMoreLess(const char*& str);

        /*!
        @brief Check for token "+-"
        @param str Pointer to current text
        @return ptr on Node
        */
        static TreeNode<type_t>* GetE(const char*& str);

        /*!
        @brief Check for token "/^*" and
        @param str Pointer to current text
        @return ptr on Node
        */
        static TreeNode<type_t>* GetT(const char*& str);

        /*!
        @brief Check for function and "({})"
        @param str Pointer to current text
        @return ptr on Node
        */
        static TreeNode<type_t>* GetP(const char*& str);

        /*!
        @brief Check for function and "({"
        @param str Pointer to current text
        @return ptr Node or nullptr if no "({"
        */
        static TreeNode<type_t>* GetParentheses(const char*& str);

        /*!
        @brief Get Variable, call function and value
        @param str Pointer to current text
        @return ptr Node
        */
        static TreeNode<type_t>* GetLeaf(const char*& str);

        /*!
        @brief Check for this token in str
        @param str Pointer to current text
        @param priority priority of operation
        @param func call this function if operation found
        @return ptr Node
        */
        static TreeNode<type_t>* SearchToken(const char*& str, int priority, TreeNode<type_t>* res,
                                                                             TreeNode<type_t>* (*func)(const char*& str));
        /*!
        @brief Get next number
        @return number
        */
        static type_t GetN(const char*& str);
};

template <typename type_t>
int Parser<type_t>::read_lines = 1;

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::CreateTree(const char* filename)
{
    size_t size = 0;

    const char* text = ReadFile(filename, &size, "r");

    #ifndef NOLATEX
    BeginLatexFile(log_filename);
    #endif

    TreeNode<type_t>* result = GetG(text);

    #ifndef NOLATEX
    fprintf(CalcTree<type_t>::log_file, "I \\quad read: \\quad ");
    result->LogToLatex(CalcTree<type_t>::log_file);
    #endif

    WriteGraphFile(result);

    return result;
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::SearchToken (const char*& str, int priority, TreeNode<type_t>* res, TreeNode<type_t>* (*func)(const char*& str))
{
    int length = 0;

    int prior = StrCmdToNum(str, &(res->number), &(res->type_node), &length);

    res->Addright();

    if (prior == priority)
    {
        str += length;
        res->Addright(func(str));
    }

    else
        res = res->left_child;

    return res;

}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetG(const char*& str)
{
    TreeNode<type_t>* res = GetLine(str);

    Parser<type_t>::read_lines += SkipToBrace(str);

    if (*str == 0)
        return res;

    else
    {
        printf("Error occured! Not all file was readed line %d\n", Parser<type_t>::read_lines);
        return nullptr;
    }
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetLine(const char*& str)
{
    TreeNode<type_t>* res = new TreeNode<type_t>(GetEqual(str), nullptr);

    return SearchToken(str, Priority::SKIP, res, GetLine);
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetEqual(const char*& str)
{
    TreeNode<type_t>* res = new TreeNode<type_t>(GetMoreLess(str), nullptr);

    return SearchToken(str, Priority::ASSIGN, res, GetEqual);
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetMoreLess(const char*& str)
{
    TreeNode<type_t>* res = new TreeNode<type_t>(GetE(str), nullptr);

    return SearchToken(str, Priority::COMPARE, res, GetMoreLess);
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetE(const char*& str)
{

    TreeNode<type_t>* res = new TreeNode<type_t>(GetT(str), nullptr);

    return SearchToken(str, Priority::ADDSUB, res, GetE);
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetT(const char*& str)
{
    TreeNode<type_t>* res = new TreeNode<type_t>(GetP(str), nullptr);

    return SearchToken(str, Priority::MULDIV, res, GetT);
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetP(const char*& str)
{
    TreeNode<type_t>* res = GetParentheses(str);

    if (res) return res;

    res = new TreeNode<type_t>();

    int length = 0;
    int prior = StrCmdToNum(str, &(res->number), &(res->type_node), &length);

    if ((prior == Priority::MATH || prior == Priority::FUNC) && res->type_node != NodeType::VARIABLE)
    {
        str += length;

        res->Addleft(GetP(str));
        res->Addright();

        if (prior == Priority::FUNC)
            res->Addright(GetP(str));
    }

    else
    {
        free(res);
        res = GetLeaf(str);
    }

    return res;
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetLeaf(const char*& str)
{
    Parser<type_t>::read_lines += SkipToBrace(str);

    int type = 0;
    int length = 0;
    type_t num = 0;

    StrCmdToNum(str, &num, &type, &length);

    if (type == NodeType::VARIABLE)
    {
        str += length;

        TreeNode<type_t>* res = new TreeNode<type_t>(num, type);

        res->Addleft(Parser<type_t>::GetParentheses(str));      //Check is this variable function

        return res;
    }

    else
        return new TreeNode<type_t>(GetN(str), NodeType::VALUE);
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetParentheses(const char*& str)
{
    Parser<type_t>::read_lines += SkipToBrace(str);

    TreeNode<type_t>* res = nullptr;

    if (*str == '(' || *str == '{' )
    {
        res = GetLine(++str);

        Parser<type_t>::read_lines += SkipToBrace(str);

        if (*str != ')' && *str != '}')
            printf("Error occured, no ')' %s line %d", str, Parser<type_t>::read_lines);

        else
            str++;
    }

    return res;
}


template <typename type_t>
type_t Parser<type_t>::GetN(const char*& str)
{
    type_t res = 0;

    int sign = 1;

//    if (*str == '-')
//    {
//        sign = -1;
//        str++;
//    }

    Parser<type_t>::read_lines += SkipToBrace(str);
    char cur_char = (*str) - '0';

    int read_comma = 0;

    while ((cur_char >= 0 && cur_char <= 9) || cur_char == ',' - '0' || cur_char == '.' - '0')
    {
        if (cur_char == '.' - '0' || cur_char == ',' - '0') read_comma = 1;

        else if (read_comma != 0)
            res += cur_char / std::pow(10, read_comma++);

        else
        {
            res *= 10;
            res += cur_char;
        }

        Parser<type_t>::read_lines += SkipToBrace(str);
        cur_char = (*(++str)) - '0';
    }

    return res*sign;
}

int SkipToBrace(const char*& ptr_on_text)
{
    int skip_lines = 0;
    while (*ptr_on_text == '\t' ||
           *ptr_on_text == ' '  ||
           *ptr_on_text == '\n' )
    {
        if (*ptr_on_text == '\n') skip_lines++;

        ptr_on_text++;
    }
    return skip_lines;
}

template <typename type_t>
int StrCmdToNum(const char*& command, type_t* number, int* type_cmd, int* length)
{
    SkipToBrace(command);

    for (int op = 0; op < Operands::NUM; op++)

        if (strstr(command, Operation<type_t>[op].name) == command && Operation<type_t>[op].type != NodeType::VARIABLE)
        {
            if (type_cmd != nullptr) *type_cmd = Operation<type_t>[op].type;

            if (number != nullptr)   *number = Operation<type_t>[op].num;

            if (length != nullptr)    *length = strlen(Operation<type_t>[op].name);

            return Operation<type_t>[op].priority;
        }

    if ((*command >= 'a' && *command <= 'z') || (*command >= 'A' && *command <= 'Z'))
    {
        char var_name[STR_LENGTH] = {};

        if (length != nullptr) sscanf(command, "%[a-zA-Z0-9_]%n", var_name, length);

        else sscanf(command, "%s", var_name);

        if (type_cmd != nullptr) *type_cmd = NodeType::VARIABLE;

        if (number != nullptr)   *number = GetStrHash<type_t>(var_name);

        return Priority::VAR;
    }

    return -1;
}

template <typename type_t>
type_t GetStrHash(const char* str)
{
    type_t hash = 1;

    for (int i = 0; i < STR_LENGTH; i++)
        hash = (((int) hash) + (23 * (str[i] + 22) * (i + 50) + str[i])) % MAX_HASH;

    return hash;
}


#endif // PARSER_H
