#pragma once
#include "Bogie.h"
#include <string.h>

class Train {
private:
	Bogie *engine;
	Bogie *Bogies;
	int TBogies;
	float LengthX, LengthY;
public:
	Train();
	void TrainMaker(int x);
	void drawTrain(sf::RenderWindow &, tgui::Gui &);
	bool addBogie();
	void removeBogie(sf::RenderWindow &, tgui::Gui &);
	void printTrain();
	bool SearchBogie(int ID);
	void ViewBogie(sf::RenderWindow &, tgui::Gui &);
	void addPassengers();
	void removePassengers();
	void viewPassengers();
	static bool compare(char* P1, char* P2);
	void DataExtraction();
	void DataSaving();
	void RecordSaving();
	~Train();
};
