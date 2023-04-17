//
// Created by Lorne on 2023-04-14.
//

#ifndef HUMANZOMBIES_GAMESPECS_H
#define HUMANZOMBIES_GAMESPECS_H


const int GRIDSIZE = 20; // size of the square grid
const int HUMAN_STARTCOUNT = 100; // inital Humans
const int ZOMBIE_STARTCOUNT = 20; //initial Zombie count
const int HUMAN_BREED = 3; // steps until an Human breeds
const int ZOMBIE_BREED = 8; // steps until an Zombie breeds
const int ZOMBIE_STARVE = 3; // steps until a Zombie starves and converts back
const char HUMAN_CH = 111;//79 "o"// ascii Human
const char SPACE_CH = 32; // " " ascii space
const char ZOMBIE_CH = 90;//90 "Z"// ascii zombie
const double PAUSE_SECONDS = .09; // pause between steps
const int ITERATIONS = 1000; // max number of steps



#endif //HUMANZOMBIES_GAMESPECS_H
