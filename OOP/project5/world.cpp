#include <iostream>
#include "world.h"
#include "rabbit.h"
#include "tiger.h"
#include "hunter.h"
#include "pit.h"
#include "grass.h"

using namespace std;

World :: World()
{	
	map = new char* [size+4]; // I will the world having 2 cells width wall
	for(int i=0; i<size+4; i++)
		map[i] = new char[size+4];

	for(int i=0; i<size+4; i++)
		for(int j=0; j<size+4; j++)
		{
			map[i][j] = '-';
		}
	for(int i=0; i<size+4; i++)
	{
		map[0][i] = 'W';
		map[1][i] = 'W';
		map[size+2][i] = 'W';
		map[size+3][i] = 'W';
		map[i][0] = 'W';
		map[i][1] = 'W';
		map[i][size+2] = 'W';
		map[i][size+3] = 'W';
	}
}
void World :: setWorld(int x, int y, char input) // change a cell's status
{
	map[x][y] = input;
}
char World :: which_animal(int x, int y) // show a cells's status
{
	return map[x][y];
}
void World :: Display() // print the world's status
{
	cout << "\n";
	for(int i=2; i<size+2; i++)
	{
		for(int j=2; j<size+2; j++)
			cout << map[i][j] <<" ";
		cout << "\n";
	}
	cout << "\n";
	cout << "number of rabbits:      " << Rabbit :: call_num() << " <born:"<< Rabbit :: call_born() << ", starve:" << Rabbit :: call_starve() << ", captured:" << Rabbit :: call_captured()  << ", fall:"<< Rabbit :: call_fall() << ">\n";
	cout << "number of tigers:       " << Tiger:: call_num() << " <born:"<<  Tiger :: call_born() << ", starve:" <<  Tiger :: call_starve() << ", captured:" <<  Tiger :: call_captured()  << ", fall:"<<  Tiger :: call_fall() << ">\n";
	cout << "number of hunters:      " << Hunter:: call_num() << " <born:"<<  Hunter :: call_born() << ", starve:" <<  Hunter :: call_starve() << ", captured:" <<  Hunter :: call_captured()  << ", fall:"<<  Hunter :: call_fall() << ">\n";
	cout << "number of grasses:      " << Grass::  call_num()<<endl ;
	cout << "number of pits:         " << Pit:: call_num() <<endl ;
	Rabbit :: reset();
	Tiger :: reset();
	Hunter :: reset();
	cout << "\nPress enter to proceed";
}
