

#ifndef DSA1_TERM_INFO_H
#define DSA1_TERM_INFO_H

#include "string"
#include <fstream>
#include "DList.h"
#include "Doc_Info.h"
#include "DList.cpp"
#include "DNode.cpp"

class Term_Info {

	std::string         keyTerm;

	DList<Doc_Info>     docs;

public:

	DList<Doc_Info>::Iterator begin();

	DList<Doc_Info>::Iterator end();

	Term_Info();

	Term_Info(const Term_Info &);

	void insert(const std::string &, std::string *, int);

	bool operator < (const Term_Info &);

	bool operator > (const Term_Info &);

	friend std::ostream& operator << (std::ostream &, const Term_Info &);

	friend std::ofstream& operator << (std::ofstream &, const Term_Info &);

	static int getDocID(const std::string &);

	~Term_Info();

	friend class Search_Engine;

	template <class T>
	friend class HashTable;

};


#endif
