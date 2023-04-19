//
// Created by Lorne on 2023-04-14.
//

#include "../inc/Organism.h"
#include <random>


//Constructors
Organism::Organism() = default;
Organism::Organism(City *city, int x, int y) {
    this->city = city;
    this->x = x;
    this->y = y;
}
Organism::~Organism() = default;

//Getters and Setters
void Organism::setPosition(Organism *organism, int j, int k){ //Sets the position of an organism in a specific city
    this->x = j;
    this->y = k;
    organism->city->setOrganism(organism, j, k);
}

int Organism::getRandomNumber() { //Generates a random number between 0-3 (N,S,E,W), used for human movement
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 3);
    return distrib(gen);
}


