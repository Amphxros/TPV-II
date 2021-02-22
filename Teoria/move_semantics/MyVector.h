// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>
#include <iostream>

template<typename T>
class MyVector {
	T **elem_;
	int size_;
	int capacity_;
public:
	MyVector() {
		size_ = 0;
		capacity_ = 10;
		elem_ = new T*[capacity_]();
	}

	virtual ~MyVector() {
		for (int i = 0; i < size_; i++) {
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

	void push_back(T&& x) {
		if (size_ + 1 > capacity_) {
			resize();
		}
		elem_[size_++] = new T(std::move(x));
	}

	template<typename ...Ts>
	void emplace_back(Ts&& ...args) {
		if (size_ + 1 > capacity_) {
			resize();
		}
		elem_[size_++] = new T(std::forward<Ts>(args)...);
	}

	T& operator[](int i) {
		assert(i < size_);
		return *elem_[i];
	}

	const T& operator[](int i) const {
		assert(i < size_);
		return *elem_[i];
	}

private:

	void resize() {
		capacity_ += 10;
		T **aux = new T*[capacity_]();
		for (int i = 0; i < size_; i++) {
			aux[i] = elem_[i];
		}
		delete[] elem_;
		elem_ = aux;
	}

};

