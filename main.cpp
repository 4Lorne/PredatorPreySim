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
    Human humans[HUMAN_STARTCOUNT];
    Zombie zombies[ZOMBIE_STARTCOUNT];
    //Zombie test = *new Zombie(city);
    //Human test2 = *new Human(city);
    //test.setPosition(&test);
    //test2.setPosition(&test2);


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
    while (iterations < 20) {
        for (int i = 0; i < HUMAN_STARTCOUNT;i++){
            humans[i].move();
        }
        for (int i = 0; i< ZOMBIE_STARTCOUNT;i++){
            zombies[i].move();
        }
        //test2.move();

        cout << city;

        cout << "Number of iterations: " << iterations << endl;
        //TODO: Number of Zombies
        //      Number of Humans

        Sleep(1000);
        iterations++;
    }

    delete &city;
}
