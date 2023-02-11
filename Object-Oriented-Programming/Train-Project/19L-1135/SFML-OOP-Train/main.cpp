#include "src/Train.h"
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

void Back(bool &x1,bool &x2,bool &x3,bool &x4, bool &x5) {
	if (!x1  && x2 ) {
		x1 = true; x2 = false;
	} else if ( !x2 && x3 ) {
		x2 = true; x3 = false;
	} else if ( !x2 && x4 ) {
		x2 = true; x4 = false;
	} else if ( !x2 && x5 ) {
		x2 = true; x5 = false;
	}
}

int Random(int min, int max) {

	int num = 0;
	for (int i = 0; i < 1; i++) {
		num = (rand() % (max - min + 1)) + min;
	}

	return num;
}

string WaitSB(){
	string Pic;
	string STB2 = "STB7.jpg",STB3 = "STB3.jpg",STB5 = "STB5.jpg",STB6 = "STB6.jpg";
	int i=Random(1,4);
	if(i==1){
		Pic=STB2;
	}else if(i==2){
		Pic=STB3;
	}else if(i==3){
		Pic=STB5;
	}else if(i==4){
		Pic=STB6;
	}

	return Pic;
}

string WaitT(){
	string Pic;
	string TB2 = "TB2.jpg",TB5 = "TB5.jpg",TB6 = "TB6.jpg";
	int i=Random(1,3);
	if(i==1){
		Pic=TB2;
	}else if(i==2){
		Pic=TB5;
	}else if(i==3){
		Pic=TB6;
	}

	return Pic;
}

string WaitP(){
	string Pic;
	string TB1 = "STB2.jpg",PB2 = "PB2.jpg",PB3 = "PB3.jpg",PB5 = "PB5.jpg",PB6 = "PB6.jpg",PB7 = "PB7.jpg";
	int i=Random(1,6);
	if(i==1){
		Pic=PB2;
	}else if(i==2){
		Pic=PB3;
	}else if(i==3){
		Pic=PB5;
	}else if(i==4){
		Pic=PB6;
	}else if(i==5){
		Pic=PB7;
	}else if(i==6){
		Pic=TB1;
	}

	return Pic;
}

string WaitB(){
	string Pic;
	string BB2 = "BB2.jpg",BB4 = "BG4.jpg",BB6 = "BB6.jpg";
	int i=Random(1,3);
	if(i==1){
		Pic=BB2;
	}else if(i==2){
		Pic=BB4;
	}else if(i==3){
		Pic=BB6;
	}

	return Pic;
}

void SoundB(int &TS,sf::Sound &sound){
	sf::Clock clock3;
	if (clock3.getElapsedTime() < sf::seconds(1.0f)) {
		TS++;
	}
	if (TS == 126) {
		TS = 0;
	}
	if (TS == 16) {
		sound.setVolume(2.f);
		sound.play();
	}
}

