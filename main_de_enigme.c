#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "enigme.h"

int main()
{
SDL_Init(SDL_INIT_VIDEO);
SDL_Surface *screen=NULL;
SDL_Surface *back=NULL;
SDL_Surface *win=NULL;
SDL_Surface *loss=NULL;
win=IMG_Load("enigme1_win.png");
loss=IMG_Load("enigme1_loss.png");
screen=SDL_SetVideoMode (1200,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_Event event;
SDL_WM_SetCaption("ENIGMEALEA\t1",NULL);
bool execute=true;
int reponse=-1;
enigme e;
e=generer();
while (execute)
{
    afficherEnigme(&e,screen);
    SDL_Flip(screen);
    while(SDL_PollEvent(&event))
	{

		switch(event.type)
		{
		case SDL_QUIT:

			execute=false;
		break;
        case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			
			case SDLK_a :
				if (e.sol==1)
                {
                     reponse=1;
                    printf("vrai");
                    ////////////////
                }
                else {
                    reponse=0;
                    printf("faux");
                }
                
      		break;
            case SDLK_z :
                if (e.sol==2)
                {
                    printf("vrai");
                    reponse=1;
                }
                else {
                    printf("faux");
                    reponse=0;
                }
            break;
            case SDLK_e:
                if (e.sol==3)
                {
                    printf("vrai");
                    reponse=1;
                }
                else {
                   reponse=0;
                    printf("faux");
                }
            break;
            }
        break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.motion.x >= 30 && event.motion.x <= 303 && event.motion.y >= 300 && event.motion.y <= 438)//cad:si on clique sur boutton1
            {
                if (e.sol==1)
                {
                    printf("vrai");
                    reponse=1;
                }
                else {
                    printf("faux");
                    reponse=0;
                }
            }
            if (event.motion.x >= 420 && event.motion.x <= 693 && event.motion.y >= 300 && event.motion.y <= 438)//clique sur boutton2
            {
                if (e.sol==2)
                {
                    printf("vrai");
                    reponse=1;
                }
                else {
                    printf("faux");
                    reponse=0;
                }
            }
            if (event.motion.x >= 720 && event.motion.x <= 993 && event.motion.y >= 300 && event.motion.y <= 438)//clique sur boutton3
            {
                if (e.sol==3)
                {
                    printf("vrai");
                    reponse=1;
                }
                else {
                    printf("faux");
                    reponse=0;
                }
            }
            break;
        }
    }


if (reponse!=-1)
{
if (reponse==1)
{
   
    SDL_BlitSurface(win, NULL, screen, NULL);
    SDL_Flip(screen);

    SDL_Delay(2000);
    execute=0;
}
else  
{ 
    SDL_BlitSurface(loss, NULL, screen, NULL); /* Blit du texte */
    SDL_Flip(screen);

    SDL_Delay(2000);
    execute=0;
}
}
}




}







 
