// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
void printNumbers(T array[], int array_size, T filter = T()) {
	for (int nIndex = 0; nIndex < array_size; ++nIndex) {
		if (array[nIndex] != filter) // Print if not filtered
			cout << array[nIndex] << endl;
	}
}

int main(int ac, char** av) {
	int a[10] = { 1, 2, 0, 3, 4, 2, 5, 6, 0, 7 };
	printNumbers(a, 10);
	cout << "-----" << endl;
	printNumbers(a, 10, 2);
	return 0;
}
