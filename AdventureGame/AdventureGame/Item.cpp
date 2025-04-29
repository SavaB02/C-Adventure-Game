#include "Item.h"

using namespace std;

Item::Item()
{
}

// Constructor
Item::Item(string i_name, string i_description) 
{
    name = i_name;
    description = i_description;
}

// Returns the name of the item
string Item::getName() {
    return name;
}

// Returns the description of the item
string Item::getDescription() {
    return description;
}