#include <iostream>
#include <synchapi.h>
#include <vector>
#include <random>

#include "inc/Organism.h"
#include "inc/Zombie.h"
#include "inc/Human.h"


//TODO: Humans get stuck on walls

int main() {
    City city;
    Human humans[20 * 20];
    Zombie zombies[ZOMBIE_STARTCOUNT];

    //Generate humans and zombies
    for (int i = 0; i < HUMAN_STARTCOUNT; i++) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        // check if the position is already occupied
        while (city.getOrganism(x, y) != nullptr) {
            x = rand() % GRIDSIZE;
            y = rand() % GRIDSIZE;
        }
        humans[i] = Human(city, x, y);
        humans[i].setPosition(&humans[i], x, y);
    }

    for (int i = 0; i < ZOMBIE_STARTCOUNT; i++) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        // check if the position is already occupied
        while (city.getOrganism(x, y) != nullptr && (city.getOrganism(x, y))->getSpecies() != "Human") {
            x = rand() % GRIDSIZE;
            y = rand() % GRIDSIZE;
        }
        zombies[i] = Zombie(city, x, y);
        zombies[i].setPosition(&zombies[i], x, y);
    }


    int iterations = 1;
    while (iterations < 1000) {
        //Human behaviour - Move, Breed
        for (int i = 0; i < HUMAN_STARTCOUNT; i++) {
            humans[i].move();
            if (humans[i].getBreedingStatus()) {
                // Checks the cardinal directions
                enum {
                    WEST, NORTH, EAST, SOUTH
                };
                int direction = humans[i].viableBreedingGrounds();
                if (direction != 4) {
                    switch (direction) {
                        case WEST:
                            humans[i] = Human(city, (humans[i].getX() + 0), (humans[i].getY() - 1));
                            break;
                        case NORTH:
                            humans[i] = Human(city, (humans[i].getX() + 0), (humans[i].getY() + 1));
                            break;
                        case EAST:
                            humans[i] = Human(city, (humans[i].getX() - 1), (humans[i].getY() + 0));
                            break;
                        case SOUTH:
                            humans[i] = Human(city, (humans[i].getX() + 1), (humans[i].getY() + 0));
                            break;
                    }
                    // Create a new human
                    humans[i] = Human(city, humans[i].getX(), humans[i].getY());
                    humans[i].setPosition(&humans[i], humans[i].getX(), humans[i].getY());
                } else {
                    // Reset the breeding status of the parent if there are no viable locations
                    humans[i].setBreedingStatus(false);
                }
            }
        }

        for (int i = 0; i < ZOMBIE_STARTCOUNT; i++) {
            zombies[i].move();
        }

        cout << city;
        cout << "Number of iterations: " << iterations << endl;

        Sleep(10);
        iterations++;

        bool isEmptySpot = false;
        for (int row = 0; row < GRID_WIDTH; row++) {
            for (int col = 0; col < GRID_HEIGHT; col++) {
                if (city.getOrganism(row, col) == nullptr) {
                    isEmptySpot = true;
                    break;
                }
            }
            if (isEmptySpot) {
                break;
            }
        }
        if (!isEmptySpot) {
            std::cout << "Game Over" << std::endl;
            break;
        }
    }
    delete &city;

}