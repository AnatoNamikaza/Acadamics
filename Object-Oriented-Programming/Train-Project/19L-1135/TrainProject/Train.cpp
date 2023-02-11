#include "Train.h"
#include "Adult.h"
#include "Kid.h"

bool Train::arrival = true;
int Train::noOfBogies = 0;

Train::Train() {
	engine = new Bogie*[++noOfBogies];
	engine[noOfBogies - 1] = new Bogie;
}

void Train::drawTrain(sf::RenderWindow &window, sf::Font &font) {

	for ( int i = 0; i < noOfBogies; i++ ){
		if ( i == 0 )
			Bogie::drawEngine(window, engine, arrival);

		else if ( i > 0 )
			Bogie::drawBoogie(window, engine, i);

	}

}

void Train::addBogie(sf::RenderWindow &window, sf::Font &font, tgui::Gui &gui) {

	int ID = 0;
	tgui::Theme theme{"/usr/share/tgui-0.8/gui-builder/themes/Black.txt"};
	tgui::Theme::setDefault(&theme);

	tgui::ChildWindow::Ptr child = tgui::ChildWindow::create("Bogie ID");
	child->setRenderer(theme.getRenderer("ChildWindow"));
	child->setSize("18%", "15%");
	child->setPosition("40%", "60%");
	gui.add(child);

	tgui::EditBox::Ptr bogieID = tgui::EditBox::create();
	bogieID->setSize({"70%", "20%"});
	bogieID->setPosition({"15%", "25%"});
	bogieID->setDefaultText("Enter ID of bogie to add");
	child->add(bogieID);
	bogieID->setFocused(true);

	// Create the Ok button
	tgui::Button::Ptr button = tgui::Button::create("Ok");
    button->setSize({"50%", "20%"});
    button->setPosition({"25%", "70%"});
    child->add(button);

	button->connect("pressed", [&](){
		if ( bogieID->getText() != std::string("") ){
			if ( ! SearchBoogie(std::stoi(bogieID->getText().toAnsiString())) ){
				ID = std::stoi(bogieID->getText().toAnsiString());
				child->close();
			}
			else {
				sf::Clock oneSecTimer;

				while ( oneSecTimer.getElapsedTime() < sf::seconds(1.0f) ){

					auto warningMessage = tgui::Label::create("Enter another bogie ID");
					warningMessage->setRenderer(theme.getRenderer("Label"));
					warningMessage->setPosition("8%", "45%");
					warningMessage->setTextSize(18);
					warningMessage->getRenderer()->setTextColor(sf::Color::Red);
					child->add(warningMessage);

					gui.draw();
					window.display();
				}

				bogieID->setText(""), bogieID->setFocused(true);
				gui.draw();
				window.display();
			}
		}
	});

	gui.draw();
	window.display();

	while( child->isFocused() ){
		sf::Event event = sf::Event();

		while (window.pollEvent(event))
			gui.handleEvent(event);

		window.clear(sf::Color::White);
		gui.draw();
		drawTrain(window, font);
		window.display();
	}

	//non-existing boogie. Need to check ID here because the ID from close button isn't validated.
	if ( !SearchBoogie(ID) ){

		auto **temp = new Bogie*[++noOfBogies];  //create new array with +1 boogies.

		for (int i = 0; i < noOfBogies - 1; i++)    //assigning previous addresses to temp
			temp[i] = engine[i];

		delete[] engine;
		engine = temp;
//		temp = nullptr;

		engine[noOfBogies - 1] = new Bogie;
		engine[noOfBogies - 1]->setBogieID(ID);

		//set next pointer.
		for ( int i = 0; i < noOfBogies - 1; i++ )
			engine[i]->setNext(&engine[i + 1]);

	}

	child->removeAllWidgets();
	gui.remove(child);
}

