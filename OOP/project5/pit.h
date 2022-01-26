#include "world.h"

#ifndef __PIT_H__
#define __PIT_H__

class Pit
{
	public:
		Pit();
		Pit(int pit_size, World* input_World);
		static int call_num() {return Pit_num;}
	private:
		static int Pit_num;
		World* myWorld;
};
#endif
