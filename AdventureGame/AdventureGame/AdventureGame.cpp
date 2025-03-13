#include <iostream>
#include <vector>
#include "Item.h"		//include item class
#include "Area.h"       //include area class
#include "Player.h"
#include <string>

using namespace std;

int main()
{
    Player player("Savkek");
    Item sword("Sword", "Long Sword");
    Character samurai("Danzo", "Tall samurai");

    Area forest("Forest", "A forest with tall trees and blue leaves");
    Area gate("Gate", "Tall gates with weird symbols");
    Area house("House", "Old, almost ruined house");

    forest.addPathway(gate);
    gate.addPathway(house);
    house.addPathway(forest);

    forest.setFarDescription("Step into the forest");
    gate.setFarDescription("Move closer to the gates");
    house.setFarDescription("Go inside the house");

    Area* currentArea = &forest;
    int userInput;
    
    while (true)
    {
        cout << "You are at " << currentArea->getName() << endl;
        cout << currentArea->getDescription() << endl;
    

        cout << "You have the following options (enter corresponding number)" << endl;
        for (int i = 0; i < currentArea->getPathways().size(); i++)
        {
            cout << "[" << i << "]" << " " << currentArea->getPathways()[i]->getFarDescription() << endl;
        }
        cout << ">>>";
        cin >> userInput;
        if (userInput >= 0 && userInput < currentArea->getPathways().size()) {
            currentArea = currentArea->getPathways()[userInput];
            system("cls");
        }
        else {
            system("cls");
            cout << "Bad input. Retry." << endl;
        }
    }
}
