// This file is part of the course TPV2@UCM - Samir Genaim


#include <iostream>
#include "Item.h"

using namespace std;

int main(int ac, char** av) {
	Item<int> item1;
	Item<double> item2;
	item1.setData(120);
	item2.setData(10.33);
	cout << item1.getData() << endl;
	cout << item2.getData() << endl;
	return 0;
}

