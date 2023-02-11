#pragma once

class Doc_Info {
private:
	int DocID;
	int TFreq;
public:
	Doc_Info(int ix = 0, int frq = 0);
	Doc_Info(Doc_Info const& obj);
	void operator = (Doc_Info & const obj);
	bool operator == (Doc_Info* const obj);
	bool compare (Doc_Info* const obj);
	int GetTFreq();
	int GetDocID();
	void SetTFreq(int freq);
	void SetDocID(int id);
	~Doc_Info();
};

//Parametarized constructor
Doc_Info::Doc_Info(int ix, int frq) {
	DocID = ix;		TFreq = frq;
};

Doc_Info::Doc_Info(Doc_Info const& obj) {
	this->DocID = obj.DocID; this->TFreq = obj.TFreq;
};

void Doc_Info::operator = (Doc_Info & const obj) {
	this->DocID = obj.GetDocID(); this->TFreq = obj.GetTFreq();
};

bool Doc_Info::operator == (Doc_Info* const obj) {
	if (this->DocID == obj->GetDocID() && this->TFreq == obj->GetTFreq())
		return true;
	return false;
};

bool Doc_Info::compare(Doc_Info* const obj) {
	if (this->DocID == obj->GetDocID() && this->TFreq == obj->GetTFreq())
		return true;
	return false;
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