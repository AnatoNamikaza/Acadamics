#include "Doc_Info.h"
#include <string>
#include "Term_Info.h"
#include "DList.h"


//Parametarized constructor
Term_Info::Term_Info(string term, Term_Info* nex, DList<Doc_Info>* docs) {
	keyterm = term;
	next = nex;
	Docs = new DList<Doc_Info>;
	if (docs != nullptr) {
		this->Docs = docs;
	}
};

//Getters and Setters
string Term_Info::GetTerm() {
	return this->keyterm;
};

Term_Info* Term_Info::Getnext() {
	return this->next;
};

DList<Doc_Info>* Term_Info::GetDocs() {
	return this->Docs;
};

void Term_Info::SetTerm(string term) {
	this->keyterm = term;
};

void Term_Info::Setnext(Term_Info* nex) {
	this->next = nex;
};

void Term_Info::SetDocs(DList<Doc_Info>* docs) {
	this->Docs = docs;
};

//Print All occurances of the term in the docs
void Term_Info::print() {
	std::cout << "KeyTerm is: " << this->keyterm << "\n";

	Node<Doc_Info>* p = this->Docs->GetHead()->Getnext();
	Doc_Info* dax;

	for (; p != this->Docs->Gettail(); p = p->Getnext()) {
		dax = p->GetData();
		std::cout << "DocID: " << dax->GetDocID() << ", Term Frequency: " << dax->GetTFreq() << "\n";
	}
};

//Analyze how many times the term occured in the document topics
void Term_Info::Analyze(std::string& file) {
	std::string topic;
	ifstream fin;

	fin.open(file);
	if (fin.is_open() != true) {
		std::cout << "File didnot open. \n";
	}

	int i, j, T, occurance;
	i = j = T = occurance = 0;

	if (this->Docs->GetHead()->Getnext() != this->Docs->Gettail() && this->Docs->Gettail()->Getprev() != this->Docs->GetHead()) {
		
		while (Docs->GetHead()->Getnext() != Docs->Gettail()) {
			Node<Doc_Info>* del = this->Docs->GetHead()->Getnext();
			this->Docs->GetHead()->Setnext(this->Docs->GetHead()->Getnext()->Getnext());
			delete del; del = nullptr;
		}
	}

	for (;; i++) {
		getline(fin, topic, '\n');

		if (topic != "") {
			T++;
			occurance = count(this->keyterm,topic);
			if (T != 0 && occurance != 0) {
				this->Docs->insertAtEnd();
				Doc_Info* dax = this->Docs->Gettail()->Getprev()->GetData();
				dax->SetDocID(T); dax->SetTFreq(occurance);
			}
		}
		else if (topic == "") {
			break;
		}
	}
};

//For counting all occurances in a document topic
int Term_Info::count(string& word, string& line) {
	int i, res; i = res = 0;
	string temp;

	for (;; i++) {
		if (line[i] != '\n' && line[i] != '\0' && line[i] != ' ') {
			temp = temp + line[i];
		}
		if (line[i] == '\n' || line[i] == ' ') {
			if (temp == word) {
				res++;
			}
			temp = "";
		}
		else if (line[i] == '\0') {
			if (temp == word) {
				res++;
			}
			break;
		}
	}

	return res;
};

//Destructor
Term_Info::~Term_Info() {
	this->keyterm = "\0";
	this->Docs = nullptr;
};
