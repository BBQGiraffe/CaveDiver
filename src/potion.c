#include "potion.h"
#include "player.h"
#include "ui.h"
void Potion_DoEffect(struct mapobj_t* object, Item_t* potion);

char potionNames[RPG_POTION_COUNT][16] = 
{
	"Poison",
	"Health Upgrade",
	"Health Pickup"
};

void Potion_HealthUpgrade(mapobj_t* user)
{
	UI_Message("max health increased by 15!");
	player->maxHealth += 15;
}

void Potion_Health(mapobj_t* user)
{
	UI_Message("restored 15 health");
	player->health += 15;
}

void Potion_Poison(mapobj_t* user)
{
	if(user->type == RPG_MAPOBJ_PLAYER)
	{
		UI_Message("you have been poisoned");
		Player_Poison();	
	}
}

void ((*potionFuncs[RPG_POTION_COUNT])(mapobj_t* user)) =
{
	Potion_Poison,
	Potion_HealthUpgrade,
	Potion_Health
};

void Potion_TouchPlayer(struct mapobj_t* potion)
{
	int potionType = rand() % RPG_POTION_COUNT;

	//pick a random potion and give it to the fucker
	Item_t potion_ = 
	{
		.character = {.character = '!', .color = 5},
		.useFunc = potionFuncs[potionType],
		.removeOnUse = true
		// .name = potionNames[potionType]
	};

	memcpy(potion_.name, potionNames[potionType], 16);

	if(Player_GiveItem(potion_))
	{
		MapObj_Delete(potion);
	}

}

mapobj_t PotionType = 
{
	.name = "Potion",
	.character = {.character = '!', .color = 5},
	.touchPlayerFunc = Potion_TouchPlayer,
};





