#include "Area.h"
#include <fstream>      //file input and output
#include <iostream>

//	Area class


Area::Area()
{
}

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

void Area::printInside()	//print inside check
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

void Area::addObstacle(Obstacle i_obstacle)
{
	obstacles.push_back(i_obstacle);
}

Obstacle& Area::getObstacle(string i_name)
{
	for (auto& obstacle : obstacles) {
		if (obstacle.getName() == i_name) {
			return obstacle;	//return the found obstacle
		}
	}
	throw runtime_error("Obstacle not found"); // Throw an error if not found
}

void Area::addItem(Item i_item)
{
	items.push_back(i_item);
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
	for (Obstacle& obstacle : obstacles) //iterates through each obstacle in the obstacles vector
	{	
		if (!obstacle.isSolved()) //if isSolved = false, then it list options
		{					
			int choice = 0;

			while (!obstacle.isSolved()) //Loops until the obstacle is solved or player leaves
			{
				cout << "Options: " << endl;
				cout << "[1] Inspect" << endl;
				cout << "[2] Use Item" << endl;
				cout << "[3] Leave" << endl;

				//if loop to validate that the input is an integer and is within valid range (1-3)
				if (!(cin >> choice) or choice < 1 or choice > 3)
				{
					cout << "Invalid input. Please choose a valid option (1-3):" << endl;
					cin.clear(); // Clear error flag if non-integer input
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
				}
				else
				{
					if (choice == 1) 
					{
						obstacle.printName();
						obstacle.printDescription();  // Show obstacle description again
						continue;
					}
					else if (choice == 2) 
					{
						// Let the player use an item from the inventory
						useItem(player, obstacle);
					}
					else if (choice == 3) 
					{
						cout << "Leaving the area..." << endl;
						return;  // Go back to a previous menu or area
					}
				}
			}
		}
	}
}

bool Area::useItem(Player& player, Obstacle& obstacle)
{
	// Display the player's inventory
	cout << "Choose an item to use:" << endl;
	for (int i = 0; i < player.getInventory().size(); ++i) 
	{
		cout << "[" << i + 1 << "] " << player.getInventory()[i].getName() << endl;
	}

	int itemChoice;
	bool validInput = false;

	while (!validInput) 
	{
		cout << "Enter your choice [1-" << player.getInventory().size() << "]: ";
		if (cin >> itemChoice) 
		{
			// Check if the choice is within the valid range
			if (itemChoice >= 1 && itemChoice <= player.getInventory().size()) 
			{
				validInput = true; // Input is valid, exit loop
			}
			else 
			{
				cout << "Invalid choice! Please choose a number between 1 and " << player.getInventory().size() << "." << endl;
			}
		}
		else 
		{
			// If input is not an integer (e.g., user enters a letter or symbol)
			cout << "Invalid input! Please enter a number between 1 and " << player.getInventory().size() << "." << endl;
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the invalid input
		}
	}

	// Once we have a valid item choice, proceed with the item selection
	Item selectedItem = player.getInventory()[itemChoice - 1]; // Store the selected item

	// Check if this item solves the obstacle
	if (selectedItem.getName() == obstacle.getRequiredItem()) 
	{
		cout << "You used the " << selectedItem.getName() << " and solved the obstacle!" << endl;
		obstacle.solve();  // Mark the obstacle as solved
		player.removeItem(selectedItem.getName());  // Remove item from inventory


		if (obstacle.getType() == "pathway") {
			cout << "A new pathway is unlocked!" << endl;
			obstacle.joinPathways();
		}
		else if (obstacle.getType() == "item") {
			player.addItem(obstacle.getRewardItem());
		}
		else {
			cout << "error." << endl;
		}
		

		


		////USELESS
		//// Check if the obstacle unlocks a new item
		//string unlockableItemName = obstacle.getUnlockItemName();

		////MB USELESS ALREADY
		//if (!unlockableItemName.empty()) 
		//{
		//	string unlockableItemDescription = obstacle.getUnlockItemDescription();
		//	// Add the unlocked item to the player's inventory
		//	player.addItem(Item(unlockableItemName, unlockableItemDescription));
		//	cout << "You unlocked a new item: " << unlockableItemName << "!" << endl;
		//}

		////ALSO USELESS
		//// Check if the obstacle unlocks a new pathway
		//if (obstacle.getUnlockPathway())
		//{
		//	// Unlock the new pathway
		//	cout << "You unlocked a new path!" << endl;
		//	obstacle.setUnlockPathway();
		//}

		// Add a pause before returning
		cout << "Press any key to continue...";
		cin.ignore();
		cin.get();

		// Exit function after solving the obstacle
		return true;

	}
	else 
	{
		cout << "This item does not work on the obstacle." << endl;
		cout << "Press any key to continue...";
		cin.ignore();
		cin.get();  // Wait for user input before exiting
		return false;
	}
}

void Area::addOption(Option i_option)
{
	options.push_back(i_option);
}

Option Area::getOption(string i_description)
{
	for (Option option : options) 
	{
		if (option.getDescription() == i_description) 
		{
			return option;
		}
	}
	// If no option found return empty option
	return Option("", "", "");
}

Option Area::getOption(int i_index)
{
	return options[i_index];
}

vector<Option> Area::getOptions()
{
	return options;
}

void Area::displayOptions()
{
	cout << "[1] Go back" << endl; 

	// Display the rest of the options
	for (int i = 0; i < options.size(); ++i) 
	{
		if (!options[i].getOptionInteracted()) 
		{
			cout << "[" << i + 2 << "] " << options[i].getDescription() << endl;
		}
		
	}


	//some logic to output only those options that has hasInteracted as false
}

int Area::getOptionSize()
{
	return options.size();
}

void Area::updateOption(string oldOptionDescription, Option newOption) 
{
	for (Option option : options) 
	{
		if (option.getDescription() == oldOptionDescription) // Find the matching option
		{  
			option = newOption;
		}
	}
}
