#pragma once
#include <iostream>

class Doc_Data {

private:

    Doc_Data* next;
    int DocID, QTerms, CTFreq;

public:

    Doc_Data() { DocID = 0, QTerms = 0, CTFreq = 0, next = nullptr; }

    Doc_Data(int ix, int qt, int cfrq, Doc_Data* nex) { DocID = ix, QTerms = qt, CTFreq = cfrq, next = nex; }

    Doc_Data(Doc_Data const& obj) { DocID = obj.GetDocID(), QTerms = obj.GetQTerms(), CTFreq = obj.GetCTFreq(); }

    void DCopy(Doc_Data const& obj) { DocID = obj.GetDocID(), QTerms = obj.GetQTerms(), CTFreq = obj.GetCTFreq(); }

    bool isEmpty() { return DocID == 0 && QTerms == 0 && CTFreq == 0 ? true : false; }

    int GetCTFreq() const { return this->CTFreq; }

    int GetDocID() const { return this->DocID; }

    int GetQTerms() const { return this->QTerms; }

    Doc_Data* Getnext() { return this->next; }

    void Setnext(Doc_Data* nex) { this->next = nex; }

    void SetQueryTerms(int qterms) { this->QTerms = qterms; }

    void SetCTFreq(int freq) { this->CTFreq = freq; }

    void SetDocID(int id) { this->DocID = id; }

    void print() const {
        std::cout << "DocID: " << DocID << ", QueryTerms: " << QTerms << ", TotalFrequency: " << CTFreq << '\n';
    }

    ~Doc_Data() { DocID = 0, QTerms = 0, CTFreq = 0, next = nullptr; }
};
