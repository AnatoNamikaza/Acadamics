#include "Search Engine.h"
#include <iostream>
#include <string>

//Default constructor
Search_Engine::Search_Engine() {
	TotalDocs = 0;
	Index = new Term_Info;
};

Search_Engine::Search_Engine(string& file) {
	Index = new Term_Info; TotalDocs = 0;
	IndexGenerator(file);
};

//Function to create the index
void Search_Engine::IndexGenerator(string& file) {
	string word[50]{}; int i, j; i = j = 0;
	ifstream fin; this->TotalDocs = FindTDocs(file);

	fin.open(file);
	if (fin.is_open() != true) {
		std::cout << "File didnot open. \n";
	}

	while (true) {
		getline(fin, word[i], ' ');
		remove_char_from_word(word[i], '\n', '.');
		if (word[i] != "") {
			i++;
		}
		else if (word[i] == "") {
			break;
		}
	}

	remove_Duplicate_word(word, i);

	for (; j < i; j++) {
		if (word[j] != "0") {
			Index->SetTerm(word[j]);
			Index->Analyze(file);
			Index = new Term_Info(word[j], Index);
		}
	}

	Index->SetTerm("New word");

};

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
			temp = temp + query[i];
		}
		if (query[i] == '\n' || query[i] == ' ') {
			if (temp != "") {
				word[j] = temp;
				j++;
			}
			temp = "";
		}
		else if (query[i] == '\0') {
			if (temp != "") {
				word[j] = temp;
				j++;
			}
			temp = "\0";
			break;
		}
	}

	remove_char_from_word(word[words], '\n', '.');

	Ranked_list(word, file);
};

//Function to find all Documnets related to the SearchQuery
void Search_Engine::Ranked_list(string* QueryWords, string& file) {
	Term_Info* SelectedIndex = nullptr; int i, STotalDocs, Cflag; i = STotalDocs = 0;
	string SearchWord; Doc_Data* AllDocs,* BDoc; AllDocs = BDoc = nullptr; Node<Doc_Info>* IDoc = nullptr;
	Term_Info* ptr;

	while (true) {
		ptr = Index->Getnext();
		SearchWord = QueryWords[i];

		if (QueryWords[i] == "") {
			SearchWord = "\0";
			ptr = nullptr;
			break;
		}

		while (true) {
			if (ptr->GetTerm() == SearchWord) {
				SelectedIndex = new Term_Info(ptr->GetTerm(), SelectedIndex, ptr->GetDocs());
			}
			if (ptr->Getnext() != nullptr) {
				ptr = ptr->Getnext();
			}
			else {
				break;
			}
		}
		i++;
	}

	ptr = SelectedIndex;
	for (; ptr != nullptr; ptr = ptr->Getnext()) {
		IDoc = ptr->GetDocs()->GetHead()->Getnext();
		Cflag = 0;
		for (; IDoc != ptr->GetDocs()->Gettail(); IDoc = IDoc->Getnext()) {
			if (AllDocs != nullptr) {
				BDoc = AllDocs;
				if (BDoc->Getnext() != nullptr) {
					for (; BDoc->Getnext() != nullptr; BDoc = BDoc->Getnext()) {
						if (BDoc->GetDocID() == IDoc->GetData()->GetDocID()) {
							BDoc->SetQueryTerms(BDoc->GetQueryTerms() + 1);
							BDoc->SetCTFreq(BDoc->GetCTFreq() + IDoc->GetData()->GetTFreq());
							Cflag = 1;
							BDoc = BDoc->Getnext();
							break;
						}
					}
				}
				else if (BDoc->Getnext() == nullptr) {
					if (BDoc->GetDocID() == IDoc->GetData()->GetDocID()) {
						BDoc->SetQueryTerms(BDoc->GetQueryTerms() + 1);
						BDoc->SetCTFreq(BDoc->GetCTFreq() + IDoc->GetData()->GetTFreq());
						Cflag = 1;
						BDoc = BDoc->Getnext();
					}
				}
				if (BDoc != nullptr && BDoc->GetDocID() != IDoc->GetData()->GetDocID() && Cflag == 0) {
					AllDocs = new Doc_Data(IDoc->GetData()->GetDocID(), 1, IDoc->GetData()->GetTFreq(), AllDocs);
					STotalDocs++;
				}
				Cflag = 0;
			}
			else if (AllDocs == nullptr) {
				AllDocs = new Doc_Data(IDoc->GetData()->GetDocID(),1, IDoc->GetData()->GetTFreq(),AllDocs);
				STotalDocs++;
			}
		}
	}



	int x = Print_Ranked_list(AllDocs,file,STotalDocs);
	if (x == 0) {
		cout << "\n\n<--Search Complete-->\n";
	}

};

