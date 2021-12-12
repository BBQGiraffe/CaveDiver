#ifndef __RPG_GAMESTATE__
#define __RPG_GAMESTATE__
typedef enum GameState_t
{
	RPG_GAMESTATE_MENU,
	RPG_GAMESTATE_CUTSCENE_FALLING,
	RPG_GAMESTATE_CUTSCENE_CLIMBING,
	RPG_GAMESTATE_GAME
}GameState_t;

enum GameState_t gamestate;

#endif