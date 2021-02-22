// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

template<typename T>
class Item {
	T data;
public:
	Item() :
			data(T()) {
	}

	void setData(const T& nValue) {
		data = nValue;
	}

	T getData() const {
		return data;
	}

};
