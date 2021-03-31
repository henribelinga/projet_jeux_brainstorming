#include "background.h"

void init_back(background *b)
{
b->cam.x=0;
b->cam.y=-80;
b->cam.w=1000;
b->cam.h=600;
b->x_relative=0;
b->y_relative=-80;
b->bg=NULL;
b->mask=IMG_Load("oumou.jpg");
b->bg=IMG_Load("oumou_final.jpg");
}

void affichage_back(SDL_Surface *ecran,background *b)
{
SDL_BlitSurface(b->bg,&b->cam,ecran,NULL);
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
		b->cam.x-=p->speedX;
    p->rect_relative.x-=p->speedX;

	}
}
