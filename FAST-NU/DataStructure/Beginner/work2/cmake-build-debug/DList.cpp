
#include "DList.h"

//Parameterized constructor of DListIterator
template<class T>
DList<T>::DListIterator::DListIterator(DNode<T> *t) {
	iptr = t;
};

//Function for accessing the data in the node that the Iterator is pointing to.
template<class T>
T & DList<T>::DListIterator::operator*(){
	return iptr->data;
}

//For checking equality of 2 iterators
template<class T>
bool DList<T>::DListIterator::operator==(const DListIterator & l) const {
	return iptr == l.iptr;
}

//For checking inequality of 2 iterators
template<class T>
bool DList<T>::DListIterator::operator!=(const DListIterator & l) const {
	return iptr != l.iptr;
}

//For pre-incrementing an iterator. Iterator starts pointing to the next node in list after increment.
template<class T>
typename DList<T>::Iterator& DList<T>::DListIterator::operator++() {
	if (iptr)
		iptr = iptr->next;

	return (*this);
}

//For post-incrementing an iterator. Iterator starts pointing to the next node in list after increment.
template<class T>
typename DList<T>::Iterator DList<T>::DListIterator::operator++(int i) {
	typename DList<T>::Iterator old = *this;
	++(*this);
	return old;
}

//For pre-decrementing an iterator. Iterator starts pointing to the previous node in list after decrement.
template<class T>
typename DList<T>::Iterator& DList<T>::DListIterator::operator--() {
	if (iptr)
		iptr = iptr->prev;

	return (*this);
}

//For post-decrementing an iterator. Iterator starts pointing to the previous node in list after decrement.
template<class T>
typename DList<T>::Iterator DList<T>::DListIterator::operator--(int i) {
	typename DList<T>::Iterator old = *this;
	--(*this);
	return old;
}

//Function for checking if iptr is null or not.
template<class T>
bool DList<T>::DListIterator::isNull() {
	return iptr->next == nullptr;
}

//Function that returns iterator pointing to the first node in the list.
template<class T>
typename DList<T>::Iterator DList<T>::begin() const {
	return head->next;
}

//Function that returns iterator pointing to the last node(dummy tail in this case) in the list.
template<class T>
typename DList<T>::Iterator DList<T>::end() const {
	return tail;
}

//Default constructor of DList(Doubly Linked List).
template<class T>
DList<T>::DList() {
	head = new DNode<T>();
	head->prev = nullptr;
	tail = new DNode<T>();
	tail->prev = head;
	tail->next = nullptr;
	head->next = tail;
	size = 0;
}

//Default constructor of DList(Doubly Linked List).
template<class T>
DList<T>::DList(int capacity) {
	head = new DNode<T>();
	head->prev = nullptr;
	tail = new DNode<T>();
	tail->prev = head;
	tail->next = nullptr;
	head->next = tail;
	size = 0;

	for ( int i = 0; i < capacity; i++ )
		insertAtEnd(T());
}

//Copy constructor of DList.
template<class T>
DList<T>::DList(const DList<T> &list){

	head = new DNode<T>();
	head->prev = nullptr;
	tail = new DNode<T>();
	tail->prev = head;
	tail->next = nullptr;
	head->next = tail;

	DNode<T> *ptr = list.head->next;	//Pointer that points to the first node in the list.

	for ( ; ptr != list.tail; ptr = ptr->next )	//Continue incrementing ptr as long as it's not equal to tail of list.
		insertAtEnd(ptr->data);	

}

//Overloaded assignment operator of DList.
template<class T>
DList<T>& DList<T>::operator = (const DList<T> &list){

	if ( this->size > 0 ){
		this->~DList();
		head = new DNode<T>();
		head->prev = nullptr;
		tail = new DNode<T>();
		tail->prev = head;
		tail->next = nullptr;
		head->next = tail;
	}


	DNode<T> *ptr = list.head->next;

	for ( ; ptr != list.tail; ptr = ptr->next )
		insertAtEnd(ptr->data);

	return *this;

}

//Function that creates a new node with the provided value and inserts that node at the start of the list.
template<class T>
void DList<T>::insertAtStart(const T &element){

	DNode<T> *ptr = new DNode<T>(element, head, head->next);

	if ( head->next == tail ){
		head->next = ptr;
		tail->prev = ptr;
	}

	else {
		head->next->prev = ptr;
		head->next = ptr;
	}

	size++;

}

//Function that creates a new node with the provided value and inserts that node at the end of the list.
template<class T>
void DList<T>::insertAtEnd(const T &element){

	DNode<T> *ptr = new DNode<T>(element, 0, tail);

	if ( head->next == tail ){
		tail->prev = ptr;
		head->next = ptr;
		ptr->prev = head;
	}

	else {
		tail->prev->next = ptr;
		ptr->prev = tail->prev;
		tail->prev = ptr;
	}

	size++;

}

//Function that creates a new node with the provided value and inserts that node at the end of the list.
template<class T>
void DList<T>::push_back(const T &element){

	DNode<T> *ptr = new DNode<T>(element, 0, tail);

	if ( head->next == tail ){
		tail->prev = ptr;
		head->next = ptr;
		ptr->prev = head;
	}

	else {
		tail->prev->next = ptr;
		ptr->prev = tail->prev;
		tail->prev = ptr;
	}

	size++;

}

//Function for printing the list.
template<class T>
void DList<T>::print() const {
	DNode<T> *temp = head->next;

	for ( ; temp != tail; temp = temp->next )
		std::cout << temp->data << ' ';

	std::cout << '\n';
}

//Function for finding a node with the provided value.
template<class T>
DNode<T>* DList<T>::find(const T &val){

	DNode<T> *temp = head->next;

	for ( ; temp != tail && temp->data != val; )
		temp = temp->next;

	return temp;

}

//Function for deleting node at the end of the list.
template<class T>
void DList<T>::DeleteAtEnd(){

	if ( head && head->next == tail ){
		delete head;
		delete tail;
		head = nullptr;
		tail = nullptr;
	}

	else {
		DNode<T> *prev = tail->prev->prev;

		delete tail->prev;
        tail->prev = prev;
        prev->next = tail;

	}

	size--;

}

//Function for deleting a node an iterator is pointing to.
template<class T>
bool DList<T>::remove(Iterator *itr){
	if ( itr->iptr && tail ){
		DNode<T> *prev = itr->iptr->prev, *next = itr->iptr->next;

		delete itr->iptr;
		prev->next = next;
		next->prev = prev;
		size--;
		return true;
	}

	return false;
}


//Function that tells whether the list is empty or not.
template<class T>
bool DList<T>::empty(){
	return head == nullptr;
}

//Function for emptying the list.
template<class T>
void DList<T>::makeEmpty() {
	for ( ; head != nullptr; )
		DeleteAtEnd();

	size = 0;
}

//Function for changing size of list.
template<class T>
void DList<T>::changeSize(int capacity) {
	head = new DNode<T>();
	head->prev = nullptr;
	tail = new DNode<T>();
	tail->prev = head;
	tail->next = nullptr;
	head->next = tail;
	size = 0;

	for ( int i = 0; i < capacity; i++ )
		insertAtEnd(T());
}

//Function that returns the node at the passed idx from the list.
template<class T>
T & DList<T>::operator[](int idx) const {
	Iterator itr = begin();

	for ( int i = 0; i < idx; i++ )
		itr++;

	return *itr;
}

//Destructor of DList.
template<class T>
DList<T>::~DList(){
	for ( ; head != nullptr; )
		DeleteAtEnd();

	size = 0;
}