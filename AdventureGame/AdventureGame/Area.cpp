#include "Area.h"
#include <fstream>      //file input and output
#include <iostream>

//	Area class


Area::Area()
{
}

Area::Area(string i_name, string i_overview, string i_mapPath, string i_mapInsidePath)
{
	name = i_name;
	overview = i_overview;
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

void Area::setOverview(string new_overview)
{
	overview = new_overview;
}

string Area::getOverview()
{
	return overview;
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
	for (auto& obstacle : obstacles) 
	{
		cout << obstacle.getName() << endl;
		if (obstacle.getName() == i_name) 
		{
			return obstacle;	//return the found obstacle
		}
	}
	throw runtime_error("Obstacle not found"); //error if not found
}

void Area::addItem(Item i_item)
{
	items.push_back(i_item);
}

void Area::removeItem(string i_name)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].getName() == i_name)
		{
			items.erase(items.begin() + i);
			return;
		}
	}
}

bool Area::hasItems()
{
	return !items.empty(); 
}

void Area::exploreArea(Player& player, Option& option)
{
	Obstacle& obstacle = option.getOptionObstacle();

	while (!obstacle.isSolved())
	{
		cout << "|| [1] Inspect                                                                                                    ||" << endl;
		cout << "|| [2] Use Item                                                                                                   ||" << endl;
		cout << "|| [3] Leave                                                                                                      ||" << endl;
		cout << "||================================================================================================================||" << endl;
		cout << ">>> ";

		int choice;
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > 3)
		{
			cout << "|| Invalid input. Press enter to try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			system("cls");
			obstacle.printImage();
			continue;
		}

		if (choice == 1)
		{
			system("cls");
			obstacle.printImage();
			cout << "|| ";
			obstacle.printDescription();
			cout << "|| Your Options are:                                                                                              ||" << endl;
			cout << "||================================================================================================================||" << endl;
		}
		else if (choice == 2)
		{
			cout << "||======================================||" << endl;
			cout << "||         Choose an item to use:" << "       ||" << endl;
			cout << "||======================================||" << endl;
			vector<Item>& inventory = player.getInventory();
			for (int i = 0; i < inventory.size(); ++i)
			{
				cout << "|| [" << i + 1 << "] " << inventory[i].getName() << endl;
			}
			cout << "||======================================||" << endl;

			int itemChoice;
			cout << "|| Enter your choice [1-" << inventory.size() << "]: ";
			cin >> itemChoice;

			if (itemChoice < 1 || itemChoice > inventory.size())
			{
				cout << "|| Wrong input. Press enter to continue ||" << endl;
				cin.ignore();
				cin.get();
				system("cls");
				obstacle.printImage();
				continue;
			}

			Item selectedItem = inventory[itemChoice - 1];

			//check if item solves the obstacle
			if (selectedItem.getName() == obstacle.getRequiredItem())
			{
				cout << "|| You use: " << selectedItem.getName() << "... - success!" << endl;
				obstacle.solve();
				option.solveInteracted(); //mark the option as interacted
				player.removeItem(selectedItem.getName());

				if (obstacle.getType() == "item")
				{
					player.addItem(obstacle.getObstacleItem());
					cout << "|| You receive: " << obstacle.getObstacleItem().getName() << endl;
				}
				else if (obstacle.getType() == "pathway")
				{
					obstacle.joinPathways();
					cout << "|| A new path has opened!" << endl;
				}

				cout << "||======================================||" << endl;
				cout << "|| Press enter to continue...           ||" << endl;
				cin.ignore();
				cin.get();
				break;
			}
			else
			{
				cout << "|| This item doesn't seem to work...    ||" << endl;
				cout << "|| Press enter to continue..." << endl;
				cin.ignore();
				cin.get();
				system("cls");
				obstacle.printImage();
				continue;
			}
		}
		else if (choice == 3)
		{
			return;
		}
	}
}

bool Area::useItem(Player& player, Obstacle& obstacle)
{
	//display the player's inventory
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
			//checking if the choice is within the valid range
			if (itemChoice >= 1 and itemChoice <= player.getInventory().size()) 
			{
				validInput = true; //input is valid, exit loop
			}
			else 
			{
				cout << "Invalid choice! Please choose a number between 1 and " << player.getInventory().size() << "." << endl;
			}
		}
		else 
		{
			//if input is not an integer (e.g., user enters a letter or symbol)
			cout << "Invalid input! Please enter a number between 1 and " << player.getInventory().size() << "." << endl;
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the rest of the invalid input
		}
	}

	Item selectedItem = player.getInventory()[itemChoice - 1]; //stores the selected item

	//check if this item solves the obstacle
	if (selectedItem.getName() == obstacle.getRequiredItem()) 
	{
		cout << "You used the " << selectedItem.getName() << " and solved the obstacle!" << endl;
		obstacle.solve();  //mark the obstacle as solved
		player.removeItem(selectedItem.getName());  //remove item from inventory


		if (obstacle.getType() == "pathway") 
		{
			cout << "A new pathway is unlocked!" << endl;
			obstacle.joinPathways();
		}
		else if (obstacle.getType() == "item") 
		{
			player.addItem(obstacle.getObstacleItem());
		}
		else 
		{
			cout << "Error." << endl;
		}
		
		cout << "Press enter to continue...";
		cin.ignore();
		cin.get();

		return true;
	}
	else 
	{
		cout << "This item does not work on the obstacle." << endl;
		cout << "Press enter to continue...";
		cin.ignore();
		cin.get();  
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

Option& Area::getOption(int i_index)
{
	return options[i_index];
}

vector<Option> Area::getOptions()
{
	return options;
}

void Area::displayOptions()
{
	cout << "|| [1] Go back to the global map" << endl; 

	// Display the rest of the options
	for (int i = 0; i < options.size(); ++i) 
	{
		if (!options[i].getHasInteracted()) 
		{
			cout << "|| [" << i + 2 << "] " << options[i].getDescription() << endl;
		}
	}
	cout << "||================================================================================================================||" << endl;
}

int Area::getOptionSize()
{
	return options.size();
}
