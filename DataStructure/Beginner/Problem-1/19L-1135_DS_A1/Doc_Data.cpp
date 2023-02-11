#include "Doc_Data.h"

//Parametarized constructor
Doc_Data::Doc_Data(int ix, int qt, int cfrq, Doc_Data* nex) {
	DocID = ix; QueryTerms = qt; CollectiveTermFrequency = cfrq; next = nex;
};

Doc_Data::Doc_Data(Doc_Data const& obj) {
	this->DocID = obj.DocID; this->QueryTerms = obj.QueryTerms; this->CollectiveTermFrequency = obj.CollectiveTermFrequency; next = obj.next;
};

void Doc_Data::operator = (Doc_Data const& obj) {
	this->DocID = obj.DocID; this->QueryTerms = obj.QueryTerms; this->CollectiveTermFrequency = obj.CollectiveTermFrequency; next = obj.next;
};

//Getter and Setters
int Doc_Data::GetCTFreq() {
	return this->CollectiveTermFrequency;
};

int Doc_Data::GetDocID() {
	return this->DocID;
};

int Doc_Data::GetQueryTerms() {
	return this->QueryTerms;
};

Doc_Data* Doc_Data::Getnext() {
	return this->next;
};

void Doc_Data::Setnext(Doc_Data* nex) {
	this->next = nex;
};

void Doc_Data::SetQueryTerms(int qterms) {
	this->QueryTerms = qterms;
};


void Doc_Data::SetDocID(int id) {
	this->DocID = id;
};

void Doc_Data::SetCTFreq(int freq) {
	this->CollectiveTermFrequency = freq;
};

//Destructor
Doc_Data ::~Doc_Data() {
	DocID = QueryTerms = CollectiveTermFrequency = 0; next = nullptr;
};