// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
void twiceit(T& tData) {
	tData *= 2;
}

template<typename T>
T& getMax(T& t1, T& t2) {
	if (t1 > t2)
		return t1;
	else
		return t2;
}

template<typename T>
void PrintTwice(const T& data) {
	cout << "Twice: " << data * 2 << endl;
}

int main(int ac, char** av) {
	int x = 50;
	int y = 64;

	twiceit(x);
	getMax(x, y) = 0;

	cout << x << " " << y << endl;

	return 0;
}
