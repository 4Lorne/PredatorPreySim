#include <iostream>
#include <synchapi.h>
#include "inc/Organism.h"
#include "inc/Zombie.h"
#include "inc/Human.h"

int main() {
    City city = *new City();
    Zombie test = *new Zombie(city);
    Human test2 = *new Human(city);
    test.setPosition(&test);

    test2.setPosition(&test2);


    int iterations = 0;
    while (iterations < 20) {
        test.move();
        test2.move();
        cout << city;
        cout << "Number of iterations: " << iterations << endl;
        //TODO: Number of Zombies
        //      Number of Humans

        Sleep(1000);
        iterations++;
    }
}
