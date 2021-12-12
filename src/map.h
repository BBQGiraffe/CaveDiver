#ifndef __RPG_MAP__
#define __RPG_MAP__
#include "mapobj.h"
#include "rooms.h"
#include "typedefs.h"
int levelNumber;

void Map_SetRenderFunc(void(*renderFunc));


void Map_SetCollisionFunc(bool(*collisionFunc)(int x, int y));

void Map_SetDefaultFuncs();

void Map_Generate();

void Map_Render();

bool Map_Walkable(int x, int y);
#endif