#pragma once
#include <iostream>

template <class type>
class Node {
private:
	type* Data;
	Node<type>* next;
	Node<type>* prev;
public:
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

//Parametarized constructor
template <class type>
Node<type>::Node(Node<type>* ptr, Node<type>* ptr2) {
	next = prev = nullptr;
	if (ptr != nullptr && ptr2 != nullptr) {
		next = ptr;
		prev = ptr2;
	}
	Data = new type;
};

template<typename type>
Node<type>::Node(Node<type> const& obj) {
	this->operator=(obj);
};

template<typename type>
void Node<type>::operator = (Node<type> const& obj) {
	this->next = obj.next;
	this->prev = obj.prev;
};

//Getters and Setters
template<typename type>
void Node<type>::Setnext(Node<type>* ptr) {
	this->next = ptr;
};

template<typename type>
void Node<type>::Setprev(Node<type>* ptr) {
	this->prev = ptr;
};

template<typename type>
void Node<type>::SetData(type* data) {
	this->Data = data;
};

template<typename type>
type* Node<type>::GetData() {
	return this->Data;
};

template<typename type>
Node<type>* Node<type>::Getnext() {
	return this->next;
};

template<typename type>
Node<type>* Node<type>::Getprev() {
	return this->prev;
};

//Destructor
template <class type>
Node<type>::~Node() {
	next = nullptr;
	prev = nullptr;
};