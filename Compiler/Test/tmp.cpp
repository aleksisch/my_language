#include <iostream>

int main() {
	unsigned char b[] =  {0x7f, 0xff, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00};
	double a = *((double*) b);
	std::cout << a;
}