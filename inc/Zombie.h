//
// Created by Lorne on 2023-04-14.
//

#include "Organism.h"

#ifndef HUMANZOMBIES_ZOMBIE_H
#define HUMANZOMBIES_ZOMBIE_H


class Zombie : public Organism{

public:
    Zombie(); //Default
    Zombie(City& city, int x, int y); //Creation w/ position
    ~Zombie(); //Destructor

    void setSpecies(string species);
    string getSpecies() override;


};

#endif //HUMANZOMBIES_ZOMBIE_H
