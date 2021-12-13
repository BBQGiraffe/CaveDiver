#include "pride.h"
#include "renderer.h"
#define PRIDEFLAG_LEN 8
void Pride_DrawStrip(int x, int y, int color, int thiccness)
{
    for(int x_ = x; x_ < x+PRIDEFLAG_LEN; x_++)
    {
        for(int y_ = y; y_ < y+thiccness; y_++)
        {
            Renderer_SetPixel(x_, y_, (char_t){.character = '#', .color = color});
        }
    }
}

void Pride_DrawBiFlag(int x, int y)
{
    int top = 24;
    int middle = 20;
    int bottom = 9;

    int topbottomthiccness = 3;
    int middlethiccness = 2;

    Pride_DrawStrip(x, y, top, topbottomthiccness);
    Pride_DrawStrip(x, y+topbottomthiccness, middle, middlethiccness);
    Pride_DrawStrip(x, y+topbottomthiccness+middlethiccness, bottom, topbottomthiccness);

};

void Pride_DrawFlags()
{
    Pride_DrawBiFlag(FRAMEBUFFER_WIDTH-PRIDEFLAG_LEN, 0);
}

