//
// Created by Lorne on 2023-04-16.
//

#include "../inc/Human.h"

Human::Human(City &city) {
    this->species = "Human";
    this->city = &city;
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