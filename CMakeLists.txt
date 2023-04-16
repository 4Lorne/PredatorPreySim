cmake_minimum_required(VERSION 3.25)
project(HumanZombies)

set(CMAKE_CXX_STANDARD 17)

add_executable(HumanZombies main.cpp inc/Organism.h inc/Zombie.h inc/Human.h inc/City.h inc/GameSpecs.h src/City.cpp src/Organism.cpp src/Zombie.cpp)
