#include "Area.h"
#include <fstream>      //file input and output
#include <iostream>

//	Area class


Area::Area()
{
}

Area::Area(std::string i_name, std::string i_overview, std::string i_mapPath, std::string i_mapInsidePath)
{
	name = i_name;
	overview = i_overview;
	mapPath = i_mapPath;
	mapInsidePath = i_mapInsidePath;
}

void Area::setName(std::string new_name)
{
	name = new_name;
}

std::string Area::getName()
{
	return name;
}

void Area::setDescription(std::string new_description)
{
	description = new_description;
}

std::string Area::getDescription()
{
	return description;
}

void Area::setExplore(std::string new_explore)
{
	explore = new_explore;
}

std::string Area::getExplore()
{
	return explore;
}

void Area::setOverview(std::string new_overview)
{
	overview = new_overview;
}

std::string Area::getOverview()
{
	return overview;
}

void Area::addPathway(Area& new_pathway)
{
	for (Area* existing : pathways)
	{
		if (existing->getName() == new_pathway.getName())
			return;
	}
	pathways.push_back(&new_pathway);
}

std::vector<Area*> Area::getPathways()
{
	return pathways;
}

std::string Area::getMapPath()
{
	return mapPath;
}

void Area::printMap()
{
	std::ifstream file(mapPath);
	if (!file) {
		std::cout << "Error opening file: " << mapPath << std::endl;
	}
	std::string line;
	while (getline(file, line))
	{
		std::cout << line << std::endl;
	}
}

void Area::printInside()	//print inside check
{
	std::ifstream file(mapInsidePath);
	if (!file) {
		std::cout << "Error opening file: " << mapInsidePath << std::endl;
	}
	std::string line;
	while (getline(file, line))
	{
		std::cout << line << std::endl;
	}
}

void Area::addObstacle(Obstacle i_obstacle)
{
	obstacles.push_back(i_obstacle);
}

Obstacle& Area::getObstacle(std::string i_name)
{
	for (auto& obstacle : obstacles) 
	{
		std::cout << obstacle.getName() << std::endl;
		if (obstacle.getName() == i_name) 
		{
			return obstacle;	//return the found obstacle
		}
	}
	throw std::runtime_error("Obstacle not found"); //error if not found
}

void Area::addItem(Item i_item)
{
	items.push_back(i_item);
}

