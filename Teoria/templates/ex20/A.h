// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

/*
 *
 */
template<typename T>
class A {
public:
	A() {
	}
	virtual ~A() {
	}
	virtual void foo(T x) = 0;
	virtual T moo(T x) = 0;
};

