#pragma once
#include <string>

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
    bool solved = false;

    /**
    * @brief Name of an item that unlocks after solving this obstacle
    */
    string unlockItemName;

    /**
    * @brief Description of an item that unlocks after solving this obstacle
    */
    string unlockItemDescription;

    /**
    * @brief Name of a pathway that unlocks after solving this obstacle
    */
    string unlockNewPathway;

public:
    /**
    * @brief Constructs an Obstacle object.
    * @param i_name Name of the obstacle
    * @param i_description Description of the obstacle.
    * @param i_obsImage Path to the .txt file of the obstacle's ASCII image.
    * @param i_requiredItem Name of the item required to solve the obstacle.
    */
    Obstacle(string i_name, string i_description, string i_obsImage, string i_requiredItem);

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
    * @brief Sets an item that's being unlocked
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
    * @brief Set the name of a path that's being unlocked 
    * @param i_unlockNewPathway Name of the pathway that unlocks after solving this obstacle
    */
    void setUnlockPathway(string i_unlockNewPathway);

    /**
    * @brief Get a name of a pathway that's being unlocked
    * @return Obstacle's unlockNewPathway
    */
    string getUnlockPathway();
};
