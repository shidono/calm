#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

typedef struct{
  Uint8 type;
  Uint8 button;
  Uint8 state;
  Uint16 x, y;
} SDL_MouseButtonEvent;

int main(void){
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Surface *low_volume,*medium_volume,*high_volume,*soundd,*soundi;
    SDL_Rect positionecran,positionlow_volume,positionmedium_volume,positionhigh_volume,positionsoundd,positionsoundi;
    SDL_Event event;
    SDL_MouseButtonEvent *mouse;
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
    positionlow_volume.w = low_volume->w;
    positionlow_volume.h = low_volume->h;
    positionmedium_volume.x = 500;
    positionmedium_volume.y = 250;
    positionmedium_volume.w = medium_volume->w;
    positionmedium_volume.h = medium_volume->h;
    positionhigh_volume.x = 500;
    positionhigh_volume.y = 250;
    positionhigh_volume.w = high_volume->w;
    positionhigh_volume.h = high_volume->h;
    positionsoundd.x = 605;
    positionsoundd.y = 265;
    positionsoundd.w = soundd->w;
    positionsoundd.h = soundd->h;
    positionsoundi.x = 605;
    positionsoundi.y = 302;
    positionsoundi.w = soundi->w;
    positionsoundi.h = soundi->h;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) == -1){
    	printf("%s",Mix_GetError());
    }
    Mix_Music *music;
    music = Mix_LoadMUS("music.mp3");
    Mix_PlayMusic(music,-1);
    int done = 1;
    while(done){
	SDL_BlitSurface(image,NULL,screen,&positionecran);
    SDL_BlitSurface(low_volume,NULL,screen,&positionlow_volume);
    SDL_BlitSurface(medium_volume,NULL,screen,&positionmedium_volume);
    SDL_BlitSurface(high_volume,NULL,screen,&positionhigh_volume);
    SDL_BlitSurface(soundd,NULL,screen,&positionsoundd);
    SDL_BlitSurface(soundi,NULL,screen,&positionsoundi);
	SDL_Flip(screen);
	Uint32 colorkey = SDL_MapRGB( low_volume->format,0xFF, 0xFF, 0xFF);
	SDL_SetColorKey(low_volume,SDL_SRCCOLORKEY,colorkey);
	while(SDL_PollEvent(&event)){
	    //check for messages
			switch(event.type){
			//exit if the window is closed
				case SDL_QUIT:
			     	SDL_Quit();
				break;
			//check for keypresses
				case SDL_KEYDOWN:
				{
				//exit if ESCAPE is pressed
			    	switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
					SDL_Quit();
					}
				}
			}//end switch
	}//end of message processing
}	
  Mix_FreeMusic(music);
  SDL_FreeSurface(low_volume);
  SDL_FreeSurface(medium_volume);
  SDL_FreeSurface(high_volume);
  SDL_FreeSurface(soundd);
  SDL_FreeSurface(soundi);
  return 0;
}
