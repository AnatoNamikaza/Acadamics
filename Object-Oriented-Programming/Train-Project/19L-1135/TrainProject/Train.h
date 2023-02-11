#ifndef TRAINPROJECT_TRAIN_H
#define TRAINPROJECT_TRAIN_H

#include "Bogie.h"

class Train {

	static bool arrival;
	Bogie **engine;

public:

	Train();

	void drawTrain(sf::RenderWindow &, sf::Font &);

	void addBogie(sf::RenderWindow &, sf::Font &, tgui::Gui &);

	void removeBogie(sf::RenderWindow &, sf::Font &, tgui::Gui &);

	void printTrain(sf::RenderWindow &, sf::Font &, tgui::Gui &);

	void printBogie(sf::RenderWindow &, sf::Font &, tgui::Gui &);

	bool SearchBoogie(int) const;

	Bogie *getBogie(int) const;

	void addPassengersToBogie(sf::RenderWindow &, sf::Font &, tgui::Gui &);

//	static void printWarningMessage(sf::RenderWindow &, tgui::Gui &, tgui::Theme &, std::shared_ptr<tgui::ChildWindow> &, const std::string &, int);

	~Train();

protected:
	static int noOfBogies;
};


#endif
