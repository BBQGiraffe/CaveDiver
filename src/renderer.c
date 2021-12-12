#include "renderer.h"
TTF_Font* font;
SDL_Window* window;
SDL_Renderer* renderer;


char_t frameBuffer[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT] = {{' '}};

bool isOpen;


SDL_Texture* textures[255];

void Renderer_Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_PrintSDLError("Renderer_Init");

    TTF_Init();
    SDL_PrintSDLError("Renderer_Init");
    
    font = TTF_OpenFont("assets/712_serif.ttf", FONT_SIZE);
    SDL_PrintSDLError("Renderer_Init");

    window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_PrintSDLError("Renderer_Init");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_PrintSDLError("Renderer_Init");

    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    isOpen = true;

    fontHeight = TTF_FontHeight(font);

    TTF_SetFontKerning(font, 0);

    //queue all the textures bc I can
    for(unsigned char c = '!'; c <= '}'; c++)
    {
        char text[1] = {c};

        SDL_Surface* surface = TTF_RenderText_Solid(font, text, (SDL_Color){.r = 255, .g = 255, .b = 255, .a = 255});
        SDL_PrintSDLError("Renderer_DrawTextEX");

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_PrintSDLError("Renderer_DrawTextEX");

        SDL_FreeSurface(surface);

        textures[c] = texture;

    }
    TTF_CloseFont(font);
}

void Renderer_DrawSprite(const char* texture, int w, int h, int x, int y)
{

}

void Renderer_FillScreen(char character, uint8_t color)
{
    for(int x = 0; x < FRAMEBUFFER_WIDTH; x++)
    {
        for(int y = 0; y < FRAMEBUFFER_HEIGHT; y++)
        {
            frameBuffer[x][y] = (char_t){.character = character, .color = color};
        }
    }
}


void Renderer_DrawTextEX(char_t* text, int len, int x, int y)
{
    int yoff = 0;
    for(int i = 0; i < len; i++)
    {
        char_t character = text[i];

        if(character.character == '\n')
        {
            yoff += fontHeight;
            continue;
        }

        if(character.character == 32 || character.character == 0)
        {
            continue;
        }


        uint8_t r,g,b;
        Color_GetColor(character.color, &r, &g, &b);

        SDL_Texture* texture = textures[character.character];

        SDL_SetTextureColorMod(texture, r, g, b);


        SDL_Rect dest = {.x = (x + i) * FONT_SIZE, .y = (y * fontHeight) + yoff, .w = FONT_SIZE, .h = fontHeight};
        SDL_RenderCopy(renderer, texture, NULL, &dest);

    }
}

void Renderer_SetPixel(int x, int y, char_t character)
{
    if(x < 0 || x >= FRAMEBUFFER_WIDTH || y < 0 || y >= FRAMEBUFFER_HEIGHT){return;}
    frameBuffer[x][y] = character;
}

void Renderer_WorldToSCreen(int x, int y, int* outx, int* outy)
{
    *outx = x - ((cameraX) - FRAMEBUFFER_WIDTH / 2);
    *outy = y - ((cameraY) - FRAMEBUFFER_HEIGHT / 2);
}


void Renderer_ScreenToWorld(int x, int y, int* outx, int* outy)
{
    *outx = x + ((cameraX) - FRAMEBUFFER_WIDTH / 2);
    *outy = y + ((cameraY) - FRAMEBUFFER_HEIGHT / 2);
}


void Renderer_DrawText(char* text, int x, int y)
{
    int offy = 0;

    for(int i = 0; i < strlen(text); i++)
    {
        unsigned char c = text[i];
        if(c == '\n')
        {
            offy++;
            continue;
        }
        if(c == ' ' || c == 0)
        {
            continue;
        }

        SDL_Texture* texture = textures[c];
        SDL_SetTextureColorMod(texture, 255, 255, 255);
        SDL_Rect dest = {.x = (x+i) * FONT_SIZE, .y = (y+offy) * fontHeight, .w = FONT_SIZE, .h = fontHeight};
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
}

void Renderer_DrawGame()
{
    for(int x = 0; x < 32; x++)
    {
        frameBuffer[x][31] = (char_t){.character = '#', .color = x};
        frameBuffer[31][x] = (char_t){.character = '#', .color = x};
    }

}
void Renderer_Clear()
{
    // memset(frameBuffer, '.', FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT);
    Renderer_FillScreen(' ', 0);
    SDL_RenderClear(renderer);
}

void Renderer_Present()
{
    for(int x = 0; x < FRAMEBUFFER_WIDTH; x++)
    {
        for(int y = 0; y < FRAMEBUFFER_HEIGHT; y++)
        {
            // strncat(str, &frameBuffer[y][x].character, 1);
            unsigned char c = frameBuffer[x][y].character;
            uint8_t r,g,b;
            Color_GetColor(frameBuffer[x][y].color, &r, &g, &b);

            if(c == 0 || c == ' '){continue;}
            SDL_Texture* texture = textures[c];
            SDL_SetTextureColorMod(texture, r, g, b);
            SDL_Rect dest = {.x = (x) * FONT_SIZE, .y = (y) * fontHeight, .w = FONT_SIZE, .h = fontHeight};
            SDL_RenderCopy(renderer, texture, NULL, &dest);
        }
    }
    SDL_RenderPresent(renderer);
}

void Renderer_ShutDown()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    for(unsigned char c = '!'; c <= '}'; c++)
    {
        SDL_DestroyTexture(textures[c]);
    }
}

void HandleWindowEvent(SDL_Event event)
{
    switch (event.window.event)
    {
    case SDL_WINDOWEVENT_CLOSE:
        isOpen = false;
        break;
    
    default:
        break;
    }
}

void Window_PollEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT:
            HandleWindowEvent(event);
            break;
        
        default:
            break;
        }
    }
}

bool Window_IsOpen()
{
    return isOpen;
}