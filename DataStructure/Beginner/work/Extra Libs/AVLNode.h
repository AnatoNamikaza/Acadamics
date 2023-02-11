#pragma once
#include <iostream>

template<class type>
struct AVLNode {
	type* data;
	int height;
	AVLNode<type>* left;
	AVLNode<type>* right;

	AVLNode() {
		data = nullptr;
		left = right = nullptr;
		height = 0;
	}

	bool operator ==(AVLNode<type>* n2) {
		if (this->data == n2->data)
			return true;
		return false;
	}

	bool operator <(AVLNode<type>* n2) {
		if (this->data < n2->data)
			return true;
		return false;
	}

	bool operator >(AVLNode<type>* n2) {
		if (this->data > n2->data)
			return true;
		return false;
	}

	bool operator <=(AVLNode<type>* n2) {
		if (!(this->data > n2->data))
			return true;
		return false;
	}

	bool operator >=(AVLNode<type>* n2) {
		if (!(this->data < n2->data))
			return true;
		return false;
	}

	void Print() {
		std::cout << "\nAVLNode-Height: " << this->height << "\n";
		this->data->print();
	}
};