//Function to print the Document topics related to the SearchQuery according to the ranking rules
int Search_Engine::Print_Ranked_list(Doc_Data* RDocs, string& file, int Tdocs) {
	Doc_Data* ADoc = RDocs, * CDoc = nullptr, * EDoc = nullptr;
	int Max_term_exist, Max_term_ID=0, Equal_Term_Docs, Max_Freq_exist, Max_Freq_ID;
	Max_term_exist = Max_term_ID = Equal_Term_Docs = Max_Freq_exist = Max_Freq_ID = 0;

	if (ADoc != nullptr) {
		Max_term_exist = 0;

		while (ADoc != nullptr) {
			if (Max_term_exist < ADoc->GetQueryTerms()) {
				Max_term_exist = ADoc->GetQueryTerms();
			}
			ADoc = ADoc->Getnext();
		}
	}

	for (int p = 0; p != Tdocs;) {
		ADoc = RDocs;
		int Cflag = 0;

		while (ADoc != nullptr) {
			if (ADoc->GetQueryTerms() <= Max_term_exist) {
				if (ADoc->GetQueryTerms() == Max_term_exist) {
					CDoc = RDocs;
					while (CDoc != nullptr) {
						if (ADoc->GetQueryTerms() == CDoc->GetQueryTerms() && ADoc->GetDocID() != CDoc->GetDocID()) {
							Cflag = 1;
							Equal_Term_Docs = 0;
							for (EDoc = RDocs; EDoc != nullptr; EDoc = EDoc->Getnext()) {
								if (ADoc->GetQueryTerms() == EDoc->GetQueryTerms()) {
									Equal_Term_Docs++;
								}
							}
							if (Equal_Term_Docs == 2) {
								if (ADoc->GetCTFreq() > CDoc->GetCTFreq()) {
									DocPrint(ADoc->GetDocID(), file);
									DocPrint(CDoc->GetDocID(), file);
									p = p + 2;
									Max_term_exist--;
								}
								else if (ADoc->GetCTFreq() < CDoc->GetCTFreq()) {
									DocPrint(CDoc->GetDocID(), file);
									DocPrint(ADoc->GetDocID(), file);
									p = p + 2;
									Max_term_exist--;
								}
								else if (ADoc->GetCTFreq() == CDoc->GetCTFreq() && ADoc->GetDocID() != CDoc->GetDocID()) {
									string s1, s2;
									ifstream fin;
									ifstream fin2;

									fin.open(file);
									fin2.open(file);
									if (fin.is_open() != true) {
										std::cout << "File didnot open. \n";
									}
									for (int i = 0; i < ADoc->GetDocID(); i++) {
										getline(fin, s1, '\n');
									}
									for (int i = 0; i < CDoc->GetDocID(); i++) {
										getline(fin2, s2, '\n');
									}
									int k = 0;
									while (true) {
										if (s1[k] < s2[k]) {
											cout << s1 << "\n";
											cout << s2 << "\n";
											break;
										}
										else if (s1[k] > s2[k]) {
											cout << s2 << "\n";
											cout << s1 << "\n";
											break;
										}
										else if (s1[k] == s2[k]) {
											k++;
										}
									}
									p = p + 2;
									Max_term_exist--;
								}
								if (p == Tdocs) { return 0; }
							}
							else if (Equal_Term_Docs > 2) {

								int Equal_Freq_Docs = 0;
								Max_Freq_ID = Max_Freq_exist=0; EDoc = RDocs;
								while (EDoc != nullptr) {
									if (ADoc->GetQueryTerms() == EDoc->GetQueryTerms() && Max_Freq_exist < EDoc->GetCTFreq()) {
										Max_Freq_exist = EDoc->GetCTFreq(); Max_Freq_ID = EDoc->GetDocID();
									}
									EDoc = EDoc->Getnext();
								}
								while (Max_Freq_exist != 0) {
									for (EDoc = RDocs; EDoc != nullptr; EDoc = EDoc->Getnext()) {
										if (ADoc->GetQueryTerms() == EDoc->GetQueryTerms() && EDoc->GetCTFreq() == Max_Freq_exist) {
											Equal_Freq_Docs++;
										}
									}
									while (Equal_Freq_Docs>0) {
										if (Equal_Freq_Docs == 1) {
											for (EDoc = RDocs; EDoc != nullptr; EDoc = EDoc->Getnext()) {
												if (ADoc->GetQueryTerms() == EDoc->GetQueryTerms() && EDoc->GetCTFreq() == Max_Freq_exist) {
													DocPrint(EDoc->GetDocID(), file);
													break;
												}
											}
											Equal_Freq_Docs--;
											p++;
										}else if (Equal_Freq_Docs == 2) {
											int nd = 0;
											for (EDoc = RDocs; EDoc != nullptr; EDoc = EDoc->Getnext()) {
												if (ADoc->GetQueryTerms() == EDoc->GetQueryTerms() && EDoc->GetCTFreq() == Max_Freq_exist && EDoc->GetDocID() != Max_Freq_ID) {
													nd = EDoc->GetDocID();
												}
											}
											string s1, s2;
											ifstream fin;
											ifstream fin2;
											fin.open(file);
											fin2.open(file);
											if (fin.is_open() != true) {
												std::cout << "File didnot open. \n";
											}
											for (int i = 0; i < Max_Freq_ID; i++) {
												getline(fin, s1, '\n');
											}
											for (int i = 0; i < nd; i++) {
												getline(fin2, s2, '\n');
											}
											int k = 0;
											while (true) {
												if (s1[k] < s2[k]) {
													cout << s1 << "\n";
													cout << s2 << "\n";
													break;
												}
												else if (s1[k] > s2[k]) {
													cout << s2 << "\n";
													cout << s1 << "\n";
													break;
												}
												else if (s1[k] == s2[k]) {
													k++;
												}
											}
											Equal_Freq_Docs= Equal_Freq_Docs -2;
											p = p + 2;
										}
										else if (Equal_Freq_Docs > 2) {
											string word[10]{}, tswap;
											ifstream fin;

											int z = 0;
											for (EDoc = RDocs; EDoc != nullptr; EDoc = EDoc->Getnext()) {
												if (ADoc->GetQueryTerms() == EDoc->GetQueryTerms() && EDoc->GetCTFreq() == Max_Freq_exist) {
													fin.open(file);
													if (fin.is_open() != true) {
														std::cout << "File didnot open. \n";
													}
													for (int w = 0; w < EDoc->GetDocID(); w++) {
														getline(fin, word[z], '\n');
													}

													fin.close();
													z++;
												}
											}
											for (int ix = 0; ix < Equal_Freq_Docs; ix++) {
												for (int jx = ix + 1; jx < Equal_Freq_Docs; jx++) {
													z = 0;
													while (true) {
														if ((word[ix][z] == 32 || (word[ix][z] > 64 && word[ix][z] < 91) || (word[ix][z] > 96 && word[ix][z] < 123)) && (word[jx][z] == 32 || (word[jx][z] > 64 && word[jx][z] < 91) || (word[jx][z] > 96 && word[jx][z] < 123))) {
															if (word[ix][z] < word[jx][z]) { break; }
															else if (word[ix][z] > word[jx][z]) {
																tswap = word[ix];
																word[ix] = word[jx];
																word[jx] = tswap;
																break;
															}
															else {
																z++;
															}
														}
														else {
															break;
														}
													}
												}
											}
											for (z = 0; word[z] != ""; z++) {
												cout << word[z] << "\n";
												Equal_Freq_Docs--;
												p++;
											}

											if (p == Tdocs) { return 0; }
										}
										if (p == Tdocs) { return 0; }
									}
									Max_Freq_exist--;
								}
							}
						}
						if (p == Tdocs) { return 0; }
						CDoc = CDoc->Getnext();
					}
					if (Cflag == 0) {
						DocPrint(ADoc->GetDocID(), file);
						p++;
						Max_term_exist--;
					}
					if (p == Tdocs) { return 0; }
				}

				if (p == Tdocs) { return 0; }
			}
			ADoc = ADoc->Getnext();
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

//Function to remove any index words from an array of strings
void Search_Engine::remove_Index_word(string* words, int size) {
	string testword;
	Term_Info* ptr = Index->Getnext();

	while (true) {
		if (ptr->GetTerm() != "\0") {
			testword = ptr->GetTerm();
		}
		for (int j = 0; j < size; j++) {
			if (testword == words[j]) {
				words[j] = "0";
			}
		}
		if (ptr->Getnext() != nullptr) {
			ptr = ptr->Getnext();
		}
		else {
			ptr = nullptr;
			break;
		}
	}
};

//Function to remove any unwanted Delimiters from a string
//Note:
//Can be modified to remove any unwanted stopper words from the string (Documemt topic)
void Search_Engine::remove_char_from_word(string& word, char rp, char rb) {
	string temp;
	for (int i = 0; i < word.size(); ++i) {
		if (word[i] != rp && word[i]!= rb) {
			temp = temp + word[i];
		}
		if (word[i] == rb) {
			temp = "0";
		}
	}
	word = temp;
	temp = "\0";
};

//Function to add a new document topic to the file(database) 
void Search_Engine::Add_Doc_to_Index(string& file) {
	string newtopic, prevText, Fulltext, brk = " . \n";
	cout << "Enter the Document Heading: \n";
	getline(cin, newtopic);

	ifstream fin;
	fin.open(file);
	if (fin.is_open() != true) {
		std::cout << "File didnot open. \n";
	}

	getline(fin, prevText, '\0');
	if (prevText != "" && newtopic != "") {
		Fulltext = prevText + newtopic + brk;
	}
	else if (prevText == "" && newtopic != "") {
		Fulltext = newtopic + brk;
	}

	if (newtopic != "") {
		this->TotalDocs++;
		ofstream myfile;
		myfile.open(file);
		myfile << Fulltext;
		myfile.close();
		myfile.open("Backup.txt");
		myfile << Fulltext;
		myfile.close();
	}

	if (this->Index->GetTerm()!="\0") {
		UpdateIndex(newtopic,file);
	}
	else if (this->Index->GetTerm() == "\0") {
		IndexGenerator(file);
	}

};

//Function to update the index when a new documnet topic is added while the program is running
void Search_Engine::UpdateIndex(string& newtopic, string& file) {
	string word[20]{}; int i, j, words; i = j = words = 0;
	ifstream fin;
	string temp;

	for (;; i++) {
		if (newtopic[i] != '\n' && newtopic[i] != '\0' && newtopic[i] != ' ') {
			temp = temp + newtopic[i];
		}
		if (newtopic[i] == '\n' || newtopic[i] == ' ') {
			if (temp != "") {
				word[j] = temp;
				j++;
			}
			temp = "";
		}
		else if (newtopic[i] == '\0') {
			if (temp != "") {
				word[j] = temp;
				j++;
			}
			temp = "\0";
			break;
		}
	}

	remove_char_from_word(word[words], '\n', '.');
	
	words = i = 0;
	Term_Info* ptr = Index->Getnext();

	while(true) {
		temp = ptr->GetTerm();
		if (temp != "\0") {
			i = ptr->count(temp, newtopic);
			if (i != 0) {
				ptr->GetDocs()->insertAtEnd();
				Doc_Info* dax = ptr->GetDocs()->Gettail()->Getprev()->GetData();
				dax->SetDocID(this->TotalDocs); dax->SetTFreq(i);
			}
		}
		if (ptr->Getnext() != nullptr) {
			ptr = ptr->Getnext();
		}
		else {
			ptr = nullptr;
			break;
		}
	}

	remove_Index_word(word, j);

	for (; i < j; i++) {
		if (word[i] != "0") {
			Index->SetTerm(word[i]);
			Index->Analyze(file);
			Index = new Term_Info(word[i], Index);
		}
	}

	Index->SetTerm("New word");
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
	if (fin.is_open() != true) {
		std::cout << "File didnot open. \n";
	}

	int T;
	T = 0;

	while (true) {
		getline(fin, topic, '\n');

		if (topic != "") {
			T++;
		}
		else if (topic == "") {
			return T;
		}
	}
};

//Getters and Setters
int Search_Engine::GetTDocs() {
	return this->TotalDocs;
};

void Search_Engine::SetTDocs(int total) {
	this->TotalDocs = total;
};

//Function to print topic of a single document with DocID = DocNo
void Search_Engine::DocPrint(int DocNo, string& file) {
	std::string topic;
	ifstream fin;

	fin.open(file);
	if (fin.is_open() != true) {
		std::cout << "File didnot open. \n";
	}

	for (int i = 0; i < DocNo; i++) {
		getline(fin, topic, '\n');
	}

	if (topic != "" && topic != " ") {
		cout << topic << "\n";
	}
};

//Function to print All information about the index words and the occurance in each topic
void Search_Engine::IndexPrint() {
	Term_Info* term = this->Index->Getnext();
	for (; term != nullptr; term = term->Getnext()) {
		cout << "<" << term->GetTerm() << ">\n";
		term->print();
		cout << "\n";
	}
};

//Destructor
Search_Engine::~Search_Engine() {
	if (Index->Getnext() != nullptr) {
		Term_Info* p = Index->Getnext();
		while (p != nullptr) {
			Term_Info* del = p;
			p = p->Getnext();
			delete del;
			del = nullptr;
		}
	}
};
