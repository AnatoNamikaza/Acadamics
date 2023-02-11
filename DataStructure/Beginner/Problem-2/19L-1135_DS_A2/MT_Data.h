#pragma once
#include <iostream>
#include <string>
using namespace std;

struct MT_Data {
	string StageName;
	MT_Data* Next;
	int StageNo, StagePoints, StageCompletionTime;

	//Parameterized constructor
	MT_Data(string Sname = "\0", int points = 0, int time = 0, int sn = 0, MT_Data* ext = nullptr) {
		this->StageName = Sname; this->StagePoints = points; this->StageCompletionTime = time; this->StageNo = sn; this->Next = nullptr;
		if (ext != nullptr) {
			this->Next = ext;
		}
	}

	//Copy constructor
	MT_Data(const MT_Data & obj) {
		this->Next = obj.Next; this->StageName = obj.StageName; this->StagePoints = obj.StagePoints; this->StageCompletionTime = obj.StageCompletionTime; this->StageNo = obj.StageNo;
	}

	//Assignment operator
	MT_Data & operator = (const MT_Data & obj) {
		this->StageName = obj.StageName; this->StagePoints = obj.StagePoints; this->StageCompletionTime = obj.StageCompletionTime; this->StageNo = obj.StageNo;
		
		return *this;
	}

	//DeepCopying Data Function
	void SetData(MT_Data const& obj) {
		this->StageName = obj.StageName; this->StagePoints = obj.StagePoints; this->StageCompletionTime = obj.StageCompletionTime; this->StageNo = obj.StageNo;
		MT_Data* tmp2 = this;
		for (MT_Data* tmp = obj.Next; tmp != nullptr; tmp = tmp->Next) {
			tmp2->Next = new MT_Data(tmp->StageName, tmp->StagePoints, tmp->StageCompletionTime, tmp->StageNo);
			tmp2 = tmp2->Next;
		}
		tmp2 = nullptr;
	}

	//Copying Data Function
	void SetData(string Sname, int points, int time, int sn) {
		this->StageName = Sname; this->StagePoints = points; this->StageCompletionTime = time; this->StageNo = sn;
	}

	void push(MT_Data const* obj) {
		MT_Data* tmp = new MT_Data(obj->StageName, obj->StagePoints, obj->StageCompletionTime, obj->StageNo);
		this->Next = tmp;
	}

	void pop() {
		MT_Data* del, * rext;
		for (rext = this; rext->Next->Next != nullptr; rext = rext->Next);
		del = rext->Next;
		rext->Next = nullptr;
		delete del;
		del = nullptr;
	}

	//Print Single Data
	void PrintS() {
		cout << "Stage#" << StageNo << ": " << this->StageName << ", Points: " << this->StagePoints << ", Time: " << this->StageCompletionTime << ".\n";
	}

	//Print All Data
	void PrintA() {
		for (MT_Data* tmp = this; tmp != nullptr && tmp->StageName != ""; tmp = tmp->Next) {
			cout << "Stage#" << tmp->StageNo << ": " << tmp->StageName << ", Points: " << tmp->StagePoints << ", Time: " << tmp->StageCompletionTime << ".\n";
		}
	}

	//Calculate Total Time of All the data 
	int CalculateTotalTime() {
		int total = 0;
		for (MT_Data* tmp = this; tmp != nullptr; tmp = tmp->Next) {
			total += tmp->StageCompletionTime;
		}
		return total;
	}

	//Calculate Total Points of All the data 
	int CalculateTotalPoints() {
		int total = 0;
		for (MT_Data* tmp = this; tmp != nullptr; tmp = tmp->Next) {
			total += tmp->StagePoints;
		}
		return total;
	}

	~MT_Data() {
		this->StagePoints = 0; this->StageCompletionTime = 0; this->StageNo = 0;
		this->Next = nullptr;
	}
};