#include "cutscene_caveclimb.h"
#include "cavegeneration.h"
#include "map.h"
extern int px;
extern int py;

int climbTimer;

char_t player_text = {.character = '@', .color = 5};
char_t rope_text = {.character = '|', .color = 29};
char_t rope_end_text = {.character = '/', .color = 29};
void Cutscene_CaveClimb_Play(bool goingUp)
{
	py = 0;
	px = (WINDOW_WIDTH / FONT_SIZE) / 2;
	climbTimer = 0;
	gamestate = RPG_GAMESTATE_CUTSCENE_CLIMBING;
	player->x = 0;
	player->y = 0;
}

void Cutscene_CaveClimb_Render()
{
	Renderer_DrawTextEX(&player_text, 1, px, py);
	
	for(int i = 0; i < py-1; i++)
	{
		Renderer_DrawTextEX(&rope_text, 1, px+1, i);
	}

	Renderer_DrawTextEX(&rope_end_text, 1, px+1, py-1);

	climbTimer += delta;
	if(climbTimer > 100)
	{
		py++;
		climbTimer = 0;
	}

	if(py > (WINDOW_HEIGHT/fontHeight) + 10)
	{
		Cave_Generate(320, 240);
		Map_SetRenderFunc(&Cave_Render);
		Map_SetCollisionFunc(&Cave_Walkable);
		gamestate = RPG_GAMESTATE_GAME;
	}
}