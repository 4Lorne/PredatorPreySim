#include <iostream>
#include <synchapi.h>
#include <vector>

#include "inc/Organism.h"
#include "inc/Zombie.h"
#include "inc/Human.h"

int main() {
    enum {
        WEST, NORTH, EAST, SOUTH, NORTHWEST, SOUTHWEST, SOUTHEAST, NORTHEAST
    };
    City city;
    Human humans[20 * 20];
    Zombie zombies[20 * 20];

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
            humans[i].move(); //Movement
            if (humans[i].getBreedingStatus()) { //Breeding
                // Checks the cardinal directions
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
                        default:
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
            zombies[i].move(); //Movement
            if (zombies[i].getBreedingStatus()) { //Breeding
                // Checks the cardinal directions
                //      Add move counter to main
                int direction = zombies[i].viableBreedingGrounds();
                if (direction != 8) {
                    switch (direction) {
                        case WEST:
                            zombies[i] = Zombie(city, (zombies[i].getX() + 0), (zombies[i].getY() - 1));
                            break;
                        case NORTH:
                            zombies[i] = Zombie(city, (zombies[i].getX() + 0), (zombies[i].getY() + 1));
                            break;
                        case EAST:
                            zombies[i] = Zombie(city, (zombies[i].getX() - 1), (zombies[i].getY() + 0));
                            break;
                        case SOUTH:
                            zombies[i] = Zombie(city, (zombies[i].getX() + 1), (zombies[i].getY() + 0));
                            break;
                        case NORTHWEST:
                            zombies[i] = Zombie(city,(zombies[i].getX() - 1), (zombies[i].getY() - 1));
                            break;
                        case SOUTHWEST:
                            zombies[i] = Zombie(city,(zombies[i].getX() + 1), (zombies[i].getY() - 1));
                            break;
                        case SOUTHEAST:
                            zombies[i] = Zombie(city,(zombies[i].getX() + 1), (zombies[i].getY() + 1));
                            break;
                        case NORTHEAST:
                            zombies[i] = Zombie(city,(zombies[i].getX() - 1), (zombies[i].getY() + 1));
                            break;
                        default:
                            break;
                    }
                    //Sets the zombie to a human after 3 steps
                    if (zombies[i].getStepsSinceEaten() == 3) {
                        humans[i] = Human(city, zombies[i].getX(), zombies[i].getY()), zombies[i].getX(), zombies[i].getY();
                        humans[i].setPosition(&humans[i], humans[i].getX(), humans[i].getY());
                        zombies[i].setStepsSinceEaten(0);
                    }
                    // Create a new Zombie
                    zombies[i] = Zombie(city, zombies[i].getX(), zombies[i].getY());
                    zombies[i].setPosition(&zombies[i], zombies[i].getX(), zombies[i].getY());
                } else {
                    // Keep the breeding status if they have been fed and there are no viable humans
                    zombies[i].setBreedingStatus(true);
                }
            }
        }

        cout << city;
        cout << "Number of iterations: " << iterations << endl;

        Sleep(10);
        iterations++;

        //If there are no empty spots, the game is over.
        int humanCount = 0;
        int zombieCount = 0;
        bool zombieWin = false;
        bool humanWin = false;
        for (int row = 0; row < GRID_WIDTH; row++) {
            for (int col = 0; col < GRID_HEIGHT; col++) {
                if (city.getOrganism(row, col) != nullptr && city.getOrganism(row,col)->getSpecies() == "Human") {
                    humanCount++;
                } else if (city.getOrganism(row, col) != nullptr && city.getOrganism(row,col)->getSpecies() == "Human"){
                    zombieCount++;
                }
            }
            //19x19 = 361
            if (humanCount == 361) {
                humanWin = true;
            } else if (zombieCount == 361){
                zombieWin = true;
            }
        }
        if (humanWin) {
            std::cout << "Humans have won!" << std::endl;
            break;
        } else if (zombieWin){
            cout << "Zombies have won!" << endl;
            break;
        }
    }
    delete &city;

}