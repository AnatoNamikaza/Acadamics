#include "Doc_Info.h"

//Parametarized constructor
Doc_Info::Doc_Info(int ix, int frq) {
	DocID = ix;		TFreq = frq;
};

Doc_Info::Doc_Info(Doc_Info const& obj) {
	this->DocID = obj.DocID; this->TFreq = obj.TFreq;
};

void Doc_Info::operator = (Doc_Info const& obj) {
	this->DocID = obj.DocID; this->TFreq = obj.TFreq;
};

//Getters and Setters
int Doc_Info::GetTFreq() {
	return this->TFreq;
};

int Doc_Info::GetDocID() {
	return this->DocID;
};

void Doc_Info::SetDocID(int id) {
	this->DocID = id;
};

void Doc_Info::SetTFreq(int freq) {
	this->TFreq = freq;
};

//Destructor
Doc_Info ::~Doc_Info() {
	DocID = TFreq = 0;
};