#ifndef __RPG_CHAR__
#define __RPG_CHAR__
#include "typedefs.h"
#include <string.h>
#include <stdlib.h>
typedef struct char_t
{
    unsigned char character;
    uint8_t color;
}char_t;

char_t* Char_ColorizeString(const char* string, uint8_t color, int* len);
#endif