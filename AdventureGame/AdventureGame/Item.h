#pragma once
#include <string>
#include <fstream>      //file input and output
#include <iostream>



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
    std::string name;

    /**
    * @brief Description of the item.
    */
    std::string description;

    /**
    * @brief Path to .txt file containing the item's ASCII image.
    */
    std::string itemImage;

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
    Item(std::string i_name, std::string i_description, std::string i_itemImage);

    /**
    * @brief Retrieves the name of the item.
    * @return The item's name.
    */
    std::string getName();

    /**
    * @brief Retrieves the description of the item.
    * @return The item's description.
    */
    std::string getDescription();

    /**
    * @brief Retrieves the image path of the item.
    * @return The item's image path.
    */
    std::string getImage();

    /**
    * @brief Displays the image's ASCII image by printing the .txt file to the screen.
    */
    void printImage();
};
