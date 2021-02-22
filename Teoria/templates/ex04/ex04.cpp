// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
T add(T n1, T n2) {
	T result;
	result = n1 + n2;

	return result;
}

int main(int ac, char** av) {
	cout << add(10, 11) << endl;
	cout << add(4.3, 3.14) << endl;
	// cout << add(1,1.14) << endl;
	return 0;
}
