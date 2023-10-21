#pragma once
#include <iostream>

template<class Type> class DList;

template <class type>
class Node {
private:
	type* Data;
	Node<type>* next;
	Node<type>* prev;
public:
//	Node();
	friend class DList<type>;
	Node(Node<type>* ptr = nullptr, Node<type>* ptr2 = nullptr);
	Node(Node<type> const& obj);
	void operator = (Node<type> const& obj);
	void Setnext(Node<type>* ptr);
	void Setprev(Node<type>* ptr);
	void SetData(type* Data);
	type* GetData();
	Node<type>* Getnext();
	Node<type>* Getprev();
	~Node();
};