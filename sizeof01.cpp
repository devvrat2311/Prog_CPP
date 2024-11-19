#include <iostream>
#include <cstdlib>
#include <cstdio>

#define NEWLINE std::cout<<std::endl
#define NAMELENGTH 20

class SomeClass {
private:
	int number;
	char name[NAMELENGTH];
	float weight;
public:
	SomeClass();
	void displayInfo();
	int getLineCustom(void);
};

int main()
{
	SomeClass myself;
	std::cout << "Enter Name: ";
	std::cout << myself.getLineCustom();
	NEWLINE;
	// system("clear");
	std::cout << "the size of a class object is: " << sizeof(SomeClass) << std::endl;
	myself.displayInfo();
}

SomeClass::SomeClass() : number(0), name(""), weight(0.0f) {
	std::cout << "Enter serial number: ";
	std::cin >> this->number;
	NEWLINE;
	std::cout << "Enter weight: ";
	std::cin >> this->weight;
	NEWLINE;

	std::cin.ignore();
}

void SomeClass::displayInfo() {
	std::cout << "number: " << this->number << std::endl;
	std::cout << "name: " << this->name << std::endl;
	std::cout << "weight: " << this->weight << std::endl;
	NEWLINE;
    std::cout << "number is " << sizeof number << " bytes wide\n";
	std::cout << "name is " << sizeof name << " bytes wide\n";
	std::cout << "weight is " << sizeof weight<< " bytes wide\n";
}

int SomeClass::getLineCustom() {
	int c, i;

	for(i = 0; i < NAMELENGTH - 1 && (c = getchar()) != EOF  && c != '\n'; ++i) {
		this->name[i] = c;
	}

	// if(c == '\n') {
	// 	this->name[i++] = c;
	// }

	this->name[i] = '\0';

	return i;
}
