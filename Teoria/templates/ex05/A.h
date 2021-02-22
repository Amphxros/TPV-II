// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

class A {
	int x;
public:
	A() :
			x(0) {
	}
	A(int a) :
			x(a) {
	}

	A& operator+=(const A &other) {
		x += other.x;
		return *this;
	}

	operator double() {
		return x;
	}
};
