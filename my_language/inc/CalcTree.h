#ifndef CalcTree_H
#define CalcTree_H

template <typename type_t>
class CalcTree
{
    public:

        CalcTree();

        ~CalcTree();

        void GraphToDot();

        void ReadGraphFile(const char* input_file = input_graph_file);

        void WriteGraphFile(TreeNode<type_t>* start_node = nullptr, const char* output_file = output_graph_file);

        TreeNode<type_t>* head_node;

        type_t GetResult(type_t variable_value);

        static FILE* log_file;

    private:

        void FillGraph(TreeNode<type_t>* current, char** ptr_on_text);

        void WriteDump(FILE* file);
};

template <typename type_t>
FILE* CalcTree<type_t>::log_file;

template <typename type_t>
CalcTree<type_t>::CalcTree()
{
    this->head_node = new TreeNode<type_t>();

    #ifndef NOLATEX
    if (CalcTree<type_t>::log_file == nullptr)
        CalcTree<type_t>::log_file = BeginLatexFile(log_filename);
    #endif
}

template <typename type_t>
CalcTree<type_t>::~CalcTree()
{
    #ifndef NOLATEX
    CloseLatexFile(CalcTree<type_t>::log_file);
    #endif

    this->head_node->FreeTree();
}


template <typename type_t>
type_t CalcTree<type_t>::GetResult(type_t variable_value)
{
    type_t res = this->head_node->GetResult(variable_value);

    #ifndef NOLATEX

    fprintf(CalcTree<type_t>::log_file, "$$$$Get \\quad result \\quad of \\quad expression, x = %.3lf: \\quad", variable_value);

    this->head_node->WriteToLatex(CalcTree<type_t>::log_file, false);

    fprintf(CalcTree<type_t>::log_file, " = %lg", res);

    #endif

    return res;
}

template <typename type_t>
int MyRound(type_t num)
{
    return static_cast<int> (std::round(num));
}


#endif // CalcTree_H
