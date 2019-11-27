#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <unistd.h>
#include <signal.h>
#include "room.h"
#include "game.h"

using namespace std;

//Refer to comments to the room.cpp file for more information

//message that launches when game starts
//asks player if they would like to read the instructions; 
//instructions are activated when player inputs "Y"
void welcome () {
	cout << "Welcome to the Adventure Command Line Game!" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "Would you like to read the instructions? (Y/N)" << endl;
	char inst;
	cin >> inst;
	if (inst == 'Y') {
		sleep(1);
		cout << "---------------------------------------------------------------" << endl;
		cout << "INSTRUCTIONS:" << endl;
		cout << "At the beginning, you are at the lobby of the castle." << endl;
		cout << "When prompted, you can decide which room to enter by typing either:" << endl;
		cout << "\t1. right" << endl;
		cout << "\t2. left" << endl;
		cout << "\t3. up" << endl;
		cout << "\t4. down" << endl;
		cout << "Your end goal is to find the princess and take her out of the castle." << endl;
		cout << "You must do this without encountering the monster, and you can only leave "<< endl;
		cout << "through the lobby." << endl;
		cout << "Both the monster and princess will appear randomly." << endl;
		cout << "To quit the game, simply type Q into the command line." << endl;
		cout << "Good luck." << endl;
	}
	cout << "---------------------------------------------------------------" << endl;
	sleep(1);
	cout << "Lets begin..." << endl;
	sleep(1);
	cout << endl << "The princess is trapped somewhere deep inside the castle." << endl;
	sleep(1);
	cout << "Your job is to find her before the monster finds you..." << endl;
	sleep(1);
	cout << "You must follow the directions from the provided map, or else" << endl;
	sleep(1);
	cout << "bad things will come..." << endl;
	sleep(1);
	cout << "TIP: Type in M to display the map of the castle." << endl;
	sleep(1);
}

//sets room names
void makeRooms() {
	lobby.setName("Lobby");
	hallway.setName("Hallway");
	chapel.setName("Chapel");
	library.setName("Library");
	kitchen.setName("Kitchen");
	guardroom.setName("Guardroom");
	solarium.setName("Solarium");
	bedroom.setName("Bedroom");
	hq.setName("Headquarters");
	office.setName("Ofiice");
	dungeon.setName("Dungeon");
	pantry.setName("Pantry");

}

//links rooms and creates the map
//links are created by setting the address of the room that leads up to the next room in the given direction
void mapRooms() {
	hallway.mapDownto(&lobby);
	lobby.mapUpto(&hallway);
	hallway.mapRightto(&chapel);
	chapel.mapLeftto(&hallway);
	chapel.mapDownto(&guardroom);
	guardroom.mapUpto(&chapel);
	chapel.mapRightto(&solarium);
	solarium.mapLeftto(&chapel);
	hallway.mapUpto(&library);
	library.mapDownto(&hallway);
	library.mapLeftto(&bedroom);
	bedroom.mapRightto(&library);
	library.mapRightto(&hq);
	hq.mapLeftto(&library);
	hq.mapRightto(&office);
	office.mapLeftto(&hq);
	hallway.mapLeftto(&kitchen);
	kitchen.mapRightto(&hallway);
	kitchen.mapDownto(&dungeon);
	dungeon.mapUpto(&kitchen);
	kitchen.mapLeftto(&pantry);
	pantry.mapRightto(&kitchen);

}

//a random integer is generated
//a princess could be in any of the six rooms below
//take the mod of the generated int and use a switch statement to decide where to place the princess
void setPrincess() {
	srand((unsigned)time(NULL));
	int randP = rand() % 6;
	//cout << "randP=" << randP << endl;

	switch(randP) {
		case 0:
			dungeon.hasPrin();
			break;
		case 1:
			hq.hasPrin();
			break;
		case 2:
			office.hasPrin();
			break;
		case 3:
			chapel.hasPrin();
			break;
		case 4:
			solarium.hasPrin();
			break;
		case 5:
			guardroom.hasPrin();
			break;
	}
}

//a random integer is generated
//a monster could be in any of the seven rooms below
//take the mod of the generated int and use a switch statement to decide where to place the monster
void setMonster() {
	srand((unsigned)time(NULL));
	int randM = rand() % 7;
	//cout << "randM=" << randM << endl;

	switch(randM) {
		case 0:
			bedroom.hasMons();
			break;
		case 1:
			dungeon.hasMons();
			break;
		case 2:
			library.hasMons();
			break;
		case 3:
			hq.hasMons();
			break;
		case 4:
			office.hasMons();
			break;
		case 5:
			solarium.hasMons();
			break;
		case 6:
			guardroom.hasMons();
			break;
	}
}

//message that asks players where to go next
//appears after they have been informed of their current location or if they request for a map
void prompt() {
	cout << "Where do you want to go?: ";
}

//prints the game over sequences
//takes two parameters and judges which endgame message to send out based on result
void endGame(int w, int l) {
	if (win) {
		cout << "---------------------------------------------------------------" << endl;
		cout << "(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ Congratulations! You have successfully rescued the princess." << endl;
		cout << "---------------------------------------------------------------" << endl;
	}

	if (lose) {
		cout << "---------------------------------------------------------------" << endl;
		cout << "Oh no! You have ran into the monster. ლ,ᔑ•ﺪ͟͠•ᔐ.ლ" << endl;
		sleep(1);
		cout << "The monster has captured you along with the princess," << endl;
		cout << "and you are forever trapped inside the castle." << endl;
		cout << "---------------------------------------------------------------" << endl;
	}
	sleep(1);
	cout << "GAME OVER" << endl;
	sleep(1);
	cout << "Thank you for playing!" << endl;
}

//what happens after a player tells the command line where they want to go
//checks if the princess is in the room 
//sets flag for defeat or victory
//tells program to keep going if princess and monster aren't present
void processes(Room* p) {
	cout << "You have entered the " << p -> getName() << "." << endl;
	sleep(1);
	found = p -> foundPrin(p);
	if (found) {
		cout << "You have found the princess! Now safely return to the lobby... (◕‿◕✿)" << endl;
	}
	win = p -> checkVictory(p, &lobby, win);
	lose = p -> checkDefeat(p);
	cout << endl;
	if (!win && !lose) {
		sleep(1);
		prompt();
	}
}

//appears when user types "M" in the command prompt
//prints out a map of the castle and a hint
void displayMap() {
	cout << endl;
	cout << "Map of the Castle: " << endl;
	cout << "		  BEDROOM <--left-- LIBRARY --right--> HEADQUARTERS --right--> OFFICE" << endl;
	cout << "                     		       ^ " << endl;
	cout << "                     		       | " << endl;
	cout << "                     		       up " << endl;
	cout << "                     		       | " << endl;
	cout << "PANTRY <--left-- KITCHEN <--left-- HALLWAY --right--> CHAPEL --right--> SOLARIUM " << endl;
	cout << "                     ^		       |		| " << endl;
	cout << "                     |		     down	      down " << endl;
	cout << "                     up		       |	   	| " << endl;
	cout << "                     |		       V	  	V   " << endl;
	cout << " 		  DUNGEON            LOBBY	    GUARDROOM " << endl;
	cout << endl << "---------------------------------------------------------------" << endl;
	cout << "TIP: To go back to the room you were in before," << endl << "\tsimply type in the opposite direction that you came from." << endl;
	cout << "\tFor example, you came from the KITCHEN in the left direction and you are currently in the PANTRY." << endl;
	cout << "\tTo go back to the KITCHEN, just go right." << endl;
	cout << "---------------------------------------------------------------" << endl;
}