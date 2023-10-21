#pragma once
#include <iostream>

class Doc_Info {

private:

    int DocID, TFreq;

public:

    Doc_Info() { DocID = 0, TFreq = 0; }

    Doc_Info(int ix, int frq) { DocID = ix, TFreq = frq; }

    Doc_Info(Doc_Info const& obj) { this->DocID = obj.DocID, this->TFreq = obj.TFreq; }

    void DCopy(Doc_Info const& obj) { this->DocID = obj.DocID, this->TFreq = obj.TFreq; }

    bool isEmpty() { return DocID == 0 && TFreq == 0 ? true : false; }

    bool compare(Doc_Info const* obj) const { return DocID == obj->DocID && TFreq == obj->TFreq ? true : false; }

    bool compare(Doc_Info const& obj) const { return DocID == obj.DocID && TFreq == obj.TFreq ? true : false; }

    Doc_Info& operator=(Doc_Info const& obj) {
        this->DocID = obj.GetDocID(), this->TFreq = obj.GetTFreq();
        return *this;
    }

    int GetTFreq() const { return this->TFreq; }

    int GetDocID() const { return this->DocID; }

    void SetTFreq(int freq) { this->TFreq = freq; }

    void SetDocID(int id) { this->DocID = id; }

    void print() const { std::cout << "DocID: " << DocID << ", TermFrequency: " << TFreq << '\n'; }

    ~Doc_Info() { this->DocID = 0, this->TFreq = 0; }
};