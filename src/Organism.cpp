//
// Created by Lorne on 2023-04-14.
//

#include "../inc/Organism.h"
#include <random>


//Constructors
Organism::Organism() {

}
Organism::Organism(City *city, int x, int y) {
    this->city = city;
    this->x = x;
    this->y = y;
}
Organism::~Organism() = default;


//Methods

//Randomly assigns an x and y position
void Organism::setPosition(Organism& organism) {

    //https://stackoverflow.com/a/38368609
    //Generates random numbers, uses another random number generator, and then a distribution system
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 18);

    x = dist(gen);
    y = dist(gen);

    //Checks if the position is empty
    if (city->getOrganism(x,y) == nullptr){
        city->setOrganism(organism,x,y);
    }
}

