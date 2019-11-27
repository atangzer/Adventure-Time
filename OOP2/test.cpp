#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class room
{
public:
	room(): princess(0), monster(0){};
	virtual ~room(){};
	virtual room* go_down();
	virtual room* go_left(){};
	virtual room* go_right(){};
	virtual room* go_up(){};
	virtual void showinfo();
	virtual void set_princess();
	virtual void set_monster();
	virtual void set_downexit(room* p);
	virtual int iswin(room* p, room *lobby, int found, int win);
	virtual int islose(room*p, int lose);
	virtual int isfound(room* p, int found);
	int princess;
	int monster;
private:
	room* downexit;	
};

class room_A: public room
{
public:
	room_A(){};
	virtual ~room_A(){};
	virtual room* go_left();
    virtual void showinfo();
    virtual void set_leftexit(room* p);
private:
	room* leftexit;
};

class room_B: public room_A
{
public:
	room_B(){};
	virtual ~room_B(){};
	virtual room* go_right();
	virtual void showinfo();
	virtual void set_rightexit(room* p);
private:
	room* rightexit;
};

class room_lobby: public room_B
{
public:
	room_lobby(){};
	virtual ~room_lobby(){};
	virtual room* go_up();
	virtual void showinfo();
	virtual void set_upexit(room* p);
private:
	room* upexit;
};

void room::set_princess(){
	princess = 1;
}

void room::set_monster(){
	monster = 1;
}

void room::set_downexit(room* p){
	downexit = p;
}

void room_A::set_leftexit(room* p){
	leftexit = p;
}

void room_B::set_rightexit(room* p){
	rightexit = p;
}

void room_lobby::set_upexit(room* p){
	upexit = p;
}

int room::iswin(room* p, room *lobby, int found, int win){
	if((p == lobby)&&(found == 1))
		win = 1;
	return win;
}

int room::islose(room*p, int lose){
	if(p -> monster == 1)
		lose = 1;
	return lose; 
}

int room::isfound(room* p, int found){
	if(p -> princess == 1)
		found = 1;
	return found;
}

room* room::go_down(){
	return downexit;
}

room* room_A::go_left(){
	return leftexit;
}

room* room_B::go_right(){
	return rightexit;
}

room* room_lobby::go_up(){
	return upexit;
}

void room::showinfo(){
	cout << "You've entered a dead end. There's only one exit: down" << endl << "Enter your command: " << endl;
}

void room_A::showinfo(){
	cout << "Welcome to room A. There are two exits as: left and down" << endl << "Enter your command: " << endl;
}

void room_B::showinfo(){
	cout << "Welcome to room B. There are three exits as: left, right and down" << endl << "Enter your command: " << endl;
}

void room_lobby::showinfo(){
	cout << "Welcome to lobby. There are three exits as: left, up and right" << endl << "Enter your command: " << endl;
}

void showinfo(room *p){
	p -> showinfo();
}

int main(){
	room C, D, E, F;
	room_A A;
	room_B B;
	room_lobby lobby;
	room* p;
	std::string cmd;
	int found = 0, win = 0, lose = 0;
	A.set_leftexit(&D);
	A.set_downexit(&lobby);
	B.set_leftexit(&E);
	B.set_downexit(&lobby);
	B.set_rightexit(&F);
	C.set_downexit(&lobby);
	D.set_downexit(&A);
	E.set_downexit(&B);
	F.set_downexit(&B);
	lobby.set_leftexit(&A);
	lobby.set_rightexit(&B);
	lobby.set_upexit(&C);
	srand((unsigned)time(NULL));
	int prin_no = rand() % 6;
	int mon_no = rand() % 6;
	switch(prin_no){
		case 0:
			A.set_princess();
			break;
		case 1:
			B.set_princess();
			break;
		case 2:
			C.set_princess();
			break;
		case 3:
			D.set_princess();
			break;
		case 4:
			E.set_princess();
			break;
		case 5:
			F.set_princess();
			break;
		}
	switch(mon_no){
		case 0:
			A.set_monster();
			break;
		case 1:
			B.set_monster();
			break;
		case 2:
			C.set_monster();
			break;
		case 3:
			D.set_monster();
			break;
		case 4:
			E.set_monster();
			break;
		case 5:
			F.set_monster();
			break;
		}
	p = &lobby;
	showinfo(p);
	while((!win)&&(!lose)){
	cin >>  cmd;
	if(cmd == "left"){
		p = p -> go_left();
		found = p -> isfound(p, found);
		if(found)
			cout << "You've found the princess. Now leave the castle with her. " << endl;
		win = p -> iswin(p, &lobby, found, win);
		lose = p -> islose(p, lose);
		if((!win)&&(!lose))
			showinfo(p);
	}
	else if(cmd == "right"){
		p = p -> go_right();
		found = p -> isfound(p, found);
		if(found)
			cout << "You've found the princess. Now leave the castle with her. " << endl;
		win = p -> iswin(p, &lobby, found, win);
		lose = p -> islose(p, lose);
		if((!win)&&(!lose))
			showinfo(p);
	}
	else if(cmd == "up"){
		p = p -> go_up();
		found = p -> isfound(p, found);
		if(found)
			cout << "You've found the princess. Now leave the castle with her. " << endl;
		win = p -> iswin(p, &lobby, found, win);
		lose = p -> islose(p, lose);
		if((!win)&&(!lose))
			showinfo(p);
	}
	else if(cmd == "down"){
		p = p -> go_down();
		found = p -> isfound(p, found);
		if(found)
			cout << "You've found the princess. Now leave the castle with her. " << endl;
		win = p -> iswin(p, &lobby, found, win);
		lose = p -> islose(p, lose);
		if((!win)&&(!lose))
			showinfo(p);
	}
}

	if(win)
		cout << "You've succeeded in resucing the princess!" << endl;
	if(lose)
		cout << "There's a monster in the room and you're killed by the monster. Game over~ " << endl;
	return 0;	
}
