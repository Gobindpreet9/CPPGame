#pragma once

/****************************************************************************************************
FileName:           Game.h
Version:            1.0
Author:             Gobindpreet S. Makkar
Student Number:     040951845
Course Name/Number: C++ Programming, CST8219
Due Date:           August 7, 2020
Submission Date:    July 30, 2020
Professor:          Eric Torunski
Purpose:            Declare Game properties and function prototypes
****************************************************************************************************/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "vector"
#include "Card.h"

#define START_GAME 0
#define QUIT 1

namespace FinalProject {
	class Game
	{
	private:
		sf::RenderWindow* window = nullptr;
		sf::VideoMode videoMode;
		sf::Event event;
		std::vector<sf::Text*> gameMenu;
		sf::Font* menuFont;
		sf::Sound mouseClickSound;
		sf::Sound backgroundMusic;
		sf::Sound cardMatchSound;
		sf::Sound noMatchSound;
		sf::Sound gameEndSound;
		std::vector<sf::Text*> gameEndText;
		sf::Sprite* startScreen;
		sf::Sprite* gameBackground;
		std::vector<sf::Sprite*> buttons;
		sf::Texture* backOfCard;
		std::vector<sf::Texture*> frontOfCards; 
		std::vector<Card*> cards; // Vector to store cards
		sf::Vector2f mousePosition; 
		int numberOfCards;
		int numberOfMoves = 0;
		int cardsMatched = 0;
		int cardSelected = -1; // index of current selected card
		bool gameEnd = false;
		bool secondChoice = false;
		bool mouseHeld = false;
		bool isGameOn = false;
		float windowHeight = NUMBER_OF_ROWS * CARD_HEIGHT + (NUMBER_OF_ROWS - 1) * GAP_BETWEEN_ROWS + 2 * STARTING_HEIGHT_OFFSET;
		float windowWidth = NUMBER_OF_COLUMNS * CARD_WIDTH + (NUMBER_OF_COLUMNS - 1) * GAP_BETWEEN_COLUMNS + 2 * STARTING_WIDTH_OFFSET;
		void initialize();
		void initCards();
		void shuffleCards();
		void initBackgrounds();
		void loadSounds();
		void loadMenu();
		void initEndScreen();
		void updateCards();
		void updateEndGameText();
		void updateMenu();
		void handleButton();
		void updateMousePosition();
		void renderStartScreen();
		void renderGame();
		void renderGameEndScreen();
		sf::Sprite* generateSprite(sf::Texture& texture, float width, float height);

	public:
		Game();
		~Game();
		void update();
		void render();
		bool isGameRunning();
	};
}
