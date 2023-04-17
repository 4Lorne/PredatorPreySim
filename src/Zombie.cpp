//
// Created by Lorne on 2023-04-16.
//

#include <utility>
#include <random>

#include "../inc/Zombie.h"
#include "../inc/Human.h"

Zombie::Zombie() {

}

Zombie::Zombie(City &city, int x, int y) {
    this->species = "Zombie";
    this->city = &city;
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
    return x;
}

int Zombie::getY() {
    return y;
}

//Functions
void Zombie::move() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 6);
    int direction = distrib(gen);
    stepsSinceEaten++;
    // Move the human up if the cell above is empty
    switch (direction) {
        case WEST:
            if (city->getOrganism(x, y - 1) != nullptr && city->getOrganism(x, y - 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x, y - 1), x, y - 1);
                canBreed = true;
                stepsSinceEaten = 0;
            } else if (city->getOrganism(x, y - 1) == nullptr && City::inBounds(x, y - 1)) {
                city->setOrganism(this, x, y - 1);
                city->setOrganism(nullptr, x, y);
                y--;
            }
            break;
        case EAST:
            if (city->getOrganism(x, y + 1) != nullptr && city->getOrganism(x, y + 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x, y + 1), x, y + 1);
                canBreed = true;
                stepsSinceEaten = 0;

            } else if (city->getOrganism(x, y + 1) == nullptr && City::inBounds(x, y + 1)) {
                city->setOrganism(this, x, y + 1);
                city->setOrganism(nullptr, x, y);
                y++;
            }
            break;
        case NORTH:
            if (city->getOrganism(x - 1, y) != nullptr && city->getOrganism(x - 1, y)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x - 1, y), x - 1, y);
                canBreed = true;
                stepsSinceEaten = 0;

            } else if (city->getOrganism(x - 1, y) == nullptr && City::inBounds(x - 1, y)) {
                city->setOrganism(this, x - 1, y);
                city->setOrganism(nullptr, x, y);
                x--;

            }
            break;
        case SOUTH:
            if (city->getOrganism(x + 1, y) != nullptr && city->getOrganism(x + 1, y)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x + 1, y), x + 1, y);
                canBreed = true;
                stepsSinceEaten = 0;

            } else if (city->getOrganism(x + 1, y) == nullptr && City::inBounds(x + 1, y)) {
                city->setOrganism(this, x + 1, y);
                city->setOrganism(nullptr, x, y);
                x++;

            }
            break;
        case NORTHWEST:
            if (city->getOrganism(x, y) != this) {
                break;
            }
            if (city->getOrganism(x - 1, y - 1) != nullptr &&
                city->getOrganism(x - 1, y - 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x - 1, y - 1), x - 1, y - 1);
                canBreed = true;
                stepsSinceEaten = 0;

            } else if (city->getOrganism(x - 1, y - 1) == nullptr && City::inBounds(x - 1, y - 1)) {
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
            if (city->getOrganism(x + 1, y - 1) != nullptr &&
                city->getOrganism(x + 1, y - 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x + 1, y - 1), x + 1, y - 1);
                canBreed = true;
                stepsSinceEaten = 0;

            } else if (city->getOrganism(x + 1, y - 1) == nullptr && City::inBounds(x + 1, y - 1)) {
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
            if (city->getOrganism(x + 1, y + 1) != nullptr &&
                city->getOrganism(x + 1, y + 1)->getSpecies() == "Human" && City::inBounds(x - 1, y + 1)) {
                city->setOrganism(new Zombie(*city, x - 1, y + 1), x - 1, y + 1);
                canBreed = true;
                stepsSinceEaten = 0;

            } else if (city->getOrganism(x + 1, y + 1) == nullptr && City::inBounds(x + 1, y + 1)) {
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
            if (city->getOrganism(x - 1, y + 1) != nullptr &&
                city->getOrganism(x - 1, y + 1)->getSpecies() == "Human") {
                city->setOrganism(new Zombie(*city, x - 1, y + 1), x - 1, y + 1);
                canBreed = true;
                stepsSinceEaten = 0;
            } else if (city->getOrganism(x - 1, y + 1) == nullptr && City::inBounds(x - 1, y + 1)) {
                city->setOrganism(this, x - 1, y + 1);
                city->setOrganism(nullptr, x, y);
                x--;
                y++;

            }
            break;
        default:
            break;

    }

    //Sets the zombie to a human after 3 steps
    //TODO: Humans change back to zombies the next turn
    if (stepsSinceEaten == 3) {
        city->setOrganism(new Human(*city, x, y), x, y);
        stepsSinceEaten = 0;
    }

    if (breedCounter > 0) {
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
    }
}

void Zombie::starve() {

}

int Zombie::viableBreedingGrounds() {
    int direction = 0;

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