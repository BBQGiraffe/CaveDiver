#include "mapobj.h"
#include "ui.h"
mapobj_t* MapObj_Create(mapobj_t template, int x, int y)
{
    int i = 0;
    while(objects[i] != NULL)
    {
        i++;
        if(i == RPG_MAXOBJECTS)
        {
            char text[32];
            sprintf(text, "reached object limit of %u!\n", RPG_MAXOBJECTS);
            UI_Message(text);
            return NULL;
        }
    }

    mapobj_t* new = malloc(sizeof(*new));

    *new = template;
    new->x = x;
    new->y = y;
    objects[i] = new;
    m_entityCount++;

    return new;
}

int offx, offy;

void MapObj_Render()
{
    offx = (cameraX) - FRAMEBUFFER_WIDTH / 2;
    offy = (cameraY) - FRAMEBUFFER_HEIGHT / 2;

    for(int i = 0; i < RPG_MAXOBJECTS; i++)
    {
        if(objects[i] == NULL)
        {
            continue;
        }

        mapobj_t* obj = objects[i];
        Renderer_SetPixel(obj->x - offx, obj->y - offy, obj->character);
    }

    for(int i = 0; i < RPG_MAXOBJECTS; i++)
    {
        if(objects[i] == NULL)
        {
            continue;
        }

        mapobj_t* obj = objects[i];
        obj->msActive += delta;
        if(obj->realTimeUpdateFunc != NULL)
        {
            obj->realTimeUpdateFunc(obj);
        }
    }

}

void MapObj_HandlePlayerInteraction(mapobj_t* object)
{
    if(player == NULL){return;}
    if(player->x == object->x && player->y == object->y)
    {
        if(object->touchPlayerFunc != NULL)
        {
            object->touchPlayerFunc(object);
        }
    }
}


void MapObj_RemoveDeletedObjects()
{
    for(int i = 0; i < RPG_MAXOBJECTS; i++)
    {
        if(objects[i] == NULL)
        {
            continue;
        }

        if(objects[i]->deleted)
        {
            objects[i] = NULL;
            m_entityCount--;
            free(objects[i]);
        }
    }
}

void MapObj_Delete(mapobj_t* obj)
{
    obj->deleted = true;
}

void MapObj_Update()
{
    for(int i = 0; i < RPG_MAXOBJECTS; i++)
    {
        if(objects[i] == NULL)
        {
            continue;
        }

        mapobj_t* obj = objects[i];
        obj->framesActive++;
        MapObj_HandlePlayerInteraction(obj);
        if(obj->updateFunc != NULL)
        {
            obj->updateFunc(obj);
        }
    }
    MapObj_RemoveDeletedObjects();
}