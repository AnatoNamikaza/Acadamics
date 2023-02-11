#pragma once

class Doc_Info {
private:
	int DocID;
	int TFreq;
public:
//	Doc_Info();
	Doc_Info(int ix = 0, int frq = 0);
	Doc_Info(Doc_Info const& obj);
	void operator = (Doc_Info const& obj);
	int GetTFreq();
	int GetDocID();
	void SetTFreq(int freq);
	void SetDocID(int id);
	~Doc_Info();
};
