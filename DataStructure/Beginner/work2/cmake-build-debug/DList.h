
#ifndef DSLAB3_DLIST_H
#define DSLAB3_DLIST_H


#include "DNode.h"

template<typename T>
class DList {

	int         size;

	DNode<T>    *head;
	DNode<T>    *tail;

	class DListIterator {

			DNode<T>    *iptr;

		public:

			friend class DList<T>;

			DListIterator(DNode<T>*t = nullptr);

			T& operator*();

			bool operator==(const DListIterator &) const;

			bool operator!=(const DListIterator &) const;

			DListIterator& operator++();

			DListIterator operator++(int);

			DListIterator& operator--();

			DListIterator operator--(int);

			bool isNull();

	};

public:

	friend class Search_Engine;

	friend class Term_Info;

	friend class HashTable<T>;

	typedef DListIterator Iterator;

	Iterator begin() const;

	Iterator end() const;

	DList();

	DList(int);

	DList(const DList<T> &);

	DList<T>& operator = (const DList<T> &);

	void insertAtStart(const T &);

	void insertAtEnd(const T &);

	void push_back(const T &);

	void print() const;

	DNode<T>* find(const T &);

	void DeleteAtEnd();

	bool remove(Iterator *);

	bool empty();

	void makeEmpty();

	void changeSize(int);

	T& operator[](int idx) const;

	~DList();

};

#endif