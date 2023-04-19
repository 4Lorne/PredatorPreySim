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

    //Generate humans on the map
    std::vector<Human> humans;
    humans.reserve(20*20);
    for (int i = 0; i < HUMAN_STARTCOUNT; i++) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        //Checks if the position is already taken
        while (city.getOrganism(x, y) != nullptr && city.getOrganism(x,y)->getSpecies() != "Zombie" &&
               City::inBounds(x, y)){
            x = rand() % GRIDSIZE;
            y = rand() % GRIDSIZE;
        }

        //Adds the human the map after a viable space is located
        Human &human = humans.emplace_back(&city,x,y);
        human.setPosition(&human, x, y);
    }

    //Generate zombies on the map
    vector<Zombie> zombies(ZOMBIE_STARTCOUNT);
    zombies.reserve(20*20);
    for (int i = 0; i < ZOMBIE_STARTCOUNT; i++) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        //Checks if the position is already taken
        while (City::isEmptyAndInBounds(x, y, &city)){
            x = rand() % GRIDSIZE;
            y = rand() % GRIDSIZE;
        }

        //Adds the zombie the map after a viable space is located
        Zombie &zombie = zombies.emplace_back(&city,x,y);
        zombie.setPosition(&zombie, x, y);
    }


    int iterations = 1;
    while (iterations < 1000) {
        //Human behaviour - Move, Breed
        for (auto& human : humans) {
            human.move(); // Movement

            if (human.getBreedingStatus()) { // Breeding
                // Checks the cardinal directions
                int direction = human.viableBreedingGrounds();
                if (direction != 4) {
                    int x = human.getX();
                    int y = human.getY();
                    switch (direction) {
                        case WEST:
                            y -= 1;
                            break;
                        case NORTH:
                            y += 1;
                            break;
                        case EAST:
                            x -= 1;
                            break;
                        case SOUTH:
                            x += 1;
                            break;
                        default:
                            break;
                    }
                    // Create a new human at the breeding location
                    Human &human = humans.emplace_back(&city,x,y);
                    human.setPosition(&human, x, y);
                } else {
                    // Reset the breeding status of the parent if there are no viable locations
                    human.setBreedingStatus(false);
                }
            }
        }
        for (auto& zombie : zombies) {
            //zombie.move(); // Movement

            /*if (human.getBreedingStatus()) { // Breeding
                // Checks the cardinal directions
                int direction = human.viableBreedingGrounds();
                if (direction != 4) {
                    int x = human.getX();
                    int y = human.getY();
                    switch (direction) {
                        case WEST:
                            y -= 1;
                            break;
                        case NORTH:
                            y += 1;
                            break;
                        case EAST:
                            x -= 1;
                            break;
                        case SOUTH:
                            x += 1;
                            break;
                        default:
                            break;
                    }
                    // Create a new human at the breeding location
                    Human &human = humans.emplace_back(city,x,y);
                    human.setPosition(&human, x, y);
                } else {
                    // Reset the breeding status of the parent if there are no viable locations
                    human.setBreedingStatus(false);
                }
            }*/
        }
        /*for (int i = 0; i < ZOMBIE_STARTCOUNT; i++) {
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
                            zombies[i] = Zombie(city, (zombies[i].getX() - 1), (zombies[i].getY() - 1));
                            break;
                        case SOUTHWEST:
                            zombies[i] = Zombie(city, (zombies[i].getX() + 1), (zombies[i].getY() - 1));
                            break;
                        case SOUTHEAST:
                            zombies[i] = Zombie(city, (zombies[i].getX() + 1), (zombies[i].getY() + 1));
                            break;
                        case NORTHEAST:
                            zombies[i] = Zombie(city, (zombies[i].getX() - 1), (zombies[i].getY() + 1));
                            break;
                        default:
                            break;
                    }
                    //Sets the zombie to a human after 3 steps
                    if (zombies[i].getStepsSinceEaten() == 3) {
                        humans[i] = Human(city, zombies[i].getX(),
                                          zombies[i].getY()), zombies[i].getX(), zombies[i].getY();
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
        }*/

        cout << city;
        cout << "Number of iterations: " << iterations << endl;

        Sleep(1000);
        iterations++;

        //If there are no empty spots, the game is over.
        /*int humanCount = 0;
        int zombieCount = 0;
        bool zombieWin = false;
        bool humanWin = false;
        for (int row = 0; row < GRID_WIDTH; row++) {
            for (int col = 0; col < GRID_HEIGHT; col++) {
                if (city.getOrganism(row, col) != nullptr && city.getOrganism(row, col)->getSpecies() == "Human") {
                    humanCount++;
                } else if (city.getOrganism(row, col) != nullptr &&
                           city.getOrganism(row, col)->getSpecies() == "Human") {
                    zombieCount++;
                }
            }
            //19x19 = 361
            if (humanCount == 361) {
                humanWin = true;
            } else if (zombieCount == 361) {
                zombieWin = true;
            }
        }
        if (humanWin) {
            std::cout << "Humans have won!" << std::endl;
            break;
        } else if (zombieWin) {
            cout << "Zombies have won!" << endl;
            break;
        }*/
    }
    delete &city;

}