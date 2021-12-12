#ifndef __RPG_COLOR__
#define __RPG_COLOR__
#include "typedefs.h"
#include "stdio.h"
#define COLOR_COUNT 32
uint8_t palette[COLOR_COUNT * 3];

void Color_GetColor(uint8_t index, uint8_t* r, uint8_t* g, uint8_t* b);
void Color_LoadPalette();
#endif