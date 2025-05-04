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
void enterInsideArea(Area* currentArea, Player& player);
void openInventory(Area* currentArea, Player& player, bool isInside);
void optionsHeader();                                   //Function to call option header


int main()
{
    //Setting up areas
    Area gates("The Gates", "Head back to the Gates", "Assets/Map/map_gates.txt", "Assets/Area/area_gates.txt");
    Area village("The Village", "Go towards the village", "Assets/Map/map_village.txt", "Assets/Area/area_village.txt");
    Area forest("The Forest", "Get near the forest", "Assets/Map/map_forest.txt", "Assets/Area/area_forest.txt");
    Area hut("The Hut", "Check out the hut", "Assets/Map/map_hut.txt", "Assets/Area/area_hut.txt");
    Area bamboo("The Bamboo Grove", "Get near the Bamboo Grove", "Assets/Map/map_bamboo.txt", "Assets/Area/area_bamboo.txt");
    Area temple("The Temple", "Head towards the Temple", "Assets/Map/map_temple.txt", "Assets/Area/area_temple.txt");
    Area castle("The Ruined Castle", "Reach the Ruined Castle", "Assets/Map/map_castle.txt", "Assets/Area/area_castle.txt");
    Area lake("The Lake", "Take a walk to the Lake", "Assets/Map/map_lake.txt", "Assets/Area/area_lake.txt");
    Area peak("The Peak", "Ascend the peak", "Assets/Map/map_peak.txt", "Assets/Area/area_peak.txt");
    Area grave("The Grave", "Make your way towards the Grave", "Assets/Map/map_grave.txt", "Assets/Area/area_grave.txt");

    //Initialising the player and creating a pointer for the current area
    Player player("Player");  
    Area* currentArea = &gates;
    bool isInside = true;           //a flag to keep track of current position in the world(inside the area or not)
    int exploreInput = 0;

    //Adding an explore button description (to get inside the location)
    gates.setExplore("Circle around the gates");
    village.setExplore("Walk towards the village centre");
    forest.setExplore("Go inside the forest");
    hut.setExplore("Step inside the hut");
    bamboo.setExplore("Go inside the bamboo grove");
    castle.setExplore("Explore the ruins of the castle");
    temple.setExplore("Investigate the temple");
    lake.setExplore("Go around the lake");
    peak.setExplore("Look around the peak");
    grave.setExplore("Get near the grave");


    //Creating initial pathways between the areas
    gates.addPathway(village);
    village.addPathway(gates);

    gates.addPathway(forest);
    forest.addPathway(gates);

    forest.addPathway(village);
    village.addPathway(forest);

    temple.addPathway(lake);
    lake.addPathway(temple);

    bamboo.addPathway(castle);
    castle.addPathway(bamboo);

    //A set to track which pathways are unlocked
    set<string> unlockedPathways; 

    //Initial player item
    player.addItem(Item("Farewell Letter", "A frayed letter that guides you toward the fading echoes of your legacy. Somewhere, your ancestor's grave waits - and with it, a silence only an offering can answer."));
    player.addItem(Item("Offerings", "A carefully prepared set of tributes: fragrant incense, a flask of sake, and modest ornaments. Meant not for the living, but for those who came before - a gesture of remembrance and respect."));

    //Gates Options
    gates.addOption(Option("Read the sign", "text", "|| Welcome to a forgotten land ravaged by time"));
    gates.addOption(Option("Check the right column", "obstacle", "You see loose soil", Obstacle("Loose soil", "You see loose soil, but you can't dig it out without a shovel.", "Assets/Obstacle/soil.txt", "Old Shovel", "item", Item("Iron Key", "An ordinary key made of iron. Usually used by villagers to lock their houses"))));
    gates.addOption(Option("Check the left column", "item", "|| You find a page attached to the column", Item("First Page", "The hardest step is the first - yet without it, no path will ever unfold")));

    //Village options
    village.addOption(Option("Read the note by the house", "text", "Saw a noble wandering by the gates - sword gleaming like moonlight. No idea what he was after, but I swear if I can get my hands on that sword..."));
    village.addOption(Option("Search the nobleman's house", "obstacle", "You get near the entrance", Obstacle("Locked Door", "The iron lock on the door looks functional — perhaps it still opens with the right key.", "Assets/Obstacle/door.txt", "Iron Key", "item", Item("Weathered Katana", "An old katana with a dulled blade. Time have scarred its surface, yet a quiet strength still lingers within."))));
    village.addOption(Option("Get near the bridge", "obstacle", "You are near the broken bridge", Obstacle("Broken Bridge", "The bridge is broken, worn down by time. A rope might help you cross.", "Assets/Obstacle/bridge.txt", "Rope", "pathway", &village, &temple)));

    //Forest options
    forest.addOption(Option("Obscure Pathway", "obstacle", "A long and twisted path", Obstacle("Pathway", "A long and twisted path, you will get lost without a map", "Assets/Obstacles/pathway.txt", "Shrine Map", "item", Item("Golden Key", "Gold - a material used by monks and nobles"))));
    forest.addOption(Option("Inpect the thickets", "item", "|| In the thicket of branches and vines you find an old shovel.", Item("Old Shovel", "Very rusty, but should be fine to dig a hole or two.")));
    forest.addOption(Option("Examine the vines", "obstacle", "You encounted vines", Obstacle("Vines", "Twisting vines and overgrown brush bar the way. Cutting through is the only option", "Assets/Obstacle/vines.txt", "Weathered Katana", "pathway", &forest, &hut)));

    //Hut options
    hut.addOption(Option("Search the hut", "obstacle", "Go inside the hut", Obstacle("Rusty chest", "A battered chest, worn and cracked, but still sturdy enough to hold whatever lies within.", "Assets/Obstacle/chest.txt", "Rusty Key", "item", Item("Rope", "A long rope with a hook attached"))));
    hut.addOption(Option("Look around the hut", "item", "On the table you find a note", Item("Second Page", "Strength lies within each of us — all it takes is the courage to uncover it.")));
    hut.addOption(Option("Check the tree hollow", "item", "You reach inside and find a key", Item("Rusty Key", "Old but should still be functioning.")));

    //Temple options
    temple.addOption(Option("Read monk's texts", "text", "Among the pages, you find a faded note: 'One of the monk's favorite places to meditate was a quiet shrine hidden deep within the forest."));
    temple.addOption(Option("Reach the temple's window", "obstacle", "You try to climb the temple", Obstacle("Window", "Above the temple’s first roof, you notice a narrow window tucked just beneath the eaves. Shame it is too high up.", "Assets/Obstacle/window.txt", "Ladder", "item", Item("Shrine Map", "A map, depicting the path towards the shrine inside the forest."))));
    temple.addOption(Option("Get near the golden gate", "obstacle", "You reached the golden gate", Obstacle("Gate", "Golden patterns shimmer across the gates, timeworn yet majestic. At their center, a keyhole shaped for a large key catches your eye.", "Assets/Obstacle/gate.txt", "Golden Key", "pathway", &temple, &bamboo)));

    //Lake options
    lake.addOption(Option("Check out the boat", "item", "|| Inside the boat you find a note.", Item("Third page", "No storm lasts forever. In its wake, the lake remembers how to be still.")));
    lake.addOption(Option("Sail to the small island", "item", "|| On the island you find nothing but ladder.", Item("Ladder", "Made of wood, it's fragile but can still be used to climb somewhere.")));
    lake.addOption(Option("Meditate", "text", "You sit down and close your eyes. Soothing waves whisper against the shore as the sun glitters across the lake — a perfect moment for stillness."));

    //Bamboo Grove options
    bamboo.addOption(Option("Inspect a passage", "obstacle", "A stiff path that leads towards the mountain.", Obstacle("Passage", "A passage looks too stiff. Without a proper equipment you won't be able to climb.", "Assets/Obstacle/passage.txt", "Climbing Equipment", "pathway", &bamboo, &peak)));
    bamboo.addOption(Option("Get near the altar", "item", "|| You spot an altar on your way. Next to it lies an axe.", Item("Well-worn Axe", "Old but reliable. Its edge has seen better days, but it still cuts true.")));

    //Castle options
    castle.addOption(Option("Take a look at the ruins", "text", "The ruined castle stands in solemn silence — once grand, now fragile beneath the weight of time."));
    castle.addOption(Option("Look around the garden area", "item", "|| On a meditating spot you locate a note.", Item("Fourth page", "Even the greatest of things fall — and that, too, is part of their story.")));
    castle.addOption(Option("Examine the blockage", "obstacle", "You get near ruined barracks", Obstacle("Blockage", "You’re met with a heap of broken wood where a passage once stood. If you had somthing, that could smash through.", "Assets/Obstacle/blockage.txt", "Well-worn Axe", "item", Item("Climbing Equipment", "Essential tools for scaling heights. Thankfully, they're still in good condition."))));

    //Peak options
    peak.addOption(Option("Collect a note", "item", "You spot a weathered note, held in place by a few small rocks.", Item("Fifth page", "You reached the summit not to conquer it, but to understand the path you endured.")));
    peak.addOption(Option("Meditate", "text", "You’ve reached the summit, yet something stirs within — doubt, perhaps. Was this the goal, or just a resting place before a higher climb you’ve yet to see?"));
    peak.addOption(Option("Perceive the Truth", "obstacle", "Find the hidden.", Obstacle("Truth", "Only the wise recognize what others overlook - and wisdom often hides in words left behind.", "Assets/Obstacle/truth.txt", "Wisdom", "pathway", &peak, &grave)));

    //Grave options
    grave.addOption(Option("Meditate", "text", "You kneel beside the grave, the wind still, the world quiet. In this silence, every step, every doubt, every scar you've carried settles into place. This is not just an end — it is the shape of everything you've become."));
    grave.addOption(Option("Offer tribute", "obstacle", "You sit down by the grave", Obstacle("Tribute", "You've reached your destination. It's time to lay down your offerings.", "Assets/Obstacle/tribute.txt", "Offerings", "item", Item("Fading tome", "This tome contains the shape of your path — the echoes of your footsteps, the weight of your knowledge, and the truths you chose to carry."))));

    //Main Game Logic

        ifstream file("Assets/title.txt");
        if (!file) {
            cout << "Error opening file: " << "title.txt" << endl;
        }
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        cin.ignore();

        while (true)
        {
            if (!player.hasItem("Wisdom"))
            {
                if (player.hasItem("First Page") and player.hasItem("Second Page") and player.hasItem("Third Page") and player.hasItem("Fourth Page") and player.hasItem("Fifth Page"))
                {
                    player.addItem(Item("Wisdom", "You found all the pages of your lost legacy. Now you are full of wisdom."));
                }
            }
            
            showMap(currentArea);
            int userInput = getUserInput(1, currentArea->getPathways().size() + 2);
            if (userInput == 1)
            {
                enterInsideArea(currentArea, player);
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
    currentArea->printMap();

    //First option of each area is to go inside that area
    cout << "[" << 1 << "]" << " " << currentArea->getExplore() << endl;

    //Second option of each area is to open the inventory
    cout << "[" << 2 << "]" << " Open Inventory" << endl;

    //for loop to create pathways options (3 - pathways vector size)
    for (int i = 0; i < currentArea->getPathways().size(); i++)
    {
        cout << "[" << i + 3 << "]" << " " << currentArea->getPathways()[i]->getOverview() << endl;
    }
}

void enterInsideArea(Area* currentArea, Player& player)
{
    bool isInside = true;
    while (true)
    {
        system("cls");
        currentArea->printInside();
        cout << "|| [" << 1 << "]" << " Go back to the global map" << endl;
        cout << "|| [" << 2 << "]" << " Explore the area" << endl;
        cout << "|| [" << 3 << "]" << " Open inventory" << endl;
        cout << "||================================================================================================================||" << endl;

        int userInput = getUserInput(1, 3);

        if (userInput == 1)
        {
            return; 
        }

        else if (userInput == 2)
        {
            system("cls");
            currentArea->printInside();
            currentArea->displayOptions();
            int exploreInput = getUserInput(1, currentArea->getOptionSize() + 1);
            system("cls");
            currentArea->printInside();

            int index = exploreInput - 2;

            if (index < 0 || index >= currentArea->getOptionSize())
            {
                return;
            }


            if (currentArea->getOption(exploreInput-2).getOptionType() == "text") 
            {
                cout << currentArea->getOption(exploreInput-2).getOptionText() << endl;
                cout << "||" << endl;
                cout << "|| Press any key to continue..." << endl;
                cout << "||================================================================================================================||" << endl;
                cin.ignore();
                cin.get();
            }

            else if (currentArea->getOption(exploreInput - 2).getOptionType() == "item" and currentArea->getOption(exploreInput - 2).getHasInteracted() == false)
            {
                currentArea->getOption(exploreInput - 2).solveInteracted();

                cout << currentArea->getOption(exploreInput - 2).getOptionText() << endl;
                player.addItem(currentArea->getOption(exploreInput - 2).getOptionItem());

                cout << "|| " << endl;
                cout << "|| A new item was added to your inventory. Press any key to continue..." << endl;
                cout << "||================================================================================================================||" << endl;
                cin.ignore();
                cin.get();
            }    

            else if (currentArea->getOption(exploreInput - 2).getOptionType() == "obstacle" and currentArea->getOption(exploreInput - 2).getHasInteracted() == false)
            {
                currentArea->exploreArea(player);
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
            enterInsideArea(currentArea, player);
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
                enterInsideArea(currentArea, player);
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
