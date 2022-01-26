#include "rabbit.h"
#include "world.h"
#include "tiger.h"
#include "hunter.h"
#include "grass.h"
#include "pit.h"
#ifndef __ACT_H__
#define __ACT_H__

class Act // manage all classes in Act class
{
	public:
		Act();
		Act(World* world);
		void set(int rabbit_size, int tiger_size, int hunter_size,int grass_size,int pit_size); // make an initial world by user's input 
		void process(); // rabbit, tiger,hunter and grass move by process function. 
	private:
		Rabbit* firstRabbit; 
		Tiger* firstTiger;
		Hunter* firstHunter;
		Grass* grass;
		Pit* pit;
		World* myWorld;
};

#endif
