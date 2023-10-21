
#include "DNode.h"

template<class T>
DNode<T>::DNode() { 
	next = nullptr; 
}

template<class T>
DNode<T>::DNode(T value, DNode<T> *prev, DNode<T> *next) {
	data = value;
	this->next = next;
	this->prev = prev;
}

template<class T>
DNode<T>::~DNode() {
	next = nullptr;
	prev = nullptr;
}