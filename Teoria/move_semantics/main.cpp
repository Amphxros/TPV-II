// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <vector>

#include "A.h"
#include "MyVector.h"
using namespace std;


void f1() {
	MyVector<A> v;

	cout << "--- A x(1,2.3)" << endl;
	A x(1,2.3);

	cout << "--- v.push_back(A(1,2.3))" << endl;
	v.push_back(A(1,2.3));
	cout << "--- v.push_back(x)" << endl;
	v.push_back(x);
	cout << "--- v.push_back(std::move(x))" << endl;
	v.push_back(std::move(x));
	cout << "--- v.emplace_back(1,2.3)" << endl;
	v.emplace_back(1,2.3);
}

void f2() {
	cout << "******************" << endl;
	A x;
	A y;
	A z;

	x = A(1,2.4);
	y = x;
	z = std::move(y);

}

int main() {
	f1();
//	f2();
}

