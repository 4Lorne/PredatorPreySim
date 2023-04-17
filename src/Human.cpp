//
// Created by Lorne on 2023-04-16.
//

#include <random>
#include "../inc/Human.h"

Human::Human(City &city, int x, int y) {
    this->species = "Human";
    this->city = &city;
    this->canBreed = false;
    this->breedCounter = HUMAN_BREED;
    this->moved = false;
    this->x = x;
    this->y = y;
}

Human::Human() {

}
Human::~Human() = default;

void Human::setSpecies(string species) {
    this->species = std::move(species);

}
string Human::getSpecies() {
    return this->species;
}

int Human::getX(){
    return x;
}

int Human::getY(){
    return y;
}

bool Human::getBreedingStatus() const{
    return this->canBreed;
}


void Human::move() {
    int direction = getRandomNumber();

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
    }
    if (breedCounter > 0){
        canBreed = false;
        breedCounter--;
    }
    if (breedCounter == 0){
        if (viableBreedingGrounds() < 5){
            canBreed = true;
        }
        breedCounter = 3;
    }
}


//TODO: Bug in code
int Human::viableBreedingGrounds(){
    int direction = 0;

    //Starts from 0 and increments up until 5, at which case we know there are no viable spots.
    /*while (direction < 5){
        switch (direction){
            case WEST:
                if (city->getOrganism(x, y - 1) == nullptr && City::inBounds(x, y - 2)) {
                    return direction;
                }
                direction++;
                break;
            case EAST:
                if (city->getOrganism(x, y + 1) == nullptr && City::inBounds(x, y + 2)){
                    return direction;
                }
                direction++;
                break;
            case NORTH:
                if (city->getOrganism(x - 1, y) == nullptr && City::inBounds(x - 2, y)){
                    return direction;
                }
                direction++;
                break;
            case SOUTH:
                if (city->getOrganism(x + 1, y) == nullptr && City::inBounds(x + 2, y)){
                    return direction;
                }
                direction++;
                break;
        }
    }*/
    return 5;
}

