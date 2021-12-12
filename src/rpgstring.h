#ifndef __RPG_STRING__
#define __RPG_STRING__
#include "char.h"
typedef struct rpgstring_t
{
    char_t text;
    int len;
}rpgstring_t;
rpgstring_t String_Create(const char* text, uint8_t color);
#endif