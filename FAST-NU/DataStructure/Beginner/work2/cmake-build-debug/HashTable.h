
#ifndef DSA1_HASHTABLE_H
#define DSA1_HASHTABLE_H


#include "DList.h"
#include "HashItem.h"
#include <assert.h>

template <class T>
class HashTable {

	int tableSize;
	int maxSize;
	DList <DList<T>> table;

	void doubleCapacity();

	unsigned int hash(const std::string &, int);

public:

	HashTable(int maxSize = 11);

	virtual void insert(const T &);

	bool deleteKey(const std::string &);

	T* get(const std::string &);

	~HashTable();

	friend class Search_Engine;

};


#endif //DSA1_HASHTABLE_H
