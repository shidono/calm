#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
int main(int argc, char **argv){
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *fenetre=NULL;
  fenetre=SDL_SetVideoMode(500,500,32,SDL_HWSURFACE);
  while(1){}
  SDL_FreeSurface(fenetre);
  SDL_Quit();
 return 0;
}
