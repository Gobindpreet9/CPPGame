/****************************************************************************************************
FileName:           Card.h
Version:            1.0
Author:             Gobindpreet S. Makkar
Student Number:     040951845
Course Name/Number: C++ Programming, CST8219
Due Date:           August 7, 2020
Submission Date:    July 30, 2020
Professor:          Eric Torunski
Purpose:            Implement properties of a game card
****************************************************************************************************/
#include "Card.h"
namespace FinalProject {

	/*
	* Constructor of card
	*
	* @param face front sprite of card
	* @param back back sprite of card
	*/
	Card::Card(sf::Sprite* face, sf::Sprite* back) {
		this->face = face;
		this->back = back;
	}

	/*
	* Compares address of texture of sprite of 2 cards
	*
	* @return true if match found
	*/
	bool Card::operator==(const Card& other) {
		if (getSprite()->getTexture() == other.getSprite()->getTexture())
			return true;
		else
			return false;
	}

	/*
	* Set method for found
	* @param found value to set
	*/
	void Card::setFound(bool found) {
		this->found = found;
	}

	/*
	* Inverses the state of isUp parameter
	*/
	void Card::flip() {
		if (isUp) {
			isUp = false;
		}
		else {
			isUp = true;
		}
	}

	/*
	* Returns sprite of card based on the state of isUp
	* 
	* @return sprite of card currently displayed
	*/
	sf::Sprite* Card::getSprite() const {
		if (isUp)
			return face;
		else
			return back;
	}

	/*
	* Draws the card on screen based on state if it is not found
	*
	* @param window window to draw the card on
	*/
	void Card::renderCard(sf::RenderWindow* window) {
		getSprite()->setPosition(sf::Vector2f(widthOffset, heightOffset));
		if (!found)
		{
			if (isUp) {
				window->draw(*face);
			}
			else {
				window->draw(*back);
			}
		}
	}

	/*
	* Sets row in the grid and calculates height offset from top of window
	*
	* @param row row in the grid
	*/
	void Card::setRow(int row) {
		this->row = row;
		heightOffset = STARTING_HEIGHT_OFFSET + (GAP_BETWEEN_COLUMNS + CARD_WIDTH) * row;
	}

	/*
	* Sets row in the grid and calculates height offset from left of window 
	*
	* @param column column in the grid
	*/
	void Card::setColumn(int column) {
		this->column = column;
		widthOffset = STARTING_WIDTH_OFFSET + (GAP_BETWEEN_ROWS + CARD_HEIGHT) * column;
	}

	/*
	* Destructor for card
	*/
	Card::~Card() {
		delete face;
		delete back;
	}
}
