#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <unistd.h>

using namespace std;

class Room {	//a deadend; base room that user can only go up and come down from(e.g. LOBBY)
	Room* doorFromDown;
	string name;

public:
	int princess;
	int monster;
	Room(): monster(0), princess(0) {};
	virtual ~Room();
	Room* goDown();
	virtual Room* goUp();
	virtual Room* goLeft();
	virtual Room* goRight();
	void hasPrin();
	void hasMons();
	void mapDownto(Room* p);
	int checkVictory(Room *p, Room *lobby, int win);
	int checkDefeat(Room *p);
	int foundPrin(Room *p);
	void setName(string roomName);
	string getName();
};

class lRoom: public Room {	//user can only go down, or left.
	Room* doorFromLeft;

public:
	lRoom();
	virtual ~lRoom();
	Room* goLeft();
	void mapLeftto(Room* p);
};

class lrRoom: public lRoom { //user can only go down, right, or left.
	Room* doorFromRight;

public:
	lrRoom();
	virtual ~lrRoom();
	Room* goRight();
	void mapRightto(Room* p);
};

class lruRoom: public lrRoom { //user can only go up, right, or left.
	Room *doorFromUp;

public:
	lruRoom();
	virtual ~lruRoom();
	Room* goUp();
	void mapUpto(Room* p);	
};

