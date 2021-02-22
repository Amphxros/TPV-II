// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

template<typename T, int SIZE=10>
class MyArray {
	T elem[SIZE];
public:
	MyArray() {
		for (int i = 0; i < SIZE; i++)
			elem[i] = T();
	}

	T operator[](int i) const {
		return elem[i];
	}

	const T& operator[](int i) const {
		return elem[i];
	}

	T& operator[](int i) {
		return elem[i];
	}

};
