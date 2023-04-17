//
// Created by Lorne on 2023-04-16.
//

#include <utility>

#include "../inc/Zombie.h"

Zombie::Zombie() {

}

Zombie::Zombie(City &city) {
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

Zombie::~Zombie() = default;


void Zombie::move() {
    int z = getRandomNumber();
    // Move the human up if the cell above is empty
    switch(z){
        case 1:
            if (city->getOrganism(x, y - 1) == nullptr && City::inBounds(x, y - 2)) {
                city->setOrganism(this, x, y - 1);
                city->setOrganism(nullptr, x, y);
                y--;
            }
            break;
        case 2:
            if (city->getOrganism(x, y + 1) == nullptr && City::inBounds(x, y + 2)) {
                city->setOrganism(this, x, y + 1);
                city->setOrganism(nullptr, x, y);
                y++;
            }
            break;
        case 3:
            if (city->getOrganism(x - 1, y) == nullptr && City::inBounds(x - 2, y)) {
                city->setOrganism(this, x - 1, y);
                city->setOrganism(nullptr, x, y);
                x--;
            }
            break;
        case 4:
            if (city->getOrganism(x + 1, y) == nullptr && City::inBounds(x + 2, y)) {
                city->setOrganism(this, x + 1, y);
                city->setOrganism(nullptr, x, y);
                x++;
            }
            break;
    }
}
