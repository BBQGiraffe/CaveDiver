#include "cavegeneration.h"
#include "rope.h"
#include <sys/stat.h>
#include "open-simplex-noise.h"
#include <time.h>

struct osx_context;

struct osx_context* ctx;

char_t* tilemap;

Cave_t loadedCave;

int deathLimit = 4;
int birthLimit = 3;

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
int j;
bool* doSimulationStep(bool* original)
{
	bool* newCells = malloc(loadedCave.w * loadedCave.h);

	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			int nbs = countAliveNeighbours(original, x, y);
			int i = (x*loadedCave.w)+y;

			if(nbs > 4)
			{
				newCells[i] = true;
			}else if (nbs < 4)
			{
				newCells = false;
			}
			

			// if(original[(x*loadedCave.w)+y])
			// {
			// 	newCells[(x*loadedCave.w)+y] = !(nbs < deathLimit);
			// }else
			// {
			// 	newCells[(x*loadedCave.w)+y] = (nbs > birthLimit);
			// }
		}
	}
	// free(original);
	return newCells;
}


char_t* tiles;

void Generate()
{
	bool* cells = NULL;

	int attempts;
	while(cells == NULL)
	{
		cells = malloc(loadedCave.w * loadedCave.h);
		attempts++;
		if(attempts > 50)
		{
			printf("failed to allocate the %d bytes needed to create tilemap? what???\n", loadedCave.w*loadedCave.h);
			break;
		}
	}

	float aliveChance = 40;
	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			float chance = randomFloat();

			cells[(x*loadedCave.w)+y] = (chance*100) < aliveChance;
		}
	}

	for(int i = 0; i < 15; i++)
	{
		cells = doSimulationStep(cells);
	}

	char_t wall = {.character = '#', .color = 1};
	char_t floor = {.character = '.', .color = 2};

	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			float nx = ((float)x/(float)loadedCave.w) - 0.5f;
			float ny = ((float)y/(float)loadedCave.h) - 0.5f;

			float color = 1 + open_simplex_noise2(ctx, nx, ny) * 3;
			floor.color = (uint8_t)color;
			loadedCave.tiles[(y*loadedCave.h)+x] = (cells[(x*loadedCave.w)+y]) ? wall : floor;
			printf("%c", loadedCave.tiles[(y*loadedCave.h)+x].character);
		}
		printf("\n");
	} 

	for(int x = 0; x < loadedCave.w; x++)
	{
		for(int y = 0; y < loadedCave.h; y++)
		{
			int n = countAliveNeighbours(cells, x, y);
			if(n == 0)
			{
				player->x = x;
				player->y = y;
			}
		}
	}
}

void Create()
{
	time_t seed;
	time(&seed);
	open_simplex_noise(seed, &ctx);
	// Cave_t cave;
	loadedCave.w = 64 + rand() % 64;
	loadedCave.h = 64 + rand() % 64;
	loadedCave.tiles = malloc(sizeof(char_t) * (loadedCave.w * loadedCave.h));

	Generate();
}


void Cave_HandleCave(Cave_t cave)
{
	int x = cave.entranceX;
	int y = cave.entranceY;
	int sx, sy;
	Renderer_WorldToSCreen(x, y, &sx, &sy);

	int radius = 4;
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
			char_t character = loadedCave.tiles[(y*loadedCave.h) + x];
			Renderer_SetPixel(x - offx, y - offy, character);
		}
	}
}