//
// Created by Lorne on 2023-04-14.
//

#include "Organism.h"

#ifndef HUMANZOMBIES_HUMAN_H
#define HUMANZOMBIES_HUMAN_H


class Human : public Organism{
private:
    bool canBreed;
    int breedCounter;
public:
    Human();
     Human(City& city);
    ~Human() override;

    void setSpecies(string species);
    string getSpecies() override;
    int viableBreedingGrounds();

    void move() override;

    bool getBreedingStatus() const;

    int getX();

    int getY();
};

#endif //HUMANZOMBIES_HUMAN_H
