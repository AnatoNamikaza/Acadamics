

#include "Term_Info.h"

//Function that returns an iterator to the first node(Doc_Info object) in the list.
typename DList<Doc_Info>::Iterator Term_Info::begin() {
	return docs.begin();
}

//Function that returns an iterator to the last node(Doc_Info object) in the list.
typename DList<Doc_Info>::Iterator Term_Info::end() {
	return docs.end();
}

Term_Info::Term_Info() : docs() {

}

Term_Info::Term_Info(const Term_Info &t) {
	keyTerm = t.keyTerm;
	docs = t.docs;
}

//Function that takes a unique term, a string array of filenames and the size of the string array.
void Term_Info::insert(const std::string &term, std::string *fileNames, int n) {

	keyTerm = term;

	std::ifstream fin;
	std::string temp, null;

	bool termFound = false;		//Boolean for checking whether the term exists in the file or not.

	for ( int i = 0; i < n; i++ ){	//Loop for opening all files in the filenames array.

		fin.open(fileNames[i]);
		Doc_Info d;

		for ( ; !fin.eof(); ){
			fin >> temp;	//read a string from the opened file
			if ( !termFound && temp == keyTerm ){
				d.docID = getDocID(fileNames[i]);	//Sets the docID to the number in the filename.
																			//For example, if the filename is "Doc5", the docID will be 5.
				d.termFrequency = 1;
				termFound = true;
				temp = null;
				continue;
			}

			if ( termFound && temp == keyTerm )	//Keep incrementing termFrequency if multiple occurrences of term in opened file.
				d.termFrequency++;

			temp = null;
		}

		if ( termFound )
			docs.insertAtEnd(d);	//Insert the Doc_Info object at the end of docs list if term was found in opened file.

		termFound = false;
		fin.close();	//Close the file.
		temp = null;

	}

}

bool Term_Info::operator<(const Term_Info &t) {
	return keyTerm < t.keyTerm;
}

bool Term_Info::operator>(const Term_Info &t) {
	return keyTerm > t.keyTerm;
}

std::ostream& operator<<(std::ostream &out, const Term_Info &t) {
	out << t.keyTerm << '\n';
	return out;
}

std::ofstream& operator<<(std::ofstream &out, const Term_Info &t) {
	out << t.keyTerm << '\n';
	return out;
}

int Term_Info::getDocID(const std::string &fileName) {
	int index = fileName.find('.') - 1;
	std::string tempDocID, docID;

	for ( ; index >= 0 && fileName[index] >= 48 && fileName[index] <= 57; index-- )
		tempDocID += fileName[index];

	for ( int i = tempDocID.size() - 1; i >= 0; i-- )
		docID += tempDocID[i];

	return std::stoi(docID);
}

Term_Info::~Term_Info() {

	for ( ; !docs.empty(); )	//Keep deleting Doc_Info objects from docs until it is empty.
		docs.DeleteAtEnd();

}