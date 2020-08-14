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
Purpose:            Declare Card properties and function prototypes
****************************************************************************************************/

#include <SFML/Graphics.hpp>

/*
* Try tinkering the bottom defines -- last two are the best but remember - their product should be EVEN to work
*/
#define CARD_WIDTH 110.0f
#define CARD_HEIGHT 150.0f
#define STARTING_WIDTH_OFFSET 150
#define STARTING_HEIGHT_OFFSET 75
#define GAP_BETWEEN_ROWS 35
#define GAP_BETWEEN_COLUMNS 75
#define NUMBER_OF_ROWS 5
#define NUMBER_OF_COLUMNS 4

namespace FinalProject {
	class Card
	{
	private:
		sf::Sprite* face; // face of card
		sf::Sprite* back; // back of card

		bool isUp = false; // true if card is facing up
		bool found = false; // true if card gets matched
		int row = 0; 
		int column = 0;
		float widthOffset = 0;
		float heightOffset = 0;

	public:
		Card(sf::Sprite* face, sf::Sprite* back);
		~Card();
		void flip();
		sf::Sprite* getSprite() const;
		void setRow(int);
		void setFound(bool);
		void setColumn(int);
		void renderCard(sf::RenderWindow* window);
		bool operator==(const Card& other);
	};
}
