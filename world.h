#ifndef WORLD_H
#define WORLD_H
#define size 20

class World
{
	public:
		World();
		void setWorld(int x, int y, char input);
		char which_animal(int x, int y);
		void Display();
	private:
		char **map;
};
#endif
