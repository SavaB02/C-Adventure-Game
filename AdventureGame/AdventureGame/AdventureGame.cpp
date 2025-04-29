#include <iostream>
#include <vector>
#include <string>
#include "Item.h"		//include item class
#include "Area.h"       //include area class
#include "Player.h"     //include player class
#include <fstream>      //file input and output
#include <set>

using namespace std;
   

//Functions used
void showMap(Area* currentArea);
int getUserInput(int min, int max);
void exploreInside(Area* currentArea, Player& player);
void openInventory(Area* currentArea, Player& player, bool isInside);
void optionsHeader();                                   //Function to call option header


int main()
{
    //Setting up areas
    Area gates("The Gates", "Head back to the Gates", "Assets/map_gates.txt", "Assets/inside_gates.txt");
    Area village("The Village", "Go towards the village", "Assets/map_village.txt", "Assets/inside_village.txt");
    Area forest("The forest", "Get near the forest", "Assets/map_forest.txt", "Assets/inside_forest.txt");
    Area hut("The hut", "Check out the hut", "Assets/map_hut.txt", "Assets/inside_hut.txt");


    //Initialising the player and creating a pointer for the current area
    Player player("Player");  
    Area* currentArea = &gates;
    bool isInside = true;
    int exploreInput = 0;

    //Adding an explore button description
    gates.setExplore("Circle around the gates");
    village.setExplore("Walk towards the village centre");
    forest.setExplore("Go inside the forest");

    //Creating pathways between the areas
    gates.addPathway(village);
    village.addPathway(gates);

    gates.addPathway(forest);
    forest.addPathway(gates);

    //A set to track which pathways are unlocked
    set<string> unlockedPathways; 

    //Initial player item
    player.addItem(Item("Farewell Letter", "Go forth my child, find your ancestor's legacy!"));
    player.addItem(Item("Bag", "Bag lol"));

    //Gates options
    gates.addOption(Option("Read the sign", "text", "The sign says you're cooked son."));
    gates.addOption(Option("Check the right collumn","item", "You got a new item!", Item("Cool Sword", "This is a rad sword")));
    gates.addOption(Option("Check the left collumn", "text", ""));

    gates.addOption(Option("Dig behind the gate", "obstacle", "You find a chest!", Obstacle("Chest", "Wooden Chest", "chest.txt", "Wooden Key", "item", Item("Sword", "A cool looking sword"))));

    gates.addOption(Option("Inspect tall", "obstacle", "You decided to inspect tall grass", Obstacle("Tall grass", "Tall grass is blocking the way, need something sharp.", "grass.txt", "Sword", "Path", &gates, &hut )));

    //Village options
    village.addOption(Option("Look inside the house", "obstacle", ""));
    village.addOption(Option("Check the roof", "item", ""));
    village.addOption(Option("Walk inside the stables", "text", ""));

    //Village obstacles
    
    village.addObstacle(Obstacle("Locked Door", "Door with a lock", "obstacle_door.txt", "Copper Key", "item", Item("Eggs", "Some fine eggs")));
    village.addObstacle(Obstacle("Tree", "The path is blocked by a fallen tree. Without an axe, getting through seems imposible.", "obstacle_tree.txt", "Rusty Axe", "pathway", &village, &hut ));

    //Forest options
    forest.addOption(Option("Climb the tree", "obstacle", "You find a nest with eggs"));
    forest.addObstacle(Obstacle("Climb the tree", "You see a couple of nice eggs. If only you had something to stash them into", "obstacle_tree.txt", "Bag", "item", Item("Eggs", "Some fine eggs")));

    forest.addOption(Option("Meditate", "item", "You got a new item!", Item("Weathered Katana", "This is a rad sword")));

    forest.addOption(Option("Examine the vines", "obstacle", "You encounted vines"));

    //forest.addObstacle(Obstacle("Vines", "Twisting vines and overgrown brush bar the way. Cutting through is the only option", "obstacle_vines.txt", "Weathered Katana", "pathway", { &forest, &hut }));


    //Forest obstacles

    //Main Game Logic
        cout << "Please, fullscreen the game for better experience" << endl;
        cout << "Fading Echoes" << endl;
        cout << "Game description" << endl;
        cout << "Press Enter to continue..." << endl;
        cin.ignore();

        while (true)
        {
            if (forest.getObstacle("Vines").isSolved())
            {
                forest.getOption("Examine the vines").solve();
                player.addItem(Item("Vine", "Vine rememberance"));
            }

            if (player.hasItem("Vine") and unlockedPathways.find("forest-hut") == unlockedPathways.end())
            {
                forest.addPathway(hut);
                hut.addPathway(forest);
                hut.setExplore("Go inside the hut");
                unlockedPathways.insert("forest-hut");
            }

            showMap(currentArea);
            int userInput = getUserInput(1, currentArea->getPathways().size() + 2);
            if (userInput == 1)
            {
                exploreInside(currentArea, player);
;
            }
            else if (userInput == 2)
            {
                openInventory(currentArea, player, isInside);
            }
            else if (userInput > 2)
            {
                currentArea = currentArea->getPathways()[userInput - 3];
            }
        }
}


