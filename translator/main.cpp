#include <iostream>
#include <fstream>
#include "Compiler.h"

int main(int argc, char** argv ) {
	if (argc == 3) {
		Compiler(argv[1], argv[2]);
	} else {
		std::cout << "Expected input filename and result filename as a input";
	}
    return 0;
}
