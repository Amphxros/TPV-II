// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>
#include <iostream>

template<typename T>
class MyVector {
	T **elem_;
	std::size_t size_;
	std::size_t capacity_;
public:
	MyVector() {
		size_ = 0;
		capacity_ = 10;
		elem_ = new T*[capacity_]();
	}

	virtual ~MyVector() {
		for (auto i = 0u; i < size_; i++) {
			delete elem_[i];
		}
		delete[] elem_;
	}

	int size() {
		return size_;
	}

	void push_back(const T &x) {
		if (size_ + 1 > capacity_) {
			resize();
		}
		elem_[size_++] = new T(x);
	}

	T& operator[](std::size_t i) {
		assert(i < size_);
		return *elem_[i];
	}

	const T& operator[](std::size_t i) const {
		assert(i < size_);
		return *elem_[i];
	}

private:

	void resize() {
		capacity_ += 10;
		T **aux = new T*[capacity_]();
		for (auto i = 0u; i < size_; i++) {
			aux[i] = elem_[i];
		}
		delete[] elem_;
		elem_ = aux;
	}

};

