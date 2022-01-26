#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tiger.h"
#include "world.h"

Tiger :: Tiger() {}
Tiger :: Tiger(World* input_World) : Critter(input_World)
{
	breedTime=4;
	Tiger_num++, Tiger_born++;
	myWorld->setWorld(xPos, yPos, 'T');
}
Tiger :: Tiger(int x, int y, World* input_World) : Critter(x,y,input_World)
{
	Tiger_num++;
	Tiger_born++;
	if(myWorld->which_animal(xPos, yPos) == 'O')
	{
		Tiger_fall++, Tiger_num--;
	}
	else
	{
		myWorld->setWorld(xPos, yPos, 'T');
		lifeTime=3, breedTime=4;
		check_newBorn = true;
	}
}
void Tiger :: move()
{
	int direction;
	if(lifeTime == 0)
		return;
	if(check_newBorn)
	{
		check_newBorn = false;
		return;
	}

	if(myWorld->which_animal(xPos+1, yPos) != 'R' && myWorld->which_animal(xPos-1,yPos) != 'R' && myWorld->which_animal(xPos, yPos+1) != 'R' && myWorld->which_animal(xPos, yPos-1) != 'R')
	{
		direction = rand()%4;

		if( direction ==0 && (myWorld->which_animal(xPos-1, yPos)=='-' || myWorld->which_animal(xPos-1, yPos) =='*') )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos--;
			myWorld->setWorld(xPos, yPos, 'T');
		}
		else if( direction ==0 && myWorld->which_animal(xPos-1, yPos)=='O' )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos--;
			Tiger_fall++, Tiger_num--;
			return;
		}
		else if( direction ==1 && (myWorld->which_animal(xPos, yPos+1)=='-' || myWorld->which_animal(xPos, yPos+1) =='*') )
		{
			myWorld->setWorld(xPos, yPos, '-');
			yPos++;
			myWorld->setWorld(xPos, yPos, 'T');
		}
		else if( direction ==1 && myWorld->which_animal(xPos, yPos+1)=='O' )
		{
			myWorld->setWorld(xPos, yPos, '-');
			yPos++;
			Tiger_fall++, Tiger_num--;
			return;
		}
		else if( direction ==2 && (myWorld->which_animal(xPos+1, yPos)=='-' || myWorld->which_animal(xPos+1, yPos) =='*') )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos++;
			myWorld->setWorld(xPos, yPos, 'T');
		}
		else if( direction ==2 && myWorld->which_animal(xPos+1, yPos)=='O' )
		{
			myWorld->setWorld(xPos, yPos, '-');
			xPos++;
			Tiger_fall++, Tiger_num--;
			return;
		}
		else if( direction  ==3 && (myWorld->which_animal(xPos, yPos-1)=='-' || myWorld->which_animal(xPos, yPos-1) =='*') )
		{
			myWorld->setWorld(xPos, yPos, '-');
			yPos--;
			myWorld->setWorld(xPos, yPos, 'T');
		}
		else if( direction  ==3 && myWorld->which_animal(xPos, yPos-1)=='O' )
		{
			myWorld->setWorld(xPos, yPos, '-');
			yPos--;
			Tiger_fall++, Tiger_num--;
			return;
		}
	}
	else
		while(1)
		{
			direction = rand()%size;
			if(direction == 0 && myWorld->which_animal(xPos-1, yPos) == 'R')
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos--;
				myWorld->setWorld(xPos,yPos, 'T');
				lifeTime=3, breedTime--;
				return;
			}	
			else if(direction == 1 && myWorld->which_animal(xPos, yPos+1) == 'R')
			{
				myWorld->setWorld(xPos, yPos, '-');
				yPos++;
				myWorld->setWorld(xPos,yPos, 'T');
				lifeTime=3, breedTime--;
				return;
			}
			else if(direction == 2 && myWorld->which_animal(xPos+1, yPos) == 'R')
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos++;
				myWorld->setWorld(xPos,yPos, 'T');
				lifeTime=3, breedTime--;
				return;
			}
			else if(direction == 3 && myWorld->which_animal(xPos, yPos-1) == 'R')
			{
				myWorld->setWorld(xPos, yPos, '-');
				yPos--;
				myWorld->setWorld(xPos,yPos, 'T');
				lifeTime=3, breedTime--;
				return;
			}
		}
	lifeTime--, breedTime--;
	if(lifeTime == 0)
	{
		myWorld->setWorld(xPos, yPos, '-');
		Tiger_starve++, Tiger_num--;
	}
}
void Tiger :: breed()
{	
	if(breedTime >0 || lifeTime ==0)
		return;

	if( (myWorld->which_animal(xPos-1, yPos) != '-') && (myWorld->which_animal(xPos-1, yPos) != '*') && (myWorld->which_animal(xPos-1, yPos) != 'O') && (myWorld->which_animal(xPos+1, yPos) != '-') && (myWorld->which_animal(xPos+1, yPos) != '*') && (myWorld->which_animal(xPos+1, yPos) != 'O') && (myWorld->which_animal(xPos, yPos+1) != '-') && (myWorld->which_animal(xPos, yPos+1) != '*') && (myWorld->which_animal(xPos, yPos+1) != 'O') && (myWorld->which_animal(xPos, yPos-1) != '-') && (myWorld->which_animal(xPos, yPos-1) != '*') && (myWorld->which_animal(xPos, yPos-1) != 'O') )
	{
		breedTime=4;
		return;
	}
	Tiger* newTiger;
	int direction;
	while(1)
	{
		direction = rand()%4;
		if(direction ==0 && ( myWorld->which_animal(xPos-1, yPos) == '-' || myWorld->which_animal(xPos-1, yPos) == '*' || myWorld->which_animal(xPos-1, yPos) == 'O') )
		{
			newTiger = new Tiger(xPos-1, yPos, myWorld);	
			newTiger->setNextTiger(nextTiger);
			setNextTiger(newTiger);
			break;
		}	
		else if(direction ==1 && ( myWorld->which_animal(xPos, yPos+1) == '-' || myWorld->which_animal(xPos, yPos+1) == '*' || myWorld->which_animal(xPos, yPos+1) == 'O') )
		{
			newTiger = new Tiger(xPos, yPos+1, myWorld);	
			newTiger->setNextTiger(nextTiger);
			setNextTiger(newTiger);
			break;
		}
		else if(direction ==2 && ( myWorld->which_animal(xPos+1, yPos) == '-' || myWorld->which_animal(xPos+1, yPos) == '*' || myWorld->which_animal(xPos+1, yPos) == 'O') )
		{
			newTiger = new Tiger(xPos+1, yPos, myWorld);	
			newTiger->setNextTiger(nextTiger);
			setNextTiger(newTiger);
			break;
		}
		else if(direction ==3 && ( myWorld->which_animal(xPos, yPos-1) == '-' || myWorld->which_animal(xPos, yPos-1) == '*' || myWorld->which_animal(xPos, yPos-1) == 'O') )
		{
			newTiger = new Tiger(xPos, yPos-1, myWorld);	
			newTiger->setNextTiger(nextTiger);
			setNextTiger(newTiger);
			break;
		}
	}
			
	breedTime=4;
}
void Tiger :: setNextTiger( Tiger* beNext)
{
	nextTiger = beNext;
}
bool Tiger :: check_live()
{
	if(myWorld->which_animal(xPos, yPos) == 'T')
		return true;
	if ( lifeTime == 0 || myWorld->which_animal(xPos, yPos) == 'O')
		return false;
	if(myWorld->which_animal(xPos, yPos) == 'H')
	{
		Tiger_captured++, Tiger_num--;
		return false;
	}
	else
		return false;
}
Tiger* Tiger :: call_nextTiger()
{
	return nextTiger;
}
