#include "renderer.h"
#include "ui.h"
#include "objtypes.h"
#include "cutscene_caveclimb.h"

void DrawMainGame()
{
    Map_Render();
    MapObj_Render();
    Renderer_DrawGame();
    UI_Draw();
}
int main()
{
    time_t seed;
    time(&seed);
    srand(seed);
    Renderer_Init();
    Color_LoadPalette();

    Renderer_FillScreen(' ', 0);

    Player_Spawn();

    uint32_t tickCount = 0;
    uint32_t elapsed = 0;

    delta = 0;

    // for(int i = 0; i < 10; i++)
    // {
    //     MapObj_Create(BowType, i, 0);
    //     MapObj_Create(PotionType, i, 2);
    // }

    Map_Generate();

    gamestate = RPG_GAMESTATE_GAME;

    // Cutscene_CaveFall_Play();
    Map_SetDefaultFuncs();

    while(Window_IsOpen())
    {

        if(gamestate == RPG_GAMESTATE_GAME)
        {
            Player_HandleRespawning();
        }
        

        Input_ProcessKeys();
        delta = (SDL_GetTicks() - tickCount);
        tickCount = SDL_GetTicks();


        //fixes the first frame having insane detatime
        if(delta <= 0 ){delta  = 1;}
        if(delta > 60){delta = 60;}

        elapsed += delta;
        if(elapsed > RPG_OBJECT_UPDATE_TIME)
        {
            elapsed = 0;
            MapObj_Update();
        }

        Renderer_Clear();
        Window_PollEvents();
        // if(gamestate == RPG_GAMESTATE_GAME)
        // {
        //     Map_Render();
        //     MapObj_Render();
        //     Renderer_DrawGame();
        //     UI_Draw();
        // }

        switch (gamestate)
        {
        case RPG_GAMESTATE_GAME:
            DrawMainGame();
            break;
        case RPG_GAMESTATE_CUTSCENE_FALLING:
            Cutscene_CaveFall_Render();
            break;
        case RPG_GAMESTATE_CUTSCENE_CLIMBING:
            Cutscene_CaveClimb_Render();
        default:
            break;
        }

        Renderer_Present();
    }
    Renderer_ShutDown();
}