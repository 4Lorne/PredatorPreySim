//
// Created by Lorne on 2023-04-16.
//

#include <random>
#include "../inc/Human.h"

Human::Human(City *city, int x, int y) {
    this->species = "Human";
    this->city = city;
    this->canBreed = false;
    this->breedCounter = HUMAN_BREED;
    this->moved = false;
    this->x = x;
    this->y = y;
}

Human::Human() = default;
Human::~Human() = default;

void Human::setSpecies(string species) {
    this->species = std::move(species);

}
string Human::getSpecies() {
    return this->species;
}

int Human::getX(){
    return this->x;
}

int Human::getY(){
    return this->y;
}

bool Human::getBreedingStatus() const{
    return this->canBreed;
}

void Human::setBreedingStatus(bool status){
    this->canBreed = status;
}


void Human::move() {
    int direction = getRandomNumber();

    // Move the human up if the cell above is empty
    switch(direction){
        case WEST:
            //Checks if it is interacting with another organism
            if (city->getOrganism(x, y) != this) {
                break;
            }
            //Checks if the space is a null pointer and moves there
            if (city->getOrganism(x, y - 1) == nullptr && City::isEmptyAndInBounds(x,y-1,city)) {
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
        default:
            break;
    }
    //Every step the breed counter decreases
    if (breedCounter > 0){
        canBreed = false;
        breedCounter--;
    }
    //Once it is at 0, if there are any viable breeding spots it will happen
    //If there are no viable spots, they lost their chance and it resets
    if (breedCounter == 0){
        int x = viableBreedingGrounds();
        if (x < 4){
            canBreed = true;
        } else {
            breedCounter = 3;
        }
    }
}

int Human::viableBreedingGrounds(){
    int direction = 0;
    //Starts from 0 and increments up until 5, at which case we know there are no viable spots.
    //If there are no valid locations, this function will return 5
    while (direction < 4) {
        switch (direction) {
            case WEST:
                if (City::isEmptyAndInBounds(x, y - 1, city)) {
                    return direction;
                }
                break;
            case NORTH:
                if (City::isEmptyAndInBounds(x, y+1, city)) {
                    return direction;
                }
                break;
            case EAST:
                if (City::isEmptyAndInBounds(x-1, y, city)) {
                    return direction;
                }
                break;
            case SOUTH:
                if (City::isEmptyAndInBounds(x + 1, y, city)) {
                    return direction;
                }
                break;
            default:
                break;
        }
        direction++;
    }
    return 4;
}



