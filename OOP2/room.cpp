#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <unistd.h>
#include "room.h"
#include "game.h"

using namespace std;

//default constructors and deconstructors
//declared as virtual because they are overwritten later by the program via polymorphism
Room::~Room() {};

lRoom::lRoom() {};

lRoom::~lRoom() {};

lrRoom::lrRoom() {};

lrRoom::~lrRoom() {};

lruRoom::lruRoom() {};

lruRoom::~lruRoom() {};

//declared as virtual because they are overwritten later by the program via polymorphism
Room* Room::goUp() {
	return 0;
};

Room* Room::goLeft() {
	return 0;
};

Room* Room::goRight() {
	return 0;
};

//generic function; sets room object name 
void Room::setName(string roomName) {
	name = roomName;
}

//generic function; returns the name of the room when prompted to
string Room::getName() {
	return this -> name;
}

//the following functions return the address of the door that leads to the next room
Room* Room::goDown() {
	return doorFromDown;
}

Room* lRoom::goLeft() {
	return doorFromLeft;
}

Room* lrRoom::goRight() {
	return doorFromRight;
}

Room* lruRoom::goUp() {
	return doorFromUp;
}

//the following functions creates the map by linking the rooms together
//the function takes the address of the room we want to link and places it in a pointer
void Room::mapDownto(Room* p) {
	doorFromDown = p;
}

void lRoom::mapLeftto(Room* p) {
	doorFromLeft = p;
}

void lrRoom::mapRightto(Room* p) {
	doorFromRight = p;
}

void lruRoom::mapUpto(Room* p) {
	doorFromUp = p;
}

//sets the princess and monster in their respective rooms
void Room::hasPrin() {
	princess = 1;
}

void Room::hasMons() {
	monster = 1;
}

//polls each iteration in main to see if player has won or lost the game
//if player has the princess and is at the lobby, then player has won
int Room::checkVictory(Room *p, Room *lobby, int win) {
	if (p == lobby) {
		return 1;
	}

	return 0;
}

//player has encountered the monster in the pointer room
int Room::checkDefeat(Room *p) {
	if (p -> monster) {
		return 1;
	}

	return 0;
}

//player has found the princess in the pointer room
int Room::foundPrin(Room *p) {
	if (p -> princess) {
		return 1;
	}

	return 0;
}

