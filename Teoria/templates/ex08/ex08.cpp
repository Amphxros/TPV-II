// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T1, typename T2>
void printNumbers(const T1& t1Data, const T2& t2Data) {
	cout << "First value:" << t1Data << endl;
	cout << "Second value:" << t2Data << endl;
}

int main(int ac, char** av) {
	int x = 1;
	double y = 2.3;

	printNumbers<double, double>(x, x);
	printNumbers<double, double>(x, y);
	printNumbers<double, double>(y, x);

	return 0;
}
