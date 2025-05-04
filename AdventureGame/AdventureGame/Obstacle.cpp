#include "Obstacle.h"
#include "Area.h"



//Obstacle that gives an item after solving
Obstacle::Obstacle(string i_name, string i_description, string i_obsImage, string i_requiredItem, string i_obstacleType, Item i_obstacleItem)
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
Obstacle::Obstacle(string i_name, string i_description, string i_obsImage, string i_requiredItem, string i_obstacleType, Area* i_toJoin1, Area* i_toJoin2)
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

string Obstacle::getName()
{
	return name;
}

void Obstacle::printName()
{
	cout << name << endl;
}

void Obstacle::printDescription()
{
	cout << description << endl;
	cout << "||================================================================================================================||" << endl;
}

string Obstacle::getRequiredItem()
{
	return requiredItem;
}


void Obstacle::printImage()
{
	ifstream file(obsImage);
	if (!file) {
		cout << "Error opening file: " << obsImage << endl;
	}
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
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


void Obstacle::setUnlockItem(string i_unlockItemName, string i_unlockItemDescription)
{
	unlockItemName = i_unlockItemName;
	unlockItemDescription = i_unlockItemDescription;
}

string Obstacle::getUnlockItemName()
{
	return unlockItemName;
}

string Obstacle::getUnlockItemDescription()
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

string Obstacle::getType()
{
	return obstacleType;
}

Item Obstacle::getObstacleItem()
{
	return obstacleItem;
}
