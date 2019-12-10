#define NOLATEX
#include <iostream>
#include "include/MainHeader.h"

int main()
{
    TreeNode<double>* cur = new TreeNode<double>;

    cur = Parser<double>::CreateTree();

    if (cur == nullptr)
    {
        printf("Error occured\n\n");
        return 0 ;
    }

    GraphToDot(cur);

    cur->Simplify();

    GraphToDot(cur);

    Assembler<double>::GraphToAsm(cur);

    WriteGraphFile(cur);

    delete cur;

    return 0;
}
