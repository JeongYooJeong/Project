#include <iostream>
#include <ctime>
#include <cstdlib>
#include "hunter.h"
#include "world.h"

Hunter :: Hunter() {}
Hunter :: Hunter(World* input_World) : Critter(input_World)
{
	myWorld->setWorld(xPos, yPos, 'H');
	breedTime=8;
	Hunter_num++, Hunter_born++;
}
Hunter :: Hunter(int x, int y, World* input_World) : Critter(x,y,input_World)// new hunter by breeding
{
	Hunter_born++;
	Hunter_num++;	
	if(myWorld->which_animal(xPos, yPos) == 'O') // new hunter falled in pit, so died
	{
		Hunter_fall++, Hunter_num--;
	}
	else
	{
		myWorld->setWorld(xPos, yPos, 'H');
		lifeTime=3, breedTime=8;
		check_newBorn=true;
	}
}
void Hunter :: move()
{
	int direction;
	if(lifeTime == 0) // dead...can not move
		return;
	if(check_newBorn == true) // he is just birth... can not move 
	{
		check_newBorn = false;
		return;
	}

	if(myWorld->which_animal(xPos+1, yPos) == 'R' || myWorld->which_animal(xPos-1,yPos) == 'R' || myWorld->which_animal(xPos, yPos+1) == 'R' || myWorld->which_animal(xPos, yPos-1) == 'R'|| myWorld->which_animal(xPos+1, yPos) == 'T' || myWorld->which_animal(xPos-1,yPos) == 'T' || myWorld->which_animal(xPos, yPos+1) == 'T' || myWorld->which_animal(xPos, yPos-1) == 'T') // there is prey nearly
		while(1)
		{
			direction = rand()%4;
			if( direction==0 && (myWorld->which_animal(xPos-1, yPos) == 'R' || myWorld->which_animal(xPos-1, yPos) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos--;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
			else if( direction==1 && (myWorld->which_animal(xPos, yPos+1) == 'R' || myWorld->which_animal(xPos, yPos+1) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				yPos++;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
			else if( direction==2 && (myWorld->which_animal(xPos+1, yPos) == 'R' || myWorld->which_animal(xPos+1, yPos) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos++;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
			else if( direction==3 && (myWorld->which_animal(xPos, yPos-1) == 'R' || myWorld->which_animal(xPos, yPos-1) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				yPos--;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
		}
	if(myWorld->which_animal(xPos+2, yPos) == 'R' || myWorld->which_animal(xPos-2,yPos) == 'R' || myWorld->which_animal(xPos, yPos+2) == 'R' || myWorld->which_animal(xPos, yPos-2) == 'R'|| myWorld->which_animal(xPos+2, yPos) == 'T' || myWorld->which_animal(xPos-2,yPos) == 'T' || myWorld->which_animal(xPos, yPos+2) == 'T' || myWorld->which_animal(xPos, yPos-2) == 'T') // there is prey. not nearly
		while(1)
		{
			direction = rand()%4; 
			if( direction==0 && (myWorld->which_animal(xPos-2, yPos) == 'R' || myWorld->which_animal(xPos-2,yPos) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos--;
				if(myWorld->which_animal(xPos, yPos) == 'O')
				{
					Hunter_fall++, Hunter_num--;
					return;
				}
				if(myWorld->which_animal(xPos, yPos) == '*')
					myWorld->setWorld(xPos, yPos, '-');
				xPos--;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
			else if( direction==1 && (myWorld->which_animal(xPos, yPos+2) == 'R' || myWorld->which_animal(xPos,yPos+2) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				yPos++;
				if(myWorld->which_animal(xPos, yPos) == 'O')
				{
					Hunter_fall++, Hunter_num--;
					return;
				}
				if(myWorld->which_animal(xPos, yPos) == '*')
					myWorld->setWorld(xPos, yPos, '-');
				yPos++;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
			else if( direction==2 && (myWorld->which_animal(xPos+2, yPos) == 'R' || myWorld->which_animal(xPos+2,yPos) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				xPos++;
				if(myWorld->which_animal(xPos, yPos) == 'O')
				{
					Hunter_fall++, Hunter_num--;
					return;
				}
				if(myWorld->which_animal(xPos, yPos) == '*')
					myWorld->setWorld(xPos, yPos, '-');
				xPos++;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
			else if( direction==3 && (myWorld->which_animal(xPos, yPos-2) == 'R' || myWorld->which_animal(xPos,yPos-2) == 'T') )
			{
				myWorld->setWorld(xPos, yPos, '-');
				yPos--;
				if(myWorld->which_animal(xPos, yPos) == 'O')
				{
					Hunter_fall++, Hunter_num--;
					return;
				}
				if(myWorld->which_animal(xPos, yPos) == '*')
					myWorld->setWorld(xPos, yPos, '-');
				yPos--;
				myWorld->setWorld(xPos, yPos, 'H');
				lifeTime=3, breedTime--;
				return;
			}
		}
	direction = rand()%4; //can not hunt
	if( direction == 0 && (myWorld->which_animal(xPos-1, yPos) == '-' || myWorld->which_animal(xPos-1, yPos) == '*') )
	{
		myWorld->setWorld(xPos, yPos, '-');
		xPos--;
		myWorld->setWorld(xPos, yPos, 'H');
	}
	else if( direction == 0 && myWorld->which_animal(xPos-1, yPos) == 'O' ) // fall in pit
	{
		myWorld-> setWorld(xPos, yPos, '-');
		xPos--;
		Hunter_fall++, Hunter_num--;
		return;
	}
	else if( direction == 1 && (myWorld->which_animal(xPos, yPos+1) == '-' || myWorld->which_animal(xPos, yPos+1) == '*') )
	{
		myWorld->setWorld(xPos, yPos, '-');
		yPos++;
		myWorld->setWorld(xPos, yPos, 'H');
	}
	else if( direction == 1 && myWorld->which_animal(xPos, yPos+1) == 'O' )
	{
		myWorld-> setWorld(xPos, yPos, '-');
		yPos++;
		Hunter_fall++, Hunter_num--;
		return;
	}
	else if( direction == 2 && (myWorld->which_animal(xPos+1, yPos) == '-' || myWorld->which_animal(xPos+1, yPos) == '*') )
	{
		myWorld->setWorld(xPos, yPos, '-');
		xPos++;
		myWorld->setWorld(xPos, yPos, 'H');
	}
	else if( direction == 2 && myWorld->which_animal(xPos+1, yPos) == 'O' )
	{
		myWorld-> setWorld(xPos, yPos, '-');
		xPos++;
		Hunter_fall++, Hunter_num--;
		return;
	}
	else if( direction == 3 && (myWorld->which_animal(xPos, yPos-1) == '-' || myWorld->which_animal(xPos, yPos-1) == '*') )
	{
		myWorld->setWorld(xPos, yPos, '-');
		yPos--;
		myWorld->setWorld(xPos, yPos, 'H');
	}
	else if( direction == 3 && myWorld->which_animal(xPos, yPos-1) == 'O' )
	{
		myWorld-> setWorld(xPos, yPos, '-');
		yPos--;
		Hunter_fall++, Hunter_num--;
		return;
	}
	lifeTime--, breedTime--;
	if(lifeTime == 0)
	{
		Hunter_starve++, Hunter_num--;
		myWorld->setWorld(xPos, yPos, '-');
	}
}
void Hunter :: breed()
{
	if(breedTime >0 || lifeTime==0) 
		return;

	if( (myWorld->which_animal(xPos-1, yPos) != '-') && (myWorld->which_animal(xPos-1, yPos) != '*') && (myWorld->which_animal(xPos-1, yPos) != 'O') && (myWorld->which_animal(xPos+1, yPos) != '-') && (myWorld->which_animal(xPos+1, yPos) != '*') && (myWorld->which_animal(xPos+1, yPos) != 'O') && (myWorld->which_animal(xPos, yPos+1) != '-') && (myWorld->which_animal(xPos, yPos+1) != '*') && (myWorld->which_animal(xPos, yPos+1) != 'O') && (myWorld->which_animal(xPos, yPos-1) != '-') && (myWorld->which_animal(xPos, yPos-1) != '*') && (myWorld->which_animal(xPos, yPos-1) != 'O') ) // surround occupied...can not breed
	{
		breedTime=8;
		return;
	}
	Hunter* newHunter;
	int direction;
	while(1)
	{
		direction = rand()%4;
		if(direction ==0 && ( myWorld->which_animal(xPos-1, yPos) == '-' || myWorld->which_animal(xPos-1, yPos) == '*' || myWorld->which_animal(xPos-1, yPos) == 'O') )
		{
			newHunter = new Hunter(xPos-1, yPos, myWorld);	
			newHunter->setNextHunter(nextHunter);
			setNextHunter(newHunter);
			break;
		}	
		else if(direction ==1 && ( myWorld->which_animal(xPos, yPos+1) == '-' || myWorld->which_animal(xPos, yPos+1) == '*' || myWorld->which_animal(xPos, yPos+1) == 'O') )
		{
			newHunter = new Hunter(xPos, yPos+1, myWorld);	
			newHunter->setNextHunter(nextHunter);
			setNextHunter(newHunter);
			break;
		}
		else if(direction ==2 && ( myWorld->which_animal(xPos+1, yPos) == '-' || myWorld->which_animal(xPos+1, yPos) == '*' || myWorld->which_animal(xPos+1, yPos) == 'O') )
		{
			newHunter = new Hunter(xPos+1, yPos, myWorld);	
			newHunter->setNextHunter(nextHunter);
			setNextHunter(newHunter);
			break;
		}
		else if(direction ==3 && ( myWorld->which_animal(xPos, yPos-1) == '-' || myWorld->which_animal(xPos, yPos-1) == '*' || myWorld->which_animal(xPos, yPos-1) == 'O') )
		{
			newHunter = new Hunter(xPos, yPos-1, myWorld);	
			newHunter->setNextHunter(nextHunter);
			setNextHunter(newHunter);
			break;
		}
	}		
	breedTime=8;
}
void Hunter :: setNextHunter(Hunter* beNext)
{
	nextHunter = beNext;
}
bool Hunter :: check_live()
{
	if(myWorld->which_animal(xPos, yPos) == 'H')
		return true;
	if(lifeTime == 0 || myWorld->which_animal(xPos, yPos) == 'O')
		return false;
	else
		return false;
}
Hunter* Hunter :: call_nextHunter()
{
	return nextHunter;
}
