#ifndef __RPG_INPUT__
#define __RPG_INPUT__
#include "mapobj.h"
void Input_GetMouse(int* x, int* y);
void Input_ProcessKeys();
bool Input_IsKeyDown(SDL_Scancode key);
#endif