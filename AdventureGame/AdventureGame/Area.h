#pragma once
#include <vector>
#include "Item.h"		//include item class
#include <string>

using namespace std;


class Character
{
private:
	string name;
	string description;
	vector <string> dialogues;


public:
	Character(string i_name, string i_description);

	string getName();
	string getDescription();
//	string talk();

};


class Area
{
private:
	string name;		//initial name of the area
	string description; //initial description of the area
	string explore;		//description when exploring the area
	string farDescription; //description of an area from another area
	vector<Item*> items;		
	vector<Character*> characters;
	vector<Area*> pathways;
	string mapPath;
	string mapInsidePath;


public:
	Area(string i_name, string i_description, string i_mapPath, string i_mapInsidePath);

	void setName(string name);
	string getName();

	void setDescription(string description);
	string getDescription();

	void setExplore(string explore);
	string getExplore();

	void setFarDescription(string farDescription);
	string getFarDescription();

	//void addPlayer(Player& player);
	void addCharacter(Character& new_character);
	
	void addPathway(Area& new_pathway);

	vector<Area*> getPathways();

	string getMapPath();

	void printMap();

	void printInside();
};






