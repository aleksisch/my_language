#define NOLATEX
#include <iostream>
#include "MainHeader.h"

int main(int argc, char** argv)
{
    if (argc == 1) 
    {
        printf("Please enter input file\n");
        return 0;
    }

    TreeNode<double>* cur = new TreeNode<double>;

    cur = Parser<double>::CreateTree(argv[1]);

    if (cur == nullptr)
    {
        printf("Error occured\n\n");
        return 0 ;
    }

    GraphToDot(cur);

    cur->Simplify();

    GraphToDot(cur);

    if (argc == 3) 
    {
        Assembler<double>::GraphToAsm(cur, argv[2]);
    }
    else
    {
        Assembler<double>::GraphToAsm(cur);
    }

    WriteGraphFile(cur);

    delete cur;

    return 0;
}
