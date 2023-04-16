#include <iostream>
#include "inc/Organism.h"
#include "inc/Zombie.h"

int main() {
    City city = *new City();
    Zombie test = *new Zombie(city,5,5);
    test.setPosition(test,5,5);
    cout << city;
}
