#include <iostream>
#include "main_proc.h"

int main(int argc, char** argv)
{
	if (argc < 3) 
	{
		printf("Please enter assembler filename and ouput binary filename");
		return 0;
	}
    make_binary_file(argv[1], argv[2]);
    disassembler("tmp_disasm.txt", argv[2]);
    cpu_struct proc;
    if (argc == 4 && strcmp(argv[3], "debug") == 0) {
    	STACK_CONSTRUCT(&(proc.cpu_stack));
    	STACK_CONSTRUCT(&(proc.func_stack));
    	CPU(&proc, argv[2]);
	}
}


