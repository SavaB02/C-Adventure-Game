#pragma once
#include <string>


using namespace std;

class Item 
{
private:
    string name;
    string description;

public:
    Item(string i_name, string i_description);

    string getName();
    string getDescription();
};


