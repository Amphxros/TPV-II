// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

template<typename T1, typename T2>
class Pair {
	T1 first_;
	T2 second_;

public:
	Pair() :
			first_(T1()), second_(T2()) {
	}

	Pair(T1 a, T2 b) :
			first_(a), second_(b) {
	}

	Pair(Pair<T1, T2> &other) :
			first_(other.first_), second_(other.second_) {
	}

	T1& getFirst() {
		return first_;
	}

	T2& getSecond() {
		return second_;
	}

	virtual ~Pair() {
	}

	bool operator==(const Pair<T1, T2> &other) const {
		return first_ == other.first_ && second_ == other.second_;
	}

};
