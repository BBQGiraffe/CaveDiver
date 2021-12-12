#include "char.h"

char_t* Char_ColorizeString(const char* string, uint8_t color, int* len)
{
    *len = strlen(string);
    char_t* out = malloc(*len * 2);

    for(int i = 0; i < *len; i++)
    {
        out[i] = (char_t){.character = string[i], .color = color};
    }
    return out;
}