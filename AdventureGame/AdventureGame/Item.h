#pragma once
#include <string>

using namespace std;

/**
* @class Item
* @brief Represents an item in the game.
*
* The Item class stores the name and description of an item
* and provides basic getter functions.
*/
class Item
{
private:
    /**
    * @brief Name of the item.
    */
    string name;

    /**
    * @brief Description of the item.
    */
    string description;

public:
    /**
    * @brief Constructs an Item object.
    * @param i_name The name of the item.
    * @param i_description The description of the item.
    */
    Item(string i_name, string i_description);

    /**
    * @brief Retrieves the name of the item.
    * @return The item's name.
    */
    string getName();

    /**
    * @brief Retrieves the description of the item.
    * @return The item's description.
    */
    string getDescription();
};