void Train::removeBogie(sf::RenderWindow &window, sf::Font &font, tgui::Gui &gui) {

	int ID = 0;
	tgui::Theme theme{"/usr/share/tgui-0.8/gui-builder/themes/Black.txt"};
	tgui::Theme::setDefault(&theme);

	auto child = tgui::ChildWindow::create("Bogie ID");
	child->setRenderer(theme.getRenderer("ChildWindow"));
	child->setSize("18%", "15%");
	child->setPosition("40%", "60%");
	gui.add(child);

	// Creating the input field for taking bogie ID
	auto bogieID = tgui::EditBox::create();
	bogieID->setSize({"80%", "20%"});
	bogieID->setPosition({"10%", "16.67%"});
	bogieID->setDefaultText("Enter ID of bogie to remove");
	child->add(bogieID);
	bogieID->setFocused(true);

	// Creating the Ok button
	auto button = tgui::Button::create("Ok");
	button->setSize({"50%", "16.67%"});
	button->setPosition({"25%", "70%"});
	child->add(button);

	button->connect("pressed", [&](){
		if ( bogieID->getText() != std::string("") ){
			int tempID = std::stoi(bogieID->getText().toAnsiString());
			if ( SearchBoogie(tempID) ){
				ID = std::stoi(bogieID->getText().toAnsiString());
				child->close();
			}
			else {
				sf::Clock oneSecTimer;

				while ( oneSecTimer.getElapsedTime() < sf::seconds(1.0f) ){

					auto warningMessage = tgui::Label::create("Boogie not found!");
					warningMessage->setRenderer(theme.getRenderer("Label"));
					warningMessage->setPosition("8%", "45%");
					warningMessage->setTextSize(18);
					warningMessage->getRenderer()->setTextColor(sf::Color::Red);
					child->add(warningMessage);

					gui.draw();
					window.display();

				}

				bogieID->setText("");
				bogieID->setFocused(true);
				gui.draw();
				window.display();
			}
		}
	});

	gui.draw();
	window.display();

	while( child->isFocused() ){
		sf::Event event = sf::Event();

		while (window.pollEvent(event))
			gui.handleEvent(event);

		window.clear(sf::Color::White);
		gui.draw();
		drawTrain(window, font);
		window.display();
	}

	if ( SearchBoogie(ID) && ID != 0 && noOfBogies > 1 ){

		for ( int i = 0; i < noOfBogies; i++ ){

			if ( engine[i]->getBogieID() == ID ){
				engine[i - 1]->setNext(engine[i]->getNext());
				delete engine[i];
				engine[i] = nullptr;

				for ( int j = i; j < noOfBogies - 1; j++ )
					engine[j] = engine[j + 1];

				break;
			}

		}

		noOfBogies--;
	}
}

void Train::printTrain(sf::RenderWindow &window, sf::Font &font, tgui::Gui &gui) {

	if ( noOfBogies > 1 ){
		sf::Clock clock;
		auto *trainID = new sf::Text [noOfBogies];

		//initializing all trainIDs
		for ( int i = 1; i < noOfBogies; i++ ){
			trainID[i] = sf::Text(std::to_string(engine[i]->getBogieID()), font, 20);
			trainID[i].setPosition((engine[i - 1]->getEndCoord().x + (engine[i]->getEndCoord().x - engine[i - 1]->getEndCoord().x) / 2),
			                    engine[i]->getEndCoord().y);

			trainID[i].setFillColor(sf::Color::Green);
			trainID[i].setStyle(sf::Text::Italic);
		}

		//moving trainIDs up and displaying them until their y axis position is greater than height * 0.065104167. This expression is equivalent to 20 px on 768 px screen.
		while ( trainID[1].getPosition().y > window.getSize().y * 0.100004167 ){

			for ( int i = 1; i < noOfBogies; i++ )
				trainID[i].move(0, -0.001f * window.getSize().y);

			for ( int i = 1; i < noOfBogies; i++ )
				window.draw(trainID[i]);

			gui.draw();
			window.display();
			window.clear(sf::Color::White);
			drawTrain(window, font);
		}

		//display trainIDs till 3s
		while ( clock.getElapsedTime() < sf::seconds(2.0f) ){
			gui.draw();
			for ( int i = 1; i < noOfBogies; i++ )
				window.draw(trainID[i]);
			window.display();
		}

		delete[] trainID;
	}
}

