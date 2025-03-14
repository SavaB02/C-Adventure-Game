#pragma once
#include <vector>
#include <string>
#include "Item.h"		//include item class
#include "Obstacle.h"	//include obstacle class
#include "Player.h"



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
	vector<Item> items;		
	vector<Character*> characters;
	vector<Area*> pathways;
	string mapPath;
	string mapInsidePath;
	vector <Obstacle> obstacles;


public:
	Area(string i_name, string i_farDescription, string i_mapPath, string i_mapInsidePath);


	//attributes set

	void setName(string name);
	string getName();

	void setDescription(string description);
	string getDescription();

	void setExplore(string explore);
	string getExplore();

	void setFarDescription(string farDescription);
	string getFarDescription();

	//void addCharacter(Character& new_character);
	
	//Pathways

	void addPathway(Area& new_pathway);

	vector<Area*> getPathways();

	//Print .txt file

	string getMapPath();

	void printMap();

	void printInside();

	//Obstacles

	void addObstacle(string i_description, string i_obsImage, string i_requiredItem);	//adds a new obstacle to area's vector 'obstacles'

	void exploreArea(Player& player);

	void useItem(Player& player, Obstacle& obstacle);

	//Items

	void addItem(string i_name, string i_description);		//adds a new item to area's vector 'items'

	void removeItem(string i_name);		//removes item from the area's vector 'items'

	bool hasItems();		// Returns true if there are items, false if the vector is empty
};






