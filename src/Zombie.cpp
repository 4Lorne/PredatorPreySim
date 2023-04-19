//
// Created by Lorne on 2023-04-16.
//

#include <utility>
#include <random>

#include "../inc/Zombie.h"
#include "../inc/Human.h"

Zombie::Zombie() = default;

Zombie::Zombie(City *city, int x, int y) {
    this->species = "Zombie";
    this->city = city;
    this->x = x;
    this->y = y;
    this->canBreed = false;
    this->breedCounter = 8;
    this->stepsSinceEaten = 0;
}

Zombie::~Zombie() = default;

//Getters and Setters
void Zombie::setSpecies(string species) {
    this->species = std::move(species);
}

int Zombie::getStepsSinceEaten() const{
    return this->stepsSinceEaten;
}

void Zombie::setStepsSinceEaten(int steps){
    this->stepsSinceEaten = steps;
}

string Zombie::getSpecies() {
    return this->species;
}

bool Zombie::getBreedingStatus() const {
    return this->canBreed;
}

bool Zombie::setBreedingStatus(bool status) {
    return this->canBreed = status;
}

int Zombie::getX() {
    return this->x;
}

int Zombie::getY() {
    return this->y;
}

//Functions
void Zombie::move() {
    //Generates a random number between 0 and 7 for each of the cardinal directions
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 7);
    int direction = distrib(gen);

    stepsSinceEaten++;

    switch (direction){
        case WEST:
            //Checks if it is interacting with another organism
            if (city->getOrganism(x, y) != this) {
                break;
            }
            //Checks if the space is a null pointer and moves there
            if (city->getOrganism(x, y - 1) != nullptr && City::isEmptyAndInBounds(x,y-1,city)) {
                city->setOrganism(this, x, y - 1);
                city->setOrganism(nullptr, x, y);
                y--;
            }
            break;
        case EAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x, y + 1) == nullptr && City::isEmptyAndInBounds(x,y+1,city)) {
                city->setOrganism(this, x, y + 1);
                city->setOrganism(nullptr, x, y);
                y++;
            }
            break;
        case NORTH:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x - 1, y) == nullptr && City::isEmptyAndInBounds(x-1,y,city)) {
                city->setOrganism(this, x - 1, y);
                city->setOrganism(nullptr, x, y);
                x--;
            }
            break;
        case SOUTH:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x + 1, y) == nullptr && City::isEmptyAndInBounds(x+1,y,city)) {
                city->setOrganism(this, x + 1, y);
                city->setOrganism(nullptr, x, y);
                x++;
            }
            break;
        case NORTHWEST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x - 1, y-1) == nullptr && City::isEmptyAndInBounds(x-1,y-1,city)) {
                city->setOrganism(this, x - 1, y-1);
                city->setOrganism(nullptr, x, y);
                x--;
                y--;
            }
            break;
        case SOUTHWEST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x + 1, y-1) == nullptr && City::isEmptyAndInBounds(x+1,y-1,city)) {
                city->setOrganism(this, x + 1, y -1);
                city->setOrganism(nullptr, x, y);
                x++;
                y--;
            }
            break;
        case SOUTHEAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x + 1, y+1) == nullptr && City::isEmptyAndInBounds(x+1,y+1,city)) {
                city->setOrganism(this, x + 1, y +1);
                city->setOrganism(nullptr, x, y);
                x++;
                y++;
            }
            break;
        case NORTHEAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x - 1, y+1) == nullptr && City::isEmptyAndInBounds(x-1,y+1,city)) {
                city->setOrganism(this, x - 1, y+1);
                city->setOrganism(nullptr, x, y);
                x--;
                y++;
            }
            break;
        default:
            break;
    }

    /*switch (direction) {
        case WEST:
            //Checks if it is interacting with itself
            if (city->getOrganism(x, y) != this) {
                break;
            }
            //Checks if the space is a human and if it is replaces the human with a zombie
            *//*if (city->getOrganism(x, y - 1) != nullptr && city->getOrganism(x, y - 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x, y - 1), x, y - 1);
                canBreed = true;
            }*//*
                //If it is a null pointer it will move without converting anything
            else if (City::isEmptyAndInBounds(x,y-1,city)){
                city->setOrganism(this, x, y - 1);
                city->setOrganism(nullptr, x, y);
                y--;
            }
            break;
        case NORTH:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            *//*if (city->getOrganism(x, y + 1) != nullptr && city->getOrganism(x, y + 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x, y + 1), x, y + 1);
                canBreed = true;

            }*//**//* else if (city->getOrganism(x, y + 1) == nullptr && City::inBounds(x, y + 1)) {
                city->setOrganism(this, x, y + 1);
                city->setOrganism(nullptr, x, y);
                y++;
            }*//*
            break;
        case EAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            *//*if (city->getOrganism(x - 1, y) != nullptr && city->getOrganism(x - 1, y)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x - 1, y), x - 1, y);
                canBreed = true;

            }*//* *//*else if (city->getOrganism(x - 1, y) == nullptr && City::inBounds(x - 1, y)) {
                city->setOrganism(this, x - 1, y);
                city->setOrganism(nullptr, x, y);
                x--;

            }*//*
            break;
        case SOUTH:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            *//*if (city->getOrganism(x + 1, y) != nullptr && city->getOrganism(x + 1, y)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x + 1, y), x + 1, y);
                canBreed = true;

            }*//* *//*else if (city->getOrganism(x + 1, y) == nullptr && City::inBounds(x + 1, y)) {
                city->setOrganism(this, x + 1, y);
                city->setOrganism(nullptr, x, y);
                x++;

            }*//*
            break;
        case NORTHWEST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
           *//* if (city->getOrganism(x - 1, y - 1) != nullptr &&
                city->getOrganism(x - 1, y - 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x - 1, y - 1), x - 1, y - 1);
                canBreed = true;

            }*//* *//*else if (city->getOrganism(x - 1, y - 1) == nullptr && City::inBounds(x - 1, y - 1)) {
                city->setOrganism(this, x - 1, y - 1);
                city->setOrganism(nullptr, x, y);
                x--;
                y--;

            }*//*
            break;

        case SOUTHWEST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            *//*if (city->getOrganism(x + 1, y - 1) != nullptr &&
                city->getOrganism(x + 1, y - 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x + 1, y - 1), x + 1, y - 1);
                canBreed = true;

            }*//* *//*else if (city->getOrganism(x + 1, y - 1) == nullptr && City::inBounds(x + 1, y - 1)) {
                city->setOrganism(this, x + 1, y - 1);
                city->setOrganism(nullptr, x, y);
                x++;
                y--;

            }*//*
            break;

        case SOUTHEAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            *//*if (city->getOrganism(x + 1, y + 1) != nullptr &&
                city->getOrganism(x + 1, y + 1)->getSpecies() == "Human" && City::inBounds(x + 1, y + 1)) {
                city->setOrganism(new Zombie(*city, x + 1, y + 1), x + 1, y + 1);
                canBreed = true;
            }*//* *//*else if (city->getOrganism(x + 1, y + 1) == nullptr && City::inBounds(x + 1, y + 1)) {
                city->setOrganism(this, x + 1, y + 1);
                city->setOrganism(nullptr, x, y);
                x++;
                y++;
            }*//*
            break;

        case NORTHEAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            *//*if (city->getOrganism(x - 1, y + 1) != nullptr &&
                city->getOrganism(x - 1, y + 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x - 1, y + 1), x - 1, y + 1);
                canBreed = true;
            }*//* *//*else if (city->getOrganism(x - 1, y + 1) == nullptr && City::inBounds(x - 1, y + 1)) {
                city->setOrganism(this, x - 1, y + 1);
                city->setOrganism(nullptr, x, y);
                x--;
                y++;

            }*//*
            break;
        default:
            break;

    }*/

    /*if (breedCounter > 0) {
        canBreed = false;
        breedCounter--;
    }
    if (breedCounter == 0) {
        int x = viableBreedingGrounds();
        if (x < 4) {
            canBreed = true;
        } else {
            breedCounter = 0;
        }
    }*/
}


