#include "input.h"
#include "renderer.h"
void Input_GetMouse(int* x, int* y)
{
	int mx = mouseX;
	int my = mouseY;
	mx /= FONT_SIZE;
	my /= fontHeight;

	
	*x = mx;
	*y = my;
}


bool* keys;

void Input_ProcessKeys()
{
	keys = (bool*)SDL_GetKeyboardState(NULL);
}

bool Input_IsKeyDown(SDL_Scancode key)
{
	return keys[key];
}