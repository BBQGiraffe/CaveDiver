#ifndef __RPG_UI__
#define __RPG_UI__
#include "player.h"
#include "pride.h"
#include "mapobj.h"
void UI_Draw();
void UI_DrawProgressBar(int8_t color, const int max, int amount, const int length, int x, int y);
void UI_Message(const char* text);
#endif