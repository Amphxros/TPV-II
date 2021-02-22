// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
T getMax(T t1, T t2) {
	if (t1 > t2)
		return t1;
	return t2;
}

int main(int ac, char** av) {
	//  cout << max(1,2.2) << endl; // ERROR
	cout << getMax<double>(2.2, 1) << endl;
	return 0;
}
