
#ifndef DSA1_SEARCH_ENGINE_H
#define DSA1_SEARCH_ENGINE_H

#include "Term_Info.h"
#include "HashTable.h"

class Search_Engine {

	HashTable<Term_Info> index;

	int size;

public:

	Search_Engine();

	void create_Index(std::string *, int);

	void search(std::string &);

	void add_Doc_to_Index(std::string &);

	void add_Doc_to_Index(const char *);

	void populate(std::string *, int &, const std::string &);

	std::string* uniqueTerms(std::string *, int, int &);

};


#endif