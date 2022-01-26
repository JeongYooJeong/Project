#include "critter.h"
#ifndef __TIGER_H__
#define __TIGER_H__

class Tiger : public Critter
{
	public:
		Tiger();
		Tiger(World* input_World);
		Tiger(int x, int y, World* input_World);
		void move();
		void breed();
		bool check_live();
		void setNextTiger(Tiger* beNext);
		Tiger* call_nextTiger();
		static void reset() { Tiger_born=0, Tiger_starve=0, Tiger_captured=0,Tiger_fall=0;}
		static int call_num() {return Tiger_num;}
		static int call_born() {return Tiger_born;}
		static int call_starve() {return Tiger_starve;}
		static int call_captured() {return Tiger_captured;}
		static int call_fall() {return Tiger_fall;}
	private:
		static int Tiger_num, Tiger_born, Tiger_starve, Tiger_captured, Tiger_fall;
		Tiger* nextTiger;
};

#endif
