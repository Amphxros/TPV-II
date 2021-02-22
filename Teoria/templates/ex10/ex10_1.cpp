// This file is part of the course TPV2@UCM - Samir Genaim


#include <iostream>

using namespace std;

template<typename T>
void printSize() {
	cout << "Size of this type:" << sizeof(T) << endl;
}

int main(int ac, char** av) {
	printSize<float>();
	printSize<int>();
	printSize<double>();
	return 0;
}
