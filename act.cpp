#include <iostream>
#include "act.h"
#include "rabbit.h"
#include "tiger.h"
#include "hunter.h"
#include "grass.h"
#include "pit.h"
Act :: Act(){ }
Act :: Act(World* world)
{
	myWorld = world;
}
void Act :: set(int rabbit_size, int tiger_size, int hunter_size,int grass_size,int pit_size) // make linkList of critters according to user's input
{
	firstHunter = NULL;
	firstTiger = NULL;
	firstRabbit = NULL;
	for(int i=0; i<hunter_size; i++) 
	{
		Hunter* makeHunter = new Hunter(myWorld);
		makeHunter->setNextHunter(firstHunter);
		firstHunter = makeHunter;
	}
	for(int i=0; i<tiger_size; i++)
	{
		Tiger* makeTiger = new Tiger(myWorld);
		makeTiger->setNextTiger(firstTiger);
		firstTiger = makeTiger;		
	}
	for(int i=0; i<rabbit_size; i++)
	{
		Rabbit* makeRabbit = new Rabbit(myWorld);
		makeRabbit->setNextRabbit(firstRabbit);
		firstRabbit = makeRabbit;
	}
	grass = new Grass(grass_size, myWorld);
	pit = new Pit(pit_size, myWorld);
}
void Act :: process()
{
	Hunter* previous_hunter=NULL;
	Hunter* fix_firstHunter = firstHunter;

	Tiger* previous_tiger=NULL;
	Tiger* fix_firstTiger = firstTiger;
	
	Rabbit* previous_rabbit=NULL;
	Rabbit* fix_firstRabbit = firstRabbit;

	while(firstHunter != NULL)
	{
		if(firstHunter->check_live() == false) //when the current firstHunter is dead
		{
			if(previous_hunter == NULL) //when the first firstHunter is dead
			{
				fix_firstHunter= firstHunter->call_nextHunter();
				delete firstHunter;
				firstHunter= fix_firstHunter;
				continue;
			}
			else
			{
				previous_hunter->setNextHunter( firstHunter->call_nextHunter() );
				delete firstHunter;
				firstHunter = previous_hunter->call_nextHunter();
				continue;
			}
		} 
		firstHunter->move();
		firstHunter->breed();
		previous_hunter = firstHunter;
		firstHunter = firstHunter->call_nextHunter();
	}	
	while(firstTiger != NULL)
	{	
			
		if(firstTiger->check_live() == false) //when the current firstTiger is dead
		{
			if(previous_tiger == NULL) //when the first firstTiger is dead
			{
				fix_firstTiger= firstTiger->call_nextTiger();
				delete firstTiger;
				firstTiger= fix_firstTiger;
				continue;
			}
			else
			{
				previous_tiger->setNextTiger( firstTiger->call_nextTiger() );
				delete firstTiger;
				firstTiger = previous_tiger->call_nextTiger();
				continue;
			}
		}
		firstTiger->move();
		firstTiger->breed();
		previous_tiger = firstTiger;
		firstTiger = firstTiger->call_nextTiger();
	}	
	while(firstRabbit != NULL)
	{
		if(firstRabbit->check_live() == false) // //when the current firstRabbit is dead
		{
			if(previous_rabbit == NULL) // when the first firstRabbit is dead
			{
				fix_firstRabbit= firstRabbit->call_nextRabbit();
				delete firstRabbit;
				firstRabbit= fix_firstRabbit;
				continue;
			}
			else
			{
				previous_rabbit->setNextRabbit( firstRabbit->call_nextRabbit() );
				delete firstRabbit;
				firstRabbit = previous_rabbit->call_nextRabbit();
				continue;
			}
		} 
		firstRabbit->move();
		firstRabbit->breed();
		previous_rabbit = firstRabbit;
		firstRabbit = firstRabbit->call_nextRabbit();
	}	
	grass->put_grass();
	firstHunter = fix_firstHunter;
	firstTiger = fix_firstTiger;
	firstRabbit = fix_firstRabbit;
}

