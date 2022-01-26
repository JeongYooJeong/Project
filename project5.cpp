#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "world.h"
#include "rabbit.h"
#include "tiger.h"
#include "hunter.h"
#include "act.h"
#include "critter.h"

using namespace std;

int Rabbit :: Rabbit_num=0, Rabbit :: Rabbit_born=0, Rabbit :: Rabbit_starve=0, Rabbit :: Rabbit_captured=0, Rabbit :: Rabbit_fall=0;
int Tiger :: Tiger_num=0, Tiger :: Tiger_born=0, Tiger :: Tiger_starve=0, Tiger :: Tiger_captured=0, Tiger :: Tiger_fall=0;
int Hunter :: Hunter_num=0, Hunter :: Hunter_born=0, Hunter :: Hunter_starve=0, Hunter:: Hunter_captured=0, Hunter :: Hunter_fall=0;
int Grass :: Grass_num =0;
int Pit :: Pit_num=0;
int main()
{
	srand((unsigned int)time(NULL));
	int rabbit_size, tiger_size, hunter_size, grass_size, pit_size;
	int time_step=0;
	

	cout << "Enter initial number of rabbits : ";
	cin >> rabbit_size;
	cout << "Enter initial number of tigers : ";
	cin >> tiger_size;
	cout << "Enter initial number of hunters : ";
	cin >> hunter_size;
	cout << "Enter initial number of grasses : ";
	cin >> grass_size;
	cout << "Enter initial number of pits : ";
	cin >> pit_size;
	getchar();

	World* myWorld = new World();
	Act* myAct = new Act(myWorld);
	myAct->set(rabbit_size, tiger_size, hunter_size,grass_size, pit_size);

	system("clear");
	while(1)
	{
		myAct->process();
		cout << "Time_step: "<< time_step++<<endl;
		myWorld->Display();
		getchar();		
		system("clear");
		
	}	
	return 0;
}
