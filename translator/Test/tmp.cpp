#include <iostream>

int main() {
	unsigned char b[] =  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f};
	double a = *((double*) b);
	std::cout << a;
}