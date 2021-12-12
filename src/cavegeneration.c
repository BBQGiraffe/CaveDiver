#include "cavegeneration.h"
#include "rope.h"
#include <sys/stat.h>
char_t* tilemap;

Cave_t loadedCave;

int deathLimit = 3;
int birthLimit = 4;

int countAliveNeighbours(bool* map, int x, int y){

    int count = 0;

    for(int i=-1; i<2; i++){

        for(int j=-1; j<2; j++){

            int neighbour_x = x+i;

            int neighbour_y = y+j;

            if(i == 0 && j == 0){

            }

            else if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= loadedCave.w || neighbour_y >= loadedCave.h){

                count = count + 1;

            }

            else if(map[(neighbour_x * loadedCave.w ) + neighbour_y]){

                count = count + 1;

            }

        }

    }
	return count;

}

bool* doSimulationStep(bool* original)
{
	bool* newCells = malloc(loadedCave.w * loadedCave.h);

	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			int nbs = countAliveNeighbours(original, x, y);
			if(original[(x*loadedCave.w)+y])
			{
				newCells[(x*loadedCave.w)+y] = !(nbs < deathLimit);
			}else
			{
				newCells[(x*loadedCave.w)+y] = (nbs > birthLimit);
			}
		}
	}
	return newCells;
}


char_t* tiles;

void Create()
{
	// Cave_t cave;
	loadedCave.w = 64 + rand() % 64;
	loadedCave.h = 64 + rand() % 64;
	loadedCave.tiles = malloc(sizeof(char_t) * (loadedCave.w * loadedCave.h));

	
	bool* cells = malloc(loadedCave.w * loadedCave.h);

	float aliveChance = 0.7f;
	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			float chance = randomFloat();

			if(chance > aliveChance)
			{
				cells[(x*loadedCave.w)+y] = true;
			}
		}
	}

	for(int i = 0; i < 50; i++)
	{
		cells = doSimulationStep(cells);
	}

	char_t wall = {.character = '#', .color = 1};
	char_t floor = {.character = '.', .color = 2};

	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			loadedCave.tiles[(y*loadedCave.h)+x] = (cells[(x*loadedCave.w)+y]) ? wall : floor;
			printf("%c", loadedCave.tiles[(y*loadedCave.h)+x]);
		}
		printf("\n");
	} 
}


void Cave_HandleCave(Cave_t cave)
{
	int x = cave.entranceX;
	int y = cave.entranceY;
	int sx, sy;
	Renderer_WorldToSCreen(x, y, &sx, &sy);

	int radius = 4;
	int outerRing = 3;
	for(x = 0; x < FRAMEBUFFER_WIDTH; x++)
	{
		for(y = 0; y < FRAMEBUFFER_HEIGHT; y++)
		{
			int distance = Math_Distance(sx, sy, x, y);


			if(distance <= radius)
			{
				Renderer_SetPixel(x, y, (char_t){.character = '#', .color = distance});
			}
		}
	}

	int mx, my;

	Input_GetMouse(&mx, &my);

	int distance = Math_Distance(mx, my, sx, sy);
	if(distance <= radius)
	{
		UI_Message("Enter Hole?");


		if(Input_IsKeyDown(SDL_SCANCODE_Y))
		{
			if(Player_HasItem(RopeItem))
			{
				Cutscene_CaveClimb_Play(false);
			}else
			{
				Cutscene_CaveFall_Play();
			}
		}
	}
	
}

void Cave_Generate(int w, int h)
{
	Create();
}

void Cave_Render()
{
	int offx = (cameraX) - FRAMEBUFFER_WIDTH / 2;
    int offy = (cameraY) - FRAMEBUFFER_HEIGHT / 2;

	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			char_t character = loadedCave.tiles[(x*loadedCave.w) + y];
			Renderer_SetPixel(x - offx, y - offy, character);
		}
	}
}