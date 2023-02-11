#pragma once
#include "Term_Info.h"
#include "Doc_Data.h"
#include"Hash_Table.h"
#include <fstream>

class Search_Engine {
private:
	HashMap<Term_Info>* Index; int TotalDocs;
public:
	Search_Engine();
//	Search_Engine(string& file);
	void IndexGenerator(string file);
	void Search_Documents(string& file);
	void Ranked_list(string* QueryWords, string& file);
	void Print_Ranked_list(int* RList, int size, string& file);
	void Add_Doc_to_Index(string& file);
	void UpdateIndex(const string Doc, string& file);
	void remove_Duplicate_word(string* words, int size);
	void remove_char_from_word(string& file, char rp, char rb);
	void clearFile(string& file);
	void clearBackup();
	int FindTDocs(string& file);
//	int GetTDocs();
//	void SetTDocs(int total);
	void DocPrint(int DocNo, string& file);
//	void TermPrint(string term);
	void GetDoc(int DocNo, string& Doc, string& file);
	void IndexPrint();
	~Search_Engine();
};

//Default constructor
Search_Engine::Search_Engine() {
	TotalDocs = 0;
	Index = nullptr;
};

//Search_Engine::Search_Engine(string& file) {
//	Index = new AVL<Term_Info>; TotalDocs = 0;
//	IndexGenerator(file);
//};

//Function to Search a file
void Search_Engine::Search_Documents(string& file) {
	IndexGenerator(file);
	string query;
	cout << "Enter Query: \n............\n>";
	getline(cin, query);
	cout << "________________________________________________________\n";
	string word[20]{}; int i, j, words; i = j = words = 0;
	string temp;

	for (;; i++) {
		if (query[i] != '\n' && query[i] != '\0' && query[i] != ' ') {
            temp += query[i];
        }
		if (query[i] == '\n' || query[i] == ' ') {
			if (!temp.empty()) {
				word[j] = temp;
				j++;
			}
			temp = "";
		}
		else if (query[i] == '\0') {
			if (!temp.empty()) {
				word[j] = temp;
			}
			break;
		}
	}

	remove_char_from_word(word[words], '\n', '.');

	Ranked_list(word, file);
};

//Function to create the index
void Search_Engine::IndexGenerator(string file) {
    string word[50]{};
    int i, j;
    i = j = 0;
    ifstream fin;
    this->TotalDocs = FindTDocs(file);

    fin.open(file);
    if (!fin.is_open()) {
        std::cout << "File did not open. \n";
    }

    while (true) {
        getline(fin, word[i], ' ');
        remove_char_from_word(word[i], '\n', '.');
        remove_char_from_word(word[i], '\r', '.');
        if (word[i].empty()) {
            break;

        } else {
            i++;
        }
    }

    remove_Duplicate_word(word, i);
    Index = new HashMap<Term_Info>;
	for (; j < i; j++) {
		Term_Info TermValue;
		int key = 0;
		for (int l = 0; l < word[j].length(); l++) {
			key += word[j][l];
		}
		if (word[j] != "0") {
			TermValue.SetTerm(word[j]);
			TermValue.Analyze(file);
			Index->insert(key, TermValue);
		}
	}
};

//Function to add a new document topic to the file(database) 
void Search_Engine::Add_Doc_to_Index(string& file) {
	string newtopic, prevText, Fulltext, brk = " . \n";
	cout << "Enter the Document Heading: \n";
	getline(cin, newtopic);

	ifstream fin;
	fin.open(file);
	if (!fin.is_open()) {
		std::cout << "File didnot open. \n";
	}

	getline(fin, prevText, '\0');
	if (!prevText.empty() && !newtopic.empty()) {
		Fulltext = prevText + newtopic + brk;
	}
	else if (prevText.empty() && !newtopic.empty()) {
		Fulltext = newtopic + brk;
	}

	if (!newtopic.empty()) {
		this->TotalDocs++;
		ofstream myfile;
		myfile.open(file);
		myfile << Fulltext;
		myfile.close();
		myfile.open("Backup.txt");
		myfile << Fulltext;
		myfile.close();
	}

	if (this->Index->GetCE() == 0) { IndexGenerator(file); }
	else { UpdateIndex(newtopic, file); }
};

