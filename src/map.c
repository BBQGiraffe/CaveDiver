#include "map.h"
#include "open-simplex-noise.h"
#include "ui.h"
#include "cavegeneration.h"
#define MAP_WIDTH 128
#define MAP_HEIGHT 128

#define CHUNK_SIMULATION_DISTANCE 8.0f

char_t tiles[256][256];

void Map_DefaultRenderer();

typedef struct chunk_t
{
	int x, y;
	char_t blocks[64][64];
	bool hasCave;
	int id;

	Cave_t cave;
}chunk_t;

chunk_t loadedChunks[(int)CHUNK_SIMULATION_DISTANCE][(int)CHUNK_SIMULATION_DISTANCE];


struct osn_context *ctx;

void (*renderFunc)();
bool (*collisionFunc)(int x, int y);


void Map_SetDefaultFuncs()
{
	renderFunc = &Map_DefaultRenderer;
}

float noise(float x, float y)
{
	return fabs(open_simplex_noise2(ctx, x, y));
}

void Map_SetRenderFunc(void(*func))
{
	renderFunc = func;
}

void Map_SetCollisionFunc(bool(*func)(int x, int y))
{
	collisionFunc = func;
}

void Map_GenerateChunks()
{
	UI_Message("loading chunks...");

	int pcx = player->x / 64;
	int pcy = player->y / 64;	

	for(int cx = -(CHUNK_SIMULATION_DISTANCE/2); cx < CHUNK_SIMULATION_DISTANCE/2; cx++)
	{
		for(int cy = -(CHUNK_SIMULATION_DISTANCE/2); cy < CHUNK_SIMULATION_DISTANCE/2; cy++)
		{
			
			for(int x = 0; x < CHUNK_SIMULATION_DISTANCE; x++)
			{
				for(int y = 0; y < CHUNK_SIMULATION_DISTANCE; y++)
				{
					if(loadedChunks[x][y].x == pcx+cx && loadedChunks[x][y].y == pcy+cy)
					{
						continue;
					}
				}
			}

			chunk_t chunk;
			chunk.x = pcx + cx;
			chunk.y = pcy + cy;

			int caveChance = rand() % 30;
			if(caveChance == 16)
			{
				chunk.hasCave = true;
				// chunk.cave = Cave_GetCave(0);

				chunk.cave.entranceX = 16 + rand() % 16;	
				chunk.cave.entranceY = 16 + rand() % 16;
			}

			for(int x = 0; x < 64; x++)
			{
				for(int y = 0; y < 64; y++)
				{
					// float nx = (1.0f / 64.0f) * (float)x;
					// float ny = (1.0f / 64.0f) * (float)y;

					float nx = x/64.0f - 0.5 + (chunk.x);
					float ny = y/64.0f - 0.5 + (chunk.y);
					
					float frequency = 1.5;

					float n =    frequency * noise(frequency * nx, frequency * ny);
						+  0.5 * noise(2 * frequency * nx, 2 * frequency * ny);
						+ 0.25 * noise(4 * frequency * nx, 4 * frequency * ny);
					
					n = n / (frequency + 0.5 + 0.25);

					n = pow(n, 0.7f);

					// float n = open_simplex_noise2(ctx, nx, ny);
					// float n2 = open_simplex_noise2(ctx, nx*2, ny*2);
					float color = (n * 4.0);

					chunk.blocks[x][y] = (char_t){.character = '.', .color = 13 - (int8_t)color};

					if(n < .2)
					{
						float water = ((n)*4);
						chunk.blocks[x][y] = (char_t){.character = '.', .color = 6 + (int8_t)water};

					}

					
				}
			}

			loadedChunks[(int)(CHUNK_SIMULATION_DISTANCE/2)+cx][(int)(CHUNK_SIMULATION_DISTANCE/2)+cy] = chunk;
		}
	}
}

int oldPx = 0, oldPy = 0;

void Map_ReloadChunks()
{
	int pcx = player->x / 64;
	int pcy = player->y / 64;	

	if(pcx != oldPx || oldPy != pcy)
	{
		Map_GenerateChunks();
	}

	oldPx = pcx;
	oldPy = pcy;
}

void Map_Generate()
{
	open_simplex_noise(levelNumber, &ctx);
	Map_GenerateChunks();
}


void Map_Render()
{
	(*renderFunc)();
}


int offx, offy;
void Map_DefaultRenderer()
{
	Map_ReloadChunks();


	if(player != NULL)
	{
		offx = (player->x) - FRAMEBUFFER_WIDTH / 2;
		offy = (player->y) - FRAMEBUFFER_HEIGHT / 2;
	}

	for(int cx = -(CHUNK_SIMULATION_DISTANCE/2); cx < CHUNK_SIMULATION_DISTANCE/2; cx++)
	{
		for(int cy = -(CHUNK_SIMULATION_DISTANCE/2); cy < CHUNK_SIMULATION_DISTANCE/2; cy++)
		{
			chunk_t chunk = loadedChunks[cx + (int)CHUNK_SIMULATION_DISTANCE/2][cy+(int)CHUNK_SIMULATION_DISTANCE/2];

			for(int x = 0; x < 64; x++)
			{
				for(int y = 0; y < 64; y++)
				{
					Renderer_SetPixel(x + (chunk.x*64) - offx, y+(chunk.y*64) - offy, chunk.blocks[x][y]);
				}
			}

			if(chunk.hasCave)
			{
				Cave_HandleCave(chunk.cave);
			}
		}
	}
}

bool Map_WalkableDefault(int x, int y)
{
	return tiles[x][y].character == '.';
}

bool Map_Walkable(int x, int y)
{
	return !collisionFunc(x,y);
}