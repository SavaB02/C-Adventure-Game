#include "Obstacle.h"
#include "Area.h"



//Obstacle that gives an item after solving
Obstacle::Obstacle(std::string i_name, std::string i_description, std::string i_obsImage, std::string i_requiredItem, std::string i_obstacleType, Item i_obstacleItem)
{
	name = i_name;
	description = i_description;
	obsImage = i_obsImage;
	requiredItem = i_requiredItem;
	unlockItemDescription = "";
	unlockItemName = "";
	unlockNewPathway = false;
	solved = false;
	obstacleType = i_obstacleType;
	obstacleItem = i_obstacleItem;
}

//Obstacle that opens a path after solving
Obstacle::Obstacle(std::string i_name, std::string i_description, std::string i_obsImage, std::string i_requiredItem, std::string i_obstacleType, Area* i_toJoin1, Area* i_toJoin2)
{
	name = i_name;
	description = i_description;
	obsImage = i_obsImage;
	requiredItem = i_requiredItem;
	unlockItemDescription = "";
	unlockItemName = "";
	unlockNewPathway = false;
	solved = false;
	obstacleType = i_obstacleType;
	obstacleItem = Item();
	toJoin[0] = i_toJoin1;
	toJoin[1] = i_toJoin2;
}

Obstacle::Obstacle()
{}

std::string Obstacle::getName()
{
	return name;
}

void Obstacle::printName()
{
	std::cout << name << std::endl;
}

void Obstacle::printDescription()
{
	std::cout << description << std::endl;
	std::cout << "||================================================================================================================||" << std::endl;
}

std::string Obstacle::getRequiredItem()
{
	return requiredItem;
}


void Obstacle::printImage()
{
	std::ifstream file(obsImage);
	if (!file) {
		std::cout << "Error opening file: " << obsImage << std::endl;
	}
	std::string line;
	while (getline(file, line))
	{
		std::cout << line << std::endl;
	}
}

bool Obstacle::isSolved()
{
	return solved;
}

void Obstacle::solve()
{
	solved = true;	// Mark the obstacle as solved
}


void Obstacle::setUnlockItem(std::string i_unlockItemName, std::string i_unlockItemDescription)
{
	unlockItemName = i_unlockItemName;
	unlockItemDescription = i_unlockItemDescription;
}

std::string Obstacle::getUnlockItemName()
{
	return unlockItemName;
}

std::string Obstacle::getUnlockItemDescription()
{
	return unlockItemDescription;
}

void Obstacle::setUnlockPathway()
{
	unlockNewPathway = true;
}

bool Obstacle::getUnlockPathway()
{
	return unlockNewPathway;
}

void Obstacle::joinPathways()
{
	toJoin[0]->addPathway(*(toJoin[1]));
	toJoin[1]->addPathway(*(toJoin[0]));
}

std::string Obstacle::getType()
{
	return obstacleType;
}

Item Obstacle::getObstacleItem()
{
	return obstacleItem;
}
