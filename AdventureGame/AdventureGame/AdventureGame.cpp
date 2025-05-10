#include <iostream>
#include <vector>
#include <string>
#include "Item.h"		//include item class
#include "Area.h"       //include area class
#include "Player.h"     //include player class
#include <fstream>      //file input and output
#include "json.hpp"     //include json library

//Functions in Main.cpp

/**
* @brief Displays the current area's ASCII image and presents with options
* @param currentArea - area to take an image from (mainly currentArea)
*/
void showMap(Area* currentArea);

/**
* @brief Displays the current area's ASCII image and presents with options
* @param currentArea - area to take an image from (mainly currentArea)
*/
int getUserInput(int min, int max);

/**
* @brief Displays the current area's ASCII image (inside of the area and presents with options
* @param currentArea - area to take an image from (mainly currentArea)
* @param player - the player of the game
*/
void enterInsideArea(Area* currentArea, Player& player);

/**
* @brief Opens player's inventory
* @param currentArea - area to take an image from (mainly currentArea)
* @param player - the player of the game
* @param isInside - flag to check if the player is inside the area or on the global map
*/
void openInventory(Area* currentArea, Player& player, bool isInside);

/**
* @brief Saves the current state of the game
* @param player - the player of the game
* @param currentArea - area to take an image from (mainly currentArea)
* @param allAreas - vector to store all areas in the game
*/
void saveGame(Player& player, Area* currentArea, std::vector<Area*>& allAreas);

/**
* @brief Loads the current state of the game
* @param player - the player of the game
* @param currentArea - area to take an image from (mainly currentArea)
* @param allAreas - vector to store all areas in the game
*/
void loadGame(Player& player, Area*& currentArea, std::vector<Area*>& allAreas);

