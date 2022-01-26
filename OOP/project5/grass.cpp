#include <iostream>
#include <cstdlib>
#include <ctime>
#include "grass.h"
#include "world.h"
Grass :: Grass() {}
Grass :: Grass(int grass_size, World* input_World) 	// place grasses into the world randomly
{
	myWorld = input_World;
	int temp_x, temp_y;
	Grass_num = grass_size;
	fix_grassNum = Grass_num;
	for(int i=0; i<Grass_num; i++)
		while(1)
		{
			temp_x = rand()%size +2;
			temp_y = rand()%size +2;
			if(myWorld-> which_animal(temp_x, temp_y) == '-')
			{
				myWorld->setWorld(temp_x, temp_y, '*');
				break;
			}
		}
}
void Grass :: put_grass()		 // make new grasses until the world has the first input grass_size
{
	int grass_num=0;	 // current number of grasses in the World
	int need_grass=0;	  // number of grasses that the world needs
	int new_grass=0;	 // number of newly made grasses
	int empty_num=0;	 // number of empty cells

	for(int i=2; i<size+2; i++)		// check number of grasses and empty cells
		for(int j=2; j<size+2; j++)
		{
			if( myWorld->which_animal(i,j) == '-')	
				empty_num++;
			else if( myWorld->which_animal(i,j) == '*')
				grass_num++;
		}
	need_grass = fix_grassNum - grass_num;
	int temp_x, temp_y;
	while(empty_num && need_grass) 
	{
		temp_x = rand()%size +2;
		temp_y = rand()%size +2;
		if( myWorld->which_animal(temp_x, temp_y) == '-')
		{
			myWorld->setWorld(temp_x,temp_y, '*') ;
			need_grass--, new_grass++, empty_num--;
		}
	}
	Grass_num = grass_num + new_grass;
}
