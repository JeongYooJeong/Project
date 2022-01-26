#include <iostream>
#include <cstdlib>
#include <ctime>
#include "pit.h"
#include "world.h"

Pit :: Pit() {}
Pit :: Pit(int pit_size, World* input_World) // place pits into the world randomly
{
	myWorld = input_World;
	Pit_num = pit_size;
	int temp_x, temp_y;
	for(int i=0; i < Pit_num; i++)
		while(1)
		{	
			temp_x = rand()%size +2;
			temp_y = rand()%size +2;
			if(myWorld->which_animal(temp_x, temp_y) == '-')
			{
				myWorld->setWorld(temp_x, temp_y, 'O');
				break;
			}
		}
}
