//
// Created by Lorne on 2023-04-16.
//

#include <utility>
#include <random>

#include "../inc/Zombie.h"

Zombie::Zombie() {

}

Zombie::Zombie(City &city, int x, int y) {
    this->species = "Zombie";
    this->city = &city;
    this->x = x;
    this->y = y;
}

void Zombie::setSpecies(string species) {
    this->species = std::move(species);
}

string Zombie::getSpecies() {
    return this->species;
}

bool Zombie::getBreedingStatus() const{
    return this->canBreed;
}

bool Zombie::setBreedingStatus(bool status){
    this->canBreed = status;
}

int Zombie::getX(){
    return x;
}

int Zombie::getY(){
    return y;
}

Zombie::~Zombie() = default;


void Zombie::move() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 6);
    int direction = distrib(gen);

    // Move the human up if the cell above is empty
    switch(direction){
        case WEST:
            if (city->getOrganism(x, y) != this) {
                // The current cell is not empty, don't move
                break;
            }
            if (city->getOrganism(x, y - 1) == nullptr && City::inBounds(x, y - 1)) {
                city->setOrganism(this, x, y - 1);
                city->setOrganism(nullptr, x, y);
                y--;
            }
            break;
        case EAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x, y + 1) == nullptr && City::inBounds(x, y + 1)) {
                city->setOrganism(this, x, y + 1);
                city->setOrganism(nullptr, x, y);
                y++;
            }
            break;
        case NORTH:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x - 1, y) == nullptr && City::inBounds(x - 1, y)) {
                city->setOrganism(this, x - 1, y);
                city->setOrganism(nullptr, x, y);
                x--;
            }
            break;
        case SOUTH:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x + 1, y) == nullptr && City::inBounds(x + 1, y)) {
                city->setOrganism(this, x + 1, y);
                city->setOrganism(nullptr, x, y);
                x++;
            }
            break;
        case NORTHWEST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x - 1, y - 1) == nullptr && City::inBounds(x - 1, y - 1)) {
                city->setOrganism(this, x - 1, y - 1);
                city->setOrganism(nullptr, x, y);
                x--;
                y--;
            }
            break;

        case SOUTHWEST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x + 1, y - 1) == nullptr && City::inBounds(x + 1, y - 1)) {
                city->setOrganism(this, x + 1, y - 1);
                city->setOrganism(nullptr, x, y);
                x++;
                y--;
            }
            break;
        case SOUTHEAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x + 1, y + 1) == nullptr && City::inBounds(x + 1, y + 1)) {
                city->setOrganism(this, x + 1, y + 1);
                city->setOrganism(nullptr, x, y);
                x++;
                y++;
            }
            break;
        case NORTHEAST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x - 1, y + 1) == nullptr && City::inBounds(x - 1, y + 1)) {
                city->setOrganism(this, x - 1, y + 1);
                city->setOrganism(nullptr, x, y);
                x--;
                y++;
            }
            break;
    }
    if (breedCounter > 0){
        canBreed = false;
        breedCounter--;
    }
    if (breedCounter == 0){
        int x = viableBreedingGrounds();
        if (x < 4){
            canBreed = true;
        } else {
            breedCounter = 0;
        }
    }
}

int Zombie::viableBreedingGrounds(){
    int direction = 0;

    //Starts from 0 and increments up until 8, at which case we know there are no viable spots.
    while (direction < 8) {
        switch (direction) {
            case WEST:
                if (city->getOrganism(x, y - 1) == nullptr && City::inBounds(x, y - 1)) {
                    return direction;
                }
                break;
            case EAST:
                if (city->getOrganism(x, y + 1) == nullptr && City::inBounds(x, y + 1)) {
                    return direction;
                }
                break;
            case NORTH:
                if (city->getOrganism(x - 1, y) == nullptr && City::inBounds(x - 1, y)) {
                    return direction;
                }
                break;
            case SOUTH:
                if (city->getOrganism(x + 1, y) == nullptr && City::inBounds(x + 1, y)) {
                    return direction;
                }
                break;
            case NORTHWEST:
                if (city->getOrganism(x - 1, y - 1) == nullptr && City::inBounds(x - 1, y - 1)) {
                    return direction;
                }
                break;
            case SOUTHWEST:
                if (city->getOrganism(x + 1, y - 1) == nullptr && City::inBounds(x + 1, y - 1)) {
                    return direction;
                }
                break;
            case SOUTHEAST:
                if (city->getOrganism(x + 1, y + 1) == nullptr && City::inBounds(x + 1, y + 1)) {
                    return direction;
                }
                break;
            case NORTHEAST:
                if (city->getOrganism(x - 1, y + 1) == nullptr && City::inBounds(x - 1, y + 1)) {
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

