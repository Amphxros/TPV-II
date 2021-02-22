// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "A.h"

/*
 *
 */
template<typename T>
class C: public A<T> {
public:
	C() {
	}
	virtual ~C() {
	}
	virtual void foo(T x) {
		// ...
	}
	virtual T moo(T x) {
		// ...
		return x;
	}
};

