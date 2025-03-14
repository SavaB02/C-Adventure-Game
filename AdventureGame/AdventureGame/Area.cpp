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


Area::Area(string i_name, string i_description, string i_mapPath, string i_mapInsidePath)
{
	name = i_name;
	description = i_description;
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

//void Area::addPlayer(Player& player)
//{
//	characters.push_back(&player);
//}

void Area::addCharacter(Character& new_character)
{
	characters.push_back(&new_character);
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
