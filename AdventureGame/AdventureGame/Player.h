#pragma once
#include <vector>
#include "Item.h"		//include item class
#include <string>

/**
* @class Player
* @brief Represents a player in the game.
*
* The Player class stores the player's name and inventory.
* It provides functions to manage inventory items.
*/
class Player
{
private:
    /**
    * @brief Name of the player.
    */
    std::string name;

    /**
    * @brief The player's inventory, stored as a vector of Item objects.
    */
    std::vector<Item> inventory;

public:
    /**
    * @brief Constructs a Player object.
    * @param i_name The player's name.
    */
    Player(std::string i_name);

    /**
    * @brief Checks if the player has a specific item in their inventory.
    * @param itemName The name of the item to check.
    * @return True if the item is in the inventory, false otherwise.
    */
    bool hasItem(std::string itemName);

    /**
    * @brief Adds an item to the player's inventory.
    * @param item The item to add.
    */
    void addItem(Item item);

    /**
    * @brief Removes an item from the player's inventory.
    * @param itemName The name of the item to remove.
    */
    void removeItem(std::string itemName);

    /**
    * @brief Retrieves the player's inventory.
    * @return A reference to the vector containing the player's items.
    */
    std::vector<Item>& getInventory();
};

