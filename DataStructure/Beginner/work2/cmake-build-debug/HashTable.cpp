
#include "HashTable.h"

//Function that creates a temporary HashTable and copies original HashTable in it, then deletes the table of original
// HashTable and copies the table of temp HashTable in the original HashTable's table and double the capacity.
template <class T>
void HashTable<T>::doubleCapacity() {
	HashTable<T> temp(maxSize * 2);

	//Copying original table in temp's table.
	for ( typename DList < DList<T>>::Iterator itr1 = table.begin(); itr1 != table.end(); itr1++ )
		for ( typename DList<T>::Iterator itr2 = (*itr1).begin(); itr2 != (*itr1).end(); itr2++ )
			temp.insert(*itr2);

	maxSize *= 2;

	table.makeEmpty();              //Delete all elements in the table.
	table.changeSize(maxSize);      //Change capacity of table

	for ( int i = 0; i < maxSize; i++ )     //copy temp table in table
		if ( temp.table[i].head )
			table[i] = temp.table[i];
}

//Function that takes a string and tableSize and returns the hash.
template <class T>
unsigned int HashTable<T>::hash(const std::string &key, int tableSize) {
	unsigned int hashVal = 0;
	for ( char ch : key )
		hashVal = 37 * hashVal + ch;
	return hashVal % tableSize;
}

template <class T>
HashTable<T>::HashTable(const int maxSize) : table(maxSize) {
	if ( maxSize < 1 )
		assert(maxSize < 1);

	this->maxSize = maxSize;
	tableSize = 0;
}

template <class T>
void HashTable<T>::insert(const T &value) {
	if ( static_cast<float>(tableSize) / maxSize >= 2.00 )  //if Load Factor >= 2, double the capacity.
		doubleCapacity();

	//insert value at the index returned by the hash function.
	table[hash(value.keyTerm, maxSize)].push_back(value);
	tableSize++;

//	typename DList<T>::Iterator itr = table[hash(value.keyTerm, maxSize)].begin();
	int Hkey = 0;
	typename DList<T>::Iterator itr = table[Hkey].begin();
	*(itr);
}

template <class T>
bool HashTable<T>::deleteKey(const std::string &key) {
	int index = hash(key, tableSize);

	typename DList<T>::Iterator itr = table[index].begin();
	for ( int i = 0; i < table[index].size; i++, itr++ ){
		if ( table[index][i].keyTerm == key ){
			table[index][i].keyTerm.clear();        //keyTerm = ""
			table[index].remove(itr);               //remove the node
			tableSize--;
			return true;
		}
	}

	return false;
}

template <class T>
T* HashTable<T>::get(const std::string &key) {
	int index = hash(key, maxSize);

	for ( int i = 0; i < table[index].size; i++ )
		if ( table[index][i].keyTerm == key )
			return &table[index][i];

	return nullptr;
}

template <class T>
HashTable<T>::~HashTable() {
	maxSize = 0;
	tableSize = 0;
}