//Checks the directions for humans & zombies
int Zombie::viableBreedingGrounds() {
    int direction = 0;
    //If there are no valid locations, this function will return 8
    while (direction < 8) {
        switch (direction) {
            case WEST:
                if (city->getOrganism(x, y - 1) == nullptr && City::inBounds(x, y - 1) ||
                    (city->getOrganism(x, y - 1) != nullptr && city->getOrganism(x, y - 1)->getSpecies() == "Human")) {
                    return direction;
                }
                break;
            case EAST:
                if (city->getOrganism(x, y + 1) == nullptr && City::inBounds(x, y + 1) ||
                    (city->getOrganism(x, y + 1) != nullptr && city->getOrganism(x, y + 1)->getSpecies() == "Human")) {
                    return direction;
                }
                break;
            case NORTH:
                if (city->getOrganism(x - 1, y) == nullptr && City::inBounds(x - 1, y) ||
                    (city->getOrganism(x + 1, y) != nullptr && city->getOrganism(x + 1, y)->getSpecies() == "Human")) {
                    return direction;
                }
                break;
            case SOUTH:
                if (city->getOrganism(x + 1, y) == nullptr && City::inBounds(x + 1, y) ||
                    (city->getOrganism(x + 1, y) != nullptr && city->getOrganism(x + 1, y)->getSpecies() == "Human")) {
                    return direction;
                }
                break;
            case NORTHWEST:
                if (city->getOrganism(x - 1, y - 1) == nullptr && City::inBounds(x - 1, y - 1) ||
                    (city->getOrganism(x - 1, y - 1) != nullptr &&
                     city->getOrganism(x - 1, y - 1)->getSpecies() == "Human")) {
                    return direction;
                }
                break;
            case SOUTHWEST:
                if (city->getOrganism(x + 1, y - 1) == nullptr && City::inBounds(x + 1, y - 1) ||
                    (city->getOrganism(x + 1, y - 1) != nullptr &&
                     city->getOrganism(x + 1, y - 1)->getSpecies() == "Human")) {
                    return direction;
                }
                break;
            case SOUTHEAST:
                if (city->getOrganism(x + 1, y + 1) == nullptr && City::inBounds(x + 1, y + 1) ||
                    (city->getOrganism(x + 1, y + 1) != nullptr &&
                     city->getOrganism(x + 1, y + 1)->getSpecies() == "Human" && City::inBounds(x + 1, y + 1))) {
                    return direction;
                }
                break;
            case NORTHEAST:
                if (city->getOrganism(x - 1, y + 1) == nullptr && City::inBounds(x - 1, y + 1) ||
                    (city->getOrganism(x - 1, y + 1) != nullptr &&
                     city->getOrganism(x - 1, y + 1)->getSpecies() == "Human")) {
                    return direction;
                }
                break;
            default:
                break;
        }
        direction++;
    }
    return 8;
}