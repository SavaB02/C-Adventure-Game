#pragma once
#include <string>
#include <fstream>      //file input and output
#include <iostream>

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

    /**
    * @brief Path to .txt file containing the item's ASCII image.
    */
    string itemImage;

public:
    /**
    * @brief An empty construct of an Item object.
    */
    Item();

    /**
    * @brief Constructs an Item object.
    * @param i_name The name of the item.
    * @param i_description The description of the item.
    * @param i_itemImage Path to the .txt file of the item's ASCII image
    */
    Item(string i_name, string i_description, string i_itemImage);

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

    /**
    * @brief Displays the image's ASCII image by printing the .txt file to the screen.
    */
    void printImage();
};
