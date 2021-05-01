#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "aleatoire.h"

int main()
{
SDL_Init(SDL_INIT_VIDEO);
SDL_Surface *ecran=NULL;
screen=SDL_SetVideoMode (800,564,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_Event evenement;
SDL_Surface *background=NULL;
SDL_WM_SetCaption("personnage\t1",NULL);
bool execute=true;
int rp=0;
enigme ayoub;
en=GenEN("aleatoire.txt");
while (execute)
{
    afficherEnigme(&en,ecran);
    SDL_Flip(screen);
 while (execute)
{
    while(SDL_PollEvent(&evenement))
	{

		switch(evenement.type)
		{
		case SDL_QUIT:

			running=false;
		break;
		case SDL_KEYDOWN:
			switch (evenementt.key.keysym.sym)
			{
			
			case SDLK_1 :
				rp1=1;
      		break;
            case SDLK_2 :
                rp2=2;
            break;
            case SDLK_3:
                rp3=3;
            break;
            }
        break;
    }
afficherEnigme(&ayoub,screen);
if (rp != 0)
{
    if (rp == ayoub.solution)
    {
        execute=false;
        printf("ok");
    }else{
        execute=false;
        printf("no");
    }
    
}

            
    }
}



}







 