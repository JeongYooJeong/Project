#include <ctime>
#include <cstdlib>
#include "world.h"
#include "critter.h"

Critter :: Critter() {}
Critter :: Critter(World* input_World) 
{
	myWorld = input_World;
	int temp_x, temp_y;
	while(1)
	{
		temp_x = rand()%size+2;
		temp_y = rand()%size+2;
		if(myWorld->which_animal(temp_x, temp_y) == '-')
			break;
	}
	xPos = temp_x;
	yPos = temp_y;
	lifeTime=3;
	check_newBorn=true;
}
Critter :: Critter(int x, int y, World* input_World)
{
	myWorld = input_World;
	xPos = x, yPos = y;
}
