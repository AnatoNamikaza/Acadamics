#pragma once
#include <fstream>
#include "Doc_Info.h"
#include "DList.h"
#include "DList.cpp"

using namespace std;

class Term_Info {
private:
	string keyterm;
	Term_Info* next;
	DList<Doc_Info>* Docs;
public:
	Term_Info(string term = "\0", Term_Info* nex = nullptr, DList<Doc_Info>* docs = nullptr);
	string GetTerm();
	Term_Info* Getnext();
	DList<Doc_Info>* GetDocs();
	int count(string& word, string& line);
	void SetTerm(string term);
	void Setnext(Term_Info* ptr);
	void SetDocs(DList<Doc_Info>* docs);
	void Analyze(string& file);
	void print();

	~Term_Info();
};