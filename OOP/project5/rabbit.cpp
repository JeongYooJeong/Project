#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rabbit.h"
#include "world.h"
using namespace std;
Rabbit :: Rabbit() {}
Rabbit :: Rabbit(World* input_World) : Critter(input_World)
{
	breedTime = 3;	
	Rabbit_num++;
	Rabbit_born++;
	myWorld->setWorld(xPos, yPos, 'R');
}
Rabbit :: Rabbit (int x, int y,World* input_World) : Critter(x,y,input_World)
{
	Rabbit_num++;
	Rabbit_born++;
	if(myWorld->which_animal(xPos, yPos) == 'O')
	{
		Rabbit_fall++, Rabbit_num--;
	}
	else
	{
		myWorld->setWorld(xPos, yPos, 'R');
		lifeTime = 3;
		breedTime = 3;		
		check_newBorn = true;
	}
}
void Rabbit :: move()
{

	int direction; // 0 is north, 1 is east, 2 is south, 3 is west 
	if(lifeTime == 0)
		return;
	if(check_newBorn)
	{
		check_newBorn = false;
		return;
	}
	if( myWorld->which_animal(xPos+1,yPos) != '*' && myWorld->which_animal(xPos-1, yPos) != '*' && myWorld->which_animal(xPos, yPos+1) != '*' && myWorld->which_animal(xPos, yPos-1) != '*')
	{
		direction = rand()%4;
		if(direction == 0 &&  myWorld->which_animal(xPos-1,yPos) == '-' )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos--;
			myWorld->setWorld(xPos,yPos, 'R');
		}
		else if(direction == 0 && myWorld->which_animal(xPos-1,yPos) == 'O' )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos--;	
			Rabbit_fall++, Rabbit_num--;
			return;
		}
		else if(direction == 1 && myWorld->which_animal(xPos,yPos+1) == '-' )
		{
			myWorld-> setWorld(xPos, yPos, '-');
			yPos++;
			myWorld-> setWorld(xPos, yPos, 'R');
		}
		else if(direction == 1 && myWorld->which_animal(xPos,yPos+1) == 'O' )
		{
			myWorld-> setWorld(xPos, yPos, '-');
			yPos++;
			Rabbit_fall++, Rabbit_num--;
			return;
		}
		else if(direction == 2 && myWorld->which_animal(xPos+1,yPos) == '-'  )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos++;
			myWorld->setWorld(xPos, yPos, 'R');
		}
		else if(direction == 2 &&  myWorld->which_animal(xPos+1,yPos) == 'O' )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos++;
			Rabbit_fall++, Rabbit_num--;
			return;
		}
		else if(direction == 3 && myWorld->which_animal(xPos,yPos-1) == '-'  )
		{
			myWorld->setWorld(xPos, yPos, '-');
			yPos--;
			myWorld->setWorld(xPos, yPos, 'R');
		}
		else if(direction == 3 && myWorld->which_animal(xPos,yPos-1) == 'O')
		{
			myWorld->setWorld(xPos, yPos, '-');
			yPos--;
			Rabbit_fall++, Rabbit_num--;
			return;
		}
	}
	else
		while(1)
		{
			direction = rand()%4;
			if(direction == 0 && myWorld->which_animal(xPos-1, yPos) == '*')
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos--;
				myWorld->setWorld(xPos, yPos, 'R');
				lifeTime=3, breedTime--;
				return;
			}
			else if(direction == 1 && myWorld->which_animal(xPos,yPos+1) == '*')
			{
				myWorld-> setWorld(xPos, yPos, '-');
				yPos++;
				myWorld->setWorld(xPos, yPos, 'R');
				lifeTime=3, breedTime--;
				return;
			}
			else if(direction == 2 && myWorld->which_animal(xPos+1,yPos) == '*')
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos++;
				myWorld->setWorld(xPos, yPos, 'R');
				lifeTime=3, breedTime--;
				return;
			}
			else if(direction == 3 && myWorld -> which_animal(xPos,yPos-1) == '*')
			{
				myWorld->setWorld(xPos, yPos, '-');
				yPos--;
				myWorld->setWorld(xPos, yPos, 'R');
				lifeTime=3, breedTime--;
				return;
			}
		}	
	lifeTime--;
	breedTime--;
	if(lifeTime ==0)
	{
		myWorld->setWorld(xPos, yPos, '-');
		Rabbit_starve++, Rabbit_num--;
	}
}
void Rabbit :: breed()
{	
	if(breedTime > 0 || lifeTime==0)
		return;

	if( (myWorld->which_animal(xPos-1, yPos) != '-') && (myWorld->which_animal(xPos-1, yPos) != '*') && (myWorld->which_animal(xPos-1, yPos) != 'O') && (myWorld->which_animal(xPos+1, yPos) != '-') && (myWorld->which_animal(xPos+1, yPos) != '*') && (myWorld->which_animal(xPos+1, yPos) != 'O') && (myWorld->which_animal(xPos, yPos+1) != '-') && (myWorld->which_animal(xPos, yPos+1) != '*') && (myWorld->which_animal(xPos, yPos+1) != 'O') && (myWorld->which_animal(xPos, yPos-1) != '-') && (myWorld->which_animal(xPos, yPos-1) != '*') && (myWorld->which_animal(xPos, yPos-1) != 'O') )
	{
		breedTime=3;
		return;
	}
	Rabbit* newRabbit;
	int direction;
	while(1)
	{
		direction = rand()%4;
		if(direction ==0 && ( myWorld->which_animal(xPos-1, yPos) == '-' || myWorld->which_animal(xPos-1, yPos) == '*' || myWorld->which_animal(xPos-1, yPos) == 'O') )
		{
			newRabbit = new Rabbit(xPos-1, yPos, myWorld);	
			newRabbit->setNextRabbit(nextRabbit);
			setNextRabbit(newRabbit);
			break;
		}	
		else if(direction ==1 && ( myWorld->which_animal(xPos, yPos+1) == '-' || myWorld->which_animal(xPos, yPos+1) == '*' || myWorld->which_animal(xPos, yPos+1) == 'O') )
		{
			newRabbit = new Rabbit(xPos, yPos+1, myWorld);	
			newRabbit->setNextRabbit(nextRabbit);
			setNextRabbit(newRabbit);
			break;
		}
		else if(direction ==2 && ( myWorld->which_animal(xPos+1, yPos) == '-' || myWorld->which_animal(xPos+1, yPos) == '*' || myWorld->which_animal(xPos+1, yPos) == 'O') )
		{
			newRabbit = new Rabbit(xPos+1, yPos, myWorld);	
			newRabbit->setNextRabbit(nextRabbit);
			setNextRabbit(newRabbit);
			break;
		}
		else if(direction ==3 && ( myWorld->which_animal(xPos, yPos-1) == '-' || myWorld->which_animal(xPos, yPos-1) == '*' || myWorld->which_animal(xPos, yPos-1) == 'O') )
		{
			newRabbit = new Rabbit(xPos, yPos-1, myWorld);	
			newRabbit->setNextRabbit(nextRabbit);
			setNextRabbit(newRabbit);
			break;
		}
	}
			
	breedTime=3;
}
void Rabbit  :: setNextRabbit(Rabbit* beNext)
{
	nextRabbit = beNext;
}
Rabbit* Rabbit :: call_nextRabbit()
{
	return nextRabbit;
}
bool Rabbit :: check_live()
{
	if(myWorld->which_animal(xPos, yPos) == 'R')
		return true;	
	if(lifeTime ==0 || myWorld->which_animal(xPos, yPos) == 'O')
		return false;	
	if(myWorld-> which_animal(xPos, yPos) == 'T' || myWorld->which_animal(xPos, yPos) == 'H')
	{
		Rabbit_captured++, Rabbit_num--;
		return false;
	}
	else
		return false;
}
