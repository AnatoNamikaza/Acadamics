#include <SFML/Audio.hpp>
#include "Train.h"

int main(){

	bool displayBgImage = true, displayLoadingLogo = false, displayLoadingText = false, displayMainMenuText = false;

//	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Train");
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, 700), "Train");

	window.setFramerateLimit(60);

	tgui::Gui gui(window);


	sf::Texture texture, loadingLogo;
	texture.loadFromFile("TrainBackground.jpg");
	loadingLogo.loadFromFile("loadingLogo.jpeg");

	sf::Font font, loadingFont, mainMenuFont;
	font.loadFromFile("HRNFMono.ttf");
	loadingFont.loadFromFile("HRNFMono.ttf");
	mainMenuFont.loadFromFile("Assassin.ttf");

	sf::RectangleShape container(sf::Vector2f(window.getSize().x, window.getSize().y));
	container.setPosition(0, 0);
	container.setTexture(&texture);

	sf::CircleShape loadingSymbol(0.03 * window.getSize().x, 1366);
	loadingSymbol.setPosition( 0, window.getSize().y - loadingSymbol.getRadius() * 2 );
	loadingSymbol.setTexture(&loadingLogo);

	sf::Text loadingText(sf::String("Loading..."), loadingFont, 20);
	loadingText.setPosition( loadingSymbol.getPosition().x + loadingSymbol.getRadius() * 2 + (0.014641288 * window.getSize().x),
	                         window.getSize().y - loadingSymbol.getRadius() - loadingText.getLocalBounds().height );

	sf::Text mainMenuText(sf::String("Welcome to Waterloo Station"), mainMenuFont, static_cast<unsigned  int>(0.078125 * window.getSize().y));
	mainMenuText.setPosition( (static_cast<float>(window.getSize().x) / 2) - (mainMenuText.getLocalBounds().width / 2),
							  static_cast<float>(window.getSize().y) / 4 - mainMenuText.getLocalBounds().height );
	mainMenuText.setFillColor(sf::Color::Red);
	mainMenuText.setOutlineThickness(5.0f);
	mainMenuText.setOutlineColor(sf::Color::White);

	Train train;

	sf::SoundBuffer soundBuffer = sf::SoundBuffer();
	if ( !soundBuffer.loadFromFile("TrainSound2.wav") )
		std::cout << "File not found!\n";

	sf::Sound sound;
	sound.setBuffer(soundBuffer);
	sound.play();
	sound.setLoop(true);

	sf::Event event = sf::Event();

	tgui::Theme theme{"/usr/share/tgui-0.8/gui-builder/themes/Black.txt"};
	tgui::Theme::setDefault(&theme);

	auto *tabs = new tgui::Tabs::Ptr[5];

	for ( int i = 0; i < 5; i++ ){
		tabs[i] = tgui::Tabs::create();
		tabs[i]->setRenderer(theme.getRenderer("Tabs"));
		tabs[i]->setTabHeight(0.0390625 * window.getSize().y);
	}

	tabs[0]->add("Add Bogie", false);
	tabs[0]->setPosition("35%", "5%");
	tabs[0]->connect("TabSelected", [&](){ train.addBogie(window, font, gui); tabs[0]->deselect(); } );

	tabs[1]->add("Remove Bogie", false);
	tabs[1]->setPosition({"40.5%", "5%"});
	tabs[1]->connect("TabSelected", [&](){ train.removeBogie(window, font, gui); tabs[1]->deselect(); } );

	tabs[2]->add("Add Passengers", false);
	tabs[2]->setPosition({"48%", "5%"});
	tabs[2]->connect("TabSelected", [&](){ train.addPassengersToBogie(window, font, gui); tabs[2]->deselect(); } );

	tabs[3]->add("Print Train", false);
	tabs[3]->setPosition("56.5%", "5%");
	tabs[3]->connect("TabSelected", [&](){ train.printTrain(window, font, gui); tabs[3]->deselect(); } );

	tabs[4]->add("Print Bogie", false);
	tabs[4]->setPosition("62%", "5%");
	tabs[4]->connect("TabSelected", [&](){ train.printBogie(window, font, gui); tabs[4]->deselect(); } );

	gui.add(tabs[0]);
	gui.add(tabs[1]);
	gui.add(tabs[2]);
	gui.add(tabs[3]);
	gui.add(tabs[4]);

	auto menu = tgui::MenuBar::create();
	menu->setRenderer(theme.getRenderer("MenuBar"));
	menu->setSize(static_cast<float>(window.getSize().x), 22.f);
	menu->addMenu("File");
	menu->addMenuItem("Exit");
	menu->connectMenuItem( "File", "Exit", [&](){ gui.removeAllWidgets(); window.close(); } );
	gui.add(menu);

	sf::Clock globalClock;

	while (window.isOpen()){

		while (window.pollEvent(event)){
			if ( event.type == sf::Event::Closed )
				window.close();

			if ( globalClock.getElapsedTime() >= sf::seconds(6.0f) && sf::Event::KeyPressed )
				displayBgImage = false, displayMainMenuText = false;

			// When the window is resized, the view is changed
			else if (event.type == sf::Event::Resized){
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
				gui.setView(window.getView());
			}

			gui.handleEvent(event);
		}

		if ( globalClock.getElapsedTime() >= sf::seconds(2.0f) && displayBgImage ){
			displayLoadingText = true, displayLoadingLogo = true;
			while ( globalClock.getElapsedTime() <= sf::seconds(6.0f) ){
//				loadingSymbol.rotate(30);
				window.draw(loadingSymbol), window.draw(loadingText);
				window.display();
			}
		}

		if ( globalClock.getElapsedTime() >= sf::seconds(6.0f) && displayBgImage ){
			displayLoadingLogo = false, displayLoadingText = false;
			window.clear();
			texture.loadFromFile("TrainStation3.jpg");
			container.setTexture(&texture, true);
			displayMainMenuText = true;
		}


		window.clear(sf::Color::White);

		if ( displayBgImage )
			window.draw(container);

		if ( displayLoadingLogo )
			window.draw(loadingSymbol);

		if ( displayLoadingText )
			window.draw(loadingText);

		if ( displayMainMenuText )
			window.draw(mainMenuText);

		else if ( !displayBgImage ){
			gui.draw();
			train.drawTrain(window, font);
		}

		window.display();

	}

	return 0;
}


