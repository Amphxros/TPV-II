// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include "Item.h"

using namespace std;


int main(int ac, char** av) {
	Item item1;
	item1.setData(120);
	cout << item1.getData() << endl;
	return 0;
}

