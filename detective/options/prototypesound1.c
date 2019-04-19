#include <stdio.h>
#include "/usr/include/SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_events.h"
#include "/usr/include/SDL/SDL_mouse.h"
int main(void){
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Surface *low_volume,*medium_volume,*high_volume,*soundd,*soundi,*currentvolume;
    SDL_Rect positionecran,positionlow_volume,positionsoundd,positionsoundi;
    SDL_Event event;
    Mix_Music *music;
    Uint8 p;
    Mix_Chunk *buttonsound = NULL;
    int x,y;
    char pause;
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    screen = SDL_SetVideoMode(1024, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL){
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return -1;
    }
    image = IMG_Load("/home/shidono/Desktop/game/options/background.png");
    if(image == NULL){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    low_volume = IMG_Load("/home/shidono/Desktop/game/options/volume/low volume.png");
    if(low_volume == NULL){
	printf("unable to load character : %s\n", SDL_GetError());
	return 1;
    }
    medium_volume = IMG_Load("/home/shidono/Desktop/game/options/volume/medium volume.png");
    if(medium_volume == NULL){
	printf("unable to load character : %s\n", SDL_GetError());
	return 1;
    }
    high_volume = IMG_Load("/home/shidono/Desktop/game/options/volume/high volume.png");
    if(high_volume == NULL){
	printf("unable to load character : %s\n", SDL_GetError());
	return 1;
    }
    soundd = IMG_Load("/home/shidono/Desktop/game/options/volume/+.png");
    if(soundd == NULL){
	printf("unable to load character : %s\n", SDL_GetError());
	return 1;
    }
    soundi = IMG_Load("/home/shidono/Desktop/game/options/volume/-.png");
    if(soundi == NULL){
	printf("unable to load character : %s\n", SDL_GetError());
	return 1;
    }
    positionecran.x = 0;
    positionecran.y = 0;
    positionecran.w = image->w;
    positionecran.h = image->h;
    positionlow_volume.x = 500;
    positionlow_volume.y = 250;
    positionsoundd.x = 605;
    positionsoundd.y = 265;
    positionsoundi.x = 605;
    positionsoundi.y = 302;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) == -1){
    	printf("%s",Mix_GetError());
    }
    currentvolume = low_volume;
    while(1){
	SDL_BlitSurface(image,NULL,screen,&positionecran);
    SDL_BlitSurface(currentvolume,NULL,screen,&positionlow_volume);
    SDL_BlitSurface(soundd,NULL,screen,&positionsoundd);
    SDL_BlitSurface(soundi,NULL,screen,&positionsoundi);
	SDL_Flip(screen);
	Uint32 colorkey = SDL_MapRGB( low_volume->format,0xFF, 0xFF, 0xFF);
	SDL_SetColorKey(low_volume,SDL_SRCCOLORKEY,colorkey);
	buttonsound = Mix_LoadWAV("/home/shidono/Desktop/game/options/volume/buttonmusic.wav");
	while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
			     	SDL_Quit();
				break;
				case SDL_MOUSEBUTTONDOWN:
					p = SDL_GetMouseState(&x,&y);
				if((x >= positionsoundd.x) && (x <= positionsoundd.x + positionsoundd.w) && ( y >= positionsoundd.y) && (y <= positionsoundd.y + positionsoundd.h) && (event.button.button == SDL_BUTTON_LEFT)){
					if(currentvolume == low_volume){
						Mix_PlayChannel(-1,buttonsound,0);
					 	currentvolume = medium_volume;
					 	Mix_Volume(1,MIX_MAX_VOLUME/2);
					 	Mix_VolumeMusic(MIX_MAX_VOLUME/2);
					 }
					 else if(currentvolume == medium_volume){
					  Mix_PlayChannel(-1,buttonsound,0);
					  currentvolume = high_volume;
					  Mix_Volume(1,MIX_MAX_VOLUME);
					  Mix_VolumeMusic(MIX_MAX_VOLUME);
					}
				}else if((x >= positionsoundi.x && x <= positionsoundd.x + positionsoundi.w) && (y >= positionsoundi.y) && (y <= positionsoundi.y + positionsoundd.h) && (event.button.button == SDL_BUTTON_LEFT)){
					if(currentvolume == high_volume){
						 Mix_PlayChannel(-1,buttonsound,0);
						 currentvolume = medium_volume;
						 Mix_Volume(1,MIX_MAX_VOLUME/2);
						 Mix_VolumeMusic(MIX_MAX_VOLUME/2);
						}else if(currentvolume == medium_volume){
						 Mix_PlayChannel(-1,buttonsound,0);
						 currentvolume = low_volume;
						 Mix_Volume(1,30);
						 Mix_VolumeMusic(30);
						}
					}
				break;
			}
		}
	}//end of message processing	
  SDL_FreeSurface(currentvolume);
  SDL_FreeSurface(soundd);
  SDL_FreeSurface(soundi);
  return 0;
}
