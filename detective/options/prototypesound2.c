#include <stdio.h>
#include "/usr/include/SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_events.h"
#include "/usr/include/SDL/SDL_mouse.h"
int hover(SDL_Rect pos,int x,int y){
	Uint8 p;
	if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
	else return 0;
}

int main(void){
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Surface *ring,*bar;
    SDL_Rect positionecran,positionring,positionbar;
    SDL_Event event;
    Mix_Music *music;
    Mix_Chunk *buttonsound = NULL;
    int x,y;
    char pause;
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    screen = SDL_SetVideoMode(1024, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    image = IMG_Load("/home/shidono/Desktop/game/options/background.png");
    bar = IMG_Load("/home/shidono/Desktop/game/options/volume/bar.png");
    ring = IMG_Load("/home/shidono/Desktop/game/options/volume/ring.png");
    positionecran.x = 0;
    positionecran.y = 0;
    positionecran.w = image->w;
    positionecran.h = image->h;
    positionbar.x = 500;
    positionbar.y = 250;
    positionring.x = 505;
    positionring.y = 250;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) == -1){
    	printf("%s",Mix_GetError());
    }
    int volume = 0;
    while(1){
	SDL_BlitSurface(image,NULL,screen,&positionecran);
    SDL_BlitSurface(bar,NULL,screen,&positionbar);
    SDL_BlitSurface(ring,NULL,screen,&positionring);
	SDL_Flip(screen);
    
	buttonsound = Mix_LoadWAV("/home/shidono/Desktop/game/options/volume/buttonmusic.wav");
	while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
			     	SDL_Quit();
				break;
				case SDL_MOUSEBUTTONDOWN: 
                        SDL_GetMouseState(&x,&y);
        				if((hover(positionring,x-26,y) == 1) && (event.button.button == SDL_BUTTON_LEFT) && (positionring.x < 760)){
        						Mix_PlayChannel(-1,buttonsound,0);
        					 	positionring.x = positionring.x + 26;
                                volume = volume + 10;
        					 	Mix_VolumeChunk(buttonsound,volume);
        				}else if((hover(positionring,x+26,y) == 1) && (event.button.button == SDL_BUTTON_LEFT) && (positionring.x > 510)){
        						 Mix_PlayChannel(-1,buttonsound,0);
                                 positionring.x = positionring.x - 26;
                                 volume = volume - 10;
                                 Mix_VolumeChunk(buttonsound,volume);
        					}
				break;
			}
		}
	}

  return 0;
}
