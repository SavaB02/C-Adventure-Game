#include "Player.h"
#include <iostream>

Player::Player(std::string i_name)
{
	name = i_name;
}

bool Player::hasItem(std::string itemName)
{
	for (auto& item : inventory)
	{
		if (item.getName() == itemName)
		{
			return true; //item found
		}
	}
	return false; //item not found
}


void Player::addItem(Item item)
{
	inventory.push_back(item); //add item to inventory
}

void Player::removeItem(std::string itemName)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it) {
		if (it->getName() == itemName) 
		{
			inventory.erase(it);  //remove the item from the player's inventory
			return;  //exit after removing the item
		}
	}
	std::cout << "Item not found in inventory!" << std::endl;  //if the item was not found
}

std::vector<Item>& Player::getInventory()
{
	return inventory;
}
