#include <iostream>
#include <vector>
#include <string>
#include "Item.h"		//include item class
#include "Area.h"       //include area class
#include "Player.h"     //include player class
#include <fstream>      //file input and output

using namespace std;
   

//Functions used
void showMap();
int getUserInput(int min, int max);
void exploreInside(Area& area);
void openInventory(Player& player);
void optionsHeader();    //Function to call option header

//  INITIAL VARIABLES
Area gates("The Gate", "Head back to the Gates", "Assets/map_gates.txt", "Assets/inside_gates.txt");    //starting area
Area* currentArea = &gates; //Creating a pointer for the current area
int userInput;

Player player("Player");    //initialising the player



int main()
{
    //Setting up areas
    Area village("The Village", "Go towards the village", "Assets/map_village.txt", "Assets/inside_village.txt");
    Area temple("The Temple", "Walk towards the temple", "Assets/map_temple.txt", "Assets/inside_temple.txt");
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

    player.addItem(Item("Shovel", "A good looking shovel"));
    player.addItem(Item("Sword", "Long sword"));


    village.addObstacle("Locked Door", "A door that appears to be locked", "door.txt", "Rusty key");

    village.addOption("Look inside the house", "Locked Door");
    village.addOption("Check the roof", "");
    village.addOption("Walk inside the stables", "");





    while (true) 
    {
        village.displayOptions();

        int userInput = getUserInput(1, 4);

        if (userInput == 1)
        {
            currentArea->getExplore();
        }
        else if (userInput == 2)
        {
            if (village.getOption("Look inside the house").getOptionType() == village.getObstacle("Locked Door").getName())
            {
                village.exploreArea(player);
            }
        }
        else if (userInput == 3)
        {
            cout << "Nothing is found here..." << endl;
            currentArea->getExplore();
        }
        else if (userInput == 4)
        {
            cout << "Nothing is found here..." << endl;
            currentArea->getExplore();
        }



        system("cls");
        showMap();

        userInput = getUserInput(1, currentArea->getPathways().size() + 2);
        

        if (userInput == 1)
        {
            exploreInside(*currentArea);
        }
        else if (userInput == 2)
        {
            openInventory(player);
        }
        else if (userInput > 2)
        {
            currentArea = currentArea->getPathways()[userInput - 3];
        }
    }
}


void showMap() 
{
    cout << "|=====================================================================================================================================================|" << endl;
    cout << "|                                                                 You are at " << currentArea->getName() << endl;
    cout << "|=====================================================================================================================================================|" << endl;
    currentArea->printMap();
    optionsHeader();

    //First option of each area is to go inside that area
    cout << "[" << 1 << "]" << " " << currentArea->getExplore() << endl;

    //Second option of each area is to open the inventory
    cout << "[" << 2 << "]" << "Open Inventory" << endl;

    //for loop to create pathways options (3 - pathways vector size)
    for (int i = 0; i < currentArea->getPathways().size(); i++) 
    {
        cout << "[" << i + 3 << "]" << " " << currentArea->getPathways()[i]->getFarDescription() << endl;
    }
}

void exploreInside(Area& area)
{
        system("cls");
        cout << "|===================================================================================================================================================|" << endl;
        cout << "|                                                                 You are inside " << currentArea->getName() << endl;
        cout << "|===================================================================================================================================================|" << endl;
        currentArea->printInside();
        optionsHeader();
        cout << "[" << 1 << "]" << " Go back to the global map" << endl;
        cout << "[" << 2 << "]" << " Explore the area" << endl;
        cout << "[" << 3 << "]" << " Open inventory" << endl;

        int userInput = getUserInput(1, 3);

        if (userInput == 1)
        {
            currentArea->printMap();
        }

        else if (userInput == 2)
        {
            //handle exploring the area
        }
        else if (userInput == 3)
        {
            openInventory(player);
        }
}

void openInventory(Player& player)
{
    // if inventory is empty
    if (player.getInventory().empty()) 
    {
        cout << "Your inventory is empty." << endl;
    }
    else 
    {
        // Loop through the inventory and display items
        for (auto& item : player.getInventory()) 
        {
            cout << "[" << &item - &player.getInventory()[0] + 1 << "] " << item.getName() << ": " << item.getDescription() << endl;
        }
    }
    cout << "[" << player.getInventory().size() + 1 << "]" << " Go back" << endl;
    cout << ">>> ";

    int choice = getUserInput(1, player.getInventory().size() + 1);

    if (choice == player.getInventory().size() + 1) {
        // Go back to the previous area
        system("cls");  // Clear the screen
        showMap();  // Display the current area map again
    }
    else 
    {
        Item selectedItem = player.getInventory()[choice - 1];

        // Display the item description
        system("cls");
        cout << "|===================================================================================================================================================|" << endl;
        cout << "| You selected: " << selectedItem.getName() << endl;
        cout << "| Description: " << selectedItem.getDescription() << endl;
        cout << "|===================================================================================================================================================|" << endl;
        cout << "[1] Go back" << endl;
        int backChoice = getUserInput(1, 1);

        if (backChoice == 1)
        {
            system("cls");
            showMap();  
            openInventory(player);
        }
    }
}


int getUserInput(int min, int max) 
{
    int userInput;
    while (true) 
    {
        cout << ">>> ";

        // Check if the input is an integer
        if (cin >> userInput) 
        {
            if (userInput >= min && userInput <= max) 
            {
                return userInput;
            }
            else 
            {
                cout << "Input is out of range. Retry." << endl;
            }
        }
        else 
        {
            // If input is not an integer, clear the error and ignore the rest of the line
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
    }
}

void optionsHeader()    //Function to call optionHeader
{
    cout << "|=====================================================================================================================================================|" << endl;
    cout << "|                                                                          Your options are:" << endl;
    cout << "|=====================================================================================================================================================|" << endl;
}
