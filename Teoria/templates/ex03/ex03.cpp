// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
T twice(T data) {
	return 2 * data;
}

int main(int ac, char** av) {
	cout << twice(10) << endl;
	cout << twice(3.14) << endl;
	cout << twice(twice(55)) << endl;
	return 0;
}