int main() {
	Train T;

	sf::RenderWindow window(sf::VideoMode(1340, 666), "Train");
	window.setFramerateLimit(60);

	tgui::Gui gui(window);
	tgui::Theme theme{"themes/Black.txt"};
	tgui::Theme::setDefault(&theme);

	srand(time(nullptr));

	auto editBox = tgui::EditBox::create();
//	tgui::EditBox::Ptr editBox = tgui::EditBox::create();

	sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setPosition(0, 0);

	sf::RectangleShape background2(sf::Vector2f(window.getSize().x, window.getSize().y));
	background2.setPosition(0, 0);

	sf::Texture bgImageTexture = sf::Texture();
	bgImageTexture.loadFromFile("InitialB.jpg");
	bgImageTexture.setSmooth(true);
	background.setTexture(&bgImageTexture);

	sf::Texture BS1 = sf::Texture();
	BS1.loadFromFile("BT1.png");
	BS1.setSmooth(true);

	sf::Texture BS2 = sf::Texture();
	BS2.loadFromFile("BT2.png");
	BS2.setSmooth(true);

	sf::Texture BS3 = sf::Texture();
	BS3.loadFromFile("BT3.png");
	BS3.setSmooth(true);

	sf::Texture BS4 = sf::Texture();
	BS4.loadFromFile("BT4.png");
	BS4.setSmooth(true);

	sf::Texture BS5 = sf::Texture();
	BS5.loadFromFile("BT5.png");
	BS5.setSmooth(true);

	sf::Texture BS6 = sf::Texture();
	BS6.loadFromFile("BT6.png");
	BS6.setSmooth(true);

	sf::Texture BS7 = sf::Texture();
	BS7.loadFromFile("BT7.png");
	BS7.setSmooth(true);

	sf::Texture BS8 = sf::Texture();
	BS8.loadFromFile("BT8.png");
	BS8.setSmooth(true);

	sf::Texture BS9 = sf::Texture();
	BS9.loadFromFile("BT9.png");
	BS9.setSmooth(true);

	sf::Texture BS10 = sf::Texture();
	BS10.loadFromFile("BT10.png");
	BS10.setSmooth(true);

	sf::Texture BS11 = sf::Texture();
	BS11.loadFromFile("BT11.png");
	BS11.setSmooth(true);

	sf::Texture BS12 = sf::Texture();
	BS12.loadFromFile("BT12.png");
	BS12.setSmooth(true);

	sf::Texture BS13 = sf::Texture();
	BS13.loadFromFile("BT13.png");
	BS13.setSmooth(true);

	sf::CircleShape logo(0.02 * window.getSize().x);
	logo.setPosition(0.0f, window.getSize().y - logo.getRadius() * 2);

	sf::Texture logoImageTexture = sf::Texture();
	logoImageTexture.loadFromFile("logo.jpg");
	logoImageTexture.setSmooth(true);

	logo.setTexture(&logoImageTexture);

	sf::Font TitleFont = sf::Font();
	if (!TitleFont.loadFromFile("Fonts/LHI.ttf")) {
		cout << "Error Title font\n";
	}

	sf::Font loadingFont = sf::Font();
	if (!loadingFont.loadFromFile("Fonts/arlrdbd.ttf")) {
		cout << "Error loading font\n";
	}
	sf::Text loading(sf::String("Loading...."), loadingFont, 20);
	loading.setPosition(
			static_cast<double>(6 + logo.getPosition().x) + static_cast<double>(logo.getRadius()) * 2.1,
			window.getSize().y - logo.getRadius() - 13);
	loading.setFillColor(sf::Color::White);

	sf::Text Creater(sf::String("By: \n Anato\n Namikaza"), loadingFont, 12);
	Creater.setPosition(
			static_cast<double>(6 + logo.getPosition().x) - 55 + static_cast<double>(logo.getRadius()) * 2.1,
			window.getSize().y - logo.getRadius() - 28);
	Creater.setFillColor(sf::Color::Black);

	sf::Text saving(sf::String("Saving Data..."), loadingFont, 20);
	saving.setPosition(
			static_cast<double>(6 + logo.getPosition().x) + static_cast<double>(logo.getRadius()) * 2.1,
			window.getSize().y - logo.getRadius() - 13);
	saving.setFillColor(sf::Color::White);


	sf::Text mainMenu(sf::String("Hikari Station"), TitleFont, 108);
	mainMenu.setPosition((static_cast<float>(window.getSize().x) / 2) - (mainMenu.getLocalBounds().width / 2),
	                     0.35 * window.getSize().y + 60 - 200);
	mainMenu.setFillColor(sf::Color::Black);
	mainMenu.setOutlineColor(sf::Color::White);
	mainMenu.setOutlineThickness(2.0);

	sf::Text mainMenu1(sf::String("Press Any Key to Start"), loadingFont, 25);
	mainMenu1.setPosition(static_cast<float>(window.getSize().x) / 2 - (mainMenu1.getLocalBounds().width / 2),
	                      0.55 * window.getSize().y + 150);
	mainMenu1.setFillColor(sf::Color::Black);
	mainMenu1.setOutlineColor(sf::Color::Red);
	mainMenu1.setOutlineThickness(2.0);

	sf::Text mainMenu2(sf::String("Hikari Station"), TitleFont, 108);
	mainMenu2.setPosition((static_cast<float>(window.getSize().x) / 2) - (mainMenu.getLocalBounds().width / 2),
	                      0.35 * window.getSize().y + 60 - 250);
	mainMenu2.setFillColor(sf::Color::Black);
	mainMenu2.setOutlineColor(sf::Color::White);
	mainMenu2.setOutlineThickness(2.0);

	sf::Text mainMenuT(sf::String("Hikari Station"), TitleFont, 90);
	mainMenuT.setPosition(
			(static_cast<float>(window.getSize().x) / 2) - (mainMenu.getLocalBounds().width / 2) + 30,
			0.35 * window.getSize().y + 60 - 200);
	mainMenuT.setFillColor(sf::Color::Black);
	mainMenuT.setOutlineColor(sf::Color::White);
	mainMenuT.setOutlineThickness(2.0);

	sf::Clock universalClock;
	bool isLoading = false;
	bool displayBgImage = false;
	bool displayBgImage2 = false;
	bool stopMainMenu = false;
	bool MainMenuBar = false;
	string temp1;
	int TS = 0,LT = 0;
	bool Home1I, Home1O, Home2O, Home3O, Home4O, Home5O, Home6O, ExitT;
	Home1I = Home1O = Home2O = Home3O = Home4O = Home5O = Home6O = ExitT = false;
	bool RandomB, RandomB1, RandomB2, RandomB3;
	RandomB = RandomB1 = RandomB2 = RandomB3 = false;
	for (int i = 0; i < 16; i++) {
		temp1 = WaitSB();
	}

//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================

	sf::Event event = sf::Event();
	auto *button = new tgui::Button::Ptr[15];
	for (int i = 0; i < 15; i++)
		button[i] = tgui::Button::create();

	button[0]->setSize(350, 100);
	button[0]->setPosition(window.getSize().x - 150 * 2 - 800, window.getSize().y - 250);
	button[0]->getRenderer()->setTexture(BS1);
	button[0]->getRenderer()->setTextureHover(BS1);
	button[0]->connect("pressed", [&]() {
		T.DataExtraction();
		Home3O = true;
		Home2O = false;
		Home1I = false;
		gui.removeAllWidgets();
		window.clear();
		RandomB = true;
	});

	button[1]->setRenderer(theme.getRenderer("Button"));
	button[1]->setSize(350, 100);
	button[1]->setPosition(window.getSize().x - 150 * 2 - 300, window.getSize().y - 250);
	button[1]->getRenderer()->setTexture(BS2);
	button[1]->getRenderer()->setTextureHover(BS2);
	button[1]->getRenderer()->setTextureDown(BS2);
	button[1]->connect("pressed", [&]() {
		Home1I = false;
		RandomB = true;
		Home2O = false;
		Home3O = true;
		gui.removeAllWidgets();
		window.clear();
	});

	button[2]->setRenderer(theme.getRenderer("Button"));
	button[2]->setSize(300, 80);
	button[2]->setPosition(window.getSize().x - 150 * 2 - 950 + 30, window.getSize().y - 300);
	button[2]->getRenderer()->setTexture(BS3);
	button[2]->getRenderer()->setTextureHover(BS3);
	button[2]->connect("pressed", [&]() {
		Home4O = true;
		Home3O = false;
		RandomB1 = true;
		gui.removeAllWidgets();
	});

	button[3]->setRenderer(theme.getRenderer("Button"));
	button[3]->setSize(300, 80);
	button[3]->setPosition(window.getSize().x - 150 * 2 - 550 + 40, window.getSize().y - 300);
	button[3]->getRenderer()->setTexture(BS4);
	button[3]->getRenderer()->setTextureHover(BS4);
	button[3]->connect("pressed", [&]() {
		RandomB2 = true;
		Home5O = true;
		Home3O = false;
		gui.removeAllWidgets();
	});

	button[4]->setRenderer(theme.getRenderer("Button"));
	button[4]->setSize(300, 80);
	button[4]->setPosition(window.getSize().x - 150 * 2 - 150 + 35, window.getSize().y - 300);
	button[4]->getRenderer()->setTexture(BS5);
	button[4]->getRenderer()->setTextureHover(BS5);
	button[4]->connect("pressed", [&]() {
		RandomB3 = true;
		Home6O = true;
		Home3O = false;
		gui.removeAllWidgets();
	});

	button[5]->setRenderer(theme.getRenderer("Button"));
	button[5]->setSize(300, 80);
	button[5]->setPosition(window.getSize().x - 150 * 2 - 950 + 210, window.getSize().y - 300);
	button[5]->getRenderer()->setTexture(BS6);
	button[5]->getRenderer()->setTextureHover(BS6);
	button[5]->connect("pressed", [&]() {
		window.clear();
		window.draw(background);
		sf::Clock clock1;
		while ( clock1.getElapsedTime() <= sf::seconds(10.0f) ) {
			T.drawTrain(window);
		}
		gui.removeAllWidgets();
	});

	button[6]->setRenderer(theme.getRenderer("Button"));
	button[6]->setSize(300, 80);
	button[6]->setPosition(window.getSize().x - 150 * 2 - 550 + 260, window.getSize().y - 300);
	button[6]->getRenderer()->setTexture(BS7);
	button[6]->getRenderer()->setTextureHover(BS7);
	button[6]->connect("pressed", [&]() {
		T.printTrain();
		gui.removeAllWidgets();
	});

	button[7]->setRenderer(theme.getRenderer("Button"));
	button[7]->setSize(300, 80);
	button[7]->setPosition(window.getSize().x - 150 * 2 - 950 + 30, window.getSize().y - 300);
	button[7]->getRenderer()->setTexture(BS8);
	button[7]->getRenderer()->setTextureHover(BS8);
	button[7]->connect("pressed", [&]() {
		T.ViewBogie();
		gui.removeAllWidgets();
	});

	button[8]->setRenderer(theme.getRenderer("Button"));
	button[8]->setSize(300, 80);
	button[8]->setPosition(window.getSize().x - 150 * 2 - 550 + 40, window.getSize().y - 300);
	button[8]->getRenderer()->setTexture(BS9);
	button[8]->getRenderer()->setTextureHover(BS9);
	button[8]->connect("pressed", [&]() {
		T.addBogie();
		gui.removeAllWidgets();
	});

	button[9]->setRenderer(theme.getRenderer("Button"));
	button[9]->setSize(300, 80);
	button[9]->setPosition(window.getSize().x - 150 * 2 - 150 + 35, window.getSize().y - 300);
	button[9]->getRenderer()->setTexture(BS10);
	button[9]->getRenderer()->setTextureHover(BS10);
	button[9]->connect("pressed", [&]() {
		T.removeBogie(window,gui);
		gui.removeAllWidgets();
	});

	button[10]->setRenderer(theme.getRenderer("Button"));
	button[10]->setSize(300, 80);
	button[10]->setPosition(window.getSize().x - 150 * 2 - 950 + 30, window.getSize().y - 300);
	button[10]->getRenderer()->setTexture(BS11);
	button[10]->getRenderer()->setTextureHover(BS11);
	button[10]->connect("pressed", [&]() { gui.removeAllWidgets();T.viewPassengers();});

	button[11]->setRenderer(theme.getRenderer("Button"));
	button[11]->setSize(300, 80);
	button[11]->setPosition(window.getSize().x - 150 * 2 - 550 + 40, window.getSize().y - 300);
	button[11]->getRenderer()->setTexture(BS12);
	button[11]->getRenderer()->setTextureHover(BS12);
	button[11]->connect("pressed", [&]() { gui.removeAllWidgets(); T.addPassengers(); });

	button[12]->setRenderer(theme.getRenderer("Button"));
	button[12]->setSize(300, 80);
	button[12]->setPosition(window.getSize().x - 150 * 2 - 150 + 35, window.getSize().y - 300);
	button[12]->getRenderer()->setTexture(BS13);
	button[12]->getRenderer()->setTextureHover(BS13);
	button[12]->connect("pressed", [&]() { gui.removeAllWidgets(); T.removePassengers();});

	button[14]->setRenderer(theme.getRenderer("Button"));
	button[14]->setSize(80, 30);
	button[14]->setPosition(window.getSize().x - 115.f - 100 + 25, window.getSize().y - 50.f + 11);
	button[14]->setText("Back");
	button[14]->connect("pressed", [&]() {
		Back(Home2O, Home3O, Home4O, Home5O, Home6O);
		gui.removeAllWidgets();
		RandomB = true;
	});

	button[13]->setRenderer(theme.getRenderer("Button"));
	button[13]->setSize(80, 30);
	button[13]->setPosition(window.getSize().x - 115.f + 25, window.getSize().y - 50.f + 11);
	button[13]->setText("Exit");
	button[13]->connect("pressed", [&]() { ExitT = true; });

	sf::SoundBuffer soundBuffer = sf::SoundBuffer();
	if (!soundBuffer.loadFromFile("TrainPB.wav"))
		std::cout << "Error loading sound buffer\n";
	sf::Sound sound;
	sound.setBuffer(soundBuffer);


	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (universalClock.getElapsedTime() >= sf::seconds(10.0f) &&
			           event.type == sf::Event::KeyPressed) {
				displayBgImage2 = false, stopMainMenu = true;
				MainMenuBar = true;
				Home1I = true;
			} else if (event.type == sf::Event::Resized) {
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width),
				                                      static_cast<float>(event.size.height))));
				gui.setView(window.getView());
			}

			gui.handleEvent(event);
		}


		if (universalClock.getElapsedTime() >= sf::seconds(4.0f)) {
			isLoading = true;
		}

		if (universalClock.getElapsedTime() >= sf::seconds(10.0f)) {
			isLoading = false, displayBgImage = false;
			if (!stopMainMenu) {
				displayBgImage2 = true;
				bgImageTexture.loadFromFile("Start.jpg");
				background.setTexture(&bgImageTexture, true);
			}
		}

		if (universalClock.getElapsedTime() <= sf::seconds(4.0f)) {
			displayBgImage = true;
		}

		if (isLoading) {
			int i = 0;
			while (universalClock.getElapsedTime() < sf::seconds(10.0f)) {
				window.clear();
				window.draw(background);
				window.draw(logo);
				if (i >= 5)     i = 0;
				window.draw(loading);
				sf::Clock clock1;
				while (clock1.getElapsedTime() <= sf::seconds(1.0f))
					window.display();
				window.display();
				i++;
			}
		}

