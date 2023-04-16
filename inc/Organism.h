//
// Created by Lorne on 2023-04-14.
//

#include "City.h"
#include <iostream>

#ifndef HUMANZOMBIES_ORGANISM_H
#define HUMANZOMBIES_ORGANISM_H


using namespace std;

class Organism {
protected:
    int x;
    int y;
    int width;
    int height;
    bool moved;
    City *city;

    enum {
        WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS
    };

public:
    Organism(); //Default
    Organism(City *city, int width, int height); //Generate the city
    virtual ~Organism(); //Destructor

    void setPosition(Organism& organism, int x, int y); //Position in the city
    void endTurn(); //Ends the turn for the species
    bool isTurn(); //Checks if it is the species turn

    friend ostream& operator<<( ostream& output, Organism* organism); //Override for output
};

#endif //HUMANZOMBIES_ORGANISM_H