/**
* @brief Checks if the player has an item called "Wisdom"
* @param player - the player of the game
*/
void checkForWisdom(Player& player);

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

    //Adding an explore button description (to get inside the location)
    gates.setExplore("Circle around the gates");
    village.setExplore("Walk towards the village centre");
    forest.setExplore("Go inside the forest");
    hut.setExplore("Step towards the hut");
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

    Player player("Player");            //Initialising the player; 
    Area* currentArea = &gates;         //a pointer for the current area the player is in
    bool isInside = true;               //a flag to check if the player is inside the area or on the global map (used for inventory)
    int exploreInput = 0;               //player's input
    std::vector<Area*> allAreas = { &gates, &village, &forest, &hut, &bamboo, &temple, &castle, &lake, &peak, &grave }; //vector of all the areas in the game. Used for save/load

    //Initial player items
    player.addItem(Item("Farewell Letter", "A frayed letter that guides you toward the fading echoes of your legacy. \n|| Somewhere, your ancestor's grave waits - and with it, a silence only an offering can answer.", "Assets/Items/letter.txt"));
    player.addItem(Item("Offerings", "A carefully prepared set of tributes: \n|| Fragrant incense, a flask of sake, and modest ornaments. \n|| Meant not for the living, but for those who came before - \n|| a gesture of remembrance and respect.", "Assets/Items/offerings.txt"));

    //Setting up Option choises for the player. Can be a text, an item (gives item on choosing), and an obstacle(that either gives an item or unlocks a pathway between the areas

    //Gates Options
    gates.addOption(Option("Read the sign", "text", "Welcome to a forgotten land ravaged by time"));
    gates.addOption(Option("Check the right column", "obstacle", "You see loose soil", Obstacle("Loose soil", "You see loose soil, but you can't dig it out without a shovel.", "Assets/Obstacle/soil.txt", "Old Shovel", "item", Item("Iron Key", "An ordinary key made of iron. Usually used by villagers to lock their houses", "Assets/Items/ironKey.txt"))));
    gates.addOption(Option("Check the left column", "item", "You find a page attached to the column", Item("First Page", "The hardest step is the first - yet without it, no path will ever unfold", "Assets/Items/firstPage.txt")));

    //Village options
    village.addOption(Option("Read the note by the house", "text", "Saw a noble wandering by the gates - sword gleaming like moonlight. \n|| No idea what he was after, but I swear if I can get my hands on that sword..."));
    village.addOption(Option("Search the nobleman's house", "obstacle", "You get near the entrance", Obstacle("Locked Door", "The iron lock on the door looks functional - perhaps it still opens with the right key.", "Assets/Obstacle/door.txt", "Iron Key", "item", Item("Weathered Katana", "An old katana with a dulled blade. Time have scarred its surface,\n|| yet a quiet strength still lingers within.", "Assets/Items/katana.txt"))));
    village.addOption(Option("Get near the bridge", "obstacle", "You are near the broken bridge", Obstacle("Broken Bridge", "The bridge is broken, worn down by time. A rope might help you cross.", "Assets/Obstacle/bridge.txt", "Rope", "pathway", &village, &temple)));

    //Forest options
    forest.addOption(Option("Obscure Pathway", "obstacle", "A long and twisted path", Obstacle("Pathway", "A long and twisted path, you will get lost without a map", "Assets/Obstacle/pathway.txt", "Shrine Map", "item", Item("Golden Key", "Gold - a material used by monks and nobles", "Assets/Items/goldenKey.txt"))));
    forest.addOption(Option("Inspect the thickets", "item", "In the thicket of branches and vines you find an old shovel.", Item("Old Shovel", "Very rusty, but should be fine to dig a hole or two.", "Assets/Items/shovel.txt")));
    forest.addOption(Option("Examine the vines", "obstacle", "You encounted vines", Obstacle("Vines", "Twisting vines and overgrown brush bar the way. Cutting through is the only option", "Assets/Obstacle/vines.txt", "Weathered Katana", "pathway", &forest, &hut)));

    //Hut options
    hut.addOption(Option("Search the hut's storage", "obstacle", "Go inside the hut", Obstacle("Old chest", "A battered chest, worn and cracked, but still sturdy enough to hold whatever lies within.", "Assets/Obstacle/chest.txt", "Rusty Key", "item", Item("Rope", "A long rope with a hook attached", "Assets/Items/rope.txt"))));
    hut.addOption(Option("Check the hut's kitchen", "item", "On the table you find a note", Item("Second Page", "Strength lies within each of us - all it takes is the courage to uncover it.", "Assets/Items/secondPage.txt")));
    hut.addOption(Option("Check the tree hollow", "item", "You reach inside and find a key", Item("Rusty Key", "Old but should still be functioning.", "Assets/Items/rustyKey.txt")));

    //Temple options
    temple.addOption(Option("Read monk's texts", "text", "Among the pages, you find a faded note: 'One of the monk's favorite places to meditate\n|| was a quiet shrine hidden deep within the forest."));
    temple.addOption(Option("Reach the temple's window", "obstacle", "You try to climb the temple", Obstacle("Window", "Above the temple's first roof, you notice a narrow window \n|| tucked just beneath the eaves. Shame it is too high up.", "Assets/Obstacle/window.txt", "Ladder", "item", Item("Shrine Map", "A map, depicting the path towards the shrine inside the forest.", "Assets/Items/map.txt"))));
    temple.addOption(Option("Get near the golden gate", "obstacle", "You reached the golden gate", Obstacle("Gate", "Golden patterns shimmer across the gates, timeworn yet majestic. \n|| At their center, a keyhole shaped for a large key catches your eye.", "Assets/Obstacle/gate.txt", "Golden Key", "pathway", &temple, &bamboo)));

    //Lake options
    lake.addOption(Option("Check out the boat", "item", "Inside the boat you find a note.", Item("Third Page", "No storm lasts forever. In its wake, the lake remembers how to be still.", "Assets/Items/thirdPage.txt")));
    lake.addOption(Option("Sail to the small island", "item", "On the island you find nothing but ladder.", Item("Ladder", "Made of wood, it's fragile but can still be used to climb somewhere.", "Assets/Items/ladder.txt")));
    lake.addOption(Option("Meditate", "text", "You sit down and close your eyes. Soothing waves whisper against the shore as the sun \n|| glitters across the lake - a perfect moment for stillness."));

    //Bamboo Grove options
    bamboo.addOption(Option("Inspect a passage", "obstacle", "A stiff path that leads towards the mountain.", Obstacle("Passage", "A passage looks too stiff. Without a proper equipment you won't be able to climb.", "Assets/Obstacle/passage.txt", "Climbing Equipment", "pathway", &bamboo, &peak)));
    bamboo.addOption(Option("Get near the altar", "item", "You spot an altar on your way. Next to it lies an axe.", Item("Well-worn Axe", "Old but reliable. Its edge has seen better days, but it still cuts true.", "Assets/Items/axe.txt")));

    //Castle options
    castle.addOption(Option("Take a look at the ruins", "text", "The ruined castle stands in solemn silence - once grand, now fragile beneath the weight of time."));
    castle.addOption(Option("Look around the garden area", "item", "On a meditating spot you locate a note.", Item("Fourth Page", "Even the greatest of things fall - and that, too, is part of their story.", "Assets/Items/fourthPage.txt")));
    castle.addOption(Option("Examine the blockage", "obstacle", "You get near ruined barracks", Obstacle("Blockage", "You’re met with a heap of broken wood where a passage once stood.\n|| If only you had something, that could smash through.", "Assets/Obstacle/blockage.txt", "Well-worn Axe", "item", Item("Climbing Equipment", "Essential tools for scaling heights. Thankfully, they're still in good condition.", "Assets/Items/equipment.txt"))));

    //Peak options
    peak.addOption(Option("Collect a note", "item", "You spot a weathered note, held in place by a few small rocks.", Item("Fifth Page", "You reached the summit not to conquer it, but to understand the path you endured.", "Assets/Items/fifthPage.txt")));
    peak.addOption(Option("Meditate", "text", "You’ve reached the summit, yet something stirs within - doubt, perhaps.\n|| Was this the goal, or just a resting place before a higher climb you've yet to see?"));
    peak.addOption(Option("Perceive the Truth", "obstacle", "Find the hidden.", Obstacle("Truth", "Only the wise recognize what others overlook \n|| - and wisdom often hides in words left behind.", "Assets/Obstacle/truth.txt", "Wisdom", "pathway", &peak, &grave)));

    //Grave options
    grave.addOption(Option("Meditate", "text", "You kneel beside the grave, the wind still, the world quiet.\n|| In this silence, every step, every doubt, every scar you've carried settles into place.\n|| This is not just an end - \n|| it is the shape of everything you've become."));
    grave.addOption(Option("Offer tribute", "obstacle", "You sit down by the grave", Obstacle("Tribute", "You've reached your destination. It's time to lay down your offerings.", "Assets/Obstacle/tribute.txt", "Offerings", "item", Item("Fading Tome", "This tome contains the shape of your path - the echoes of your footsteps,\n|| the weight of your knowledge, and the truths you chose to carry.", "Assets/Items/tome.txt"))));

    //Main Game Logic
    std::cout << "||-----------------------------------------------------------------------------------------||" << std::endl;
    std::cout << "||      Please, Fullscreen or Maximaze the game for better experience!(alt + enter)	   ||" << std::endl;
    std::cout << "||                               Press enter to continue	                           ||" << std::endl;
    std::cout << "||-----------------------------------------------------------------------------------------||" << std::endl;
    std::cin.ignore();
    system("cls");

    //printing title screen
    std::ifstream file("Assets/title.txt");
    if (!file)
    {
        std::cout << "Error opening file: " << "title.txt" << std::endl;
    }
    std::string line;
    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }
    file.close();

    int startChoice = getUserInput(1, 2);

    if (startChoice == 2)
    {
        loadGame(player, currentArea, allAreas);    //loads the save file
        checkForWisdom(player);
    }
    system("cls");


    while (true)
    {
        checkForWisdom(player);
        showMap(currentArea);
        int pathCount = currentArea->getPathways().size();  //stores the size of all the pathways in the area
        int totalOptions = pathCount + 5;                   //stores a value of all the pathways in the area and adds 5 (options)
        int userInput = getUserInput(1, totalOptions);

        if (userInput == 1)
        {
            enterInsideArea(currentArea, player);
        }
        else if (userInput == 2)
        {
            openInventory(currentArea, player, isInside);
        }
        else if (userInput >= 3 and userInput <= pathCount + 2)
        {
            currentArea = currentArea->getPathways()[userInput - 3];
        }
        else if (userInput == pathCount + 3)
        {
            saveGame(player, currentArea, allAreas);
        }
        else if (userInput == pathCount + 4)
        {
            loadGame(player, currentArea, allAreas);
        }   
        else if (userInput == pathCount + 5)
        {
            std::cout << "Thank you for playing. See you next time!" << std::endl;
            break;
        }
        
    }       
}