//----------------------------------------------------------------------------------------------



		window.clear();

		if (displayBgImage) {
			window.draw(background);
		} else if (displayBgImage2) {
			window.draw(background);
			window.draw(mainMenu);
			window.draw(mainMenu1);
			window.draw(Creater);
		}

		if (Home1O && !ExitT) {
			if (Home1I) {
				sf::Clock clock1;
				temp1 = WaitSB();
				bgImageTexture.loadFromFile(temp1);
				background.setTexture(&bgImageTexture, true);

				while (clock1.getElapsedTime() < sf::seconds(3.0f)) {
					window.draw(background);
					window.draw(logo);
					window.draw(loading);

					window.display();
				}
				Home1O = false;
			}
		}

		if (RandomB && !ExitT) {
			sf::Clock clock1;
			temp1 = WaitT();
			bgImageTexture.loadFromFile(temp1);
			background.setTexture(&bgImageTexture, true);

			while (clock1.getElapsedTime() < sf::seconds(2.0f)) {
				window.draw(background);
				window.draw(logo);
				window.draw(loading);

				window.display();
			}

			bgImageTexture.loadFromFile("Home.jpg");
			background.setTexture(&bgImageTexture, true);
			RandomB = false;
		}

		if (Home1I) {
			bgImageTexture.loadFromFile("Home.jpg");//
			background.setTexture(&bgImageTexture, true);
			Home2O = true;
		}

		if (Home2O && !ExitT) {
			if (Home2O) {
				if (MainMenuBar) {
					window.draw(background);
					window.draw(mainMenu);
					SoundB(TS, sound);
					gui.add(button[0]);
					gui.add(button[1]);
					gui.add(button[13]);
					gui.add(button[14]);

					gui.draw();
				}
			}
		}

		if (Home3O && !ExitT) {
			if (MainMenuBar) {
				if (RandomB && !ExitT) {

					sf::Clock clock1;
					temp1 = WaitT();
					bgImageTexture.loadFromFile(temp1);
					background.setTexture(&bgImageTexture, true);

					while (clock1.getElapsedTime() < sf::seconds(2.0f)) {
						window.draw(background);
						window.draw(logo);
						window.draw(loading);

						window.display();
					}

					RandomB = false;
				}

				bgImageTexture.loadFromFile("Home.jpg");
				background.setTexture(&bgImageTexture, true);
				window.draw(background);
				window.draw(mainMenu);
				gui.add(button[2]);
				gui.add(button[3]);
				gui.add(button[4]);
				gui.add(button[13]);
				gui.add(button[14]);
				gui.draw();
			}
		}

		if (Home4O && !ExitT) {
			if (MainMenuBar) {

				if (RandomB1 && !ExitT) {

					sf::Clock clock1;
					temp1 = WaitT();
					bgImageTexture.loadFromFile(temp1);
					background.setTexture(&bgImageTexture, true);

					while (clock1.getElapsedTime() < sf::seconds(2.0f)) {
						window.draw(background);
						window.draw(logo);
						window.draw(loading);

						window.display();
					}
					RandomB1 = false;
				}

				bgImageTexture.loadFromFile("TrainBG.jpg");
				background.setTexture(&bgImageTexture, true);
				window.draw(background);
				window.draw(mainMenu);

				SoundB(TS, sound);
				gui.add(button[5]);
				gui.add(button[6]);
				gui.add(button[13]);
				gui.add(button[14]);

				gui.draw();
			}
		}

		if (Home5O && !ExitT) {
			if (MainMenuBar) {
				if (RandomB2 && !ExitT) {

					sf::Clock clock1;
					temp1 = WaitB();
					bgImageTexture.loadFromFile(temp1);
					background.setTexture(&bgImageTexture, true);

					while (clock1.getElapsedTime() < sf::seconds(2.0f)) {
						window.draw(background);
						window.draw(logo);
						window.draw(loading);

						window.display();
					}
					RandomB2 = false;
				}

				bgImageTexture.loadFromFile("BogieBG.jpg");
				background.setTexture(&bgImageTexture, true);
				window.draw(background);
				window.draw(mainMenu);

				SoundB(TS, sound);
				gui.add(button[7]);
				gui.add(button[8]);
				gui.add(button[9]);
				gui.add(button[13]);
				gui.add(button[14]);

				gui.draw();
			}
		}

		if (Home6O && !ExitT) {
			if (MainMenuBar) {
				if (RandomB3 && !ExitT) {

					sf::Clock clock1;
					temp1 = WaitP();
					bgImageTexture.loadFromFile(temp1);
					background.setTexture(&bgImageTexture, true);

					while (clock1.getElapsedTime() < sf::seconds(2.0f)) {
						window.draw(background);
						window.draw(logo);
						window.draw(loading);

						window.display();
					}
					RandomB3 = false;
				}

				bgImageTexture.loadFromFile("PassBG.jpg");
				background.setTexture(&bgImageTexture, true);

				window.draw(background);
				window.draw(mainMenu);

				SoundB(TS, sound);
				gui.add(button[10]);
				gui.add(button[11]);
				gui.add(button[12]);
				gui.add(button[13]);
				gui.add(button[14]);

				gui.draw();
			}
		}


		if (ExitT) {
			sf::Clock clock2;
			T.DataSaving();
			T.RecordSaving();

			bgImageTexture.loadFromFile("ExitB.jpg");
			background.setTexture(&bgImageTexture, true);

			while (clock2.getElapsedTime() < sf::seconds(4.0f)) {
				window.draw(background);
				window.draw(logo);
				window.draw(saving);
				window.display();
			}

			gui.removeAllWidgets();
			window.close();
			return 0;
		}
		window.display();
	}


	system("pause");

	return 0;
}