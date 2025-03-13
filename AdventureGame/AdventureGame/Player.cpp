#include "Player.h"

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


void Player::pickupItem(Item& item)
{
	inventory.push_back(item); //add item to inventory
}