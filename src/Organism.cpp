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

//Getters and Setters
void Organism::setPosition(Organism *organism, int x, int y){ //Sets the position of an organism in a specific city
    this->x = x;
    this->y = y;
    city->setOrganism(organism, x, y);
}

int Organism::getRandomNumber() { //Generates a random number between 0-3 (N,S,E,W), used for human movement
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 3);
    return distrib(gen);
}


