//
// Created by Lorne on 2023-04-14.
//
#include <iostream>
#include <windows.h>


#include "../inc/City.h"
#include "../inc/Organism.h"

City::City(){ //Fills the city with nullptrs
    for (auto & i : grid) {
        for (auto & j : i) {
            j = nullptr;
        }
    }
}

City::~City() = default;

Organism* City::getOrganism(int x, int y) { //Returns the organism in the city location
    return grid[x][y];
}

void City::setOrganism(Organism* organism, int x, int y) { //Sets the organism in a specific coordinate
    this->grid[x][y] = organism;
}

//Prints the city
ostream &operator<<(ostream &output, City &city) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Does color stuff
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

//Checks the bounds of the walls, minus 1 to account for the wall character
bool City::inBounds(int x, int y) {
    return (x >= 1 && x <= 20 && y >= 1 && y <= 20);
}
bool City::isEmptyAndInBounds(int x, int y, City* city) {
    return city->getOrganism(x, y) == nullptr && City::inBounds(x, y);
}


