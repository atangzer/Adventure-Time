#include "room.h"
#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <signal.h>

using namespace std;

//function that overthrows seg faults
void segfault_sigaction(int sig, siginfo_t *si, void *arg);

//declared rooms in the castle
//total of 3 types; lruRoom, lRoom and lrRoom
lruRoom chapel, lobby, hallway, guardroom, kitchen, dungeon;
lRoom solarium;
lrRoom library, bedroom, hq, office, pantry;

//flag variables to track if player has won or lost the game, or if princess is found
int win = 0, lose = 0, found = 0;

int main() {

	//parameters for overthrowing segfault
	//only linux compatible
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;

	//room initialization
	welcome();
	makeRooms();
	mapRooms();
	setPrincess();
	setMonster();

	string cmd;
	Room* p;
	p = &lobby;	//initialization; start at lobby
	/*cmd = takes in the commands from user; directions, show map or quit game
	p = points to room in given direction
	*/

	sigaction(SIGSEGV, &sa, NULL);

	cout << endl << "You have entered: " << lobby.getName() << endl;
	sleep(1);
	cout << "Proceed to go up: ";

	//loop will iterate as long as player is still in game
	while (!lose && !win) {
		cin >> cmd;

		if (cmd == "Q") { //user has chosen to quit game, exit loop
			cout << "---------------------------------------------------------------" << endl;
			break;
		}
		else if (cmd == "M") { //user has requested the map
			displayMap();
			sleep(1);
			prompt();	//after map provided, prompt user to enter a direction
		}
		else if (cmd == "up") { 
			p = p -> goUp(); //pointer points to the room upstairs
			processes(p);
		}
		else if (cmd == "down") { 
			p = p -> goDown(); //pointer points to the room downstairs
			processes(p);
		}
		else if (cmd == "right") { 
			p = p -> goRight(); //pointer points to the room on the right
			processes(p);
		}
		else if (cmd == "left") { 
			p = p -> goLeft(); //pointer points to the room on the left
			processes(p);
		}
		else { //user has made a typo or has given invalid input
			cout << "There exists no path in which you can go through your given direction..." << endl;
			sleep(1);
			prompt(); //user gets a chance to re-enter their direction 
		}
	}

	endGame(win, lose); //end the game here
	return 0;
}

//a seg fault occurs when the player tries to go to a room in a direction that does not exist on the map
//in this scenario, we overthrow this and trap them
void segfault_sigaction(int sig, siginfo_t *si, void *arg) {
	cout << "black hole." << endl;
	cout << "There is no way out and you are trapped in there forever." << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "GAME OVER" << endl;
	exit(0);
}