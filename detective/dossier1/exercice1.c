#include <stdio.h>
#include "/usr/include/SDL/SDL.h"

int main(void){
        SDL_Surface* screen = NULL;
        char pause;
        SDL_Init(SDL_INIT_EVERYTHING);
        screen = SDL_SetVideoMode(600, 400, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        if(!screen){
                printf("Unable to set 600x400 video: %s\n", SDL_GetError());
                return -1;
        }
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 0));
        SDL_Flip(screen);
        pause = getchar();
        return 0;
}


