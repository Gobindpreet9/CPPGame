/****************************************************************************************************
FileName:           Game.h
Version:            1.0
Author:             Gobindpreet S. Makkar
Student Number:     040951845
Course Name/Number: C++ Programming, CST8219
Due Date:           August 7, 2020
Submission Date:    July 30, 2020
Professor:          Eric Torunski
Purpose:            Create and launch game
****************************************************************************************************/
#include <iostream>
#include "Game.h"

int main()
{
    FinalProject::Game game;

    while (game.isGameRunning())
    {
        game.update();
        game.render();
    }
	
	return 0;
}
