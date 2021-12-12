#include "projectile.h"

void Projectile_Update(mapobj_t* projectile)
{
	//todo: implement doom-style blockmaps
	for(int i = 0; i < RPG_MAXOBJECTS; i++)
	{
		if(objects[i] == NULL){continue;}
		
	}

	projectile->x += projectile->dx;
	projectile->y += projectile->dy;
};

mapobj_t ProjectileType = 
{
	.updateFunc = &Projectile_Update
};