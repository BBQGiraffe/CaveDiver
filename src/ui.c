#include "ui.h"

char position[32];
char message[64];
char weaponText[32];

#define MANABAR_LEN 16
#define MANABAR_COLOR 6

#define HEALTHBAR_LEN 24
#define HEALTHBAR_COLOR 17

#define PROGRESSBAR_BACKGROUND_COLOR 2

int textLen;


int elapsedMessageTime = 0;
int elapsedChangeTime = 0;

const uint32_t colorChangeTime = 300;
const uint32_t messsageTime = 1500;

uint8_t color = 5;

void UI_DrawProgressBar(int8_t color, const int max, int amount, const int length, int x, int y)
{
    const int len = (int)(((float)amount / (float)max) * (float)length);
    char_t bar[length];

    for(int i = 0; i < length; i++)
    {
        bar[i] = (char_t){.character = '#', .color = (len > i)? color : PROGRESSBAR_BACKGROUND_COLOR};
    }

    Renderer_DrawTextEX(bar, length, x, y);  
}

char selectionArrow[2] = "<-";

void UI_DrawPlayerInventory()
{
    Renderer_DrawText("Inventory:", 34, 3);
    for(int i = 0; i < RPG_PLAYER_MAX_ITEMS; i++)
    {
        if(player_items[i] == NULL){continue;}
    

        char text[33];
        sprintf(text, "%s (x%d) %s", player_items[i]->name, player_items[i]->amount, (i == player_itemIndex) ? selectionArrow : "");

        Renderer_DrawText(text, 34, 4 + i);
    }
}

void UI_DrawPlayerInfo()
{   
    if(!player){return;}

    UI_DrawProgressBar(MANABAR_COLOR, player->p_maxMana, player->p_mana, MANABAR_LEN, 0, 34);
    UI_DrawProgressBar(HEALTHBAR_COLOR, player->maxHealth, player->health, HEALTHBAR_LEN, 0, 35);
    UI_DrawPlayerInventory();
}

void UI_HandleSelection()
{
    int x,y;
    Input_GetMouse(&x,&y);
    Renderer_SetPixel(x, y, (char_t){.character = '|', .color = 5});


    int wx, wy;
    Renderer_ScreenToWorld(x, y, &wx, &wy);

    for(int i = 0; i < RPG_MAXOBJECTS; i++)
    {
        if(objects[i] == NULL){continue;}
        if(objects[i]->x == wx && objects[i]->y == wy)
        {
            Renderer_DrawText(objects[i]->name, 34, 17);
        }
    }
}


bool shown = true;

void UI_Message(const char* text)
{

    elapsedMessageTime = 0;
    elapsedChangeTime = 0;

    color = 5;
    shown = true;
    sprintf(message, "%s",  text);
}

void UI_PrintMessage()
{
    if(message == NULL){return;}
    if(elapsedMessageTime > messsageTime)
    {
        elapsedChangeTime += delta;
        if(elapsedChangeTime > colorChangeTime)
        {
            elapsedChangeTime = 0;
            if(color > 0)
            {
                color--;
            }else
            {
                shown = false;
            }
        }
    }

    if(shown)
    {
        elapsedMessageTime += delta;
        Renderer_DrawTextEX(Char_ColorizeString(message, color, &textLen), textLen, 33, 0);
    }
}

void UI_Draw()
{
    UI_DrawPlayerInfo();
    UI_HandleSelection();
    UI_PrintMessage();

    // Pride_DrawFlags();
}
