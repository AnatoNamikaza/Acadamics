#pragma once
#include"MT_Node.h"


template<class type>
class MT_Stack {
private:
	MT_Node<type>* top;
public:
	//Default Constructor
	MT_Stack() {
		MT_Node<type>* tmp = new MT_Node<type>;
		top = tmp;
	}

	//Copy Constructor
	MT_Stack(MT_Stack<type> const& obj) {
		MT_Node<type>* p = obj.top->next;
		MT_Node<type>* tmp = top->next;
		for (; p->next != nullptr; p = p->next) {
			MT_Node<type>* tmp2 = new MT_Node<type>(tmp);
			top->next = tmp2;
			tmp = top->next;
			tmp2->Setdata(p->Getdata());
		}
	}

	//Assignment Operator
	MT_Stack& operator=(const MT_Stack<type>& obj) {
		if (top->next != nullptr) {
			while (top->next != nullptr) {
				MT_Node<type>* tmp = top->next;
				top->next = top->next->next;
				delete tmp;
				tmp = nullptr;
			}
		}

		MT_Node<type>* p = obj.top->next;
		MT_Node<type>* tmp = top->next;
		for (; p->next != nullptr; p = p->next) {
			MT_Node<type>* tmp2 = new MT_Node<type>(tmp);
			top->next = tmp2;
			tmp = top->next;
			tmp2->Setdata(p->Getdata());
		}

		return *this;
	}

	//Pop the first node of the stack
	bool pop() {
		bool deleted = false;
		MT_Node<type>* del;
		if (IsEmpty() == 0) {}
		else {
			del = top->next;
			top->next = top->next->next;
			delete del;
			del = nullptr;
			deleted = true;

		}

		return deleted;
	}

	//Pushes data to the top of the stack
	bool push(type const * element) {
		bool pushed = false;
		MT_Node<type>* tmp = new MT_Node<type>;
		tmp->Info->SetData(*element);
		tmp->next = top->next;
		top->next = tmp;

		return pushed;
	}

	//Tell if stack is empty or not
	bool IsEmpty() {
		if (top->next != nullptr) {
			return 1;
		}
		else {
			return 0;
		}
	}

	//Gives the top node of stack (Note: We have taken top node of satck as a Dummy node)
	MT_Node<type>* Gettop() {
		return this->top;
	}

	//Print all the data in each node of the stack
	void print() const {
		for (MT_Node<type>* tmp = top->next; tmp != nullptr; tmp = tmp->next) {
			cout << "-------------------------------------------------------------------\n";
			tmp->Info->PrintA();
		}
		cout << "-------------------------------------------------------------------\n";
	}

	//Print the data of the node containing the max Points in the stack
	void Best() const {
		MT_Node<type>* Best = top->next; int MaxPoints = Best->Info->CalculateTotalPoints();
		for (MT_Node<type>* tmp = top->next; tmp != nullptr; tmp = tmp->next) {
			if (tmp->Info->CalculateTotalPoints() > MaxPoints) {
				Best = tmp;
				MaxPoints = Best->Info->CalculateTotalPoints();
			}
		}
		cout << "\nBest Choice:\n------------\n";
		Best->Info->PrintA();
		cout << "\n>Total Points Being Earned: "<<MaxPoints;
		Best = nullptr; MaxPoints = 0;
	}

	//Destructor
	~MT_Stack() {
		MT_Node<type>* tmp2 = this->top->next;
		while (tmp2 != nullptr) {
			MT_Node<type>* del = tmp2;
			tmp2 = tmp2->next;
			delete del;
			del = nullptr;
		}
		delete top;
		top = nullptr;
	}
};