void Area::removeItem(std::string i_name)
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
		std::cout << "|| [1] Inspect                                                                                                    ||" << std::endl;
		std::cout << "|| [2] Use Item                                                                                                   ||" << std::endl;
		std::cout << "|| [3] Leave                                                                                                      ||" << std::endl;
		std::cout << "||================================================================================================================||" << std::endl;
		std::cout << ">>> ";

		int choice;
		std::cin >> choice;

		if (std::cin.fail() || choice < 1 || choice > 3)
		{
			std::cout << "|| Invalid input. Press enter to try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			system("cls");
			obstacle.printImage();
			continue;
		}

		if (choice == 1)
		{
			system("cls");
			obstacle.printImage();
			std::cout << "|| ";
			obstacle.printDescription();
			std::cout << "|| Your Options are:                                                                                              ||" << std::endl;
			std::cout << "||================================================================================================================||" << std::endl;
		}
		else if (choice == 2)
		{
			std::cout << "||======================================||" << std::endl;
			std::cout << "||         Choose an item to use:       ||" << std::endl;
			std::cout << "||======================================||" << std::endl;
			std::cout << "|| [1] Go back                          ||" << std::endl;

			std::vector<Item>& inventory = player.getInventory();
			for (int i = 0; i < inventory.size(); ++i)
			{
				std::cout << "|| [" << i + 2 << "] " << inventory[i].getName() << std::endl;
			}
			std::cout << "||======================================||" << std::endl;

			int itemChoice;
			std::cout << "|| Enter your choice [1-" << inventory.size() + 1 << "]: ";
			std::cin >> itemChoice;

			if (itemChoice == 1)
			{
				system("cls");
				obstacle.printImage();
				continue; //go back to the previous menu
			}

			if (itemChoice < 2 || itemChoice > inventory.size() + 1)
			{
				std::cout << "|| Wrong input. Press enter to continue ||" << std::endl;
				std::cin.ignore();
				std::cin.get();
				system("cls");
				obstacle.printImage();
				continue;
			}

			Item selectedItem = inventory[itemChoice - 2];

			//check if item solves the obstacle
			if (selectedItem.getName() == obstacle.getRequiredItem())
			{
				std::cout << "|| You use: " << selectedItem.getName() << "... - success!" << std::endl;
				obstacle.solve();
				option.solveInteracted(); //mark the option as interacted
				player.removeItem(selectedItem.getName());

				if (obstacle.getType() == "item")
				{
					player.addItem(obstacle.getObstacleItem());
					std::cout << "|| You receive: " << obstacle.getObstacleItem().getName() << std::endl;
				}
				else if (obstacle.getType() == "pathway")
				{
					obstacle.joinPathways();
					std::cout << "|| A new path has opened!" << std::endl;
					std::cout << "|| Please, go back to the global map." << std::endl;
				}

				std::cout << "||======================================||" << std::endl;
				std::cout << "|| Press enter to continue...           ||" << std::endl;
				std::cin.ignore();
				std::cin.get();
				break;
			}
			else
			{
				std::cout << "|| This item doesn't seem to work...    ||" << std::endl;
				std::cout << "|| Press enter to continue..." << std::endl;
				std::cin.ignore();
				std::cin.get();
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
	std::cout << "Choose an item to use:" << std::endl;
	for (int i = 0; i < player.getInventory().size(); ++i) 
	{
		std::cout << "[" << i + 1 << "] " << player.getInventory()[i].getName() << std::endl;
	}

	int itemChoice;
	bool validInput = false;

	while (!validInput) 
	{
		std::cout << "Enter your choice [1-" << player.getInventory().size() << "]: ";
		if (std::cin >> itemChoice)
		{
			//checking if the choice is within the valid range
			if (itemChoice >= 1 and itemChoice <= player.getInventory().size()) 
			{
				validInput = true; //input is valid, exit loop
			}
			else 
			{
				std::cout << "Invalid choice! Please choose a number between 1 and " << player.getInventory().size() << "." << std::endl;
			}
		}
		else 
		{
			//if input is not an integer (e.g., user enters a letter or symbol)
			std::cout << "Invalid input! Please enter a number between 1 and " << player.getInventory().size() << "." << std::endl;
			std::cin.clear(); // Clear the error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore the rest of the invalid input
		}
	}

	Item selectedItem = player.getInventory()[itemChoice - 1]; //stores the selected item

	//check if this item solves the obstacle
	if (selectedItem.getName() == obstacle.getRequiredItem()) 
	{
		std::cout << "You used the " << selectedItem.getName() << " and solved the obstacle!" << std::endl;
		obstacle.solve();  //mark the obstacle as solved
		player.removeItem(selectedItem.getName());  //remove item from inventory


		if (obstacle.getType() == "pathway") 
		{
			std::cout << "A new pathway is unlocked!" << std::endl;
			obstacle.joinPathways();
		}
		else if (obstacle.getType() == "item") 
		{
			player.addItem(obstacle.getObstacleItem());
		}
		else 
		{
			std::cout << "Error." << std::endl;
		}
		
		std::cout << "Press enter to continue...";
		std::cin.ignore();
		std::cin.get();

		return true;
	}
	else 
	{
		std::cout << "This item does not work on the obstacle." << std::endl;
		std::cout << "Press enter to continue...";
		std::cin.ignore();
		std::cin.get();
		return false;
	}
}

void Area::addOption(Option i_option)
{
	options.push_back(i_option);
}

Option& Area::getOption(std::string i_description)
{
	for (Option& option : options)
	{
		if (option.getDescription() == i_description)
		{
			return option;
		}
	}

	throw std::runtime_error("Option not found: " + i_description);
}

Option& Area::getOption(int i_index)
{
	return options[i_index];
}

std::vector<Option> Area::getOptions()
{
	return options;
}

void Area::displayOptions()
{
	std::cout << "|| [1] Go back to the global map" << std::endl;

	// Display the rest of the options
	for (int i = 0; i < options.size(); ++i) 
	{
		if (!options[i].getHasInteracted()) 
		{
			std::cout << "|| [" << i + 2 << "] " << options[i].getDescription() << std::endl;
		}
	}
	std::cout << "||================================================================================================================||" << std::endl;
}

int Area::getOptionSize()
{
	return options.size();
}
