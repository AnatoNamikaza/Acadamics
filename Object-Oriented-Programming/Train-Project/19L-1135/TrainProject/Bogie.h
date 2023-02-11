
#ifndef TRAINPROJECT_BOGIE_H
#define TRAINPROJECT_BOGIE_H

#include <fstream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Person.h"

class Bogie {

	char noOfKids, noOfAdults;

	int Bogie_ID;

	sf::Vector2f endCoord;

	Bogie **next;

	Person **Adults;
	Person **Kids;

	std::string familyName;

public:

	Bogie();

	Bogie(int);

	void AddPassengers(Person **, Person **);

//	bool readPassengersFromFile();

	void Print();

	void setBogieID(int);

	int getBogieID() const;

	void setEndCoord(const sf::Vector2f &);

	const sf::Vector2f &getEndCoord() const;

	void setNext(Bogie **);

	Bogie **getNext() const;

	static void drawEngine(sf::RenderWindow &, Bogie **, bool &);

	static void drawBoogie(sf::RenderWindow &, Bogie **, int);

	void setNoOfAdults(char);

	char getNoOfAdults();

	void setNoOfKids(char);

	char getNoOfKids();

	void setFamilyName(const std::string &);

	const std::string &getFamilyName();

	const Person *getKid(int);

	const Person *getAdult(int);

	~Bogie();

protected:

};


#endif