//Function to find all Documnets related to the SearchQuery
//void Search_Engine::Ranked_list(string* QueryWords, string& file) {
//    int s = this->TotalDocs, *RList = new int[s]{0}, *QTerms = new int[s]{0}, *TFs = new int[s]{0};
//    Term_Info *Searched;
//	for (int i = 0; !QueryWords[i].empty(); i++) {
//		int key = 0;
//		for (int l = 0; l < QueryWords[i].length(); l++) {
//			key += QueryWords[i][l];
//		}
//		Term_Info* TermValue;
//		TermValue->SetTerm(QueryWords[i]);
//		Searched = &Index->SearchItem(key, TermValue);
//        if (Searched) {
//            Node<Doc_Info> *DocsNo = Searched->GetDocs()->GetHead()->Getnext();
//            while (DocsNo != Searched->GetDocs()->GetTail()) {
//                int j = DocsNo->GetData().GetDocID();
//                if (j > 0) {
//                    RList[j - 1] = j;
//                    QTerms[j - 1] = QTerms[j - 1] + 1;
//                    TFs[j - 1] = TFs[j - 1] + DocsNo->GetData().GetTFreq();
//                }
//                DocsNo = DocsNo->Getnext();
//            }
//            DocsNo = nullptr;
//        } else
//            break;
//    }
//
//    if (Searched) {
//        for (int i = 0; i < s; i++) {
//            for (int j = i + 1; j < s; j++) {
//                if (QTerms[i] < QTerms[j]) {
//                    int temp = RList[i], temp1 = QTerms[i], temp2 = TFs[i];
//                    RList[i] = RList[j];
//                    QTerms[i] = QTerms[j];
//                    TFs[i] = TFs[j];
//                    RList[j] = temp;
//                    QTerms[j] = temp1;
//                    TFs[j] = temp2;
//                }
//            }
//        }
//
//        for (int i = 0; i < s; i++) {
//            for (int j = i + 1; j < s; j++) {
//                if (QTerms[i] == QTerms[j] && TFs[i] < TFs[j]) {
//                    int temp = RList[i], temp1 = QTerms[i], temp2 = TFs[i];
//                    RList[i] = RList[j];
//                    QTerms[i] = QTerms[j];
//                    TFs[i] = TFs[j];
//                    RList[j] = temp;
//                    QTerms[j] = temp1;
//                    TFs[j] = temp2;
//                }
//            }
//        }
//
//        for (int i = 0; i < s; i++) {
//            for (int j = i + 1; j < s; j++) {
//                if (QTerms[i] == QTerms[j] && TFs[i] == TFs[j]) {
//                    string str1, str2;
//                    GetDoc(RList[i], str1, file);
//                    GetDoc(RList[j], str2, file);
//                    if (str1 < str2) {
//                        int temp = RList[i], temp1 = QTerms[i], temp2 = TFs[i];
//                        RList[i] = RList[j];
//                        QTerms[i] = QTerms[j];
//                        TFs[i] = TFs[j];
//                        RList[j] = temp;
//                        QTerms[j] = temp1;
//                        TFs[j] = temp2;
//                    }
//                }
//            }
//        }
//
//        Print_Ranked_list(RList, s, file);
//    } else
//        cout << "No results found.\n";
//    delete[]RList, QTerms, TFs;
//    RList = nullptr;
//    QTerms = nullptr, TFs = nullptr;
//    Searched = nullptr;
//};

//Function to print the Document topics related to the SearchQuery according to the ranking rules
void Search_Engine::Print_Ranked_list(int* RList, int size, string& file) {
	for (int i = 0; i < size; i++) {
		if (RList[i] > 0)
			DocPrint(RList[i], file);
		else
			break;
	}
};

