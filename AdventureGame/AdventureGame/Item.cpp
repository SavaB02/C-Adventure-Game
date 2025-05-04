#include "Item.h"

using namespace std;

Item::Item()
{
}

// Constructor
Item::Item(string i_name, string i_description, string i_itemImage)
{
    name = i_name;
    description = i_description;
    itemImage = i_itemImage;
}

// Returns the name of the item
string Item::getName() 
{
    return name;
}

// Returns the description of the item
string Item::getDescription() 
{
    return description;
}

string Item::getImage()
{
	return itemImage;
}

void Item::printImage()
{
	ifstream file(itemImage);
	if (!file) 
	{
		cout << "Error opening file: " << itemImage << endl;
	}
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
}