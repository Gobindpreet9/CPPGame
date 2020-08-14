/****************************************************************************************************
FileName:           Game.cpp
Version:            1.0
Author:             Gobindpreet S. Makkar
Student Number:     040951845
Course Name/Number: C++ Programming, CST8219
Due Date:           August 7, 2020
Submission Date:    July 30, 2020
Professor:          Eric Torunski
Purpose:            Creates and draws elements on windows
****************************************************************************************************/
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <string>

namespace FinalProject {
	/*
	* Constructor for game class
	*/
	Game::Game() {
		numberOfCards = NUMBER_OF_COLUMNS * NUMBER_OF_ROWS;
		videoMode.height = (int)windowHeight;
		videoMode.width = (int)windowWidth;
		window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Close);
		initialize();
	}

	/*
	* Loads graphics and sounds for the game
	*/
	void Game::initialize()
	{
		loadMenu();
		initBackgrounds();
		initCards();
		loadSounds();
		initEndScreen();
		backgroundMusic.setLoop(true);
		backgroundMusic.play();
	}

	/*
	* Loads the graphics for game menu
	*/
	void Game::loadMenu() {
		// Declare and load a menuFont
		menuFont = new sf::Font();
		menuFont->loadFromFile("Acme-Regular.ttf");
		// Creating Start game option
		gameMenu.push_back(new sf::Text("Start Game", *menuFont));
		gameMenu[START_GAME]->setCharacterSize(30);
		gameMenu[START_GAME]->setStyle(sf::Text::Bold);
		gameMenu[START_GAME]->setFillColor(sf::Color::White);
		gameMenu[START_GAME]->setPosition(sf::Vector2f(windowWidth / 2.0f - gameMenu[START_GAME]->getLocalBounds().width / 2.0f, windowHeight / 2.0f - 99));
		// Creating quit option
		gameMenu.push_back(new sf::Text("Quit", *menuFont));
		gameMenu[QUIT]->setCharacterSize(30);
		gameMenu[QUIT]->setStyle(sf::Text::Bold);
		gameMenu[QUIT]->setFillColor(sf::Color::White);
		gameMenu[QUIT]->setPosition(sf::Vector2f(windowWidth / 2.0f - gameMenu[QUIT]->getLocalBounds().width / 2.0f, windowHeight / 2.0f - 49));
		gameMenu.shrink_to_fit(); // getting rid of extra space
	}

	/*
	* Loads graphics of cards
	*/
	void Game::initCards() {
		sf::Texture* texture;
		/*
		Loading back and front textures
		*/
		texture = new sf::Texture();
		if (!texture->loadFromFile("TileBackground.jpg"))
		{
			throw("Couldn't load card background");
		}
		backOfCard = texture;
		for (int i = 0; i < numberOfCards / 2; i++)
		{
			texture = new sf::Texture();
			if (!texture->loadFromFile("Cards//" + std::to_string(i + 1) + ".jpg"))
			{
				throw("Couldn't load card faces");
			}
			frontOfCards.push_back(texture);
		}

		/*
		Making 20 cards of which 10 are unique
		*/
		sf::Sprite* frontSprite, * backSprite;
		for (int i = 0; i < numberOfCards / 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				frontSprite = generateSprite(*frontOfCards[i], CARD_WIDTH, CARD_HEIGHT);
				backSprite = generateSprite(*backOfCard, CARD_WIDTH, CARD_HEIGHT);
				cards.push_back(new Card(frontSprite, backSprite));
			}
		}
		cards.shrink_to_fit(); // avoiding nulls in shuffle
		shuffleCards();
	}

	/*
	* Shuffles the cards and assigns them their new row and columns
	*/
	void Game::shuffleCards() {
		srand((unsigned int)time(0)); // seed for random shuffle
		std::random_shuffle(cards.begin(), cards.end()); // Shuffle the array

		/*
		Assigning rows and columns to cards
		*/
		for (int i = 0; i < numberOfCards; i++)
		{
			cards[i]->setRow((int)(i / NUMBER_OF_COLUMNS));
			cards[i]->setColumn((int)(i % NUMBER_OF_COLUMNS));
		}
	}

	/*
	* Loads backgrounds for game
	*/
	void Game::initBackgrounds()
	{
		//Game background
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile("Background.png"))
		{
			throw ("Could not load game background");
		}
		gameBackground = generateSprite(*texture, windowWidth, windowHeight);
		gameBackground->setPosition(sf::Vector2f(0, 0));

		//start menu background
		texture = new sf::Texture();
		if (!texture->loadFromFile("StartMenu.jpg"))
		{
			throw ("Could not load start screen background");
		}
		startScreen = generateSprite(*texture, windowWidth, windowHeight);
		startScreen->setPosition(sf::Vector2f(0, 0));
	}

	/*
	* Loads the sounds for games
	*/
	void Game::loadSounds() {
		// Background music
		sf::SoundBuffer* buffer = new sf::SoundBuffer;
		if (!buffer->loadFromFile("backgroundMusic.wav"))
			throw ("Could not load background music");
		backgroundMusic.setBuffer(*buffer);

		// Mouse click sound
		buffer = new sf::SoundBuffer;
		if (!buffer->loadFromFile("mouseClickSound.wav"))
			throw ("Could not load mouse click sound");
		mouseClickSound.setBuffer(*buffer);

		// card match sound
		buffer = new sf::SoundBuffer;
		if (!buffer->loadFromFile("cardMatchSound.wav"))
			throw ("Could not load card match sound");
		cardMatchSound.setBuffer(*buffer);

		// card not matched sound
		buffer = new sf::SoundBuffer;
		if (!buffer->loadFromFile("noMatchSound.wav"))
			throw ("Could not load card not matched sound");
		noMatchSound.setBuffer(*buffer);

		// game end sound
		buffer = new sf::SoundBuffer;
		if (!buffer->loadFromFile("gameEndSound.wav"))
			throw ("Could not game end sounds");
		gameEndSound.setBuffer(*buffer);

	}

	/*
	* Loads buttons to show at the end of the game
	*/
	void Game::initEndScreen() {
		sf::Texture* texture = new sf::Texture();
		// loading restart button
		if (!texture->loadFromFile("restartButton.png"))
		{
			throw ("Could not load restart button");
		}
		buttons.push_back(generateSprite(*texture, 175, 100));
		texture = new sf::Texture();
		// loading quit button for game
		if (!texture->loadFromFile("quitButton.png"))
		{
			throw ("Could not load quit button");
		}
		buttons.push_back(generateSprite(*texture, 175, 100));
		// Assigning positions to buttons
		buttons[0]->setPosition(sf::Vector2f(windowWidth / 2.0f - 175, windowHeight / 2.0f + 1));
		buttons[1]->setPosition(sf::Vector2f(windowWidth / 2.0f, windowHeight / 2.0f + 1));
		buttons.shrink_to_fit();
		// Creating text to show at the end screen
		gameEndText.push_back(new sf::Text("You matched all the cards in..", *menuFont));
		gameEndText[0]->setCharacterSize(30);
		gameEndText[0]->setStyle(sf::Text::Bold);
		gameEndText[0]->setFillColor(sf::Color::Black);
		gameEndText[0]->setPosition(sf::Vector2f(windowWidth / 2.0f - gameEndText[0]->getLocalBounds().width / 2.0f, windowHeight / 2.0f - 99));
		gameEndText.push_back(new sf::Text("Moves!", *menuFont));
		gameEndText[1]->setCharacterSize(30);
		gameEndText[1]->setStyle(sf::Text::Bold);
		gameEndText[1]->setFillColor(sf::Color::Black);
		gameEndText[1]->setPosition(sf::Vector2f(windowWidth / 2.0f - 25, windowHeight / 2.0f - 49)); 
		gameEndText.push_back(new sf::Text(std::to_string(numberOfMoves), *menuFont));
		gameEndText[2]->setCharacterSize(30);
		gameEndText[2]->setStyle(sf::Text::Bold);
		gameEndText[2]->setFillColor(sf::Color::Red);
		gameEndText[2]->setPosition(sf::Vector2f(windowWidth / 2.0f - gameEndText[2]->getLocalBounds().width - 40, windowHeight / 2.0f - 49));
		gameEndText.shrink_to_fit();
	}

	/*
	* Updates game state based on user interaction
	*/
	void Game::update() {
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window->close();
				break;
			}
		}
		updateMousePosition(); // mouse position on screen
		if (!gameEnd && isGameOn)
		{
			updateCards();
		}
		if (!isGameOn && !gameEnd)
		{
			updateMenu();
		}
		if (gameEnd) {
			handleButton();
		}
		if (cardsMatched == numberOfCards / 2)
		{
			gameEnd = true;
		}
	}

	/*
	* Update states of cards based on user choice
	*/
	void Game::updateCards() {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!mouseHeld) {
				mouseClickSound.play();
				mouseHeld = true;
				for (int i = 0; i < numberOfCards; i++)
				{
					if (cards[i]->getSprite()->getGlobalBounds().contains(mousePosition)) {
						numberOfMoves++;
						cards[i]->flip();
						render();
						if (!secondChoice) {
							cardSelected = i;
							secondChoice = true; // next card clicked will be second one
						}
						else {
							if (*cards[cardSelected] == *cards[i] && cardSelected != i) {
								cardsMatched++; // found match
								// update states
								cards[cardSelected]->setFound(true);
								cards[i]->setFound(true);
								//check game end condition
								if (cardsMatched == numberOfCards / 2)
								{
									updateEndGameText();
									isGameOn = false;
									gameEnd = true;
									gameEndSound.play();
								}
								else {
									cardMatchSound.play();
								}
								sf::sleep(sf::milliseconds(3000)); // sleep to let user see
							}
							else {
								noMatchSound.play();
								sf::sleep(sf::milliseconds(3000));  // sleep to let user see
								// didn't find a match, turn over cards again
								cards[cardSelected]->flip(); 
								cards[i]->flip();
								cardSelected = -1;
							}
							secondChoice = false;
						}
					}
				}
			}
		}
		else {
			mouseHeld = false;
		}
	}

	void Game::updateEndGameText() {
		delete gameEndText[2];
		gameEndText[2] = new sf::Text(std::to_string(numberOfMoves), *menuFont);
		gameEndText[2]->setCharacterSize(30);
		gameEndText[2]->setStyle(sf::Text::Bold);
		gameEndText[2]->setFillColor(sf::Color::Red);
		gameEndText[2]->setPosition(sf::Vector2f(windowWidth / 2.0f - gameEndText[2]->getLocalBounds().width - 40, windowHeight / 2.0f - 49));
	}
	/*
	* Updates display screen from user's choice on start screen
	*/
	void Game::updateMenu() {
		for (int i = 0; i < gameMenu.size(); i++)
		{
			// Underline text on mouse hover
			if (gameMenu[i]->getGlobalBounds().contains(mousePosition)) {
				gameMenu[i]->setCharacterSize(31);
				gameMenu[i]->setStyle(sf::Text::Underlined);
			}
			else {
				gameMenu[i]->setStyle(sf::Text::Regular);
				gameMenu[i]->setCharacterSize(30);
			}
		}
		// handle mouse clicks
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!mouseHeld) {
				mouseHeld = true;
				mouseClickSound.play();
				if (gameMenu[START_GAME]->getGlobalBounds().contains(mousePosition)) {
					isGameOn = true;
				}
				else if (gameMenu[QUIT]->getGlobalBounds().contains(mousePosition)) {
					window->close();
				}
			}
		}
		else {
			mouseHeld = false;
		}
	}

	/*
	* Updates display screen from user's choice on game-end screen
	*/
	void Game::handleButton() {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!mouseHeld) {
				mouseHeld = true;
				mouseClickSound.play();
				if (buttons[0]->getGlobalBounds().contains(mousePosition)) {
					// resets everything required for new game
					gameEnd = false;
					numberOfMoves = 0;
					for (int i = 0; i < numberOfCards; i++)
					{
						cards[i]->flip();
						cards[i]->setFound(false);
					}
					shuffleCards();
					isGameOn = true;
					cardsMatched = 0;
				}
				else if (buttons[1]->getGlobalBounds().contains(mousePosition)) {
					window->close();
				}
			}
		}
		else {
			mouseHeld = false;
		}
	}

	/*
	* draws start screen on window
	*/
	void Game::renderStartScreen() {
		window->draw(*startScreen);
		// Draw Game Menu
		for (int i = 0; i < gameMenu.size(); i++)
		{
			window->draw(*gameMenu[i]);
		}
	}

	/*
	* draws game on window
	*/
	void Game::renderGame() {
		sf::Texture texture;

		//Draw gameBackground
		window->draw(*gameBackground);

		//Top-left border
		sf::Sprite tlBorder;
		if (!texture.loadFromFile("TopLeftBorder.png"))
		{
			// error...
		}
		tlBorder = *generateSprite(texture, 200, 200);
		tlBorder.setPosition(sf::Vector2f(0, 0));
		window->draw(tlBorder);

		// rendering cards
		for (int i = 0; i < numberOfCards; i++)
		{
			cards[i]->renderCard(window);
		}
	}

	/*
	* draws end game screen on window
	*/
	void Game::renderGameEndScreen() {
		window->draw(*gameBackground);
		for (int i = 0; i < gameEndText.size(); i++)
		{
			window->draw(*gameEndText[i]);
		}
		for(int i = 0; i < buttons.size(); i++){
			window->draw(*buttons[i]);
		}
	}

	/*
	* draws the window
	*/
	void Game::render() {
		window->clear();

		if (!isGameOn && !gameEnd)
		{
			renderStartScreen();
		}
		else if (isGameOn) {
			renderGame();
		}
		else {
			renderGameEndScreen();
		}

		window->display();
	}

	/*
	* sprite builder method
	*
	* @param width preferred width of returning sprite
	* @param height preferred height of returning sprite
	* @return pointer to generated sprite
	*/
	sf::Sprite* Game::generateSprite(sf::Texture& texture, float width, float height)
	{
		sf::Sprite* returnSprite = new sf::Sprite();
		returnSprite->setTexture(texture);
		sf::Vector2f targetSize(width, height);
		returnSprite->setScale(targetSize.x / returnSprite->getLocalBounds().width, targetSize.y / returnSprite->getLocalBounds().height);
		return returnSprite;
	}

	/*
	* Gets the position of mouse on screen
	*/
	void Game::updateMousePosition() {
		mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	}

	/*
	* Returns true if game is running
	*/
	bool Game::isGameRunning() {
		return window->isOpen();
	}

	/*
	* Destructor for game, clears all memory on heap
	*/
	Game::~Game() {
		delete window;
		// Deleting cards
		delete backOfCard;
		for (int i = 0; i < numberOfCards / 2; i++)
		{
			delete frontOfCards[i];
		}
		for (int i = 0; i < numberOfCards; i++)
		{
			delete cards[i];
		}
		// Deleting backgrounds and menu
		delete startScreen->getTexture();
		delete startScreen;
		delete gameBackground->getTexture();
		delete gameBackground;
		for (int i = 0; i < buttons.size(); i++)
		{
			delete buttons[i]->getTexture();
			delete buttons[i];
		}
		delete menuFont;
		for (int i = 0; i < gameMenu.size(); i++)
		{
			delete gameMenu[i];
		}
		// Deleting sound buffers
		delete backgroundMusic.getBuffer();
		delete cardMatchSound.getBuffer();
		delete gameEndSound.getBuffer();
		delete mouseClickSound.getBuffer();
		delete noMatchSound.getBuffer();
	}
}

