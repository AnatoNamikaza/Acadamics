#pragma once

class Doc_Data {
private:
	int DocID;
	Doc_Data* next;
	int QueryTerms;
	int CollectiveTermFrequency;
public:
	Doc_Data(int ix = 0, int qt = 0, int cfrq = 0,Doc_Data* nex=nullptr);
	Doc_Data(Doc_Data const& obj);
	void operator = (Doc_Data const& obj);
	int GetCTFreq();
	int GetDocID();
	int GetQueryTerms();
	Doc_Data* Getnext();
	void Setnext(Doc_Data* nex);
	void SetQueryTerms(int qterms);
	void SetCTFreq(int freq);
	void SetDocID(int id);
	~Doc_Data();
};
