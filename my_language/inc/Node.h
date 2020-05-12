#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED


/*!
@brief Run operation
@param first first variable
@param second second variable
@param operands Number of operation
@return result of operation
*/
template <typename type_t>
type_t ExecuteOperation(type_t first, type_t second, type_t operands);


template <typename type_t>
class TreeNode
{
    public:

        TreeNode<type_t>(const type_t num = 0, int type_node_t = NodeType::UNKNOWN, TreeNode<type_t>* left_t = nullptr, TreeNode<type_t>* right_t = nullptr) :
            number(num),
            type_node(type_node_t),
            left_child(left_t),
            right_child(right_t)
        {}

        TreeNode<type_t>(TreeNode<type_t>* left_t, TreeNode<type_t>* right_t = nullptr) :
            left_child(left_t),
            right_child(right_t)
        {}

        type_t GetResult(type_t variable_value);

        void WriteDump(FILE* file);

        void FreeTree();

        TreeNode<type_t>* Copy();

        TreeNode<type_t>* DiffNode(bool is_first = true);

        void UpdateNode(type_t number, int type, TreeNode<type_t>* left, TreeNode<type_t>* right);
        void UpdateNode(type_t number, int type);

        void UpdateNode(TreeNode<type_t>* left, TreeNode<type_t>* right);

        void Addright(TreeNode<type_t>* to_add);

        void Addright(type_t new_elem = 0, int type = NodeType::VALUE, TreeNode<type_t>* left = nullptr, TreeNode<type_t>* right = nullptr);

        void Addleft (TreeNode<type_t>* to_add);

        void Addleft (type_t new_elem = 0, int type = NodeType::VALUE, TreeNode<type_t>* left = nullptr, TreeNode<type_t>* right = nullptr);

        void WriteGraph(FILE* output_file, bool is_first = false);

        void NodeToFile(FILE* output_file);

        void WriteToLatex(FILE* output_file = nullptr, bool is_first = true, const char* out_filename = output_latex);

        type_t number;

        int type_node;

        TreeNode<type_t>* left_child;

        TreeNode<type_t>* right_child;

        TreeNode<type_t>* Simplify();

        void LogToLatex(FILE* output_file, const char* filename = output_latex);

    private:

        void NodeToTex(FILE* output_file);

};

template <typename type_t>
void WriteGraphFile(TreeNode<type_t>* start_node = nullptr, const char* output_file = output_graph_file);


template <typename type_t>
void GraphToDot(TreeNode<type_t>* start_node, const char* output_file = output_graphviz);

#endif // NODE_H_INCLUDED