void showMap(Area* currentArea)
{
    system("cls");
    currentArea->printMap();

    //First option of each area is to go inside that area
    std::cout << "|| [" << 1 << "]" << " " << currentArea->getExplore() << std::endl;

    //Second option of each area is to open the inventory
    std::cout << "|| [" << 2 << "]" << " Open Inventory" << std::endl;

    //for loop to create pathways options (3 - pathways vector size)
    for (int i = 0; i < currentArea->getPathways().size(); i++)
    {
        std::cout << "|| [" << i + 3 << "]" << " " << currentArea->getPathways()[i]->getOverview() << std::endl;
    }
    std::cout << "||======================================||" << std::endl;
    //option to save the game
    std::cout << "|| [" << currentArea->getPathways().size() + 3 << "] Save Game" << std::endl;

    //option to load the game
    std::cout << "|| [" << currentArea->getPathways().size() + 4 << "] Load Game" << std::endl;

    //option to quit the game
    std::cout << "|| [" << currentArea->getPathways().size() + 5 << "] Exit Game" << std::endl;
    std::cout << "||======================================||" << std::endl;
}

void enterInsideArea(Area* currentArea, Player& player)
{
    bool isInside = true;
    while (true)
    {
        system("cls");
        currentArea->printInside();
        std::cout << "|| [" << 1 << "]" << " Go back to the global map" << std::endl;
        std::cout << "|| [" << 2 << "]" << " Explore the area" << std::endl;
        std::cout << "|| [" << 3 << "]" << " Open inventory" << std::endl;
        std::cout << "||================================================================================================================||" << std::endl;

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
                std::cout << "|| ";
                std::cout << currentArea->getOption(exploreInput-2).getOptionText() << std::endl;
                std::cout << "||" << std::endl;
                std::cout << "|| Press any enter to continue..." << std::endl;
                std::cout << "||================================================================================================================||" << std::endl;
                std::cin.ignore();
                std::cin.get();
            }

            else if (currentArea->getOption(exploreInput - 2).getOptionType() == "item" and currentArea->getOption(exploreInput - 2).getHasInteracted() == false)
            {
                currentArea->getOption(exploreInput - 2).solveInteracted();

                std::cout << "|| ";
                std::cout << currentArea->getOption(exploreInput - 2).getOptionText() << std::endl;
                player.addItem(currentArea->getOption(exploreInput - 2).getOptionItem());

                std::cout << "|| " << std::endl;
                std::cout << "|| A new item was added to your inventory. Press enter to continue..." << std::endl;
                std::cout << "||================================================================================================================||" << std::endl;
                std::cin.ignore();
                std::cin.get();
            }    

            else if (currentArea->getOption(exploreInput - 2).getOptionType() == "obstacle" and !currentArea->getOption(exploreInput - 2).getHasInteracted())
            {
                Option& selectedOption = currentArea->getOption(exploreInput - 2);
                currentArea->exploreArea(player, selectedOption);
            }
            
        }
        else if (userInput == 3)
        {
            openInventory(currentArea, player, isInside);
        }
    }
}

