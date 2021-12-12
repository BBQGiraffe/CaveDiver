#include "cutscene_cavefall.h"
#include "gamestate.h"
#include "player.h"
int px = FRAMEBUFFER_WIDTH / 2;
int py;
int textLen;
char_t* text;

int deadTime;
int fallTimer = 0;

void Cutscene_CaveFall_Play()
{
	py = 0;
	gamestate = RPG_GAMESTATE_CUTSCENE_FALLING;

	text = Char_ColorizeString("should have brought a rope", 5, &textLen);
	fallTimer = 0;
}

void Cutscene_CaveFall_Render()
{

	fallTimer += delta;
	if(fallTimer > 100)
	{
		fallTimer = 0;
		py++;
	}

	Renderer_SetPixel(px, py, (char_t){.character = '@', .color = 5});
	if(py > FRAMEBUFFER_HEIGHT + 5 )
	{
		deadTime += delta;
		if(deadTime >= 3000)
		{
			gamestate = RPG_GAMESTATE_GAME;
			Player_Spawn();
		}
		Renderer_DrawTextEX(text, textLen, ((WINDOW_WIDTH/FONT_SIZE)/2) - textLen/2, 10);
	}
}