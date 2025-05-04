#pragma once
#include <string>
#include "Item.h"
#include "Obstacle.h"

using namespace std;

/**
* @class Option
* @brief Represents options in the game.
*
* The Item class stores the description and type of the option,
* as well as the text describing that option.
* and provides basic getter functions.
*/
class Option
{
private:
	/**
	* @brief Description of the option.
	*/
	string description;
	/**
	* @brief Option type. Can be 'text', 'item' or 'obstacle'.
	*/
	string optionType = "";
	/**
	* @brief Option text that appears when interacting with an option.
	*/
	string optionText;
	/**
	* @brief Item that an option gives on interacting
	*/
	Item optionItem;
	/**
	* @brief Obstacle attached to an option
	*/
	Obstacle optionObstacle;
	/**
	* @brief Flag to check if interacted with an object
	*/
	bool hasInteracted;			

public:
	Option(string i_description, string i_optionType, string i_optionText);
	Option(string i_description, string i_optionType, string i_optionText, Item i_optionItem);
	Option(string i_description, string i_optionType, string i_optionText, Obstacle i_optionObstacle);

	/**
	* @brief Retrieves the description of the option.
	* @return The option's description.
	*/
	string getDescription();

	/**
	* @brief Retrieves the type of the option.
	* @return The option's type.
	*/
	string getOptionType();

	/**
	* @brief Retrieves the option text.
	* @return The option's text.
	*/
	string getOptionText();

	/**
	* @brief Retrieves the item that the option gives.
	* @return The option's item.
	*/
	Item getOptionItem();

	/**
	* @brief Retrieves the obstacle that the option has.
	* @return The option's obstacle.
	*/
	Obstacle& getOptionObstacle();

	/**
	* @brief Returns true if the option has been interacted with(solved)
	* @return hasInteracted.
	*/
	bool getHasInteracted();

	/**
	* @brief Renders option as solved by making hasInteracted = true
	*/
	void solveInteracted();

};

