

#include "Search_Engine.h"
#include "HashTable.cpp"

//Struct used for ranking the documents
struct ranking {
	int     docID;
	int     docFrequency;
	int     CTF;
};

//Default constructor of Search_Engine.
Search_Engine::Search_Engine() : size(0), index(11) {}

//Function for creating the index of search engine.
void Search_Engine::create_Index(std::string *docs, int n) {

	for ( int i = 0; i < n; i++)
		add_Doc_to_Index(docs[i]);

}

void Search_Engine::search(std::string &query) {

	DList<Term_Info> tempTerms;     //DList for storing Term_Info objects present in search query.
	auto *queryWords = new std::string[100];		//String array for storing the words in the search query.
	int queryWordsSize = 0, queryWordsIdx = 0;
	char *tempQuery = new char[50];		//Char * for storing a word in the search query.

	//Loop for extracting every word in the search query and adding every word to the queryWords string array.
	for ( int i = 0, j = 0, k = 0; i < query.size(); i++ ){

		j = 0;

		for ( ; query[i] != ' ' && i < query.size(); )
			tempQuery[j++] = query[i++];		//Continue adding characters in char* till space found.

		tempQuery[j] = '\0';		//Terminate the char* will null character.

		queryWords[k++] = tempQuery;		//Insert the word in queryWords string array and increment its index.
		queryWordsSize++;

	}

	delete[] tempQuery, tempQuery = nullptr;

	//Loop for adding every term that exists in index and is in the query, in the temporary search engine object.
	Term_Info *tempTerm = nullptr;
	for ( int i = 0; i < queryWordsSize; i++ ){
		tempTerm = index.get(queryWords[i]);

		if ( tempTerm )
			tempTerms.push_back(*tempTerm);
	}

	//No point in continuing if no word in the query exists in the index.
	if ( tempTerms.size > 0 ){

		DList<Doc_Info> queryDocs;  //List that contains the docs(Doc_IDs) that the query terms are present in.
		bool isUnique = false;

		//Loop for inserting all Doc_Info objects in the first Term_Info object of temporary search engine.
		DList<Term_Info>::Iterator itr = tempTerms.begin();
		DList<Doc_Info>::Iterator l1Itr = (*itr).begin(), l2Itr = l1Itr;
		for ( int i = 0; i < (*itr).docs.size; i++, l1Itr++ )
			queryDocs.insertAtEnd(*l1Itr);

		itr++;
		//l2Itr iterates over the Doc_Info objects of queryDocs
		if ( !itr.isNull() ){
			l1Itr = (*itr).begin();
			l2Itr = queryDocs.begin();
		}

		//Loop for taking union of Doc_Info lists
		for ( int i = 0; i < tempTerms.size - 1; i++ ){

			for ( int k = 0; !itr.isNull() && k < (*itr).docs.size; k++ ){

				for ( int l = 0; l < queryDocs.size; l++, l2Itr++ ){
					if ( (*l1Itr).docID == (*l2Itr).docID ){	//if a docID exists in both queryDocs and (*l1Itr), then it's not unique.
						isUnique = false;
						break;
					}

					else
						isUnique = true;
				}

				if ( isUnique )	//Insert the Doc_Info object if it's ID doesn't match with any Doc_Info object in queryDocs.
					queryDocs.insertAtEnd(*l1Itr);

				l1Itr++;
				l2Itr = queryDocs.begin();
				isUnique = false;

			}

			itr++;
			if ( !itr.isNull() ){
				l1Itr = (*itr).begin();
				l2Itr = queryDocs.begin();
			}

		}

		//Ranking of documents starts here
		//Rule 1

		//Create a ranking struct object with the same size as queryDocs.
		auto *r = new ranking[queryDocs.size];

		for ( int i = 0; i < queryDocs.size; i++ ){
			r[i].docID = queryDocs[i].docID;
			r[i].docFrequency = 0;
			r[i].CTF = 0;
		}

		queryWordsIdx = 0;
		itr = tempTerms.begin();
		l1Itr = (*itr).begin();

		//Loop for setting the docFrequency(no of terms a doc contains) and collective term frequency.
		for ( int i = 0; i < tempTerms.size; i++ ){
			for ( int j = 0; !itr.isNull() && j < (*itr).docs.size; j++, l1Itr++ ) {
				for ( int k = 0; k < queryDocs.size; k++ ) {
					if (r[k].docID == (*l1Itr).docID) {
						r[k].CTF += (*l1Itr).termFrequency;
						r[k].docFrequency++;
					}
				}
			}

			itr++;
			if ( !itr.isNull() )
				if ( (*itr).docs.size > 0 )	//If next Term_Info object has >= 1 object, set l1Itr, otherwise don't.
					l1Itr = (*itr).begin();
		}

		//Loop that that sorts the ranking object according to Rule1.
		for ( int i = 0; i < queryDocs.size; i++ ){
			int maxIdx = i, max = 0;
			for ( int j = i; j < queryDocs.size; j++ ){
				if ( r[j].docFrequency > max ){
					max = r[j].docFrequency;
					maxIdx = j;
				}
			}

			ranking tempRanking = r[i];
			r[i] = r[maxIdx];
			r[maxIdx] = tempRanking;
		}

		//Loop that that sorts the ranking object according to Rule2.
		for ( int i = 0; i < queryDocs.size - 1; i++ ){
			if ( r[i].docFrequency == r[i + 1].docFrequency ){
				if ( r[i].CTF < r[i + 1].CTF ){
					ranking tempRanking = r[i];
					r[i] = r[i + 1];
					r[i + 1] = tempRanking;
				}
			}
		}

		//Loop that that sorts the ranking object according to Rule3.
		for ( int i = 0; i < queryDocs.size - 1; i++ ){
			if ( r[i].docFrequency == r[i + 1].docFrequency && r[i].CTF == r[i + 1].CTF ){
				if ( r[i].docID > r[i + 1].docID ){
					ranking tempRanking = r[i];
					r[i] = r[i + 1];
					r[i + 1] = tempRanking;
				}
			}
		}

		std::cout << "Search query: " << query << "\nResults\n";
		for ( int i = 0; i < queryDocs.size; i++ )
			std::cout << "Doc " << r[i].docID << '\n';

		delete[] r;
	}

	else
		std::cerr << "No documents match the query term!\n";

	delete[] queryWords;

}