//Function to update the index when a new documnet topic is added while the program is running
void Search_Engine::UpdateIndex(const string Doc, string& file) {
	string word[50]{}; int i, j; i = j = 0;
	this->TotalDocs = FindTDocs(file);

	for (int k = 0; k < Doc.size(); ++k) {
        if (Doc[k] != ' ' && Doc[k] != '\0')
            word[i] = word[i] + Doc[k];
        if (Doc[k] == ' ' || Doc[k] == '\0')
            i++;
    }
	
	remove_Duplicate_word(word, i);
	for (; j < i; j++) {
		int key = 0;
		for (int l = 0; l < word[j].length(); l++) {
			key += word[j][l];
		}
		if (word[j] != "0") {
			Term_Info TermValue;
			TermValue.SetTerm(word[j]);
			TermValue.Analyze(file);
			Index->insert(key, TermValue);
		}
	}
};

//Function to remove any Duplicate words from an array of strings
void Search_Engine::remove_Duplicate_word(string* words, int size) {
	string testword;
	for (int i = 0; i < size; i++) {
		if (words[i] != "0") {
			testword = words[i];
		}
		for (int j = i + 1; j < size; j++) {
			if (testword == words[j]) {
				words[j] = "0";
			}
		}
	}
};

//Function to remove any unwanted Delimiters from a string
//Note:
//Can be modified to remove any unwanted stopper words from the string (Documemt topic)
void Search_Engine::remove_char_from_word(string& word, char rp, char rb) {
    string temp;
    for (char i : word) {
        if (i != rp && i != rb) {
            temp += i;
        }
        if (i == rb) {
            temp = "0";
        }
    }
    word = temp;
    temp = "\0";
};

//Function to clear all data from the file(database)
void Search_Engine::clearFile(string& file) {
	string clr = "\0";
	ofstream myfile;
	myfile.open(file);
	myfile << clr;
	myfile.close();
};

//Function to clear all data from the file backup(database backup)
void Search_Engine::clearBackup() {
	string clr = "\0";
	ofstream myfile;
	myfile.open("Backup.txt");
	myfile << clr;
	myfile.close();
};

//Function to find the total number of document topics in the file(database)
int Search_Engine::FindTDocs(string& file) {
    std::string topic;
    ifstream fin;

    fin.open(file);
    if (!fin.is_open()) {
        std::cout << "File did not open. \n";
    }

    int T;
    T = 0;

    while (true) {
        getline(fin, topic, '\n');
        if (!topic.empty())
            T++;
        else
            return T;
    }
};

//Getters and Setters
//int Search_Engine::GetTDocs() {
//	return this->TotalDocs;
//};

//void Search_Engine::SetTDocs(int total) {
//	this->TotalDocs = total;
//};

//void Search_Engine::TermPrint(string term) {
//	AVLNode<Term_Info>* Searched = Index->SearchAddress(term, Index->GetRoot());
//	if (Searched)
//		Searched->Print();
//	Searched = nullptr;
//};

//Function to print topic of a single document with DocID = DocNo
void Search_Engine::DocPrint(int DocNo, string& file) {
    std::string topic;
    ifstream fin;

    fin.open(file);
    if (!fin.is_open())
        std::cout << "File did not open. \n";

    for (int i = 0; i < DocNo; i++)
        getline(fin, topic, '\n');

    if (!topic.empty() && topic != " ")
        cout << topic << "\n";
    topic = "";
};

void Search_Engine::GetDoc(int DocNo, string& Doc, string& file) {
	ifstream fin;

	fin.open(file);
	if (!fin.is_open()) {
		std::cout << "File did not open. \n";
	}

	for (int i = 0; i < DocNo; i++) {
		getline(fin, Doc, '\n');
	}
};

//Function to print All information about the index words and the occurance in each topic
void Search_Engine::IndexPrint() {
	Index->Print();
};

//Destructor
Search_Engine::~Search_Engine() {
	if (Index != nullptr) {
		HashMap<Term_Info>* Del = Index;
		Index = nullptr;
		delete Del; Del = nullptr;
	}
};
