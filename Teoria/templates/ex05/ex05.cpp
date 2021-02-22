// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
double ave(const T tArray[], int nElements) {
	T tSum = T(); // tSum = 0

	for (int nIndex = 0; nIndex < nElements; ++nIndex) {
		tSum += tArray[nIndex];
	}

	// Whatever type of T is, convert to double
	return double(tSum) / nElements;
}


int main(int ac, char** av) {
	int IntArray[5] = { 100, 200, 400, 500, 1000 };
	float FloatArray[3] = { 1.55f, 5.44f, 12.36f };

	cout << ave(IntArray, 5) << endl;
	cout << ave(FloatArray, 3) << endl;

	return 0;
}