void Search_Engine::add_Doc_to_Index(std::string &fileName) {

	std::ifstream fin(fileName);
	std::string temp;
	bool found = false;

	if ( fin ){

		int uniqueElems = 0;
		std::string *list = uniqueTerms(&fileName, 1, uniqueElems);

		for ( int i = 0; i < uniqueElems; i++ ){

			temp = list[i];
			found = false;

			if ( index.get(temp) )
				found = true;

			if ( found ){
				Term_Info t;
				t.insert(temp, &fileName, 1);

				Term_Info *tempTerm = index.get(temp);
				DList<Doc_Info>::Iterator i2 = t.docs.begin();
				(*tempTerm).docs.insertAtEnd(*i2);
			}

			else {
				Term_Info t;
				t.insert(temp, &fileName, 1);
				index.insert(t);
				size++;
			}
		}

		delete[] list;
		fin.close();

	}

	else
		std::cerr << "File " << '"' << fileName << '"'<< " not found!\n";

}

void Search_Engine::add_Doc_to_Index(const char *fileName) {

	std::ifstream fin(fileName);
	std::string temp, tempFilename(fileName);
	bool found = false;

	if ( fin ){

		int uniqueElems = 0;
		std::string *list = uniqueTerms(&tempFilename, 1, uniqueElems);

		for ( int i = 0; i < uniqueElems; i++ ){

			temp = list[i];
			found = false;

			if ( index.get(temp) )
				found = true;

			if ( found ){
				Term_Info t;
				t.insert(temp, &tempFilename, 1);

				Term_Info *tempTerm = index.get(temp);
				DList<Doc_Info>::Iterator i2 = t.docs.begin();
				(*tempTerm).docs.insertAtEnd(*i2);
			}

			else {
				Term_Info t;
				t.insert(temp, &tempFilename, 1);
				index.insert(t);
				size++;
			}
		}

		fin.close();
	}

	else
		std::cerr << "File " << '"' << fileName << '"'<< " not found!\n";

}

//Function that takes a string array and inserts every word in the fileName starting from the passed idx.
void Search_Engine::populate(std::string *list, int &idx, const std::string &fileName) {
	std::ifstream fin(fileName);

	if ( fin ) {
		for ( ; !fin.eof(); )
			fin >> list[idx++];

		fin.close();
	}
	else
		std::cerr << "File " << '"' << fileName << '"' << " not found!\n";
}

//Function that returns a string array containing the unique elements extracted from the files in the filenames string array.
std::string * Search_Engine::uniqueTerms(std::string *docs, int n, int &uniqueElems) {
	auto *tempList = new std::string[1000];
	int idx = 0;

	for ( int i = 0; i < n; i++ )
		populate(tempList, idx, docs[i]);

	std::string null;

	//Loop the removes the duplicates terms from tempList and calculate the number of unique terms.
	for ( int i = 0; i < idx; i++ ){

		//Loop for setting any duplicate string to null.
		for ( int j = i + 1; j < idx; j++ ) {
			if ( tempList[j] == tempList[i] )
				tempList[j] = null;
		}

		if ( !tempList[i].empty() )
			uniqueElems++;

	}

	auto *list = new std::string[uniqueElems];

	//Loop for adding all non-null strings from tempList in the list.
	for ( int i = 0, j = 0; i < idx; i++ )
		if ( !tempList[i].empty() )
			list[j++] = tempList[i];

	delete[] tempList;
	return list;
}