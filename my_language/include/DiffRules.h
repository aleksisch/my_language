
#ifndef DIFFRULES_H_INCLUDED
#define DIFFRULES_H_INCLUDED

#include "CalcTree.h"

template <typename type_t>
TreeNode<type_t>* TreeNode<type_t>::DiffNode(bool is_first)
{
    assert(this);

    TreeNode<type_t>* new_node = new TreeNode<type_t>(this->number, this->type_node);

    if (this->type_node == NodeType::VARIABLE)
    {
        new_node->UpdateNode(1, NodeType::VALUE);
        return new_node;
    }

    else if (this->type_node == NodeType::VALUE)
    {
        new_node->UpdateNode(0, NodeType::VALUE);
        return new_node;
    }

    TreeNode<type_t>*& left  = this->left_child;
    TreeNode<type_t>*& right = this->right_child;

    TreeNode<type_t>*& new_left  = new_node->left_child;
    TreeNode<type_t>*& new_right = new_node->right_child;

    TreeNode<type_t>* left_diff  = left->DiffNode(false);
    TreeNode<type_t>* right_diff = right->DiffNode(false);

    switch(MyRound(this->number))
    {
        using namespace Operands;
        case (ADD):
        case (SUB):

            new_node->UpdateNode(left_diff, right_diff);
            break;

        case (MUL):

            new_node->UpdateNode(ADD, NodeType::OPERATION);

            new_node->Addleft (MUL, NodeType::OPERATION, left_diff, right->Copy());
            new_node->Addright(MUL, NodeType::OPERATION, left->Copy(), right_diff);
            break;

        case (DIV):

            new_node->Addleft(SUB, NodeType::OPERATION);
            new_node->Addright(POW, NodeType::OPERATION);

            new_left->Addleft (MUL, NodeType::OPERATION, left_diff, right->Copy());
            new_left->Addright(MUL, NodeType::OPERATION, left->Copy(), right_diff);

            new_right->Addright(2);
            new_right->Addleft(right->Copy());
            break;

        case (SIN):

            new_node ->UpdateNode(MUL, NodeType::OPERATION, right_diff, nullptr);
            new_right->UpdateNode(COS, NodeType::MATH, nullptr, right->Copy());
            break;

        case (COS):

            new_node ->UpdateNode(SUB, NodeType::OPERATION, nullptr, nullptr);
            new_right->UpdateNode(SIN, NodeType::MATH, nullptr, right_diff);
            break;

        case (TAN):

            new_node ->UpdateNode(DIV, NodeType::OPERATION, right_diff, nullptr);
            new_right->UpdateNode(POW, NodeType::MATH, this->Copy(), nullptr);

            new_right->right_child->UpdateNode(2, NodeType::VALUE);
            new_right->left_child->UpdateNode(COS, NodeType::MATH);
            break;

        case POW:
            if (left->type_node == NodeType::VARIABLE && right->type_node == NodeType::VALUE)
            {
                new_node->UpdateNode(MUL, NodeType::OPERATION);
                new_node->Addleft(right->number, NodeType::VALUE);
                new_node->Addright(POW, NodeType::OPERATION);

                new_right->Addleft (left ->number, NodeType::VARIABLE);
                new_right->Addright(right->number - 1, NodeType::VALUE);
            }

            else
            {
                TreeNode<type_t>* tmp_node = new TreeNode<type_t>(LN, FUNC, new TreeNode<type_t>(), left->Copy());

                new_node->UpdateNode(MUL, NodeType::OPERATION, nullptr, this->Copy());
                new_left->UpdateNode(ADD, NodeType::OPERATION);

                new_left->Addleft (MUL, NodeType::OPERATION, tmp_node->DiffNode(false), right->Copy());
                new_left->Addright(MUL, NodeType::OPERATION, tmp_node, right_diff);
            }
            break;

        case LN:

            new_node->UpdateNode(DIV, NodeType::OPERATION, right_diff, right->Copy());
            break;

        case SINH:

            new_node ->UpdateNode(MUL, NodeType::OPERATION, right_diff, this->Copy());
            new_right->UpdateNode(COSH, NodeType::MATH);
            break;

        case COSH:

            new_node ->UpdateNode(MUL, NodeType::OPERATION, right_diff, this->Copy());
            new_right->UpdateNode(SINH, NodeType::MATH);
            break;

        default:

            perror("Be careful, return nullptr, diff_node, UNKNOWN OPERATION");
            return nullptr;
    }

    if (is_first)
    {
        new_node = new_node->Simplify();

        #ifndef NOLATEX
        fprintf(CalcTree<type_t>::log_file, "$$$$Differencial\\quad is \\quad ");
        new_node->LogToLatex(CalcTree<type_t>::log_file);
        #endif
    }

    return new_node;
}

#endif // DIFFRULES_H_INCLUDED
