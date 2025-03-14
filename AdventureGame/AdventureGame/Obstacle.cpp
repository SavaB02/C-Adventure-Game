#include "Obstacle.h"
#include <fstream>      //file input and output
#include <iostream>


Obstacle::Obstacle(string i_description, string i_obsImage, string i_requiredItem)
{
	description = i_description;
	obsImage = i_obsImage;
	requiredItem = i_requiredItem;
}

string Obstacle::getDescription()
{
	return description;
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
