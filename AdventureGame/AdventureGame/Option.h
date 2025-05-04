#pragma once
#include <string>
#include "Item.h"
#include "Obstacle.h"

using namespace std;

class Option
{
private:
	string description;
	string optionType = "";		//can be 'text', 'item' or 'obstacle'. 
	string optionText;
	Item optionItem;
	Obstacle optionObstacle;
	bool hasInteracted;			//flag to check if interacted with an object

public:
	Option(string i_description, string i_optionType, string i_optionText);
	Option(string i_description, string i_optionType, string i_optionText, Item i_optionItem);
	Option(string i_description, string i_optionType, string i_optionText, Obstacle i_optionObstacle);

	string getDescription();

	string getOptionType();

	string getOptionText();

	Item getOptionItem();

	Obstacle& getOptionObstacle();

	bool getHasInteracted();

	void solveInteracted();

};

