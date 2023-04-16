//
// Created by Lorne on 2023-04-16.
//

#include <utility>

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

Zombie::~Zombie() = default;
