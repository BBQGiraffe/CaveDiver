#ifndef __RPG_MAP_OBJ__
#define __RPG_MAP_OBJ__
#include "mapobjtype.h"
#include "renderer.h"
#include "timer.h"
#include "item.h"
#include "map.h"
#include "gamestate.h"
#include "cutscene_cavefall.h"


typedef struct mapobj_t
{
    char_t character;
    char name[32];
    int x,y;
    int dx, dy;
    MapObjType_t type;

    bool canInteract;
    char interactionText[32];

    int16_t health;
    int16_t maxHealth;

    //the ms elapsed in game when the object was created
    uint64_t startTime;

    //the ms elapsed since the objects was created
    uint64_t msActive;

    uint64_t framesActive;

    /*      Container/Door related vars     */

    bool isOpen;
    bool isLocked;

    /*      NPC related vars        */
    int sightRange;
    int meleeDamage;
    int attackTime;

    /*      Player related vars     */

    int p_mana;
    int p_maxMana;
    int p_manaRegenTime;    
    int p_manaRegenTimeElapsed;


    /*      Pickup related vars     */

    void (*touchPlayerFunc)(struct mapobj_t* object);
    void (*interactionFunc)(struct mapobj_t* object);
    
    //updated every single frame
    void (*realTimeUpdateFunc)(struct mapobj_t* object);

    //updated 13 times per second
    void (*updateFunc)(struct mapobj_t* object);


    void (*constructorFunc)(struct mapobj_t* object);

    bool deleted;
}mapobj_t;

#define RPG_MAXOBJECTS 256
#define RPG_OBJECT_UPDATE_TIME 75

struct mapobj_t* objects[RPG_MAXOBJECTS];
int m_entityCount;
struct mapobj_t* player;

mapobj_t* MapObj_Create(mapobj_t classtype, int x, int y);
void MapObj_Render();
void MapObj_Update();
void MapObj_Delete(mapobj_t* obj);
#endif