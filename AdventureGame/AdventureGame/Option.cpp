#include "Option.h"

Option::Option(string i_description, string i_optionType)
{
	description = i_description;
	optionType = i_optionType;
}

string Option::getDescription()
{
	return description;
}

string Option::getOptionType()
{
	return optionType;
}
