// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>

class A {
	int n_;
	int m_;
public:
	A() {
		n_ = m_ = 0;
	}

	A(int n, int m) {
		n_ = n;
		m_ = m;
	}

	A(const A &other) {
		n_ = other.n_;
		m_ = other.m_;
	}

	virtual ~A() {
	}

	int getN() {
		return n_;
	}
	int getM() {
		return m_;
	}


};