void openInventory(Area* currentArea, Player& player, bool isInside)
{
    checkForWisdom(player);
    if (player.hasItem("Fading Tome"))
    {
        player.removeItem("First Page");
        player.removeItem("Second Page");
        player.removeItem("Third Page");
        player.removeItem("Fourth Page");
        player.removeItem("Fifth Page");
    }
    std::cout << "||======================================||" << std::endl;
    std::cout << "||            Your inventory            ||" << std::endl;
    std::cout << "||======================================||" << std::endl;
    std::cout << "|| [1] Go back" << std::endl;

    int index = 2;      //index start from 2 — items begin from option
    for (auto& item : player.getInventory())
    {
        std::cout << "|| [" << index << "] " << item.getName() << std::endl;  //iterating through each item
        ++index;
    }

    std::cout << "||======================================||" << std::endl;

    int choice = getUserInput(1, player.getInventory().size() + 1);
    if (choice == 1)
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

    else
    {
        Item selectedItem = player.getInventory()[choice - 2];

        //show item info
        system("cls");
        selectedItem.printImage();
        std::cout << "|| Description: " << selectedItem.getDescription() << std::endl;
        std::cout << "||================================================================================================================||" << std::endl;
        std::cout << "|| [1] Go back" << std::endl;

        int backChoice = getUserInput(1, 1);
        if (backChoice == 1)
        {
            //check for Fading Tome — if present, show credits and exit
            if (selectedItem.getName() == "Fading Tome")
            {
                system("cls");
                std::cout << "||=====================================================================================||" << std::endl;
                std::cout << "||                          Congratulations, you’ve finished the game!                 ||" << std::endl;
                std::cout << "||=====================================================================================||" << std::endl;
                std::cout << "||                                                                                     ||" << std::endl;
                std::cout << "||               Your journey through fading echoes has come to an end.                ||" << std::endl;
                std::cout << "||      The spirits rest, the past is honored, and your legacy has been fulfilled.     ||" << std::endl;
                std::cout << "||                                                                                     ||" << std::endl;
                std::cout << "||                       Thank you for playing. Farewell, wanderer.                    ||" << std::endl;
                std::cout << "||                                                                                     ||" << std::endl;
                std::cout << "||=====================================================================================||" << std::endl;
                std::cin.ignore();
                std::cin.get();
                exit(0); //exit the game
            }

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
        std::cout << ">>> ";

        //check if the input is an integer
        if (std::cin >> userInput)
        {
            if (userInput >= min && userInput <= max) 
            {
                return userInput;
            }
            else 
            {
                std::cout << "|| Input is out of range. Try again." << std::endl;
            }
        }
        else 
        {
            //if input is not an integer, clear the error and ignore the rest of the line
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); //clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore invalid input
        }
    }
}


