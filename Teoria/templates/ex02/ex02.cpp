// This file is part of the course TPV2@UCM - Samir Genaim

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

using namespace std;

template<typename T>
void printdata(T data) {
	cout << "DATA: " << data << endl;
}

typedef struct {
	int x;
	int y;
} point;

ostream& operator<<(ostream& out, const point& p) {
	out << "(" << p.x << "," << p.y << ")" << endl;
	return out;
}

int main(int ac, char** av) {
	point p = {2,3};
	printdata(100);
	printdata(102.22);
	printdata("Hola!");
	printdata(p); // this give an error if << is not defined for 'point'
	return 0;
}
