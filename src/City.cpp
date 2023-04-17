//
// Created by Lorne on 2023-04-14.
//
#include <iostream>
#include <windows.h>


#include "../inc/City.h"
#include "../inc/Organism.h"

City::City(){
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = nullptr;
        }
    }
}

City::~City() = default;

Organism* City::getOrganism(int x, int y) {
    return grid[x][y];
}

void City::setOrganism(Organism* organism, int x, int y) {
    this->grid[x][y] = organism;
}

//Prints the city
ostream &operator<<(ostream &output, City &city) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console
    for (int i = 0; i < GRID_HEIGHT; i++){
        for (int j = 0; j < GRID_WIDTH; j++){
            if (i == 0 || i == GRID_HEIGHT - 1) {
                output << "- ";
            } else if(j == 0 || j == GRID_WIDTH - 1){
                output << "| ";
            } else if (city.grid[i][j] != nullptr){ //If not a null pointer, checks for human or zombie.
                if ((city.grid[i][j])->getSpecies() == std::string("Zombie")){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    output << "Z ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
                } else if ((city.grid[i][j])->getSpecies() == std::string("Human")){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                    output << "H ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
                }
            } else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                output << city.grid[i][j] << " ";
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
            }
        }
        output << endl;
    }
    return output;
}

bool City::inBounds(int x, int y) {
    return (x >= 0 && x < GRIDSIZE && y >= 0 && y < GRIDSIZE);
}


