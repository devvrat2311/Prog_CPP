#include <iostream>

int main() {
	int x = 10;
	int *p = &x;
	int **pp = &p;
	int ***ppp = &pp;

	std::cout << x << "\t\t" << &x << '\n';
	std::cout << p << '\t' << &p << '\n';
	std::cout << pp << '\t' << &pp << '\n';
	std::cout << ppp << '\t' << &ppp << '\n';

	return 0;
}
