#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_events.h"
#include "/usr/include/SDL/SDL_mouse.h"
int ispushed(SDL_Event event){
    if(event.button.button == SDL_BUTTON_LEFT) return 1;
    else return 0;
}
int hover(SDL_Rect pos,int x,int y){
    Uint8 p;
    if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
    else return 0;
}
int main(void){
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Surface *ring,*bar,*unmute,*mute,*muteunmute,*cocher,*noncocher,*cocherfullscreen,*cocherwindowed;
    SDL_Rect positionecran,positionringeffect,positionringmusic,positionbareffect,positionbarmusic,positionmute,positionfullscreen,positionwindowed;
    SDL_Event event;
    Mix_Music *music;
    Mix_Chunk *buttonsound;
    int x,y;
    screen = SDL_SetVideoMode(1024, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    image = IMG_Load("/home/shidono/Desktop/game/options/background.png");
    bar = IMG_Load("/home/shidono/Desktop/game/options/volume/bar.png");
    ring = IMG_Load("/home/shidono/Desktop/game/options/volume/ring.png");
    mute = IMG_Load("/home/shidono/Desktop/game/options/volume/mute.png");
    unmute = IMG_Load("/home/shidono/Desktop/game/options/volume/unmute.png");
    cocher = IMG_Load("/home/shidono/Desktop/game/options/volume/cocher.png");
    noncocher = IMG_Load("/home/shidono/Desktop/game/options/volume/noncocher.png");
    positionecran.x = 0;
    positionecran.y = 0;
    positionecran.w = image->w;
    positionecran.h = image->h;
    positionbareffect.x = 500;
    positionbareffect.y = 250;
    positionringeffect.x = 505;
    positionringeffect.y = 250;
    positionbarmusic.x = 500;
    positionbarmusic.y = 300;
    positionringmusic.x = 500;
    positionringmusic.y = 300;
    positionmute.x = 500;
    positionmute.y = 350;
    positionfullscreen.x = 600;
    positionfullscreen.y = 450;
    positionwindowed.x = 500;
    positionwindowed.y = 450;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) == -1){
        printf("%s",Mix_GetError());
    }
    float volumemusic,volumeeffect,max=770,xfloat;
    int change = 1,changefs = 0,changewindowed = 1;
    buttonsound = Mix_LoadWAV("/home/shidono/Desktop/game/options/volume/buttonmusic.wav");
    muteunmute = unmute;
    int left;
    cocherwindowed = cocher;
    cocherfullscreen = noncocher;
    while(1){ 
    SDL_BlitSurface(image,NULL,screen,&positionecran);
    SDL_BlitSurface(bar,NULL,screen,&positionbareffect);
    SDL_BlitSurface(bar,NULL,screen,&positionbarmusic);
    SDL_BlitSurface(ring,NULL,screen,&positionringeffect);
    SDL_BlitSurface(ring,NULL,screen,&positionringmusic);
    SDL_BlitSurface(muteunmute,NULL,screen,&positionmute);
    SDL_BlitSurface(cocherfullscreen,NULL,screen,&positionfullscreen);
    SDL_BlitSurface(cocherwindowed,NULL,screen,&positionwindowed);
    SDL_Flip(screen);
    SDL_GetMouseState(&x,&y);
    if(hover(positionbareffect,x,y)){
        if((x<770 && x>500) && (event.button.button == SDL_BUTTON_LEFT)){
        positionringeffect.x = x;
        xfloat = x;
        volumeeffect = ((x-500)*128)/(770-500);        
        Mix_Volume(1,volumeeffect);
        Mix_PlayChannel(1,buttonsound,0);
        }
    }
    if(hover(positionbarmusic,x,y)){
        if((x<770 && x>500) && (event.button.button == SDL_BUTTON_LEFT)){
        positionringmusic.x = x;
        xfloat = x;
        volumemusic = ((x-500)*128)/(770-500);        
        Mix_VolumeMusic(volumemusic);
        //normally play music
        }
    }
    while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(hover(positionwindowed,x,y) && (event.button.button == SDL_BUTTON_LEFT)){
                        if(changewindowed == 0 && changefs == 1){
                            changewindowed = 1;
                            changefs = 0;
                            cocherwindowed = cocher;
                            cocherfullscreen = noncocher;
                            screen = SDL_SetVideoMode(1024, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        } 
                    }
                    if(hover(positionfullscreen,x,y) && (event.button.button == SDL_BUTTON_LEFT)){
                        if(changefs == 0 && changewindowed == 1){
                            changefs = 1;
                            changewindowed = 0;
                            cocherfullscreen = cocher;
                            cocherwindowed = noncocher;
                            screen = SDL_SetVideoMode(1366,768, 32,SDL_DOUBLEBUF^SDL_FULLSCREEN);
                        } 
                    }
                    if(hover(positionmute,x,y) && (event.button.button == SDL_BUTTON_LEFT)){
                    if(change == 1){
                        Mix_VolumeMusic(volumemusic);
                        Mix_Volume(1,volumeeffect);
                        muteunmute = mute;
                        change = 0;
                        printf("%d\n",change);
                    }else{
                        Mix_VolumeMusic(0);
                        Mix_Volume(1,0);
                        muteunmute = unmute;
                        change = 1;
                        printf("%d\n",change);
                    }
                }
            break;
        }
    }
}
  SDL_FreeSurface(image);
  SDL_FreeSurface(bar);
  SDL_FreeSurface(ring);
  return 0;
}