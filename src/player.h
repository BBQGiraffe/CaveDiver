#ifndef __RPG_PLAYER__
#define __RPG_PLAYER__
#include "mapobj.h"
#include "input.h"
#include "item.h"

#define RPG_PLAYER_MAX_ITEMS 12


typedef struct PlayerData_t
{
	char testString[32];
	int sex;
}PlayerData_t;

//player inventory
Item_t* player_items[RPG_PLAYER_MAX_ITEMS];
int player_itemIndex;

extern mapobj_t PlayerType;


//returns true if the player was able to pick it up
bool Player_GiveItem(Item_t item);
bool Player_HasItem(Item_t item);
void Player_UpdatePlayer(struct mapobj_t* player);

//causes inevitable death, unless you find a cure
void Player_Poison();

//handles the player respawn 
void Player_HandleRespawning();
void Player_Spawn();

#endif