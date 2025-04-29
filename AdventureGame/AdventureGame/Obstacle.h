class Area;

#pragma once
#include <string>
#include "Area.h"

using namespace std;

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
    string name;
    /**
    * @brief Description of the obstacle.
    */
    string description;

    /**
    * @brief Path to the .txt file containing the obstacle's ASCII image.
    */
    string obsImage;

    /**
    * @brief Name of the item required to solve this obstacle.
    */
    string requiredItem;

    /**
    * @brief Flag indicating whether the obstacle is solved (default: false).
    */
    bool solved;

    /**
    * @brief Name of an item that unlocks after solving this obstacle
    */
    string unlockItemName;

    /**
    * @brief Description of an item that unlocks after solving this obstacle
    */
    string unlockItemDescription;

    /**
    * @brief Flag indicating if unlocked pathway is opened (true) or closed (false)
    */
    bool unlockNewPathway = false;

    string obstacleType;
    Area* toJoin[2];
    Item obstacleItem;

public:
    /**
    * @brief Constructs an Obstacle object.
    * @param i_name Name of the obstacle
    * @param i_description Description of the obstacle.
    * @param i_obsImage Path to the .txt file of the obstacle's ASCII image.
    * @param i_requiredItem Name of the item required to solve the obstacle.
    */
    Obstacle(string i_name, string i_description, string i_obsImage, string i_requiredItem, string i_obstacleType, Item i_obstacleItem);
    Obstacle(string i_name, string i_description, string i_obsImage, string i_requiredItem, string i_obstacleType, Area* i_toJoin1, Area* i_toJoin2);

    /**
    * @brief An empty construct of an Obstacle object.
    */
    Obstacle();

    /**
    * @brief Retrieves the name of the obstacle
    * @return Name of the obstacle
    */
    string getName();

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
    string getRequiredItem();

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
    void setUnlockItem(string i_unlockItemName, string i_unlockItemDescription);

    /**
    * @brief Get a name of an item's that's being unlocked
    * @return Obstacle's unlockItemName
    */
    string getUnlockItemName();

    /**
    * @brief Get a description of an item that's being unlocked
    * @return Obstacle's unlockItemDescription
    */
    string getUnlockItemDescription();

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

    //Joins pathways from toJoin array
    void joinPathways();

    //returns obstacle type
    string getType();

    //returns obstacle's item (that it gives)
    Item getRewardItem();
};
