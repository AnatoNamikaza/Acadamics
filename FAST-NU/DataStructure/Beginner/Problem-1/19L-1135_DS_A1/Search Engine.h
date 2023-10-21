#pragma once
#include "Term_Info.h"
#include "Doc_Data.h"
#include <fstream>

class Search_Engine {
private:
	Term_Info* Index; int TotalDocs;
public:
	Search_Engine();
	Search_Engine(string& file);
	void IndexGenerator(string& file);
	void Search_Documents(string& file);
	void Ranked_list(string* QueryWords, string& file);
	int Print_Ranked_list(Doc_Data* RDocs, string& file, int Tdocs);
	void Add_Doc_to_Index(string& file);
	void UpdateIndex(string& newtopic, string& file);
	void remove_Duplicate_word(string* words, int size);
	void remove_Index_word(string* words, int size);
	void remove_char_from_word(string& file, char rp, char rb);
	void clearFile(string& file);
	void clearBackup();
	int FindTDocs(string& file);
	int GetTDocs();
	void SetTDocs(int total);
	void DocPrint(int DocNo, string& file);
	void IndexPrint();
	~Search_Engine();
};
