#include<iostream>
#include "DList.h"
#include "Node.h"
#include "Node.cpp"

//Parametarized constructor
template<typename type>
DList<type>::DList(Node<type>* ptr, Node<type>* ptr2) {
	tail = new Node<type>[1];
	head = new Node<type>[1];
	tail->Setprev(head); 
	tail->Getprev()->Setnext(tail);

	if (ptr != nullptr && ptr2 != nullptr) {
		tail = ptr;
		head = ptr2;
		tail->Setprev(head);
		tail->Getprev()->Setnext(tail);

	}
	
};

//Additional functions for future use

//template<typename type>
//DList<type>::DList(DList<type> const& obj) {
//	if (head->Getnext() != tail) {
//		while (tail->Getprev() != head) {
//			this->tail = tail->Getprev();
//			delete tail->Getnext();
//			tail->Setnext(nullptr);
//		}
//	}
//
//	Node<type>* p = obj.head->Getnext();
//	for (; p != obj.tail; p = p->Getnext()) {
//		this->insertAtEnd();
//	}
//};

//template<typename type>
//void DList<type>::operator = (DList<type> const& obj) {
//	if (head->next != tail) {
//		while (tail->prev != head) {
//			tail = tail->prev;
//			delete tail->next;
//			tail->next = nullptr;
//		}
//	}
//	Node<type>* p = obj.head->next;
//	for (; p != obj.tail; p = p->next) {
//		this->insertAtEnd();
//	}
//};
//template<typename type>
//void DList<type>::print() const {
//	Node<type>* tmp = head;
//	for ( tmp != tail; tmp = tmp->next) {
//		std::cout << tmp-> << " ";
//	}
//	std::cout << "\n";
//};
//
//template<typename type>
//void DList<type>::reverseprint() const {
//	Node<type>* tmp;
//	for (tmp = tail; tmp != 0; tmp = tmp->prev) {
//		std::cout << tmp->data << " ";
//	}
//	std::cout << "\n";
//};

//functions for insterting and deleting nodes at the end of the Doublylist
template<typename type>
void DList<type>::deleteAtEnd() {
	if (head->next != tail) {
		Node<type>* tmp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete tmp;
		tmp = nullptr;
	}
};

template<typename type>
void DList<type>::insertAtEnd() {
	Node<type>* tmp = new Node<type>(tail, tail->Getprev());
	tail->prev->next = tmp;
	tail->prev = tmp;
};

//Getters and Setters
template<typename type>
Node<type>* DList<type>::GetHead() {
	return this->head;
};

template<typename type>
Node<type>* DList<type>::Gettail() {
	return this->tail;
};

template<typename type>
void DList<type>::reverse() {
	Node<type>* tmp1 = head->next;
	Node<type>* tmp2 = tail->prev;

	int size = 0;
	for (; tmp1 != tail; tmp1 = tmp1->next) {
		size++;
	}

	size = size / 2;
	tmp1 = head->next;

	for (; size != 0; size--) {
		Node<type>* p = tmp1->next;
		Node<type>* q = tmp1->prev;
		Node<type>* r = tmp2->prev;

		if (size == 1) {
			tmp1->prev->next = tmp2;
			tmp2->next->prev = tmp1;

			tmp1->next = tmp2->next;
			tmp2->next = tmp1;
			tmp1->prev = tmp2;
			tmp2->prev = q;

		}
		else {

			tmp1->next = tmp2->next;
			tmp1->prev = r;
			tmp1->prev->next = tmp1;
			tmp2->next->prev = tmp1;

			tmp2->next = p;
			tmp2->prev = q;
			tmp2->prev->next = tmp2;
			tmp2->next->prev = tmp2;

		}

		tmp1 = p;
		tmp2 = r;
		p = q = r = nullptr;

	}

	tmp1 = tmp2 = nullptr;
};

//Destructor
template<typename type>
DList<type>::~DList() {
	if (head->next != tail) {
		while (tail->prev != head) {
			deleteAtEnd();
		}
	}
};

