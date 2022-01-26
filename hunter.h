#include "critter.h"
#ifndef __HUNTER_H__
#define __HUNTER_H__

class Hunter : public Critter
{
	public:
		Hunter();
		Hunter(World* input_World);
		Hunter(int x, int y, World* input_World);
		void move();
		void breed();
		bool check_live();
		void setNextHunter(Hunter* beNext);
		Hunter* call_nextHunter();
		static void reset() { Hunter_born=0, Hunter_starve=0, Hunter_captured=0, Hunter_fall=0; }
		static int call_num() {return Hunter_num;}
		static int call_born() {return Hunter_born;}
		static int call_starve() {return Hunter_starve;}
		static int call_captured() {return Hunter_captured;}
		static int call_fall() {return Hunter_fall;}
	private:
		static int Hunter_num, Hunter_born, Hunter_starve, Hunter_captured, Hunter_fall;
		Hunter* nextHunter;
};

#endif
