#include "perso.h"
#define GRAVITY 9.8
#define vitesse 6
#define vitesse_max 17
#define MAX_JUMP_SPEED 20
#define MAX_SPEED 17


void init_perso (perso *p){
    int i,j;
    char nomFich[60];

    for ( i = 0; i < 10; i++)
    {
        sprintf(nomFich,"per/%d.png",i);
        p->mvtright[i]=IMG_Load(nomFich);
    }
    for ( i = 0; i < 10; i++)
    {
        sprintf(nomFich,"per/%d.png",i+10);
        p->mvtleft[i]=IMG_Load(nomFich);
    }
    for ( i = 0; i < 16; i++)
    {
        sprintf(nomFich,"per/%d.png",i+20);
        p->JPR[i]=IMG_Load(nomFich);
    }
    for ( i = 0; i < 16; i++)
    {
        sprintf(nomFich,"per/%d.png",i+35);
        p->jumpleft[i]=IMG_Load(nomFich);
    }
    for ( i = 0; i < 11; i++)
    {
        sprintf(nomFich,"per/%d.png",i+50);
        p->runright[i]=IMG_Load(nomFich);
    }
    for ( i = 0; i < 11; i++)
    {
        sprintf(nomFich,"per/%d.png",i+61);
        p->runleft[i]=IMG_Load(nomFich);
    }
    for ( i = 0; i < 9; i++)
    {
        sprintf(nomFich,"per/%d.png",i+71);
        p->die[i]=IMG_Load(nomFich);
    }
p->rect.x=0;
p->rect.y=150; 
p->rect_relative.x=0;
p->rect_relative.y=150; 
p->rect.w=138;
p->rect.h=233;
p->speedX=0;
p->speedY=0;
p->frame=p->mvtright[0];
p->fr=0;

    
}

void afficher_perso (perso *p,SDL_Surface *ecran)
{
  SDL_BlitSurface(p->frame,NULL,ecran,&p->rect);
}

void animation_right (perso *p){
if (p->speedX<7)
{
    if ((p->fr<0)||(p->fr>9))
    {
        p->fr=0;
    }
    p->fr++;
    p->frame=p->mvtright[p->fr];
    
}else{
    if (p->fr < 0 || p->fr > 11) p->fr=0;
    p->fr++;
    p->frame=p->runright[p->fr];
}

}

void animation_left (perso *p){
if (p->speedX<7)
{
    if ((p->fr<0)||(p->fr>9))
    {
        p->fr=0;
    }
    p->fr++;
    p->frame=p->mvtleft[p->fr];
    
}else{
    if (p->fr < 0 || p->fr > 11) p->fr=0;
    p->fr++;
    p->frame=p->runleft[p->fr];
}

}


void mouvementright (perso *p)
{
  
if (p->speedX=MAX_SPEED)
	p->speedX=MAX_SPEED;
if (p->rect.x<350)
{

p->rect.x+=p->speedX;
p->rect_relative.x+=p->speedX;
}
}

void mouvementleft (perso *p)
{
  
if (p->speedX=MAX_SPEED)
	p->speedX=MAX_SPEED;
if (p->rect.x<350)
{

p->rect.x-=p->speedX;
p->rect_relative.x-=p->speedX;
}
}


void JPR (perso *p) //jump right 
{

if (p->speedX>=MAX_JUMP_SPEED)
	p->speedX=MAX_JUMP_SPEED;
if (p->rect.x<350)
{
  p->speedX+=5;
p->rect.x+=p->speedX;
p->rect_relative.x+=p->speedX;
}
}

void JPL (perso *p) //jump left
{
if (p->speedX>=MAX_JUMP_SPEED)
	p->speedX=MAX_JUMP_SPEED;
if (p->rect.x>0){
p->rect.x-=p->speedX;00
p->rect_relative.x-=p->speedX;
}
}

void init_input (Input *I)
{
I->left=0;
I->right=0;
I->down=0;
I->jump=0;
I->acction=0;
}




