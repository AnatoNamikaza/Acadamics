/*
  Main function for testing *Response classes.

  Takes a file containing <keywords, responses, and happy/sad indicators> and 
  an integer for the number of input strings as arguments.

  YOU MUST NOT CHANGE ANYTHING IN THIS FILE (unless we say otherwise)

  Note that you should still read through this file to understand how your 
  classes will be used.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "response.h"

using namespace std;

void usage(int argc, char** argv);
void load_file(vector <Response*> &respList, char* fileName);
void get_input(vector <Response*> respList, char* msgFile, char* outFile);
void respondToInput(vector <Response*> respList, string input, 
                    ofstream& output);
void cleanup(vector <Response*> respList);

int main(int argc, char** argv)
{
    // This is like an array of Response pointers
    // but it's a vector, so its size is dynamically managed
    vector <Response*> responseList;

    // Verify given arguments
    usage(argc, argv);

    // Load keywords and responses from file
    load_file(responseList, argv[1]);

    // Execute the input / response runs
    get_input(responseList, argv[2], argv[3]);

    cleanup(responseList);

    return 0;
}

void usage(int argc, char** argv)
{
    if(argc < 4) {
        cout << "usage: " << argv[0] 
             << " <keyword-response file> <message file> <output file>" 
             << endl;
        exit(EXIT_FAILURE);
    }
}

void load_file(vector <Response*>& respList, char* fileName)
{
    // Open file using ifstream - input file stream class 
    ifstream inFile;
    // Default argument to open() is in - i.e., equivalent call would
    // be inFile.open(fileName, ifstream::in);
    inFile.open(fileName);

    // Read the file
    string word;
    while(inFile >> word) {
        // The first word is the keyword - this is what the user will enter
        string keyword = word;

        // The second word is the response - this is what should be shown 
        // when the user enters the 'keyword'
        string response;
        inFile >> response;
       
        // This is the happiness indicator - 
        // 1 -> happy
        // 0 -> neutral
        // -1 -> sad
        int happy;
        inFile >> word;
        // Convert string to an int using stringstream
        stringstream tmp(word);
        tmp >> happy;
        
        // Determine what class to use for each keyword-response pair
        if (happy == 0) {
            // For neutral response, create a regular Response object
            Response *r = new Response(keyword, response);
            respList.push_back(r);
        } else if (happy > 0) {
            // For happy response, create a HappyResponse object
            HappyResponse *hr = new HappyResponse(keyword, response);
            respList.push_back(hr);
        } else {
            // For angry response, create a AngryResponse object
            AngryResponse *ar = new AngryResponse(keyword, response);
            respList.push_back(ar);
        }
    }
}

void get_input(vector <Response*> respList, char* msgFileName, 
               char* outFileName)
{
    // Another way to open a file - using a constructor
    ifstream msgFile(msgFileName);
    ofstream outFile(outFileName);

    string line;
    while(getline(msgFile, line)) {
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        respondToInput(respList, line, outFile);
    } 

    msgFile.close();
    outFile.close();
}

void respondToInput(vector <Response*> respList, string input, 
                    ofstream& output)
{
    bool found = false;
    for (unsigned int i = 0; i < respList.size(); i++) {

        // Notice that checkAndRespond accepts ostream& not ofstream&
        // However, this works because ofstream derives from ostream, 
        // as they both involve output to something - OOP at work!
        bool exists = respList[i]->checkAndRespond(input, output);
        if(exists) {
            found = true;
        }
    }
    if(!found) {
        output << "I don't understand what you are saying\n" << endl;
    }
}


void cleanup(vector <Response*> respList)
{
    for(unsigned int i = 0; i < respList.size(); i++) {
        delete respList[i];
    }
}
