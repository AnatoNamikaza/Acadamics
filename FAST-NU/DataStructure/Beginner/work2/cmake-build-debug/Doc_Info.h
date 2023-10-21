

#ifndef DSA1_DOC_INFO_H
#define DSA1_DOC_INFO_H


class Doc_Info {

	int docID, termFrequency;

public:

	Doc_Info();

	friend class Term_Info;

	friend class Search_Engine;

};


#endif
