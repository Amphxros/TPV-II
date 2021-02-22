// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

class Item {
	int data;
public:
	Item() :
			data(0) {
	}

	void setData(int nValue) {
		data = nValue;
	}

	int getData() const {
		return data;
	}

};
