#include "zombie.h"

void Zombie_Update(mapobj_t* zombie)
{
	if(zombie->framesActive % 4 == 0)
	{
		
		int newX = zombie->x + zombie->dx;
		int newY = zombie->y + zombie->dy;

		if(!Map_Walkable(newX, newY))
		{
			zombie->dx = 2 - (1+rand() % 3);
			zombie->dy = 2 - (1+rand() % 3);

			if(zombie->dx == 0 && zombie->dx == 0){zombie->dx = 1;}
		}else
		{
			zombie->x = newX;
			zombie->y = newY;
		}
	}
}

void Zombie_Constructor(mapobj_t* zombie)
{
	zombie->dx = 2 - (1+rand() % 3);
	zombie->dy = 2 - (1+rand() % 3);
}

mapobj_t ZombieType = 
{
	.name = "Zombie",
	.character = {.character = 'Z', .color = 11},
	.updateFunc = &Zombie_Update,
	.constructorFunc = &Zombie_Constructor
};