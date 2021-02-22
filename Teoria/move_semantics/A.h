// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>

class A {
	struct LinkedList {
		int x;
		double z;
		LinkedList *next;
	};

	LinkedList *data;

private:
	void freeList() {
		while ( data != nullptr ) {
			LinkedList *tmp = data;
			data = data->next;
			delete tmp;
		}
		data = nullptr;
	}

	void copyList(LinkedList* o) {
		LinkedList *last = nullptr;
		while (o != nullptr) {
			LinkedList *tmp = new LinkedList { o->x, o->z, nullptr };
			if ( data == nullptr ) {
				data = last = tmp;
			} else {
				last = last->next = tmp;
			}
			o = o->next;
		}
	}

public:
	A() {
		data = nullptr;
	}

	A(int x, double &z) {
		std::cout << "ctor. 1" << std::endl;
		data = new LinkedList { x, z, nullptr };
	}

	A(int x, double &&z) {
		std::cout << "ctor. 2" << std::endl;
		data = new LinkedList { x, z, nullptr };
	}

	A(const A &o) {
		std::cout << "copy ctor." << std::endl;
		data = nullptr;
		copyList(o.data);
	}

	A(A &&o) {
		std::cout << "move ctor." << std::endl;
		data = o.data;
		o.data = nullptr;
	}

	~A() {
		freeList();
	}

	void addData(int x, double z) {
		data = new LinkedList( { x, z, data });
	}

	A& operator=(const A &o) {
		std::cout << "copy operator=" << std::endl;
		freeList();
		copyList(o.data);
		return *this;
	}
	A& operator=(A &&o) {
		std::cout << "move operator=" << std::endl;
		freeList();
		data = o.data;
		o.data = nullptr;
		return *this;
	}

};
