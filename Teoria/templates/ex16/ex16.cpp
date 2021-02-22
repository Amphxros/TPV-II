// This file is part of the course TPV2@UCM - Samir Genaim


#include <iostream>
#include "MyArray.h"

using namespace std;


int main(int ac, char** av) {
	MyArray<int, 10> x;
	MyArray<string, 5> y;
	MyArray<float> z;

	x[1] = 10;
	y[1] = "Hola!";
	z[1] = 12.34f;

	cout << x[1] << endl;
	cout << y[1] << endl;
	cout << z[1] << endl;


	return 0;
}
