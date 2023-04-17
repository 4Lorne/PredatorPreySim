//
// Created by Lorne on 2023-04-14.
//

#ifndef HUMANZOMBIES_CITY_H
#define HUMANZOMBIES_CITY_H

#include <iostream>
#include "GameSpecs.h"

using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City{
public:
    City(); //Default
    virtual ~City(); //Destructor


    //Checks what organism is located at the coordinates
    Organism *getOrganism(int x, int y);
    //Sets a specific organism to a coordinate.
    void setOrganism(Organism* organism, int x, int y);

    //Checks if the zombie or human are within the bounds of the city
    static bool inBounds(int x, int y);

    //Overloaded output operator
    friend ostream& operator<<(ostream& output, City& city); //Override for output

    Organism *grid[GRID_HEIGHT][GRID_WIDTH]{};
};

#endif //HUMANZOMBIES_CITY_H