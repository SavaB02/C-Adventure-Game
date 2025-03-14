#pragma once
#include <vector>
#include "Item.h"		//include item class
#include <string>

class Player
{
private:
	string name;
	vector<Item> inventory;

public:
	Player(string i_name);

	bool hasItem(string itemName);

	void addItem(Item item);

	void removeItem(string itemName);

	vector<Item>& getInventory();	//return inventory

};


