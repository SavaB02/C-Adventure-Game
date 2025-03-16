#include "Obstacle.h"
#include <fstream>      //file input and output
#include <iostream>


Obstacle::Obstacle(string i_name, string i_description, string i_obsImage, string i_requiredItem)
{
	name = i_name;
	description = i_description;
	obsImage = i_obsImage;
	requiredItem = i_requiredItem;
	unlockItemDescription = "";
	unlockItemName = "";
	unlockNewPathway = "";
	solved = false;
}

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

void Obstacle::setUnlockPathway(string i_unlockNewPathway)
{
	unlockNewPathway = i_unlockNewPathway;
}

string Obstacle::getUnlockPathway()
{
	return unlockNewPathway;
}