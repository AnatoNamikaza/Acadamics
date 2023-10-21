#pragma once
#include <iostream>
#include "Node.h"

template<class type>
class DList {
private:
	Node<type>* head;
	Node<type>* tail;
public:
//	DList();
	DList(Node<type>* ptr = nullptr, Node<type>* ptr2 = nullptr);
//	DList(DList<type> const& obj);
//	void operator = (DList<type> const& obj);
	void insertAtEnd();
	Node<type>* GetHead();
	Node<type>* Gettail();
	void deleteAtEnd();
	void reverse();
	~DList();
};