void saveGame(Player& player, Area* currentArea, std::vector<Area*>& allAreas)
{
    //saving the game state to a JSON file
    nlohmann::json saveData;
    saveData["area"] = currentArea->getName();
    nlohmann::json inventoryArray;

    //saving inventory
    for (Item& item : player.getInventory())        //iterating through the player's inventory and copying each item to a save file
    {
        nlohmann::json itemJson;
        itemJson["name"] = item.getName();
        itemJson["description"] = item.getDescription();
        itemJson["image"] = item.getImage();
        inventoryArray.push_back(itemJson);
    }

    saveData["inventory"] = inventoryArray;

    //saving all interacted options
    nlohmann::json interactedArray;
    for (Area* area : allAreas)                //iterating through each area in the allAreas vector and copying options that have been interacted to a save file
    {
        for (Option& opt : area->getOptions()) 
        {
            if (opt.getHasInteracted()) 
            {
                nlohmann::json interacted;
                interacted["area"] = area->getName();
                interacted["option"] = opt.getDescription();
                interactedArray.push_back(interacted);
            }
        }
    }
    saveData["interactedOptions"] = interactedArray;

    //saving all solved obstacles
    nlohmann::json solvedObstaclesArray;
    for (Area* area : allAreas)                 //iterating through each area in the allAreas vector, then through each option that is an obstacle and have been solved to copy to a save file
    {
        for (Option& opt : area->getOptions())  
        {
            if (opt.getOptionType() == "obstacle") 
            {
                Obstacle obs = opt.getOptionObstacle();
                if (obs.isSolved()) 
                {
                    nlohmann::json solved;
                    solved["area"] = area->getName();
                    solved["option"] = opt.getDescription();
                    solvedObstaclesArray.push_back(solved);
                }
            }
        }
    }
    saveData["solvedObstacles"] = solvedObstaclesArray;

    //saving all unlocked pathways
    nlohmann::json openPathwaysArray;
    for (Area* area : allAreas) 
    {
        for (Area* connectedArea : area->getPathways()) 
        {
            nlohmann::json path;
            path["from"] = area->getName();
            path["to"] = connectedArea->getName();
            openPathwaysArray.push_back(path);
        }
    }
    saveData["openPathways"] = openPathwaysArray;

    std::ofstream file("save.json");     //creating a save file
    if (file.is_open()) 
    {
        file << saveData.dump(4);   //writing all the saved date to the save file
        file.close();
        std::cout << "Game saved successfully!\n";
        std::cin.ignore();
        std::cin.get();
    }
    else 
    {
        std::cerr << "Failed to save the game.\n";
        std::cin.ignore();
        std::cin.get();
    }
}

