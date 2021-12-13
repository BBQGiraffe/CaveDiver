#ifndef __RPG_CAVE_GENERATION__
#define __RPG_CAVE_GENERATION__
#include "math.h"
#include "objtypes.h"
#include "char.h"
#include "cutscene_caveclimb.h"
#include <unistd.h>
typedef enum CaveType_t
{
	RPG_CAVETYPE_NORMAL, //regular ol cave
	RPG_CAVETYPE_CRYPT, //burial place
	RPG_CAVETYPE_CULT, //cult hangout
	RPG_CAVETYPE_RUINS //the rarest type, full of posessed skeletons and shit
}CaveType_t;

typedef struct Cave_t
{
	// char_t tiles[256*256];
	int w, h;
	int entranceX, entranceY;
	uint64_t id;
	
	CaveType_t type;
}Cave_t;


bool Cave_Walkable(int x, int y);
void Cave_Generate(int w, int h);
void Cave_Render();

void Cave_HandleCave(Cave_t cave);

#endif