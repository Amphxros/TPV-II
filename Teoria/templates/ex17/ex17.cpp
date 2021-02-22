// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

#include "MyVector.h"

using namespace std;


int main() {
	MyVector<int> v;

	v.push_back(11);
	v.push_back(15);
	v.push_back(17);
	cout << v.size() << endl;

	cout << v[0] << " " << v[1] << " " << v[2] << endl;
	v[1] = 4;
	cout << v[0] << " " << v[1] << " " << v[2] << endl;
}
