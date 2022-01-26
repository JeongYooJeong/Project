#include "world.h"
#ifndef __GRASS_H__
#define __GRASS_H__

class Grass
{
	public:
		Grass();
		Grass(int grass_size, World* input_World);
		void put_grass();
		static int call_num () {return Grass_num;}
	private:
		static int Grass_num;
		World* myWorld;
		int fix_grassNum;
};

#endif 
