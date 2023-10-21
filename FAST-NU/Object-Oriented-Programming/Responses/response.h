/*
  Header file with class definitions for Response, AngryReponse, and 
  HappyResponse

  Note that we don't use `using namespace std;` incase some other file which 
  includes this header doesn't want to use all of the std namespace.
*/

#include <iostream>
#include <string>

/* 
  Word class - this is used to keep track of the keywrod word for the Response
  class, so that it can more easily determine its all upper case and all lower 
  case equivalents
 */
class Word {
    std::string theWord;
public:
    // This is a constructor for the Word class - whenever you create a new
    // object of type Word, you can instantiate 'theWord' with 'newWord'
    // Constructor has no return value and has the same name as the class
    Word(std::string newWord) { theWord = newWord; }
    std::string normal() { return theWord; }
    std::string upper();
    std::string lower();
};

/*
  Base class with common functionality
*/
class Response {
protected:
    // These fields keep track of the word to listen for and the response for 
    // that word
    // These are protectd, so they can be inherited by AngryResponse and 
    // HappyResponse classes
    Word keyword;
    std::string response;

private:
    // This method insert's the object's response into the given output stream
    virtual void respond(std::ostream& toWhere);

public:
    // This is a constructor which creates a new object to listen for the 
    // given keyword and respond with the given response
    // keyword(str1), response(str2) is another way of initializing 'keyword' 
    // and 'response' to 'str1' and 'str2', respectively
    Response(std::string str1, std::string str2) : keyword(str1), response(str2)
    {} 

    // This is a destructor which does not have much to do
    virtual ~Response() {}

    // If this object's keyword is found in the message, then this method 
    // inserts this object's response into the given stream.
    bool checkAndRespond(const std::string& inMessage, std::ostream& toWhere);

    // This is a utility function to print the object's keyword and response
    void printKeyword() { std::cout << keyword.normal() << " " << response 
                                    << std::endl; }
};


// This class inherits the Response class
class AngryResponse : public Response {
    // Overide respond method for angry responses via polymorphism
    void respond(std::ostream& toWhere);

public:
    // Simple constructor which just calls the parent's constructor
    // That is, AngryResponse also has members 'keyword' and 'response'
    // These variables are initialized using str1 and str2
    AngryResponse(std::string str1, std::string str2) : Response(str1, str2) {}
};

class HappyResponse : public Response {
    // Overide respond method for angry responses via polymorphism
    void respond(std::ostream& toWhere);

public:
    // Simple constructor which just calls the parent's constructor
    // That is, AngryResponse also has members 'keyword' and 'response'
    // These variables are initialized using str1 and str2
    HappyResponse(std::string str1, std::string str2) : Response(str1, str2) {}
};

// TODO:
// Implement the HappyResponse class definition
// This will look somewhat similar to AngryResponse class
