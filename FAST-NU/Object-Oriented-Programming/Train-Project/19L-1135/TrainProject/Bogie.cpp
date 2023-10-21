#include "Bogie.h"
#include "Adult.h"
#include "Kid.h"

Bogie::Bogie() :
		Bogie_ID(0), endCoord(), next(nullptr), Adults(nullptr), Kids(nullptr), familyName(""),
        noOfKids(0), noOfAdults(0) { }


Bogie::Bogie(int ID) :
		Bogie_ID(ID), endCoord(), next(nullptr), Adults(nullptr), Kids(nullptr), familyName(""),
        noOfKids(0), noOfAdults(0) { }


void Bogie::AddPassengers(Person **adults, Person **kids) {

	Adults = new Person*[noOfAdults];
	for ( int i = 0; i < noOfAdults; i++ )
		Adults[i] = adults[i];

	Kids = new Person*[noOfKids];
	for ( int i = 0; i < noOfAdults; i++ )
		Kids[i] = kids[i];

}

void Bogie::Print() {
	for ( int i = 0; i < noOfAdults; i++ )
		Adults[i]->print();

	for ( int i = 0; i < noOfKids; i++ )
		Kids[i]->print();
}

void Bogie::setBogieID(int ID) {
	Bogie_ID = ID;
}

int Bogie::getBogieID() const {
	return Bogie_ID;
}

void Bogie::setEndCoord(const sf::Vector2f &coord) {
	endCoord = coord;
}

const sf::Vector2f &Bogie::getEndCoord() const {
	return endCoord;
}

void Bogie::setNext(Bogie **b) {
	next = b;
}

Bogie **Bogie::getNext() const {
	return next;
}

void Bogie::drawEngine(sf::RenderWindow &window, Bogie **train, bool &arrival) {

	sf::Texture engineTexture = sf::Texture();
	engineTexture.loadFromFile("TrainEngine.jpg");
	engineTexture.setSmooth(true);

	sf::RectangleShape engine(sf::Vector2f(0.18301611 * window.getSize().x, 0.1953125 * window.getSize().y));
	if ( arrival ){
		engine.setPosition(window.getSize().x, window.getSize().y * 0.15494792);
		engine.setTexture(&engineTexture);

		while( engine.getPosition().x >= window.getSize().x * 0.014641288 ){
			engine.move(-0.020f * window.getSize().x, 0.0f);
			window.clear(sf::Color::White);
			window.draw(engine);
			window.display();
		}
		arrival = false;
	}

	else {
		engine.setPosition(window.getSize().x * 0.014641288, window.getSize().y * 0.15494792);
		engine.setTexture(&engineTexture);
	}

	train[0]->setEndCoord(sf::Vector2f(engine.getPosition().x + engine.getSize().x, engine.getPosition().y));

	window.draw(engine);


}

void Bogie::drawBoogie(sf::RenderWindow &window, Bogie **train, int bogieNum) {

	sf::Texture texture;
	texture.loadFromFile("Bogie.jpg");
	texture.setSmooth(true);

	sf::RectangleShape bogie(sf::Vector2f(0.18301611 * window.getSize().x, 0.1953125 * window.getSize().y));
	bogie.setPosition(train[bogieNum - 1]->getEndCoord().x, train[bogieNum - 1]->getEndCoord().y);
	bogie.setTexture(&texture);

	train[bogieNum]->setEndCoord(sf::Vector2f(train[bogieNum - 1]->getEndCoord().x + bogie.getSize().x, train[bogieNum - 1]->getEndCoord().y));

	window.draw(bogie);

}

void Bogie::setNoOfAdults(char a) {
	noOfAdults = a;
}

char Bogie::getNoOfAdults() {
	return noOfAdults;
}

void Bogie::setNoOfKids(char k) {
	noOfKids = k;
}

char Bogie::getNoOfKids() {
	return noOfKids;
}

void Bogie::setFamilyName(const std::string &fn) {
	familyName.assign(fn);
}

const std::string& Bogie::getFamilyName() {
	return familyName;
}

const Person *Bogie::getKid(int i) {
	return Kids[i];
}

const Person *Bogie::getAdult(int i) {
	return Adults[i];
}

Bogie::~Bogie() {
	next = nullptr;
}