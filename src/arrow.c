#include "arrow.h"

void Arrow_Update(mapobj_t* arrow)
{
	arrow->character.color = 7 + (arrow->framesActive % 2);

	arrow->x += arrow->dx;
	arrow->y += arrow->dy;

	if(arrow->msActive > 10000)
	{
		MapObj_Delete(arrow);
	}
}

mapobj_t ArrowType = 
{
	.character = {.character = '*', .color = 7},
	.updateFunc = &Arrow_Update
};