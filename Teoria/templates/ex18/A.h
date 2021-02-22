// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>

class A {
	int n_;
public:
	A() {
		n_ = 0;
	}

	A(int n) {
		n_ = n;
	}

	A(const A &other) {
		n_ = other.n_;
	}

	virtual ~A() {
	}

	int getN() {
		return n_;
	}

};