void Train::printBogie(sf::RenderWindow &window, sf::Font &font, tgui::Gui &gui) {

	int ID = 0;

	tgui::Theme theme1{"/usr/share/tgui-0.8/gui-builder/themes/Black.txt"};
	tgui::Theme::setDefault(&theme1);

	tgui::ChildWindow::Ptr child = tgui::ChildWindow::create("Print bogie");
	child->setRenderer(theme1.getRenderer("ChildWindow"));
	child->setSize("18%", "15%");
	child->setPosition("40%", "60%");
	child->setFocused(true);
	gui.add(child);

	tgui::EditBox::Ptr bogieID = tgui::EditBox::create();
	bogieID->setSize({"90%", "20%"});
	bogieID->setPosition({"5%", "20%"});
	bogieID->setDefaultText("Enter ID of bogie to print");
	child->add(bogieID);

	// Create the Ok button
	tgui::Button::Ptr button = tgui::Button::create("Ok");
	button->setSize({"50%", "20%"});
	button->setPosition({"25%", "70%"});
	child->add(button);

	button->connect("pressed", [&](){
		if ( bogieID->getText() != std::string("") ){
			if ( SearchBoogie(std::stoi(bogieID->getText().toAnsiString())) && bogieID->getText() != sf::String("0") ){
				ID = std::stoi(bogieID->getText().toAnsiString());
				child->setFocused(false);
			}
			else {

				sf::Clock oneSecTimer;

				auto warningMessage = tgui::Label::create("Bogie with this ID doesn't exist!");
				warningMessage->setRenderer(theme1.getRenderer("Label"));
				warningMessage->setPosition("3%", "45%");
				warningMessage->setTextSize( static_cast<unsigned>(window.getSize().y * 0.0234375) );
				warningMessage->getRenderer()->setTextColor(sf::Color::Red);
				child->add(warningMessage);

				while( oneSecTimer.getElapsedTime() < sf::seconds(1.0f) ){
					gui.draw();
					window.display();
				}

				bogieID->setText("");
				bogieID->setFocused(true);
				gui.draw();
				window.display();
				child->remove(warningMessage);
			}
		}
	});

	gui.draw();
	window.display();

	while( child->isFocused() ){
		sf::Event event = sf::Event();

		while (window.pollEvent(event))
			gui.handleEvent(event);

		window.clear(sf::Color::White);
		gui.draw();
		drawTrain(window, font);
		window.display();
	}

	if ( SearchBoogie(ID) && ID != 0 && getBogie(ID)->getFamilyName() != std::string("") ){

		char noOfKids = getBogie(ID)->getNoOfKids();
		char noOfAdults = getBogie(ID)->getNoOfAdults();

		child->removeAllWidgets();
		child->setFocused(true);
		child->setSize({"50%", "58%"});
		child->setPosition({"20%", "38%"});
		child->setTitleButtons(1);

		sf::Font familyNameFont;
		familyNameFont.loadFromFile("Anonymice Nerd Font Complete Mono.ttf");

		//print family name
		tgui::Label::Ptr familyName = tgui::Label::create(sf::String( getBogie(ID)->getFamilyName() + std::string(" family") ));
		familyName->setSize({"40%", "10%"});
		familyName->setPosition({"40%", "5%"});
		familyName->setTextSize(20);
		familyName->getRenderer()->setFont(familyNameFont);
		familyName->getRenderer()->setTextColor(sf::Color::Blue);
		child->add(familyName);

		auto **kidsTable = new tgui::Tabs::Ptr*[noOfKids + 1];

		for ( int i = 0; i < noOfKids + 1; i++ )
			kidsTable[i] = new tgui::Tabs::Ptr[4];  //as there are 4 members in Kid class.

		for ( int i = 0; i < noOfKids + 1; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				kidsTable[i][j] = tgui::Tabs::create();
				kidsTable[i][j]->setTabHeight(0.0390625 * window.getSize().y);
				kidsTable[i][j]->setRenderer(theme1.getRenderer("Tabs"));
				kidsTable[i][j]->connect( "TabSelected", [&](){ kidsTable[i][j]->deselect(); } );
				child->add(kidsTable[i][j]);
			}
		}

		kidsTable[0][0]->add("Name", false);
		kidsTable[0][0]->setPosition({"5%", "20%"});
		kidsTable[0][1]->add("Age", false);
		kidsTable[0][1]->setPosition({"12.5%", kidsTable[0][0]->getPosition().y });
		kidsTable[0][2]->add("Gender", false);
		kidsTable[0][2]->setPosition({"18%", kidsTable[0][1]->getPosition().y });
		kidsTable[0][3]->add("BFormNumber", false);
		kidsTable[0][3]->setSize({"20%", kidsTable[0][2]->getSize().y});
		kidsTable[0][3]->setPosition({"26.5%", kidsTable[0][2]->getPosition().y });

		for ( int i = 0; i < 4; i++ )
			kidsTable[0][i]->getRenderer()->setTextColor(sf::Color::Green);

		for ( int i = 1; i < noOfKids + 1; i++ ) {
			for ( int j = 0; j < 4; j++ ) {

				kidsTable[i][j]->setRenderer(theme1.getRenderer("Tabs"));
				kidsTable[i][j]->setSize(kidsTable[i - 1][j]->getSize());
				kidsTable[i][j]->setPosition({ kidsTable[i - 1][j]->getPosition().x, kidsTable[i - 1][j]->getPosition().y + kidsTable[i - 1][j]->getSize().y });


				if ( j == 0 )
					kidsTable[i][j]->add(getBogie(ID)->getKid(i - 1)->getName(), false);

				else if ( j == 1 )
					kidsTable[i][j]->add(std::to_string(getBogie(ID)->getKid(i - 1)->getAge()), false);

				else if ( j == 2 )
					kidsTable[i][j]->add(getBogie(ID)->getKid(i - 1)->getGender(), false);

				else if ( j == 3 )
					kidsTable[i][j]->add(getBogie(ID)->getKid(i - 1)->getBFormNumber(), false);
			}
		}

		//Adults table
		auto **adultsTable = new tgui::Tabs::Ptr*[noOfAdults + 1];

		for ( int i = 0; i < noOfAdults + 1; i++ )
			adultsTable[i] = new tgui::Tabs::Ptr[6];  //as there are 6 members in Adult class.

		for ( int i = 0; i < noOfAdults + 1; i++ ) {
			for ( int j = 0; j < 6; j++ ) {
				adultsTable[i][j] = tgui::Tabs::create();
				adultsTable[i][j]->setTabHeight(0.0390625 * window.getSize().y);
				adultsTable[i][j]->setRenderer(theme1.getRenderer("Tabs"));
				adultsTable[i][j]->connect( "TabSelected", [&](){ adultsTable[i][j]->deselect(); } );
				child->add(adultsTable[i][j]);
			}
		}
w

		adultsTable[0][0]->add("Name", false);
		adultsTable[0][0]->setPosition({"5%", kidsTable[noOfKids][0]->getPosition().y + kidsTable[noOfKids][0]->getSize().y * 2 });
		adultsTable[0][1]->add("Age", false);
		adultsTable[0][1]->setPosition({adultsTable[0][0]->getPosition().x + adultsTable[0][0]->getSize().x, adultsTable[0][0]->getPosition().y });
		adultsTable[0][2]->add("Gender", false);
		adultsTable[0][2]->setPosition({adultsTable[0][1]->getPosition().x + adultsTable[0][1]->getSize().x, adultsTable[0][1]->getPosition().y });
		adultsTable[0][3]->add("Occupation", false);
		adultsTable[0][3]->setPosition({adultsTable[0][2]->getPosition().x + adultsTable[0][2]->getSize().x, adultsTable[0][2]->getPosition().y });
		adultsTable[0][3]->setSize({"30%", adultsTable[0][2]->getSize().y});
		adultsTable[0][4]->add("Qualification", false);
		adultsTable[0][4]->setPosition({adultsTable[0][3]->getPosition().x + adultsTable[0][3]->getSize().x, adultsTable[0][3]->getPosition().y });
		adultsTable[0][5]->add("NIC", false);
		adultsTable[0][5]->setPosition({adultsTable[0][4]->getPosition().x + adultsTable[0][4]->getSize().x, adultsTable[0][4]->getPosition().y });
		adultsTable[0][5]->setSize({"20%", adultsTable[0][4]->getSize().y});

		for ( int i = 0; i < 6; i++ )
			adultsTable[0][i]->getRenderer()->setTextColor(sf::Color::Green);


		for ( int i = 1; i < noOfAdults + 1; i++ ) {
			for ( int j = 0; j < 6; j++ ) {

				adultsTable[i][j]->setRenderer(theme1.getRenderer("Tabs"));
				adultsTable[i][j]->setSize(adultsTable[i - 1][j]->getSize());
				adultsTable[i][j]->setPosition({ adultsTable[i - 1][j]->getPosition().x, adultsTable[i - 1][j]->getPosition().y + adultsTable[i - 1][j]->getSize().y });

				if ( j == 0 )
					adultsTable[i][j]->add(getBogie(ID)->getAdult(i - 1)->getName(), false);

				else if ( j == 1 )
					adultsTable[i][j]->add(std::to_string(getBogie(ID)->getAdult(i - 1)->getAge()), false);

				else if ( j == 2 )
					adultsTable[i][j]->add(getBogie(ID)->getAdult(i - 1)->getGender(), false);

				else if ( j == 3 )
					adultsTable[i][j]->add(getBogie(ID)->getAdult(i - 1)->getOccupation(), false);

				else if ( j == 4 )
					adultsTable[i][j]->add(getBogie(ID)->getAdult(i - 1)->getQualification(), false);

				else if ( j == 5 )
					adultsTable[i][j]->add(getBogie(ID)->getAdult(i - 1)->getNIC(), false);
			}
		}

		gui.draw();
		window.display();

		while( child->isFocused() ){
			sf::Event event = sf::Event();

			while (window.pollEvent(event))
				gui.handleEvent(event);

			window.clear(sf::Color::White);
			gui.draw();
			drawTrain(window, font);
			window.display();
		}

	}


	else {
		sf::Clock twoSecTimer;

		auto warningMessage = tgui::Label::create("Empty bogie!");
		warningMessage->setRenderer(theme1.getRenderer("Label"));
		warningMessage->setPosition("22%", "45%");
		warningMessage->setTextSize(18);
		warningMessage->getRenderer()->setTextColor(sf::Color::Red);
		child->add(warningMessage);

		while ( twoSecTimer.getElapsedTime() < sf::seconds(2.0f) ){
			gui.draw();
			window.display();
		}

		bogieID->setText("");
		bogieID->setFocused(true);
		gui.draw();
		window.display();
		child->remove(warningMessage);
	}

	child->removeAllWidgets();
	gui.remove(child);

}

