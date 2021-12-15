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


    //inheritance!!
    uint8_t* classData;   


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

void MapObj_SetClassData(mapobj_t* obj, void* data, int len);

mapobj_t* MapObj_Create(mapobj_t classtype, int x, int y);
void MapObj_Render();
void MapObj_Update();
void MapObj_Delete(mapobj_t* obj);
#endif