#include "room.h"
#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <signal.h>

using namespace std;

void segfault_sigaction(int sig, siginfo_t *si, void *arg);

lruRoom chapel, lobby, hallway, guardroom, kitchen, dungeon;
lRoom solarium;
lrRoom library, bedroom, hq, office, pantry;
int win = 0, lose = 0, found = 0;

int main() {

	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;

	welcome();
	makeRooms();
	mapRooms();
	setPrincess();
	setMonster();

	string cmd;
	Room* p;
	p = &lobby;

	sigaction(SIGSEGV, &sa, NULL);

	cout << endl << "You have entered: " << lobby.getName() << endl;
	sleep(1);
	cout << "Proceed to go up: ";

	while (!lose && !win) {
		cin >> cmd;

		if (cmd == "Q") {
			cout << "---------------------------------------------------------------" << endl;
			break;
		}
		else if (cmd == "M") {
			displayMap();
			sleep(1);
			prompt();
		}
		else if (cmd == "up") {
			p = p -> goUp();
			processes(p);
		}
		else if (cmd == "down") {
			p = p -> goDown();
			processes(p);
		}
		else if (cmd == "right") {
			p = p -> goRight();
			processes(p);
		}
		else if (cmd == "left") {
			p = p -> goLeft();
			processes(p);
		}
		else {
			cout << "There exists no path in which you can go through your given direction..." << endl;
			sleep(1);
			prompt();
		}
	}

	endGame(win, lose);
	return 0;
}

void segfault_sigaction(int sig, siginfo_t *si, void *arg) {
	cout << "black hole." << endl;
	cout << "There is no way out and you are trapped in there forever." << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "GAME OVER" << endl;
	exit(0);
}