bool Train::SearchBoogie(int ID) const {

	for ( int i = 0; i < noOfBogies; i++ )
		if ( engine[i]->getBogieID() == ID )
			return true;

	return false;
}

Bogie *Train::getBogie(int ID) const {
	if ( SearchBoogie(ID) ){
		for ( int i = 0; i < noOfBogies; i++ )
			if ( engine[i]->getBogieID() == ID )
				return engine[i];
	}
	return nullptr;
}

void Train::addPassengersToBogie(sf::RenderWindow &window, sf::Font &font, tgui::Gui &gui) {

	int ID = 0;

	tgui::Theme theme{"/usr/share/tgui-0.8/gui-builder/themes/Black.txt"};
	tgui::Theme::setDefault(&theme);

	auto child = tgui::ChildWindow::create();
	child->setRenderer(theme.getRenderer("ChildWindow"));
	child->setSize("22%", "15%");
	child->setPosition("40%", "60%");
	child->setTitle("Add Passengers");
	child->setFocused(true);
	gui.add(child);

	auto bogieID = tgui::EditBox::create();
	bogieID->setSize({"90%", "20%"});
	bogieID->setPosition({"5%", "20%"});
	bogieID->setDefaultText("Enter ID of bogie to add passengers to");
	child->add(bogieID);

	auto button = tgui::Button::create("Ok");
	button->setSize({"35%", "16.67%"});
	button->setPosition({"30%", "70%"});
	child->add(button);

	button->connect("pressed", [&](){
		if ( bogieID->getText() != std::string("") ){
			if ( SearchBoogie(std::stoi(bogieID->getText().toAnsiString())) && bogieID->getText() != sf::String("0") ){
				ID = std::stoi(bogieID->getText().toAnsiString());
				child->setFocused(false);
			}
			else {

				sf::Clock oneSecTimer;

				auto warningMessage = tgui::Label::create("Bogie with this ID doesn't exist!");
				warningMessage->setRenderer(theme.getRenderer("Label"));
				warningMessage->setPosition("3%", "45%");
				warningMessage->setTextSize( static_cast<unsigned>(window.getSize().y * 0.0234375) );
				warningMessage->getRenderer()->setTextColor(sf::Color::Red);
				child->add(warningMessage);

				while( oneSecTimer.getElapsedTime() < sf::seconds(1.0f) ){
					gui.draw();
					window.display();
				}

				bogieID->setText("");
				bogieID->setFocused(true);
				gui.draw();
				window.display();
				child->remove(warningMessage);
			}
		}
	});

	gui.draw();
	window.display();

	while( child->isFocused() ){
		sf::Event event = sf::Event();

		while (window.pollEvent(event))
			gui.handleEvent(event);

		window.clear(sf::Color::White);
		gui.draw();
		drawTrain(window, font);
		window.display();
	}

	if ( SearchBoogie(ID) && ID != 0 && getBogie(ID)->getFamilyName() == std::string("") ){

		child->remove(bogieID);
		child->setFocused(true);
		child->setSize("25%", "30%");

		auto familyNameBox = tgui::EditBox::create();
		familyNameBox->setSize({"66.67%", "12.5%"});
		familyNameBox->setPosition({"16.67%", "10%"});
		familyNameBox->setDefaultText("Enter family name");
		child->add(familyNameBox);

		auto kidsBox = tgui::EditBox::create();
		kidsBox->setSize({"66.67%", "12.5%"});
		kidsBox->setPosition({"16.67%", "33%"});
		kidsBox->setDefaultText("Enter number of kids");
	    child->add(kidsBox);

		auto adultsBox = tgui::EditBox::create();
		adultsBox->setSize({"66.67%", "12.5%"});
		adultsBox->setPosition({"16.67%", "56%"});
		adultsBox->setDefaultText("Enter number of adults");
		child->add(adultsBox);

		button->setSize({"30%", "12.5%"});
		button->setPosition({"35%", "85%"});
		child->add(button);
		button->disconnectAll();

		button->connect("pressed", [&](){
			if ( adultsBox->getText() != std::string("") && kidsBox->getText() != std::string("") ){
				if ( ( adultsBox->getText() > sf::String("0") && adultsBox->getText() < sf::String("5") )
					&& ( adultsBox->getText() > sf::String("0") && kidsBox->getText() < sf::String("7") ) && familyNameBox->getText() != sf::String("") ){

					getBogie(ID)->setNoOfKids(std::stoi(kidsBox->getText().toAnsiString()));
					getBogie(ID)->setNoOfAdults(std::stoi(adultsBox->getText().toAnsiString()));
					getBogie(ID)->setFamilyName(familyNameBox->getText().toAnsiString());
					child->setFocused(false);
				}
				else {
					sf::Clock twoSecTimer;

					auto warningMessage = tgui::Label::create("Enter correct number of adults and kids!");
					warningMessage->setRenderer(theme.getRenderer("Label"));
					warningMessage->setPosition("5%", "73%");
					warningMessage->setTextSize(14);
					warningMessage->getRenderer()->setTextColor(sf::Color::Red);
					child->add(warningMessage);

					while ( twoSecTimer.getElapsedTime() < sf::seconds(2.0f) ){
						gui.draw();
						window.display();
					}

					kidsBox->setText("");
					adultsBox->setText("");
					kidsBox->setFocused(true);
					gui.draw();
					window.display();
					child->remove(warningMessage);
				}
			}
		});

		gui.draw();
		window.display();

		while( child->isFocused() ){
			sf::Event event = sf::Event();

			while (window.pollEvent(event))
				gui.handleEvent(event);

			window.clear(sf::Color::White);
			gui.draw();
			drawTrain(window, font);
			window.display();
		}

		if ( ( adultsBox->getText() > sf::String("0") && adultsBox->getText() < sf::String("5") )
		     && ( adultsBox->getText() > sf::String("0") && kidsBox->getText() < sf::String("7") ) && familyNameBox->getText() != sf::String("") ){

			auto **tempAdults = new Person*[getBogie(ID)->getNoOfAdults()];
			auto **tempKids = new Person*[getBogie(ID)->getNoOfKids()];

			int kidCounter = 0, adultCounter = 0;

			while ( adultCounter < getBogie(ID)->getNoOfAdults() ){

				child->removeAllWidgets();

				gui.draw();
				window.display();

				child->setTitle("Add Adult");
				child->setTitleButtons(0);
				child->setPosition({"38%", "39%"});
				child->setSize({"25%", "44.69%"});
				child->setFocused(true);

				auto editBox1 = tgui::EditBox::create();
				editBox1->setDefaultText("Enter name");
				editBox1->setPosition({"20%", "8%"});
				editBox1->setSize({"60%", "7.5%"});
				editBox1->setMaximumCharacters(50);
				child->add(editBox1);

				auto editBox2 = tgui::EditBox::create();
				editBox2->setDefaultText("Enter age");
				editBox2->setPosition({"20%", "20.5%"});
				editBox2->setSize({"60%", "7.5%"});
				editBox2->setMaximumCharacters(3);
				child->add(editBox2);

				auto editBox3 = tgui::EditBox::create();
				editBox3->setDefaultText("Enter gender");
				editBox3->setPosition({"20%", "33%"});
				editBox3->setSize({"60%", "7.5%"});
				editBox3->setMaximumCharacters(1);
				child->add(editBox3);

				auto editBox4 = tgui::EditBox::create();
				editBox4->setDefaultText("Enter occupation");
				editBox4->setPosition({"20%", "45.5%"});
				editBox4->setSize({"60%", "7.5%"});
				editBox4->setMaximumCharacters(50);
				child->add(editBox4);

				auto editBox5 = tgui::EditBox::create();
				editBox5->setDefaultText("Enter qualification");
				editBox5->setPosition({"20%", "58%"});
				editBox5->setSize({"60%", "7.5%"});
				editBox5->setMaximumCharacters(50);
				child->add(editBox5);

				auto editBox6 = tgui::EditBox::create();
				editBox6->setDefaultText("Enter NIC");
				editBox6->setPosition({"20%", "70.5%"});
				editBox6->setSize({"60%", "7.5%"});
				editBox6->setMaximumCharacters(15);
				child->add(editBox6);

				auto addButton = tgui::Button::create("Add");
				addButton->setPosition({"35%", "88%"});
				addButton->setSize({"28%", "6%"});
				child->add(addButton);

				sf::String nullString("");

				addButton->connect("Pressed", [&](){
					if ( editBox1->getText() != nullString && editBox2->getText() != nullString && editBox3->getText() != nullString
						&& editBox4->getText() != nullString && editBox5->getText() != nullString && editBox6->getText() != nullString ){

						tempAdults[adultCounter++] = new Adult(editBox1->getText().toAnsiString(), std::stoi(editBox2->getText().toAnsiString()), editBox3->getText().toAnsiString().at(0),
											   editBox4->getText().toAnsiString(), editBox5->getText().toAnsiString(), editBox6->getText().toAnsiString());

						editBox1->setText(nullString), editBox2->setText(nullString), editBox3->setText(nullString), editBox4->setText(nullString),
						editBox5->setText(nullString), editBox6->setText(nullString);

						if ( adultCounter >= getBogie(ID)->getNoOfAdults() )
							child->setFocused(false);
					}
					else{
						sf::Clock twoSecTimer;

						auto warningMessage = tgui::Label::create("One or more fields are empty!");
						warningMessage->setRenderer(theme.getRenderer("Label"));
						warningMessage->setPosition("20%", "80%");
						warningMessage->setTextSize(13);
						warningMessage->getRenderer()->setTextColor(sf::Color::Red);
						child->add(warningMessage);

						while ( twoSecTimer.getElapsedTime() < sf::seconds(2.0f) ){
							gui.draw();
							window.display();
						}

						editBox1->setText(nullString), editBox2->setText(nullString), editBox3->setText(nullString), editBox4->setText(nullString),
						editBox5->setText(nullString), editBox6->setText(nullString);

						editBox1->setFocused(true);
						gui.draw();
						window.display();
						child->remove(warningMessage);
					}
				});

				gui.draw();
				window.display();

				while( child->isFocused() ){
					sf::Event event = sf::Event();

					while (window.pollEvent(event))
						gui.handleEvent(event);

					window.clear(sf::Color::White);
					gui.draw();
					drawTrain(window, font);
					window.display();
				}

			}


			while ( kidCounter < getBogie(ID)->getNoOfKids() ){

				child->removeAllWidgets();

				gui.draw();
				window.display();

				child->setTitle("Add Kid");
				child->setTitleButtons(0);
				child->setPosition({"38%", "50%"});
				child->setSize({"17%", "35%"});
				child->setFocused(true);

				auto editBox1 = tgui::EditBox::create();
				editBox1->setDefaultText("Enter name");
				editBox1->setPosition({"15%", "8%"});
				editBox1->setSize({"70%", "10%"});
				editBox1->setMaximumCharacters(50);
				child->add(editBox1);

				auto editBox2 = tgui::EditBox::create();
				editBox2->setDefaultText("Enter age");
				editBox2->setPosition({"15%", "28%"});
				editBox2->setSize({"70%", "10%"});
				editBox2->setMaximumCharacters(1);
				child->add(editBox2);

				auto editBox3 = tgui::EditBox::create();
				editBox3->setDefaultText("Enter gender");
				editBox3->setPosition({"15%", "48%"});
				editBox3->setSize({"70%", "10%"});
				editBox3->setMaximumCharacters(1);
				child->add(editBox3);

				auto editBox4 = tgui::EditBox::create();
				editBox4->setDefaultText("Enter BForm number");
				editBox4->setPosition({"15%", "68%"});
				editBox4->setSize({"70%", "10%"});
				editBox4->setMaximumCharacters(50);
				child->add(editBox4);

				auto addButton = tgui::Button::create("Add");
				addButton->setPosition({"35%", "88%"});
				addButton->setSize({"28%", "8%"});
				child->add(addButton);

				sf::String nullString("");

				addButton->connect("Pressed", [&](){
					if ( editBox1->getText() != nullString && editBox2->getText() != nullString
						&& editBox3->getText() != nullString && editBox4->getText() != nullString ){

						tempKids[kidCounter++] = new Kid(editBox1->getText().toAnsiString(), std::stoi(editBox2->getText().toAnsiString()),
													  editBox3->getText().toAnsiString().at(0), editBox4->getText().toAnsiString());

						editBox1->setText(nullString), editBox2->setText(nullString), editBox3->setText(nullString), editBox4->setText(nullString);

						if ( kidCounter >= getBogie(ID)->getNoOfKids() )
							child->setFocused(false);

					}
					else{
						sf::Clock twoSecTimer;

						auto warningMessage = tgui::Label::create("One or more fields are empty!");
						warningMessage->setRenderer(theme.getRenderer("Label"));
						warningMessage->setPosition("8%", "80%");
						warningMessage->setTextSize(13);
						warningMessage->getRenderer()->setTextColor(sf::Color::Red);
						child->add(warningMessage);

						while ( twoSecTimer.getElapsedTime() < sf::seconds(2.0f) ){
							gui.draw();
							window.display();
						}

						editBox1->setText(nullString), editBox2->setText(nullString), editBox3->setText(nullString), editBox4->setText(nullString);
						editBox1->setFocused(true);
						gui.draw();
						window.display();
						child->remove(warningMessage);
					}

				});

				gui.draw();
				window.display();

				while( child->isFocused() ){
					sf::Event event = sf::Event();

					while (window.pollEvent(event))
						gui.handleEvent(event);

					window.clear(sf::Color::White);
					gui.draw();
					drawTrain(window, font);
					window.display();
				}
			}
			getBogie(ID)->AddPassengers(tempAdults, tempKids);
		}
	}
	else {
		sf::Clock twoSecTimer;

		auto warningMessage = tgui::Label::create("Bogie is reserved!");
		warningMessage->setRenderer(theme.getRenderer("Label"));
		warningMessage->setPosition("8%", "45%");
		warningMessage->setTextSize(18);
		warningMessage->getRenderer()->setTextColor(sf::Color::Red);
		child->add(warningMessage);

		while ( twoSecTimer.getElapsedTime() < sf::seconds(2.0f) ){
			gui.draw();
			window.display();
		}

		bogieID->setText("");
		bogieID->setFocused(true);
		gui.draw();
		window.display();
		child->remove(warningMessage);
	}

	child->removeAllWidgets();
	gui.remove(child);
}

//void Train::printWarningMessage(sf::RenderWindow &window, tgui::Gui &gui, tgui::Theme &theme, tgui::ChildWindow &child, int) {
//	sf::Clock timer;
//
//	while ( timer.getElapsedTime() < sf::seconds(1.0f) ){
//
//		auto warningMessage = tgui::Label::create("Enter another bogie ID");
//		warningMessage->setRenderer(theme.getRenderer("Label"));
//		warningMessage->setPosition("8%", "45%");
//		warningMessage->setTextSize(18);
//		warningMessage->getRenderer()->setTextColor(sf::Color::Red);
//		child->add(warningMessage);
//
//		gui.draw();
//		window.display();
//	}
//}

Train::~Train() {
	if ( engine != nullptr )
		delete[] engine, engine = nullptr;
}