// This file is part of the course TPV2@UCM - Samir Genaim


#include <iostream>
#include "Pair.h"

using namespace std;


int main(int ac, char** av) {
	Pair<int, int> x(1, 2);
	Pair<int, int> y(x);
	Pair<double, string> z(1.2, "Hola");

	if (x == y) {
		cout << "They are equal!" << endl;
	}
	cout << x.getFirst() << " " << x.getSecond() << endl;
	cout << y.getFirst() << " " << y.getSecond() << endl;
	cout << z.getFirst() << " " << z.getSecond() << endl;
	return 0;
}
