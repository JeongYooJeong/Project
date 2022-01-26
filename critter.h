#include "world.h"
#ifndef __CRITTER_H__
#define __CRITTER_H__

class Critter
{
	public: 
		Critter();
		Critter(World* input_World);
		Critter(int x, int y, World* input_World);
		virtual void move()=0;
		virtual void breed()=0;
		virtual bool check_live()=0;
	protected:
		int xPos;
		int yPos;
		int lifeTime;
		int breedTime;
		bool check_newBorn;
		World* myWorld;
	private:
};

#endif
