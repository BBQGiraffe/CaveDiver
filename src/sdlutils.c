#include "sdlutils.h"

void SDL_PrintSDLError(const char* funcName)
{
    const char* error = SDL_GetError();
    if(strlen(error) == 0){return;}
    printf("[%s]: %s\n", funcName, error);
}