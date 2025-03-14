#include "Area.h"
#include <fstream>      //file input and output
#include <iostream>

// Character class

Character::Character(string i_name, string i_description)
{
	name = i_name;
	description = i_description;
}

string Character::getName()
{
	return name;
}

string Character::getDescription()
{
	return description;
}

//string Character::talk()
//{
	//	return dialogues;
//}

//	Area class


Area::Area(string i_name, string i_farDescription, string i_mapPath, string i_mapInsidePath)
{
	name = i_name;
	farDescription = i_farDescription;
	mapPath = i_mapPath;
	mapInsidePath = i_mapInsidePath;
}

void Area::setName(string new_name)
{
	name = new_name;
}

string Area::getName()
{
	return name;
}


void Area::setDescription(string new_description)
{
	description = new_description;
}

string Area::getDescription()
{
	return description;
}

void Area::setExplore(string new_explore)
{
	explore = new_explore;
}

string Area::getExplore()
{
	return explore;
}

void Area::setFarDescription(string new_farDescription)
{
	farDescription = new_farDescription;
}

string Area::getFarDescription()
{
	return farDescription;
}

//void Area::addCharacter(Character& new_character)
//{
//	characters.push_back(&new_character);
//}

void Area::addPathway(Area& new_pathway)
{
	pathways.push_back(&new_pathway);
}

vector<Area*> Area::getPathways()
{
	return pathways;
}

string Area::getMapPath()
{
	return mapPath;
}

void Area::printMap()
{
	ifstream file(mapPath);
	if (!file) {
		cout << "Error opening file: " << mapPath << endl;
	}
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
}

void Area::printInside()
{
	ifstream file(mapInsidePath);
	if (!file) {
		cout << "Error opening file: " << mapInsidePath << endl;
	}
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
}

void Area::addObstacle(string i_description, string i_obsImage, string i_requiredItem)
{
	obstacles.push_back(Obstacle(i_description, i_obsImage, i_requiredItem));
}

void Area::addItem(string i_name, string i_description)
{
	items.push_back(Item(i_name, i_description));
}

void Area::removeItem(string i_name)
{
	auto it = remove_if(items.begin(), items.end(), [&](Item& item)
		{
			return item.getName() == i_name; //Match item name
		});

	//If item is found, remove it from the vector
	if (it != items.end())
	{
		items.erase(it, items.end());	//remove the matched item
	}
}

bool Area::hasItems()	// Returns true if there are items, false if the vector is empty
{
	return !items.empty(); 
}

void Area::exploreArea(Player& player)
{
	for (auto& obstacle : obstacles) {
		if (!obstacle.isSolved()) {
			cout << "Options: " << endl;
			cout << "1) Inspect Obstacle" << endl;
			cout << "2) Use Item" << endl;
			cout << "3) Leave" << endl;

			int choice;
			cin >> choice;

			if (choice == 1) {
				obstacle.getDescription();  // Show obstacle description again
			}
			else if (choice == 2) {
				// Let the player use an item from the inventory
				useItem(player, obstacle);
			}
			else if (choice == 3) {
				cout << "Leaving the area..." << endl;
				return;  // Go back to a previous menu or area
			}
		}
	}
}

void Area::useItem(Player& player, Obstacle& obstacle)
{
	// Display player's inventory
	cout << "Choose an item to use:" << endl;
	for (int i = 0; i < player.getInventory().size(); ++i) {
		cout << i + 1 << ") " << player.getInventory()[i].getName() << endl;
	}

	int itemChoice;
	cin >> itemChoice;

	if (itemChoice >= 1 && itemChoice <= player.getInventory().size()) {
		Item selectedItem = player.getInventory()[itemChoice - 1];	//creates a copy of players choice and stores it in this variable

		// Check if this item solves the obstacle
		if (selectedItem.getName() == obstacle.getRequiredItem()) {
			cout << "You used the " << selectedItem.getName() << " and solved the obstacle!" << endl;
			obstacle.solve();  // Mark the obstacle as solved
			player.removeItem(selectedItem.getName());  // Remove item from player's inventory
		}
		else {
			cout << "This item does not work on the obstacle." << endl;
		}
	}
}