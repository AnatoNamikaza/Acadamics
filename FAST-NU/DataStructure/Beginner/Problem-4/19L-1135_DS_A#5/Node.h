#pragma once
#include <iostream>

template <class type>
class Node {

private:

	Node<type>* next, *prev;

public:

	type Data;

	Node() { next = nullptr, prev = nullptr; }

	Node(Node<type>* ptr, Node<type>* ptr2, type TData) {
		if (ptr)
			next = ptr;
		if (ptr2)
			prev = ptr2;
		Data = TData;
	}

	Node(Node<type> const& obj) {
		this->next = obj.Getnext(), this->prev = obj.Getprev(), this->Data = obj.GetData();
	}

	Node& operator=(Node<type> const& obj) {
		this->next = obj.Getnext(), this->prev = obj.Getprev(), this->Data = obj.GetData();
		return *this;
	}

	void SetValue(type const& d) { this->Data = new type; this->Data->DCopy(d); }

	void Setnext(Node<type>* ptr) { this->next = ptr; }

	void Setprev(Node<type>* ptr) { this->prev = ptr; }

	void SetData(type const& d) { this->Data = d; }

	type GetData() { return this->Data; }

	type& GetDataAds() { return &this->Data; }

	Node<type>* Getnext() { return this->next; }

	Node<type>* Getprev() { return this->prev; }

	void print() { this->Data->print(); }

	~Node() { next = nullptr, prev = nullptr; }
};
