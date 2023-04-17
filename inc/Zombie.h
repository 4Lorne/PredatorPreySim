//
// Created by Lorne on 2023-04-14.
//

#include "Organism.h"

#ifndef HUMANZOMBIES_ZOMBIE_H
#define HUMANZOMBIES_ZOMBIE_H


class Zombie : public Organism{
private:
    bool canBreed;
    int breedCounter;
public:
    Zombie(); //Default
    explicit Zombie(City& city, int x, int y); //Constructor that assigns the zombie to a city
    ~Zombie() override; //Destructor

    void setSpecies(string species);
    string getSpecies() override;

    void move() override;


    int viableBreedingGrounds();

    bool getBreedingStatus() const;

    bool setBreedingStatus(bool status);

    int getX();

    int getY();
};

#endif //HUMANZOMBIES_ZOMBIE_H
