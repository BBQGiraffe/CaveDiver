#include "player.h"
#include "ui.h"
#include "math.h"
#include "rope.h"
#include "cavegeneration.h"
void Player_HandleInput(mapobj_t* player);


#define RPG_PLAYER_MANA_LIMIT 32

int player_itemCount = 0;
bool player_poisoned = false;

uint32_t timeDead = 0;
const uint32_t respawnTime = 2000;

mapobj_t PlayerType = {
    .character = {'@', 5},
    .interactionText = "Our \"Hero\"",
    .canInteract = true,
    .type = RPG_MAPOBJ_PLAYER,
    .name = "BBQ",
    .updateFunc = Player_UpdatePlayer,
    .realTimeUpdateFunc = Player_HandleInput,
    .health = 100,
    .maxHealth = 100,

    //set dx so that if you shoot an arrow before moving it isn't frozen
    .dx = 1,
    .dx = 0,
    .p_maxMana = 4,
    .p_mana = 4,
    .p_manaRegenTime = 250
};

bool moving;

char player_deathMessage[32];

void Player_HandleInput(mapobj_t* player)
{
    moving = false;
    if(Input_IsKeyDown(SDL_SCANCODE_UP))
    {
        moving = true;
        player->dy = -1;
        player->dx = 0;
    }
    if(Input_IsKeyDown(SDL_SCANCODE_DOWN))
    {
        moving = true;
        player->dy = 1;
        player->dx = 0;
    }
    if(Input_IsKeyDown(SDL_SCANCODE_LEFT))
    {
        moving = true;
        player->dx = -1;
        player->dy = 0;
    }
    if(Input_IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        moving = true;
        player->dx = 1;
        player->dy = 0;
    }


    // printf("%d %d\n", x, y);

    int mx, my, x, y;

    Input_GetMouse(&mx, &my);

    Renderer_ScreenToWorld(mx, my, &x, &y);

    // printf("%d\n", Math_Distance(x, y, player->x, player->y));

    // Cave_HandleCave(10, 10);
}


bool Player_HasItem(Item_t item)
{
    for(int i = 0; i < player_itemCount; i++)
    {
        if(strcmp(item.name, player_items[i]->name) == 0)
        {
            return true;
        }
    }
    return false;
}

void Player_UseItem()
{
    Item_t* item = player_items[player_itemIndex];
    
    if(item == NULL){return;}

    item->useFunc(player, item);
    if(item->removeOnUse)
    {
        item->amount--;
        
        //if item is depleted, remove from inventory
        if(item->amount == 0)
        {
            player_itemCount--;
            free(item);
            player_items[player_itemIndex] = NULL;
            for(int i = 1; i < RPG_PLAYER_MAX_ITEMS; i++)
            {
                if(player_items[i-1] == NULL)
                {
                    player_items[i-1] = player_items[i];
                    player_items[i] = NULL;
                }
            }
        }
    }
}


void Player_Poison()
{
    player_poisoned = true;
}

void Player_HandleDeath()
{
    if(player->health < 0)
    {
        //kill the bitch
        UI_Message("you died, dumbass");
        MapObj_Delete(player);
        player = NULL;
        return;
    }
}

void Player_UpdatePlayer(mapobj_t* player)
{

    if(player_poisoned && player->framesActive % 4 == 0)
    {
        player->health -= 5;
    }

    if(Input_IsKeyDown(SDL_SCANCODE_LCTRL) && player->framesActive % 2 == 0)
    {
        Player_UseItem();
    }

    if(!Input_IsKeyDown(SDL_SCANCODE_LCTRL) && player->p_mana < player->p_maxMana)
    {
        if(player->p_manaRegenTimeElapsed > player->p_manaRegenTime)
        {
            player->p_manaRegenTimeElapsed = 0;
            player->p_mana++;
        }
        player->p_manaRegenTimeElapsed += delta;
    }

    if(Input_IsKeyDown(SDL_SCANCODE_LEFTBRACKET))
    {
        player_itemIndex--;
    }
    if(Input_IsKeyDown(SDL_SCANCODE_RIGHTBRACKET))
    {
        player_itemIndex++;
    }


    if(player_itemIndex < 0){player_itemIndex = 0;}
    if(player_itemIndex >= player_itemCount){player_itemIndex = player_itemCount-1;}

    if(moving && player->framesActive % 2 == 0)
    {
        player->x += player->dx;
        player->y += player->dy;
    }

    if(player->health > player->maxHealth){player->health = player->maxHealth;}
    Player_HandleDeath();


    cameraX = player->x;
    cameraY = player->y;    
}
extern Item_t BowWeapon;

void Player_Spawn()
{
    //remove weapons if they exist
    for(int i = 0; i < player_itemCount; i++)
    {
        free(player_items[i]);
        player_items[i] = NULL;
    }

    player_itemCount = 0;
    player_itemIndex = 0;

    player = MapObj_Create(PlayerType, 0, 0);
    Player_GiveItem(BowWeapon);
    Player_GiveItem(RopeItem);
}

void Player_HandleRespawning()
{
    if(player != NULL){return;}
    
    timeDead += delta;
    printf("%d\n", timeDead);

    if(timeDead > respawnTime)
    {
        Player_Spawn();
    }
}


bool Player_GiveItem(Item_t item)
{
    int i = 0;
    while(player_items[i] != NULL)
    {
        //if we have this item, add to its stack 
        if(strcmp(item.name, player_items[i]->name) == 0)
        {
            char pickupText[27];
            sprintf(pickupText, "grabbed %s", item.name);
            UI_Message(pickupText);

            player_items[i]->amount++;
            return true;
        }

        i++;
        if(i == RPG_PLAYER_MAX_ITEMS)
        {
            return false;
        }
    }

    char pickupText[27];
    sprintf(pickupText, "grabbed %s", item.name);
    UI_Message(pickupText);
    player_itemCount++;

    Item_t* new = malloc(sizeof(Item_t));
    *new = item;
    new->amount = 1;
    player_items[i] = new;

    return true;
}