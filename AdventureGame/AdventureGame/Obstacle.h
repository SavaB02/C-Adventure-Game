#pragma once
#include <string>
#include <fstream>      //file input and output
#include <iostream>
#include "Item.h"



class Area;

/**
* @class Obstacle
* @brief Represents an obstacle in the game.
*
* The Obstacle class stores descriptions, paths to .txt files (ASCII images),
* and the item required to solve the obstacle.
*/
class Obstacle
{
private:
    /**
    * @brief Name of the obstacle.
    */
    std::string name;
    /**
    * @brief Description of the obstacle.
    */
    std::string description;

    /**
    * @brief Path to .txt file containing the obstacle's ASCII image.
    */
    std::string obsImage;

    /**
    * @brief Name of the item required to solve this obstacle.
    */
    std::string requiredItem;

    /**
    * @brief Flag indicating whether the obstacle is solved (default: false).
    */
    bool solved;

    /**
    * @brief Name of an item that unlocks after solving this obstacle
    */
    std::string unlockItemName;

    /**
    * @brief Description of an item that unlocks after solving this obstacle
    */
    std::string unlockItemDescription;

    /**
    * @brief Flag indicating if unlocked pathway is opened (true) or closed (false)
    */
    bool unlockNewPathway = false;

    /**
    * @brief flag to indicate the type of the obstacle. Can be "pathway" or "item"
    */
    std::string obstacleType;

    /**
    * @brief array that stores 2 areas
    */
    Area* toJoin[2];

    /**
    * @brief item that obstacle gives after solving it
    */
    Item obstacleItem;

public:
    /**
    * @brief Constructs an Obstacle object.
    * @param i_name Name of the obstacle
    * @param i_description Description of the obstacle.
    * @param i_obsImage Path to the .txt file of the obstacle's ASCII image.
    * @param i_requiredItem Name of the item required to solve the obstacle.
    * @param i_obstacleType Flag to indicate the type of the obstacle. Can be "pathway" or "item"
    * @param i_obstacleItem Item that obstacle gives after solving it
    */
    Obstacle(std::string i_name, std::string i_description, std::string i_obsImage, std::string i_requiredItem, std::string i_obstacleType, Item i_obstacleItem);

    /**
    * @brief Constructs an Obstacle object.
    * @param i_name Name of the obstacle
    * @param i_description Description of the obstacle.
    * @param i_obsImage Path to the .txt file of the obstacle's ASCII image.
    * @param i_requiredItem Name of the item required to solve the obstacle.
    * @param i_obstacleType Flag to indicate the type of the obstacle. Can be "pathway" or "item"
    * @param i_toJoin1 First area to join with the second
    * @param i_toJoin2 Second area to join with the first
    */
    Obstacle(std::string i_name, std::string i_description, std::string i_obsImage, std::string i_requiredItem, std::string i_obstacleType, Area* i_toJoin1, Area* i_toJoin2);

    /**
    * @brief An empty construct of an Obstacle object.
    */
    Obstacle();

    /**
    * @brief Retrieves the name of the obstacle
    * @return Name of the obstacle
    */
    std::string getName();

    /**
    * @brief Prints the name of the obstacle.
    * @return The obstacle's name in the console
    */
    void printName();

    /**
    * @brief Prints the description of the obstacle.
    * @return The obstacle's description in the console
    */
    void printDescription();

    /**
    * @brief Retrieves the name of the item required to solve the obstacle.
    * @return The name of the required item.
    */
    std::string getRequiredItem();

    /**
    * @brief Displays the obstacle's ASCII image by printing the .txt file to the screen.
    */
    void printImage();

    /**
    * @brief Checks if the obstacle is solved.
    * @return True if the obstacle is solved, false otherwise.
    */
    bool isSolved();

    /**
    * @brief Marks the obstacle as solved (sets `solved` to true).
    */
    void solve();

    /**
    * @brief Unlocks an item after solving this obstacle
    * @param i_unlockItemName Name of the item that unlocks after solving this obstacle
    * @param i_unlockItemDescription Description of the item that unlocks after solving this obstacle
    */
    void setUnlockItem(std::string i_unlockItemName, std::string i_unlockItemDescription);

    /**
    * @brief Get a name of an item's that's being unlocked
    * @return Obstacle's unlockItemName
    */
    std::string getUnlockItemName();

    /**
    * @brief Get a description of an item that's being unlocked
    * @return Obstacle's unlockItemDescription
    */
    std::string getUnlockItemDescription();

    /**
    * @brief Unlocks a pathway after solving this obstacle
    * @param i_unlockNewPathway Bool check of the pathway that unlocks after solving this obstacle
    */
    void setUnlockPathway();

    /**
    * @brief Getter for unlockable Pathway (if an obstacle unlocks a pathway)
    * @return unlockNewPathway = true;
    */
    bool getUnlockPathway();

    /**
    * @brief Joins pathways from toJoin array
    */
    void joinPathways();

    /**
    * @brief Returns obstacle type
    * @return obstacle type
    */
    std::string getType();

    /**
    * @brief Gives the item after solving an obstacle
    */
    Item getObstacleItem();
};