void showMap(Area* currentArea)
{
    system("cls");
    cout << "|===============================================================================================================|" << endl;
    cout << "|                                            You are at " << currentArea->getName() << endl;
    cout << "|===============================================================================================================|" << endl;
    currentArea->printMap();
    optionsHeader();

    //First option of each area is to go inside that area
    cout << "[" << 1 << "]" << " " << currentArea->getExplore() << endl;

    //Second option of each area is to open the inventory
    cout << "[" << 2 << "]" << " Open Inventory" << endl;

    //for loop to create pathways options (3 - pathways vector size)
    for (int i = 0; i < currentArea->getPathways().size(); i++)
    {
        cout << "[" << i + 3 << "]" << " " << currentArea->getPathways()[i]->getFarDescription() << endl;
    }
}

void exploreInside(Area* currentArea, Player& player)
{
    bool isInside = true;
    while (true)
    {
        system("cls");
        cout << "|====================================================================================================================================================|" << endl;
        cout << "|                                                                 You are inside " << currentArea->getName() << endl;
        cout << "|====================================================================================================================================================|" << endl;
        currentArea->printInside();
        optionsHeader();
        cout << "[" << 1 << "]" << " Go back to the global map" << endl;
        cout << "[" << 2 << "]" << " Explore the area" << endl;
        cout << "[" << 3 << "]" << " Open inventory" << endl;

        int userInput = getUserInput(1, 3);

        if (userInput == 1)
        {
            return;
        }

        else if (userInput == 2)
        {
            system("cls");
            cout << "|====================================================================================================================================================|" << endl;
            cout << "|                                                                 You are inside " << currentArea->getName() << endl;
            cout << "|====================================================================================================================================================|" << endl;
            currentArea->printInside();
            optionsHeader();
            currentArea->displayOptions();
            int exploreInput = getUserInput(1, currentArea->getOptionSize() + 1);
            system("cls");
            cout << "|====================================================================================================================================================|" << endl;
            cout << "|                                                                 You are inside " << currentArea->getName() << endl;
            cout << "|====================================================================================================================================================|" << endl;
            currentArea->printInside();
            optionsHeader();

            if (currentArea->getOption(exploreInput-2).getOptionType() == "text") 
            {
                cout << currentArea->getOption(exploreInput-2).getOptionText() << endl;
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();

            }
            else if (currentArea->getOption(exploreInput - 2).getOptionType() == "item") 
            {
                cout << currentArea->getOption(exploreInput - 2).getOptionText() << endl;
                player.addItem(currentArea->getOption(exploreInput - 2).getOptionItem());
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();
            }    
            else if (currentArea->getOption(exploreInput - 2).getOptionType() == "obstacle")
            {
                currentArea->exploreArea(player);
            }
            

            if (isInside)
            {
                showMap(currentArea);
            }
            else
            {
                exploreInside(currentArea, player);
            }

            
        }
        else if (userInput == 3)
        {
            openInventory(currentArea, player, isInside);
        }
    }
}

void openInventory(Area* currentArea,Player& player, bool isInside)
{
    cout << "|==========================================|" << endl;
    cout << "|            Your inventory    " << "            |" << endl;
    cout << "|==========================================|" << endl;
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
            cout << "[" << &item - &player.getInventory()[0] + 1 << "] " << item.getName() << endl;
        }
    }
    cout << "[" << player.getInventory().size() + 1 << "]" << " Go back" << endl;
    cout << ">>> ";

    int choice = getUserInput(1, player.getInventory().size() + 1);

    if (choice == player.getInventory().size() + 1) 
    {
        // Go back to the previous area
        system("cls");  // Clear the screen

        if (isInside)
        {
            showMap(currentArea);
        }
        else
        {
            exploreInside(currentArea, player);
        }
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

            if (isInside)
            {
                showMap(currentArea);
            }
            else
            {
                exploreInside(currentArea, player);
            }
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
    cout << "|==========================================|" << endl;
    cout << "|            Your options are:" << "             |" << endl;
    cout << "|==========================================|" << endl;
}
