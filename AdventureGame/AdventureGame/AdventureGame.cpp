#include <iostream>
#include <vector>
#include "Item.h"		//include item class
#include "Area.h"       //include area class
#include "Player.h"
#include <string>
#include <fstream>      //file input and output

using namespace std;
   

void optionsHeader()
{
    cout << "|===================================================================================================================================================|" << endl;
    cout << "|===================================================================================================================================================|" << endl;
    cout << "|                                                                          Your options are:" << endl;
    cout << "|===================================================================================================================================================|" << endl;
    cout << "|===================================================================================================================================================|" << endl;
}

int main()
{
    Area gate("The Gate", "Tall gates with weird symbols", "Assets/map_gates.txt", "Assets/inside_gates.txt");
    Area village("The Village", "Old village", "Assets/map_village.txt", "Assets/inside_village.txt");
    Area temple("The Tample", "Broken down temple", "Assets/map_temple.txt", "Assets/inside_temple.txt");
    Area castle("The castle", "Tall and strong castle", "Assets/map_castle.txt", "Assets/inside_castle.txt");

    gate.addPathway(village);
    village.addPathway(gate);
    village.addPathway(temple);
    temple.addPathway(village);
    village.addPathway(castle);
    castle.addPathway(village);


    gate.setFarDescription("Head back to the Gates");
    village.setFarDescription("Go inside the village");
    village.setExplore("Head towards the town centre");
    gate.setExplore("Walk around the gates");


    Area* currentArea = &gate;
    int userInput;


    while (true) {
        system("cls");
        cout << "|===================================================================================================================================================|" << endl;
        cout << "|===================================================================================================================================================|" << endl;
        cout << "|                                                                 You are at " << currentArea->getName() << endl;
        cout << "|===================================================================================================================================================|" << endl;
        cout << "|===================================================================================================================================================|" << endl;
        currentArea->printMap();
        optionsHeader();

        cout << "[" << 1 << "]" << " " << currentArea->getExplore() << endl;

        for (int i = 0; i < currentArea->getPathways().size(); i++) {
            cout << "[" << i + 2 << "]" << " " << currentArea->getPathways()[i]->getFarDescription() << endl;
        }
        cout << ">>>";
        cin >> userInput;
        if (userInput > 0 && userInput <= currentArea->getPathways().size() + 1 && userInput != 1) {
            currentArea = currentArea->getPathways()[userInput - 2];
            system("cls");
        }
        
        else if (userInput == 1)
        {
            system("cls");
            cout << "|===================================================================================================================================================|" << endl;
            cout << "|===================================================================================================================================================|" << endl;
            cout << "|                                                                 You are inside " << currentArea->getName() << endl;
            cout << "|===================================================================================================================================================|" << endl;
            cout << "|===================================================================================================================================================|" << endl;
            currentArea->printInside();
            optionsHeader();
            cout << "[" << 1 << "]" << " Go back to the global map" << endl;
            cout << "[" << 2 << "]" << " Explore the area" << endl;

            cout << ">>> ";
            cin >> userInput;

        }

        else {
            system("cls");
            cout << "Bad input. Retry." << endl;
            cin >> userInput;
        }

    }

}

