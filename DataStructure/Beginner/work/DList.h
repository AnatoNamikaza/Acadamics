#pragma once
#include "Node.h"

template<class type>
class DList {

private:

    Node<type>* head, * tail;

public:

	DList() {
		head = new Node<type>;
		tail = new Node<type>;
		head->Setnext(tail);
		tail->Setprev(head);
	}

    DList(Node<type>* ptr, Node<type>* ptr2) { if (ptr && ptr2 && !head && !tail) { head = ptr, tail = ptr2; } }

    void DinsertAtEnd(type const& Tdata) {
        Node<type>* tmp = new Node<type>(this->tail, this->tail->Getprev(), nullptr);
        this->tail->Getprev()->Setnext(tmp);
        this->tail->Setprev(tmp);
        tmp->SetValue(Tdata);
    }

	void CopyDList(DList<type> & obj) {
		if (head->Getnext() != tail)
			while (tail->Getprev() != head)
				deleteAtEnd();
		Node<type>* p = obj.GetHead()->Getnext();
		for (; p != obj.GetTail(); p = p->Getnext())
			this->DinsertAtEnd(p->GetData());
		p = nullptr;
	}

	void Merge(DList<type>* const obj) {
		Node<type>* tmp, *tmp2 = obj->GetHead()->Getnext();
		while (tmp2 != obj->GetTail()) {
			tmp = this->head->Getnext();
			while (tmp != this->tail) {
				if (tmp->GetData().compare(tmp2->GetPData()))
					break;
				tmp = tmp->Getnext();
				if (tmp == this->tail) {
					this->insertAtEnd(tmp2->GetData());
				}
			}
			tmp2 = tmp2->Getnext();
		}
		tmp = tmp2 = nullptr;
	};

    void insertAtEnd(type const& Tdata) {
        Node<type>* tmp = new Node<type>(this->tail, this->tail->Getprev(), Tdata);
        this->tail->Getprev()->Setnext(tmp);
        this->tail->Setprev(tmp);
    }

	void insertNodeAtEnd(Node<type>* temp) {
		Node<type>*tmp = new Node<type>(this->tail, this->tail->Getprev(), temp->Data);
		this->tail->Getprev()->Setnext(tmp);
		this->tail->Setprev(tmp);
	}

	void insertNodeAtEnd(Node<type>& temp) {
		temp.Setnext(this->tail);
		temp.Setprev(this->tail->Getprev());
		this->tail->Getprev()->Setnext(&temp);
		this->tail->Setprev(&temp);
	}

    void deleteAtEnd() {
        if (head->Getnext() != tail) {
            Node<type>* tmp = tail->Getprev();
            tail->Setprev(tail->Getprev()->Getprev()), tail->Getprev()->Setnext(this->tail);
            delete tmp, tmp = nullptr;
        }
    }

    Node<type>* GetHead() { return this->head; }

    Node<type>* GetTail() { return this->tail; }

    ~DList() {
        while (head->Getnext() != tail)
            deleteAtEnd();
        if (head && tail)
            delete this->head, delete this->tail;
        this->head = nullptr, this->tail = nullptr;
    }
};