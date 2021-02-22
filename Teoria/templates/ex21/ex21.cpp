// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <vector>

#include "MyVector.h"

#include "A.h"

using namespace std;


int main() {
	MyVector<A> v;

	A x(1,2);
	v.push_back(x);

	v.emplace_back(1,2);
}
