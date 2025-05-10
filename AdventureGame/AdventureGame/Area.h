#pragma once
#include <vector>
#include <string>
#include "Item.h"		//include item class
#include "Obstacle.h"	//include obstacle class
#include "Player.h"
#include "Option.h"



/**
* @class Area
* @brief Represents an area in the game.
*
* The Area class manages all areas, the pathways between them, and the content inside each area.
* It interacts with the Obstacle, Player, and Item classes.
*/
class Area
{
private:
    /**
    * @brief Name of the area.
    */
    std::string name;

    /**
    * @brief Description of the area.
    */
    std::string description;

    /**
    * @brief Description when exploring the area's inside zone.
    */
    std::string explore;

    /**
    * @brief Overview of the area from another area's perspective.
    */
    std::string overview;

    /**
    * @brief Vector of items present inside the area.
    */
    std::vector<Item> items;

    /**
    * @brief Vector of pathways connected to this area.
    */
    std::vector<Area*> pathways;

    /**
    * @brief Path to a .txt file containing the image of this area on the map.
    */
    std::string mapPath;

    /**
    * @brief Path to a .txt file containing the image of this area's inside zone.
    */
    std::string mapInsidePath;

    /**
    * @brief Vector of obstacles present inside the area.
    */
    std::vector<Obstacle> obstacles;

    /**
    * @brief Vector of options present inside the area.
    */
    std::vector<Option> options;

public:
    /**
    * @brief An empty construct of an Area object.
    */
    Area();

    /**
    * @brief Constructs an Area object.
    * @param i_name The name of the area.
    * @param i_overview The overview of the area from another area’s perspective.
    * @param i_mapPath Path to the .txt file representing the area on the map.
    * @param i_mapInsidePath Path to the .txt file representing the inside zone of the area.
    */
    Area(std::string i_name, std::string i_overview, std::string i_mapPath, std::string i_mapInsidePath);

    // Getters and Setters for parameters -----------------------------

    /**
    * @brief Sets the name of the area.
    * @param name The new name of the area.
    */
    void setName(std::string name);

    /**
    * @brief Retrieves the name of the area.
    * @return The name of the area.
    */
    std::string getName();

    /**
    * @brief Sets the description of the area.
    * @param description The description of the area.
    */
    void setDescription(std::string description);

    /**
    * @brief Retrieves the description of the area.
    * @return The description of the area.
    */
    std::string getDescription();

    /**
    * @brief Sets the explore description for the area (e.g., for going inside).
    * @param explore The explore description for the area.
    */
    void setExplore(std::string explore);

    /**
    * @brief Retrieves the explore description for the area.
    * @return The explore description of the area.
    */
    std::string getExplore();

    /**
    * @brief Sets the overview of the area from another area’s perspective.
    * @param overview The overview of the area.
    */
    void setOverview(std::string overview);

    /**
    * @brief Retrieves the overview of the area.
    * @return The overview of the area.
    */
    std::string getOverview();

    // Pathways --------------------------------------------------------

    /**
    * @brief Adds a new pathway from this area to another.
    * @param new_pathway The area to which the current area should connect.
    */
    void addPathway(Area& new_pathway);

    /**
    * @brief Retrieves all the pathways connected to this area.
    * @return A vector of areas connected to this area.
    */
    std::vector<Area*> getPathways();

    // Map Printing ----------------------------------------------------

    /**
    * @brief Retrieves the path to the .txt file representing the area on the map.
    * @return The map path of the area.
    */
    std::string getMapPath();

    /**
    * @brief Prints the .txt file representing the area’s map on screen.
    */
    void printMap();

    /**
    * @brief Prints the .txt file representing the inside zone of the area on screen.
    */
    void printInside();

    // Obstacles -------------------------------------------------------

    /**
    * @brief Adds a new obstacle to the area’s list of obstacles.
    * @param i_obstacle New obstacle
    */
    void addObstacle(Obstacle i_obstacle);

    /**
    * @brief Gets an obstacle's name from area's 'obstacle' vector
    * @param i_name Name of the obstacle.
    */
    Obstacle& getObstacle(std::string i_name);

    /**
    * @brief Presents the player with options to interact with an obstacle.
    * 1) Inspect the obstacle
    * 2) Let the player use an item from their inventory
    * 3) Leave the obstacle (go back to the area’s inside zone).
    * @param player The player interacting with the obstacle.
    */
    void exploreArea(Player& player, Option& option);

    /**
    * @brief Allows the player to choose an item from their inventory and checks if it is the correct item to solve the obstacle.
    * @param player The player interacting with the obstacle.
    * @param obstacle The obstacle the player is attempting to solve.
    */
    bool useItem(Player& player, Obstacle& obstacle);

    // Items ----------------------------------------------------------

    /**
    * @brief Adds a new item to the area’s list of items.
    * @param i_item New item
    */
    void addItem(Item i_item);

    /**
    * @brief Removes an item from the area’s list of items.
    * @param i_name The name of the item to be removed.
    */
    void removeItem(std::string i_name);

    /**
    * @brief Checks if the area contains any items.
    * @return True if there are items in the area, false otherwise.
    */
    bool hasItems();

    /**
    * @brief Adds an option to select when exploring the area
    * @param i_option New option
    */
    void addOption(Option i_option);

    /**
    * @brief Getter for an option
    * @param i_description Description of that option
    */
    Option& getOption(std::string i_description);

    /**
    * @brief Getter for an index of an option
    * @param i_index Index of an option you want to get
    */
    Option& getOption(int i_index);

    /**
    * @brief Getter for all options inside an area
    * @return All the options inside an area's vector
    */
    std::vector<Option> getOptions();

    /**
    * @brief Displays all the options in the area in a list
    * @return Vector of options
    */
    void displayOptions();

    /**
    * @brief Gets all the size of the list of options inside an area
    * @return The size of options inside an area
    */
    int getOptionSize();
};




