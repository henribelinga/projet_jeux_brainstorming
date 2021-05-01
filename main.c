//PARTIE AFFICHAGE DE BACKGROUND::

#include "perso.h"
#include "background.h"

#define GRAVITY 10
#define SPEED 5
#define MAX_SPEED 10
#define MAX_JUMP_SPEED 30
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>  
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

int ground=330; //480 pour les obstacles


void main()
{
SDL_Init(SDL_INIT_VIDEO);
SDL_Surface *ecran;
SDL_Surface *back;
back=IMG_Load("background.png");
ecran=SDL_SetVideoMode (1000,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

SDL_WM_SetCaption("personnage\t1",NULL);//titre de la fenetre

background b;
Input I;
perso p, p2;

SDL_Event event;
initialiser_perso(&p);
initialiser_perso(&p2);
initialiser_input(&I);
initialiser_background(&b);
bool running=true;
int keysHeld[323]={0};


SDL_EnableKeyRepeat(200,0);//pour ne pas maintenir des boutons en meme temps

        
while(running)
{


while(SDL_PollEvent(&event))
	{

		switch(event.type)
		{
		case SDL_QUIT:
		// (*action)=0;
			running=false;
		break;
		case SDL_KEYDOWN:// touche enfoncee
                        keysHeld[event.key.keysym.sym]=1;
			switch (event.key.keysym.sym)
			{
			
			case SDLK_LEFT :
				I.left=1;



      		break;
      		case SDLK_RIGHT :
				I.right=1;
				
       //action d'entrer une variable dans un programme

      		break;
			case SDLK_SPACE :
				I.jump=1;
				if(p.rect.y==ground)//collision with ground
			  p.speedY = -60; // diminution de la vitesse de mvt
			 //collision with stairs -1 au lieu de -30
			p.speedX=MAX_JUMP_SPEED;// augmentation du mouvement
			break; 
			
			}
		break;
		case SDL_KEYUP:// lorsque la touche est relachee
                          keysHeld[event.key.keysym.sym]=0;
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				I.right=0;
			break;
			case SDLK_LEFT :
				I.left=0;
      		break;
			case SDLK_SPACE :
			I.jump=0; 

			break;
			
			}
		break;
		}
	}


 if (I.right==1)
{
	p.speedX+=1;
	animation_right(&p);
	if (I.jump==0) mouvementright (&p);
	 else if (I.jump==1) jumpright (&p);
scrolling_right (&b,&p,ecran);// defilement a droite du back sur l'ecran
}
else if (I.left==1 )
{
	p.speedX-=1;
	animation_left(&p);
	if (I.jump==0)  mouvementleft (&p);
	else if (I.jump==1) jumpleft (&p);
		scrolling_left (&b,&p,ecran);

}

 p.speedY+=GRAVITY; //exercion de la gravite
 p.rect.y += p.speedY;
 p.rect_relative.y += p.speedY;
 if(p.rect.y >= ground)
 	 {
 		 p.rect.y= ground;
		 p.rect_relative.y= ground;
 		 p.speedY = 0;
}
        afficher_background2(ecran,&b);
        afficher_background(ecran,&b);
        //je dois faire le partage à ce niveau
        //afficher_perso(&p2,ecran);
	//afficher_perso(&p,ecran);
	
	SDL_Flip(ecran);
	SDL_Delay(16); // temps maximal d'execution
}






SDL_Quit();
return 0;
}


