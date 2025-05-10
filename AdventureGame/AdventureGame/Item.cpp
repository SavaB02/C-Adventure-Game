#include "Item.h"

Item::Item()
{
}

// Constructor
Item::Item(std::string i_name, std::string i_description, std::string i_itemImage)
{
    name = i_name;
    description = i_description;
    itemImage = i_itemImage;
}

// Returns the name of the item
std::string Item::getName()
{
    return name;
}

// Returns the description of the item
std::string Item::getDescription()
{
    return description;
}

std::string Item::getImage()
{
	return itemImage;
}

void Item::printImage()
{
	std::ifstream file(itemImage);
	if (!file) 
	{
		std::cout << "Error opening file: " << itemImage << std::endl;
	}
	std::string line;
	while (getline(file, line))
	{
		std::cout << line << std::endl;
	}
}