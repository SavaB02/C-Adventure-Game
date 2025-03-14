#include <iostream>
#include <vector>
#include <string>
#include "Item.h"		//include item class
#include "Area.h"       //include area class
#include "Player.h"     //include player class
#include <fstream>      //file input and output

using namespace std;
   

void optionsHeader()    //Function to call optionHeader
{
    cout << "|===================================================================================================================================================|" << endl;
    cout << "|===================================================================================================================================================|" << endl;
    cout << "|                                                                          Your options are:" << endl;
    cout << "|===================================================================================================================================================|" << endl;
    cout << "|===================================================================================================================================================|" << endl;
}

int main()
{
    //Setting up areas
    Area gates("The Gate", "Head back to the Gates", "Assets/map_gates.txt", "Assets/inside_gates.txt");
    Area village("The Village", "Go towards the village", "Assets/map_village.txt", "Assets/inside_village.txt");
    Area temple("The Tample", "Walk towards the temple", "Assets/map_temple.txt", "Assets/inside_temple.txt");
    Area castle("The castle", "Get near the castle", "Assets/map_castle.txt", "Assets/inside_castle.txt");

    //Adding an explore button description
    village.setExplore("Walk towards the village centre");
    gates.setExplore("Circle around the gates");
    temple.setExplore("Reach the temple");
    castle.setExplore("Go inside the castle");

    //Creating pathways between the areas
    gates.addPathway(village);
    village.addPathway(gates);
    
    gates.addPathway(temple);
    temple.addPathway(gates);

    temple.addPathway(castle);
    castle.addPathway(temple);

    //Creating a pointer
    Area* currentArea = &gates;
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

        //First option of each area is to go inside that area
        cout << "[" << 1 << "]" << " " << currentArea->getExplore() << endl;

        //for loop to create pathways options (2-4)
        for (int i = 0; i < currentArea->getPathways().size(); i++) {
            cout << "[" << i + 2 << "]" << " " << currentArea->getPathways()[i]->getFarDescription() << endl;
        }
        cout << ">>>";
        cin >> userInput;
        if (userInput > 0 && userInput <= currentArea->getPathways().size() + 1 && userInput != 1) {
            currentArea = currentArea->getPathways()[userInput - 2];
            userInput = 0;
        }
        
        //if player chooses to go inside the area
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

            if (userInput == 1)
            {
                currentArea->printMap();
                userInput = 0;
            }

            else if (userInput == 2)
            {

            }

            else
            {
                cout << "Bad input. Retry." << endl;
                cin >> userInput;
            }
            
        }

        else {
            cout << "Bad input. Retry." << endl;
            cin >> userInput;
        }

    }

}

