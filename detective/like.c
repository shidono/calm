#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
int main(void){
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Surface *detective;
    SDL_Rect positionecran;
    char pause;
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    screen = SDL_SetVideoMode(600, 400, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL){
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return -1;
    }
    image = SDL_LoadBMP("background.bmp");
    if(image == NULL){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    detective = IMG_Load("character.png");
    if(detective == NULL){
	printf("unable to load character : %s\n", SDL_GetError());
	return 1;
    }
    positionecran.x = 0;
    positionecran.y = 0;
    positionecran.w = image->w;
    positionecran.h = image->h;
    
    int done = 1;
    while(done){
	SDL_BlitSurface(image,NULL,screen,&positionecran);
        SDL_BlitSurface(detective,NULL,screen,&positionecran);
	SDL_Flip(screen);
    }
    SDL_FreeSurface(image);
    SDL_FreeSurface(detective);
    pause = getchar();
    return 0;
}
