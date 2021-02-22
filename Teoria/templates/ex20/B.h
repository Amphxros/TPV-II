// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "A.h"

/*
 *
 */
class B: public A<int> {
public:
	B() {
	}
	virtual ~B() {
	}
	virtual void foo(int x) {
		// ...
	}
	virtual int moo(int x) {
		// ...
		return 0;
	}

};

