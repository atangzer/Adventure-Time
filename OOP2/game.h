#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <signal.h>
#include <unistd.h>

using namespace std;

extern lruRoom chapel, lobby, hallway, guardroom, kitchen, dungeon;
extern lRoom solarium;
extern lrRoom library, bedroom, hq, office, pantry;
extern int win, lose, found;

void welcome();

void makeRooms();

void mapRooms();

void setPrincess();

void setMonster();

void processes(Room* p);

void prompt();

void endGame(int w, int l);

void displayMap();