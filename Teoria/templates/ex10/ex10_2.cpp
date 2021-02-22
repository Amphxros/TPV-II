// This file is part of the course TPV2@UCM - Samir Genaim


#include <iostream>

using namespace std;

class A {};
class B {};

template<typename T>
T* create() {
	return new T();
}

int main(int ac, char** av) {
	A* a = create<A>();
	B* b = create<B>();
	return 0;
}
