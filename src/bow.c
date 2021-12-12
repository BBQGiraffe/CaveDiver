#include "bow.h"
#include "arrow.h"
#include "player.h"
mapobj_t BowType = 
{
    .character = {.character = '_', .color = 29},
    .type = RPG_MAPOBJ_BOW,
    .name = "Bow",
    .updateFunc = NULL,
	.touchPlayerFunc = &Bow_Pickup
};

void Bow_Fire(mapobj_t* owner, Item_t* item)
{
    // UI_Message("*twunk*");
    mapobj_t* arrow = MapObj_Create(ArrowType, owner->x + owner->dx, owner->y + owner->dy);
    if(arrow)
    {
        owner->p_mana--;
        arrow->dx = owner->dx;
        arrow->dy = owner->dy;
    }
}

Item_t BowWeapon = 
{
    .name = "magic staff",
    .useFunc = &Bow_Fire,
    // .shootFunc = &Bow_Fire
};


void Bow_Pickup(mapobj_t* bow)
{
	// UI_Message("Picked up a staff");
    if(Player_GiveItem(BowWeapon))
    {
        MapObj_Delete(bow);
    }
}