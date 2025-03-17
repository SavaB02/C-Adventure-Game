#include "Player.h"
#include <iostream>

Player::Player(string i_name)
{
	name = i_name;
}

bool Player::hasItem(string itemName)
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

void Player::removeItem(string itemName)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it) {
		if (it->getName() == itemName) {
			inventory.erase(it);  // Remove the item from the player's inventory
			return;  // Exit after removing the item
		}
	}
	cout << "Item not found in inventory!" << endl;  // If the item was not found
}

vector<Item>& Player::getInventory()
{
	return inventory;
}