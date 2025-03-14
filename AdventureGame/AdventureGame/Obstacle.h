#pragma once
#include <string>


using namespace std;

class Obstacle
{
private:
	string description;
	string obsImage;		//store an image of an obstacle
	string requiredItem;
	bool solved = false;			//flag to check if the obstacle is solved

public:
	Obstacle(string i_description, string i_obsImage, string i_requiredItem);

	string getDescription();

	string getRequiredItem();

	void printImage();

	bool isSolved();

	void solve();
};

