#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <unistd.h>
#include "room.h"
#include "game.h"

using namespace std;

//Room::Room(): monster(0), princess(0) {};

Room::~Room() {};

lRoom::lRoom() {};

lRoom::~lRoom() {};

lrRoom::lrRoom() {};

lrRoom::~lrRoom() {};

lruRoom::lruRoom() {};

lruRoom::~lruRoom() {};

Room* Room::goUp() {
	return 0;
};

Room* Room::goLeft() {
	return 0;
};

Room* Room::goRight() {
	return 0;
};

void Room::setName(string roomName) {
	name = roomName;
}

string Room::getName() {
	return this -> name;
}

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

void Room::hasPrin() {
	princess = 1;
}

void Room::hasMons() {
	monster = 1;
}

int Room::checkVictory(Room *p, Room *lobby, int win) {
	if (p == lobby) {
		return 1;
	}

	return 0;
}

int Room::checkDefeat(Room *p) {
	if (p -> monster) {
		return 1;
	}

	return 0;
}

int Room::foundPrin(Room *p) {
	if (p -> princess) {
		return 1;
	}

	return 0;
}

