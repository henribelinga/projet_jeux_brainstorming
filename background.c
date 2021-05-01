#include "background.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>  
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

void initialiser_background(background *b)
{
b->cam.x=0;
b->cam.y=0;
b->cam.w=500;
b->cam.h=600;
b->posecran1.x=0;
b->posecran1.y=0;
b->posecran1.w=500;
b->posecran1.h=600;
b->camera.x=0;
b->camera.y=0;
b->camera.w=500;
b->camera.h=600;
b->posecran2.x=500;
b->posecran2.y=0;
b->posecran2.w=500;
b->posecran2.h=600;
b->x_relative=0;
b->y_relative=-80;
b->bg=NULL;
b->mask=NULL;
b->mask=IMG_Load("mask.jpg");
b->bg=IMG_Load("bg_final.jpg");
}
void afficher_background2( SDL_Surface *ecran,background * b) 
{
SDL_BlitSurface(b->bg,&b->camera,ecran,&b->posecran2);
}
void afficher_background( SDL_Surface *ecran,background * b) 
{
SDL_BlitSurface(b->bg,&b->cam,ecran,&b->posecran1);
}

void scrolling_right (background *b,perso *p,SDL_Surface *ecran)
{
	if (b->cam.x<5000)
	{
		b->cam.x+=p->speedX;
    p->rect_relative.x+=p->speedX;

	}
}

void scrolling_left (background *b,perso *p,SDL_Surface *ecran)
{
	if (b->cam.x>0)
	{
		b->cam.x-=p->speedX;// cest le mouvement du personnage selon     				l'axe des x;
    p->rect_relative.x-=p->speedX;

	}
}
