//
// Created by Lorne on 2023-04-14.
//

#include "Organism.h"

#ifndef HUMANZOMBIES_HUMAN_H
#define HUMANZOMBIES_HUMAN_H


class Human : public Organism{
public:
    Human();
    explicit Human(City& city);
    ~Human() override;

    void setSpecies(string species);
    string getSpecies() override;
};

#endif //HUMANZOMBIES_HUMAN_H
