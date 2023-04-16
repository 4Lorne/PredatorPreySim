#include <iostream>
#include <synchapi.h>
#include <windows.h>
#include "inc/Organism.h"
#include "inc/Zombie.h"
#include "inc/Human.h"

int main() {
    City city = *new City();
    Zombie test = *new Zombie(city);
    Human test2 = *new Human(city);
    for (int i = 0; i < ZOMBIE_STARTCOUNT; i++){
        test.setPosition(test);
    }
    for (int i = 0; i < HUMAN_STARTCOUNT; i++){
        test2.setPosition(test2);
    }

    int iterations = 0;
    while (iterations < 100) {
        system("cls");
        cout << city;
        cout << "Number of iterations: " << iterations << endl;
        //TODO: Number of Zombies
        //      Number of Humans

        Sleep(1000);
        iterations++;
    }
}
