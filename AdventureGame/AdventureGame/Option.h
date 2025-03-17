#pragma once
#include <string>

using namespace std;

class Option
{
private:
	string description;
	string optionType = "";		// must match the name of an obstacle, otherwise ""
public:
	Option(string i_description, string i_optionType);

	string getDescription();

	string getOptionType();
};