//			else if ( event.type == sf::Event::KeyPressed ){
//				if ( event.key.code == sf::Keyboard::Q )
//					window.close();
//
//				else if ( event.key.code == sf::Keyboard::A ){
//					std::cout << "Enter ID of Bogie to add: ";
//					short ID = 0;
//					std::cin >> ID;
//					train.addBogie(gui);
//				}
//
//				else if ( event.key.code == sf::Keyboard::R ){
//
//					if ( train.getNoOfBogies() > 1 ){
//
//						std::cout << "Enter ID of Bogie to remove: ";
//						short ID = 0;
//						std::cin >> ID;
//						train.removeBogie(ID);
//
//					}
//
//					else
//						std::cout << "No bogies to remove!\n";
//				}
//
//				else if ( event.key.code == sf::Keyboard::P ){
//
//					train.printTrain(window, font, width, height, gui);
//					window.display();
//
//				}
//
//				else if ( event.key.code == sf::Keyboard::B ){
//
//					bogie.AddPassengers(window, gui);
//					window.display();
//
////					sf::Clock clock;
////
////					while ( clock.getElapsedTime() < sf::seconds(5.0f) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
////					        && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::R) ){
////
////
////					}
////					short ID = 0;
////					std::cout << "Enter ID of bogie to add passengers in: ";
////					std::cin >> ID;
//				}
//			}
