#include "critter.h"
#ifndef __RABBIT_H__
#define __RABBIT_H__

class Rabbit : public Critter
{
	public:
		Rabbit();
		Rabbit(World* input_World);
		Rabbit(int x, int y,World* input_World);
		void move();
		void breed();
		bool check_live();
		void setNextRabbit(Rabbit* beNext);
		Rabbit* call_nextRabbit();
		static void reset() {Rabbit_born = 0, Rabbit_starve = 0, Rabbit_captured = 0, Rabbit_fall = 0;}
		static int call_num() {return Rabbit_num;}
		static int call_born() {return Rabbit_born;}
		static int call_starve() {return Rabbit_starve;}
		static int call_captured() {return Rabbit_captured;}
		static int call_fall() {return Rabbit_fall;}
	private:
		static int Rabbit_num, Rabbit_born, Rabbit_starve, Rabbit_captured, Rabbit_fall;
		Rabbit* nextRabbit;
};

#endif
