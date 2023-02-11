#pragma once
using namespace std;

template <class type>
struct MT_Node {
	type* Info;
	MT_Node<type>* next;

	//Parameterized Constructor
	MT_Node(MT_Node<type>* ptr = nullptr, type* info = nullptr) {
		this->Info = new type; next = nullptr;
		if (ptr != nullptr) {
			this->next = ptr;
		}
		if (info != nullptr) {
			this->Info = info;
		}
	}

	//Copy Constructor
	MT_Node(const MT_Node<type>  & obj) {
		this->Info->Next = obj.Next; this->Info->StageName = obj.StageName; this->Info->StagePoints = obj.StagePoints; this->Info->StageCompletionTime = obj.StageCompletionTime;
	}

	//Assignment operator
	MT_Node & operator = (MT_Data const& obj) {
		this->Info->Next = obj.Next; this->Info->StageName = obj.StageName; this->Info->StagePoints = obj.StagePoints; this->Info->StageCompletionTime = obj.StageCompletionTime;

		return *this;
	}

	~MT_Node() {
		delete this-> Info;
		this->Info = nullptr;
			this-> next = nullptr;
	}
};