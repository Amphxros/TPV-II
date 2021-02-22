// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
T sumOfNumbers(int a, int b) {
	T t = T(); // Call default CTOR for T

	t = T(a) + b;

	return t;
}

int main(int ac, char** av) {
	double sum;
	sum = sumOfNumbers<double>(120, 200);
	cout << sum << endl;
	return 0;
}
