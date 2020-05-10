#include <iostream>	
int main() {
	unsigned char arr[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7f, 0x40};
	double t = *((double*) arr);
	std::cout << t << "\n";
}