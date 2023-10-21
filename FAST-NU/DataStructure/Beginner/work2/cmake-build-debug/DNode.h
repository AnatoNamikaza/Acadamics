
#ifndef DSLAB3_DNODE_H
#define DSLAB3_DNODE_H

#include <iostream>

template <typename T> class DList;
template <typename T> class HashTable;

template <class T>
class DNode {

	T data;

	DNode<T> *next;
	DNode<T> *prev;

public:

	friend class DList<T>;

	friend class HashTable<T>;

	DNode();

	DNode(T value, DNode<T> *prev = 0, DNode<T> *next = 0);

	~DNode();

};


#endif
