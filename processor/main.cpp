#include <iostream>
#include "main_proc.h"

int main()
{
    make_binary_file("asm.txt");
    disassembler();
    cpu_struct proc;
    STACK_CONSTRUCT(&(proc.cpu_stack));
    STACK_CONSTRUCT(&(proc.func_stack));
    CPU(&proc);
}


