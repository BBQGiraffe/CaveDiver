#ifndef __RPG_RENDERER__
#define __RPG_RENDERER__
#include "sdlutils.h"
#include "char.h"
#include "color.h"

#define FRAMEBUFFER_WIDTH 32
#define FRAMEBUFFER_HEIGHT 32
#define FONT_SIZE 24
int fontHeight;
#define WINDOW_WIDTH FRAMEBUFFER_WIDTH * FONT_SIZE * 2
#define WINDOW_HEIGHT FRAMEBUFFER_HEIGHT * FONT_SIZE

#define WINDOW_NAME "ArPG"
SDL_Renderer* renderer;

int mouseX;
int mouseY;

int cameraX, cameraY;
void Renderer_Init();
void Renderer_Clear();
void Renderer_DrawSprite(const char* texture, int w, int h, int x, int y);
void Renderer_DrawText(char* text, int x, int y);
void Renderer_DrawTextEX(char_t* text, int len, int x, int y);
void Renderer_DrawGame();
void Renderer_Present();
void Renderer_FillScreen(char character, uint8_t color);
void Renderer_ShutDown();

void Renderer_ScreenToWorld(int x, int y, int* outx, int* outy);
void Renderer_WorldToSCreen(int x, int y, int* outx, int* outy);

void Renderer_SetPixel(int x, int y, char_t character);

bool Window_IsOpen();
void Window_PollEvents();
#endif