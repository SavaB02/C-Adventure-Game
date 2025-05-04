#include "Option.h"

Option::Option(string i_description, string i_optionType, string i_optionText)
{
	description = i_description;
	optionType = i_optionType;
	optionText = i_optionText;
	hasInteracted = false;
}

Option::Option(string i_description, string i_optionType, string i_optionText, Item i_optionItem) //constructor for option with item
{
	description = i_description;
	optionType = i_optionType;
	optionText = i_optionText;
	optionItem = i_optionItem;
	hasInteracted = false;
}

Option::Option(string i_description, string i_optionType, string i_optionText, Obstacle i_optionObstacle)
{
	description = i_description;
	optionType = i_optionType;
	optionText = i_optionText;
	optionObstacle = i_optionObstacle;
	hasInteracted = false;
}

string Option::getDescription()
{
	return description;
}

string Option::getOptionType()
{
	return optionType;
}

string Option::getOptionText()
{
	return optionText;
}

Item Option::getOptionItem()
{
	return optionItem;
}

Obstacle& Option::getOptionObstacle()
{
	return optionObstacle;
}

bool Option::getHasInteracted()
{
	return hasInteracted;
}

//Marks the option as interacted 
void Option::solveInteracted()
{
	hasInteracted = true;
}
