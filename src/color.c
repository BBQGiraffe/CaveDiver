#include "color.h"

void Color_GetColor(uint8_t index, uint8_t* r, uint8_t* g, uint8_t* b)
{
    int i = index * 3;
    *r = palette[i];
    *g = palette[i + 1];
    *b = palette[i + 2];
}

void Color_LoadPalette()
{   
    FILE* fp = fopen("assets/palette", "rt");

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        
        int r, g, b;
        sscanf(line, "%02x%02x%02x", &r, &g, &b);

        palette[i] = r;
        palette[i+1] = g;
        palette[i+2] = b;

        i += 3;


    }
    fclose(fp);
}