//loading the game state from a JSON save file
void loadGame(Player& player, Area*& currentArea, std::vector<Area*>& allAreas)
{
    std::ifstream file("save.json"); //getting the save file
    if (!file.is_open()) {
        std::cerr << "Failed to open save file.\n";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    nlohmann::json saveData;
    file >> saveData;   //loading all the saved data to a saveData variable
    file.close();

    //loading current area
    std::string areaName = saveData["area"];
    for (Area* area : allAreas)         //checking for a matching name and and making that a current area
    {
        if (area->getName() == areaName) 
        {
            currentArea = area;
            break;
        }
    }

    //loading inventory
    player.getInventory().clear();
    for (nlohmann::json itemData : saveData["inventory"])
    {
        std::string name = itemData["name"];
        std::string desc = itemData["description"];
        std::string image = itemData["image"];
        player.addItem(Item(name, desc, image));        //adding all the saved items back to player's inventory
    }

    //loading interacted options
    for (nlohmann::json entry : saveData["interactedOptions"])
    {
        std::string entryArea = entry["area"];
        std::string optionDesc = entry["option"];

        for (Area* area : allAreas)
        {
            if (area->getName() == entryArea)
            {
                try
                {
                    Option& opt = area->getOption(optionDesc);  //checking for a matching description and rendering that option as interacted
                    opt.solveInteracted();
                }
                catch (const std::runtime_error& e)
                {
                    std::cerr << "Warning: " << e.what() << std::endl;
                }
            }
        }
    }
    
    //loading solved obstacles
    for (nlohmann::json solvedEntry : saveData["solvedObstacles"])
    {
        std::string areaName = solvedEntry["area"];
        std::string optionDesc = solvedEntry["option"];

        for (Area* area : allAreas) 
        {
            if (area->getName() == areaName) 
            {
                for (Option& opt : area->getOptions()) 
                {
                    if (opt.getDescription() == optionDesc and opt.getOptionType() == "obstacle")   //checking for an obstacle type of the option and rendering it as solved
                    {
                        opt.getOptionObstacle().solve();
                        opt.solveInteracted();
                    }
                }
            }
        }
    }

    std::cout << "Game loaded successfully!\n";
    std::cin.ignore();
    std::cin.get();

    
    //loading unlocked pathways
    if (saveData.contains("openPathways")) 
    {
        for (nlohmann::json path : saveData["openPathways"])
        {
            std::string from = path["from"];
            std::string to = path["to"];
            Area* fromArea = nullptr;
            Area* toArea = nullptr;

            for (Area* area : allAreas) 
            {
                if (area->getName() == from) fromArea = area;
                if (area->getName() == to) toArea = area;
            }

            if (fromArea and toArea) 
            {
                //checking if pathway already exists
                bool alreadyExists = false;
                for (Area* existing : fromArea->getPathways()) 
                {
                    if (existing->getName() == toArea->getName()) 
                    {
                        alreadyExists = true;
                        break;
                    }
                }

                if (!alreadyExists) 
                {
                    fromArea->addPathway(*toArea);
                }
            }
        }
    }
}

void checkForWisdom(Player& player) 
{
    if (!player.hasItem("Wisdom")) 
    {
        if (player.hasItem("First Page") and
            player.hasItem("Second Page") and
            player.hasItem("Third Page") and
            player.hasItem("Fourth Page") and
            player.hasItem("Fifth Page"))
        {
            player.addItem(Item("Wisdom", "You found all the pages of your lost legacy. Wisdom flows through you.", "Assets/Items/wisdom.txt"));
            std::cout << "=== Wisdom becomes a part of you.... ===" << std::endl;
        }
    }
}