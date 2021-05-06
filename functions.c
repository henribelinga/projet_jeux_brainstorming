#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_rotozoom.h>
#include<math.h>
#include<time.h>
#include <SDL/SDL_ttf.h>
#include "functions.h"
#define E 2.71828182845904523
perso initialiser_background(perso p)
{
    p.background[0]=IMG_Load("map1.png");//background
    p.bg.x=0;
    p.bg.w=p.background[0]->w;		//position de background
    p.bg.y=0;
    p.background[1]=IMG_Load("mask.png");//le mask pour la collision avec le background
    p.background[2]=IMG_Load("black.jpg");//black screen
    return p;
}
perso gestion_vie_et_score(perso p,int health,int score)
{
    int hp=health;
    if(hp>0)
    {
        if(p.hp[0]+hp<100)
            p.hp[0]=p.hp[0]+hp;
        else
        {
            p.hp[1]=p.hp[1]+p.hp[0]+hp-100;
            p.hp[0]=100;
        }
    }
    else
    {
        while((p.hp[1]>0)&&(hp!=0))
        {
            p.hp[1]--;
            hp++;
        }
        p.hp[0]+=hp;
    }
//si le hp ajoute avec le hp[0] du perso est inferieur à 100 le hp[0] du perso recoit son hp[0] plus le hp ajouté sinon on met hp superieur à 100 dans le hp[1](barriere)
    p.score[0]=p.score[0]+score;
//le score augmente
    return p;
}
void afficher_personnage(SDL_Surface *screen,perso p,unsigned int time)
{
    char t[12];
    SDL_Surface *text=NULL;
    TTF_Font *font;
    font=TTF_OpenFont("Blanka-Regular.ttf", 40);
    SDL_Color color= {255,255,255};
//on met le temps dans la variable t
    sprintf(t,"%d%s%d%s%d ",time/3600,":",time%3600 /60,":",time%60);
    text=TTF_RenderText_Blended(font,t,color);
    char score[5];
    sprintf(score,"%d",p.score[0]);
    SDL_Rect pos;
    int i=p.score[0];
    pos.x=1220;
    pos.y=20;
//affichage du temps
    SDL_BlitSurface(text,NULL,screen,&pos);
    text=TTF_RenderText_Blended(font,score,color);
    pos.x=1865;
    pos.y=60;
    while(i/10>0)
    {
        i=i/10;
        pos.x-=10;
    }
//affichage du score
    SDL_BlitSurface(text,NULL,screen,&pos);
    Uint32 couleur = SDL_MapRGB(screen->format,0,255,255);
    pos.x=30;
    pos.y=30;
    pos.h=20;
    pos.w=10;
//affichage des points de barriere
    for(i=0; i<p.hp[1]*2/3; i++)
    {
        if(i%2==0)
        {
            SDL_FillRect(screen,&pos,couleur);
            pos.x+=6;
        }
        pos.x+=4;
    }
//affichage des points de vie
    couleur = SDL_MapRGB(screen->format,252,0,0);
    pos.x=30;
    pos.y+=40;
    for(i=0; i<p.hp[0]*2/3; i++)
    {
        if(i%2==0)
        {
            SDL_FillRect(screen,&pos,couleur);
            pos.x+=6;
        }
        pos.x+=4;
    }
//affichage du nombre de vies
    couleur = SDL_MapRGB(screen->format,9,255,0);
    pos.x=1860;
    pos.y=20;
    pos.w=40;
    pos.h=10;
    for(i=0; i<p.score[1]; i++)
    {
        SDL_FillRect(screen,&pos,couleur);
        pos.y+=14;
    }
SDL_FreeSurface(text);
text=NULL;
TTF_CloseFont(font);
font=NULL;
}
void afficher_personnage_multiplayer(SDL_Surface *screen,perso p,unsigned int time)
{
//meme principe que l affichage mais on a changé les positions de l affichage
    char t[12];
    SDL_Surface *text=NULL;
    SDL_Color color= {255,255,255};
    TTF_Font *font;
    font=TTF_OpenFont("Blanka-Regular.ttf", 40);
    sprintf(t,"%d%s%d%s%d ",time/3600,":",time%3600 /60,":",time%60);
    text=TTF_RenderText_Blended(font,t,color);
    char score[5];
    sprintf(score,"%d",p.score[0]);
    SDL_Rect pos;
    int i=p.score[0];
    pos.x=-500+960*p.number;
    pos.y=20;
    SDL_BlitSurface(text,NULL,screen,&pos);
    text=TTF_RenderText_Blended(font,score,color);
    pos.x=-45+960*p.number;
    pos.y=60;
    while(i/10>0)
    {
        i=i/10;
        pos.x-=10;
    }
    SDL_BlitSurface(text,NULL,screen,&pos);
    Uint32 couleur = SDL_MapRGB(screen->format,0,255,255);
    pos.x=-930+960*p.number;
    pos.y=30;
    pos.h=20;
    pos.w=10;
    for(i=0; i<p.hp[1]*2/3; i++)
    {
        if(i%2==0)
        {
            SDL_FillRect(screen,&pos,couleur);
            pos.x+=6;
        }
        pos.x+=4;
    }
    couleur = SDL_MapRGB(screen->format,252,0,0);
    pos.x=-930+960*p.number;
    pos.y+=40;
    for(i=0; i<p.hp[0]*2/3; i++)
    {
        if(i%2==0)
        {
            SDL_FillRect(screen,&pos,couleur);
            pos.x+=6;
        }
        pos.x+=4;
    }
    couleur = SDL_MapRGB(screen->format,9,255,0);
    pos.x=-40+960*p.number;
    pos.y=20;
    pos.w=40;
    pos.h=10;
    for(i=0; i<p.score[1]; i++)
    {
        SDL_FillRect(screen,&pos,couleur);
        pos.y+=14;
    }
SDL_FreeSurface(text);
text=NULL;
TTF_CloseFont(font);
font=NULL;
}
unsigned int compteur(int *exit,int exit_time)
{
//
    unsigned int lastTime = 0, currentTime;
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 1000)
    {
        lastTime = currentTime;
    }
    if (currentTime>exit_time*1000)
        (*exit)=1;
    return currentTime;
}

int bounding_box(SDL_Rect t1,SDL_Rect t2)
{
    if ((t1.x>t2.x)&&(t1.x<t2.x+t2.w)&&(t1.y>t2.y)&&(t1.y<t2.y+t2.h))
        return 1;
    if ((t1.x+t1.w>t2.x)&&(t1.x+t1.w<t2.x+t2.w)&&(t1.y>t2.y)&&(t1.y<t2.y+t2.h))
        return 1;
    if ((t1.x+t1.w>t2.x)&&(t1.x+t1.w<t2.x+t2.w)&&(t1.y+t1.h>t2.y)&&(t1.y+t1.h<t2.y+t2.h))
        return 1;
    if ((t1.x>t2.x)&&(t1.x<t2.x+t2.w)&&(t1.y+t1.h>t2.y)&&(t1.y+t1.h<t2.y+t2.h))
        return 1;
    return 0;
}
ea deplacement_aleatoire(ea b)
{
    float x;
    x=b.pos.x;
    x=x/125 -5.65;
    b.pos.y=8*((pow(E,x)+pow(E,-x))/2);
    if(b.pos.x%200==0)
        b.d=rand()%2;
    if(b.d==0)
    {
        if(b.pos.x+b.pos.w<1400)
            b.pos.x=b.pos.x+b.speed;
        else
            b.d=1;
    }
    if(b.d==1)
    {
        if(b.pos.x>40)
            b.pos.x=b.pos.x-b.speed;
        else
            b.d=0;
    }
    return b;
}
ea initialisation_ea(ea b)
{
    b.speed=5;
    b.pos.x=50;
    b.pos.y=100;
    b.image[0][0]=IMG_Load("blackfrog/1.png");
    b.image[0][1]=IMG_Load("blackfrog/2.png");
    b.image[0][2]=IMG_Load("blackfrog/3.png");
    b.image[0][3]=IMG_Load("blackfrog/4.png");
    b.image[0][4]=IMG_Load("blackfrog/5.png");
    b.image[1][0]=IMG_Load("blackfrog/1.png");
    b.image[1][1]=IMG_Load("blackfrog/2.png");
    b.image[1][2]=IMG_Load("blackfrog/3.png");
    b.image[1][3]=IMG_Load("blackfrog/4.png");
    b.image[1][4]=IMG_Load("blackfrog/5.png");
    b.pos.w=b.image[0][0]->w;
    b.pos.h=b.image[0][0]->h;
    b.num_animation=0;
    b.d=0;
    b.d1=0;
    b.num=0;
    b.animation_speed=8;
    return b;
}
ea animation_ea(ea b)
{
    if(b.pos.x%(b.animation_speed*5)<2)
        if(b.num_animation==4)
            b.num_animation=0;
        else
            b.num_animation++;
    return b;
}
int collision_trigo(SDL_Rect t1,SDL_Rect t2)
{
    int d1,d2,x1,x2,y1,y2,r1,r2;
    y1=(t1.h)/2;
    x1=(t1.w)/2;
    y2=(t2.h)/2;
    x2=(t2.w)/2;
    if(y1>x1)
        r1=y1;
    else
        r1=x1;
    if(y2>x2)
        r2=y2;
    else
        r2=x2;
    d1=sqrt((t1.x+x1-t2.x-x2)*(t1.x+x1-t2.x-x2)+(t1.y+y2-t2.y-y2)*(t1.y+y2-t2.y-y2));
    d2=r1+r2;
    if(d1<d2)
        return 1;
    return 0;
}
perso speed_control(perso p)
{
    if(SDL_GetModState() & p.k.sprinting)
        {if(p.speed<10) p.speed++;}
    else
        {if(p.speed>5) p.speed--;}
    return p;
}
perso jump_trigger(perso p)
{
    if ((SDL_GetModState() & p.k.jumping)&&(ground_test(p.background[1],p)==1))
        p.jump=1;
    return p;
}

perso mouvementv2(perso p,int *should_move,int *exit)
{
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if(keystate[p.k.move_left]==1)
        p.direction=1;
    if(keystate[p.k.move_right]==1)
        p.direction=0;
    if(keystate[SDLK_ESCAPE]==1)
        (*exit)=1;
    if((keystate[p.k.move_left]!=1)&&(keystate[p.k.move_right]!=1))
        (*should_move)=0;
    else(*should_move)=1;
    return p;
}
int test_scrolling(perso p)
{
    if(p.direction==0)
    {
        if ((p.pos.x<820)&&(p.bg.x+p.bg.w>1440))
            return 1;
        else if(p.bg.x+p.bg.w>-0)
            return 2;
        else if(p.pos.x+p.pos.w<1400)
            return 0;
    }
    else if(p.direction==1)
    {
        if ((p.pos.x>600)&&(p.bg.x<-10))
            return 1;
        else if(p.bg.x<-10)
            return 2;
        else if(p.pos.x>10)
            return 0;
    }
    return 0;
}
perso scrolling_background(perso p)
{
    if(color_test(p.background[1],p)==0)
        if(p.direction==0)
        {
            if ((p.pos.x<820)&&(p.bg.x+p.bg.w>1440))
            {
                p.pos.x=p.pos.x+p.speed;
                p.bg.x=p.bg.x-p.speed;
                p.pos_absolue=-p.speed;
            }
            else if(p.bg.x+p.bg.w>1920)
            {
                p.bg.x=p.bg.x-(2*p.speed);
                p.pos_absolue=-(2*p.speed);
            }
            else if(p.pos.x+p.pos.w<1920)
                p.pos.x=p.pos.x+(2*p.speed);
        }
    if(color_test(p.background[1],p)==0)
        if(p.direction==1)
        {
            if ((p.pos.x>600)&&(p.bg.x<-10))
            {
                p.pos.x=p.pos.x-p.speed;
                p.bg.x=p.bg.x+p.speed;
                p.pos_absolue=p.speed;
            }
            else if(p.bg.x<-11)
            {
                p.bg.x=p.bg.x+(2*p.speed);
                p.pos_absolue=(2*p.speed);
            }
            else if(p.pos.x>20)
                p.pos.x=p.pos.x-(2*p.speed);
        }
    return p;
}
perso scrolling_background_multiplayer(perso p)
{
    if(color_test(p.background[1],p)==0)
        if(p.direction==0)
        {
            if ((p.pos.x<410*(p.number-1))&&(p.bg.x+p.bg.w>1440))
            {
                p.pos.x=p.pos.x+p.speed;
                p.bg.x=p.bg.x-p.speed;
                p.pos_absolue=-p.speed;
            }
            else if(p.bg.x+p.bg.w>960)
            {
                p.bg.x=p.bg.x-(2*p.speed);
                p.pos_absolue=-(2*p.speed);
            }
            else if(p.pos.x+p.pos.w<960)
                p.pos.x=p.pos.x+(2*p.speed);
        }
    if(color_test(p.background[1],p)==0)
        if(p.direction==1)
        {
            if ((p.pos.x>410)&&(p.bg.x<-10))
            {
                p.pos.x=p.pos.x-p.speed;
                p.bg.x=p.bg.x+p.speed;
                p.pos_absolue=p.speed;
            }
            else if(p.bg.x<-11)
            {
                p.bg.x=p.bg.x+(2*p.speed);
                p.pos_absolue=(2*p.speed);
            }
            else if(p.pos.x>20)
                p.pos.x=p.pos.x-(2*p.speed);
        }
    return p;
}


void affichage_entites_secondaires(test t[8],SDL_Surface *ecran)
{
    int i;
    for(i=0; i<3; i++)
        if(t[i].num>-1)
            SDL_BlitSurface(t[i].image[t[i].d],&t[i].crop, ecran, &t[i].pos);
}
void affichage_entites_secondaires_multiplayer(test t[8],SDL_Surface *ecran,int n)
{
    int i;
    for(i=0; i<3; i++)
        if(t[i].num>-1)if(t[i].pos.x+50<n)
            SDL_BlitSurface(t[i].image[t[i].d],&t[i].crop, ecran, &t[i].pos);
}
void initialisation_e_s(test t[8])
{
    int i;
    for(i=0; i<3; i++)
    {
        t[i].num=1;
        t[i].speed=5;
        t[i].triggered=0;
        t[i].image[1]=IMG_Load("entite/monster left.png");
        t[i].image[0]=IMG_Load("entite/monster right.png");
        t[i].xmin=1200+(500*i);
        t[i].xmax=1500+(500*i);
        t[i].pos.w=t[i].image[0]->w/4;
        t[i].pos.h=t[i].image[0]->h;
        t[i].pos.x=t[i].xmin;
        t[i].pos.y=600;
        t[i].d=0;
	t[i].crop.w=t[i].image[0]->w/4;
	t[i].crop.h=t[i].image[0]->h;
	t[i].crop.y=0;
    }
}
void initialisation_e_s_p2(test t[8])
{
    int i;
    for(i=0; i<3; i++)
    {
        t[i].num=1;
        t[i].speed=5;
        t[i].triggered=0;
        t[i].image[1]=IMG_Load("entite/monster left.png");
        t[i].image[0]=IMG_Load("entite/monster right.png");
        t[i].xmin=2160+(500*i);
        t[i].xmax=2460+(500*i);
        t[i].pos.w=t[i].image[0]->w/4;
        t[i].pos.h=t[i].image[0]->h;
        t[i].pos.x=t[i].xmin;
        t[i].pos.y=600;
        t[i].d=0;
	t[i].crop.w=t[i].image[0]->w;
	t[i].crop.h=t[i].image[0]->h;
	t[i].crop.y=0;
    }
}
void gestion_pos_e_s(test t[8],perso p)
{
    int i;
    for(i=0; i<3; i++)
        if(t[i].triggered==0)
        {
            if(t[i].d==0)
            {
                if(t[i].pos.x+t[i].pos.w<t[i].xmax)
                    t[i].pos.x=t[i].pos.x+t[i].speed;
                else
                    t[i].d=1;
            }
            if(t[i].d==1)
            {
                if(t[i].pos.x>t[i].xmin)
                    t[i].pos.x=t[i].pos.x-t[i].speed;
                else
                    t[i].d=0;
            }
        }
}
void animation_e_s(test t[8])
{int i;SDL_Rect crop;
    for(i=0; i<3; i++)
{if(t[i].num>-1){if(t[i].num<3) t[i].num++;else t[i].num=0;}
t[i].crop.x=t[i].num*t[i].crop.w;}
}
perso animate_initialisation(perso p)
{
    int i;
    char name[40];
    for(i=1; i<5; i++)
    {
        sprintf(name,"%s%d%s","char/movement/right/s",i,".png");
        p.p[0][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/movement/left/s",i,".png");
        p.p[1][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/movement/right/s",i,".png");
        p.p[2][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/movement/left/s",i,".png");
        p.p[3][i-1]=IMG_Load(name);
    }
    return p;
}
perso animate_animation(perso p)
{
    if(p.direction==p.previous_direction)
    {
        if(p.num!=3)
            p.num++;
        else
            p.num=0;
    }
    else
        p.num=0;
    p.previous_direction=p.direction;
    return p;
}
void animate_blit(perso p,SDL_Surface *ecran)
{if(p.number!=3)p.pos.x+=(p.number-1)*960;
    if(p.speed==5)
        SDL_BlitSurface(p.p[p.direction][p.num], NULL, ecran, &p.pos);
    else
    {
        SDL_BlitSurface(p.p[2+p.direction][p.num], NULL, ecran, &p.pos);
    }
}
perso initialisation_personnage(perso p)
{
    p.bg.x=0;
    p.hp[0]=100;
    p.hp[1]=20;
    p.score[0]=0;
    p.pos.x=360+960*p.number;
    p.pos.y=200;
    p.pos.w=p.p[0][0]->w;
    p.pos.h=p.p[0][0]->h;
    p.direction=0;
    p.previous_direction=0;
    p.num=0;
    p.pos_absolue=0;
    p.next=100;
    p.jump=0;
    p.speed=5;
    p.done=0;
    p.s.e_d=0;
    p.s.r_s=0;
    p.s.l_r=3;
    p.done=0;
    return p;
}
perso gestion_position_absolue(perso p)
{
    p.pos.x=p.pos.x+p.pos_absolue;
    return p;
}
void gestion_position_absolue_e_s(test t[8],perso p)
{
    int i;
    for(i=0; i<3; i++)
    {
        t[i].xmin+=p.pos_absolue*test_scrolling(p);
        t[i].xmax+=p.pos_absolue*test_scrolling(p);
    }
    p.pos_absolue=0;
}

void affichage_background(perso p,SDL_Surface *ecran)
{SDL_Rect crop;crop.x=0;crop.y=0;crop.w=p.number*960-p.bg.x;crop.h=2000;
    //if(p.speed==5) SDL_SetAlpha(p.background[0],SDL_SRCALPHA,255);
//else SDL_SetAlpha(p.background[0],SDL_SRCALPHA,150);
    if(p.number!=3) {p.bg.x+=960*(p.number-1);SDL_BlitSurface(p.background[0],&crop,ecran, &p.bg);}
else SDL_BlitSurface(p.background[0],NULL,ecran, &p.bg);
}
void affichage_ea(ea b,SDL_Surface *ecran)
{
    SDL_BlitSurface(b.image[b.d][b.num_animation], NULL, ecran, &b.pos);
}
void affichage(perso p,SDL_Surface *ecran,test tab[8],ea b[5],unsigned int time)
{
    affichage_ea(b[0],ecran);
    affichage_ea(b[1],ecran);
    affichage_entites_secondaires(tab,ecran);
    afficher_personnage(ecran,p,time);
}
void affichage_multiplayer(perso p,SDL_Surface *ecran,test tab[8],ea b[5],unsigned int time)
{
    affichage_ea(b[0],ecran);
    affichage_ea(b[1],ecran);
    affichage_entites_secondaires_multiplayer(tab,ecran,960*p.number);
    afficher_personnage_multiplayer(ecran,p,time);
}
void afficher_temps_with_ticks(SDL_Surface *ecran,unsigned int time,int finish)
{
    float x=time;
    x=x/(finish*1000) *1920;
    int k;//1440=screen_width
    SDL_Rect pos;
    pos.x=0;
    pos.y=20;
    pos.h=10;
    k=round(x);
    int n;
    n= 1920/finish;
    if(k % n==2)
        pos.w=k;
    else
        pos.w=k/n *n;//144=screen_width/10;
    Uint32 couleur = SDL_MapRGB(ecran->format,255,255,255);
    SDL_FillRect(ecran,&pos,couleur);
}

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
    SDL_Color color;
    Uint32 col=0;
    char* pPosition=(char* ) pSurface->pixels;
    pPosition+= (pSurface->pitch * y);
    pPosition+= (pSurface->format->BytesPerPixel *x);
    memcpy(&col,pPosition,pSurface->format->BytesPerPixel);
    SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
    return (color);
}
int color_test(SDL_Surface *pSurface,perso p)
{
    SDL_Color color;
    SDL_Rect pos[6];
    int i;
    pos[0].x=p.pos.x+p.pos.w-20;
    pos[0].y=p.pos.y+p.pos.h-50;
    pos[1].x=p.pos.x+20;
    pos[1].y=p.pos.y+p.pos.h-50;
   // pos[4].x=p.pos.x+10;
    //pos[4].y=p.pos.y+63;
    for(i=0; i<2; i++)
    {
        color=GetPixel(pSurface,pos[i].x-p.bg.x,pos[i].y-p.bg.y);
        if((color.r==0)&&(color.g==0)&&(color.b==0))
            return 1;
    }
    return 0;
}
int ground_test(SDL_Surface *pSurface,perso p)
{
    SDL_Color color;
    color=GetPixel(pSurface,p.pos.x-p.bg.x+10,p.pos.y+p.pos.h-35-p.bg.y);
    if((color.r==0)&&(color.g==0)&&(color.b==0))
        return 1;
    color=GetPixel(pSurface,p.pos.x+p.pos.w-10-p.bg.x,p.pos.y+p.pos.h-35-p.bg.y);
    if((color.r==0)&&(color.g==0)&&(color.b==0))
        return 1;
    /*color=GetPixel(pSurface,p.pos.x+(p.pos.w/2)-p.bg.x,p.pos.y+p.pos.h-35-p.bg.y);
    if((color.r==0)&&(color.g==0)&&(color.b==0))
        return 1;
    */return 0;
}
int roof_test(SDL_Surface *pSurface,perso p)
{
    SDL_Color color;
    color=GetPixel(pSurface,p.pos.x+25-p.bg.x,p.pos.y+20-p.bg.y);
    if((color.r==0)&&(color.g==0)&&(color.b==0))
        return 1;
    color=GetPixel(pSurface,p.pos.x+86-p.bg.x,p.pos.y+20-p.bg.y);
    if((color.r==0)&&(color.g==0)&&(color.b==0))
        return 1;
    return 0;
}
perso mouvement_souris_initialiser(perso p,Sint32 x)
{
    p.next=x-40;
    return p;
}

perso mouvement_souris(SDL_Surface *ecran,perso p,int *souris)
{
    if((p.pos.x-p.next>10)||((p.next-p.pos.x>10)))
    {
        if(p.pos.x<p.next)
        {
            p.next=p.next-5*test_scrolling(p)*(p.speed/5);
            p.direction=0;
        }
        else if(p.pos.x>p.next)
        {
            p.next=p.next+5*test_scrolling(p)*(p.speed/5);
            p.direction=1;
        }
        p=scrolling_background(p);
        p=animate_animation(p);
        SDL_Flip(ecran);
    }
    else(*souris)=0;
    return p;
}
void enigme_taktak(enigme t[20])
{
    enigme t1[20];
    int i;
    for(i=0; i<20; i++)
        t1[i].type=1;
    generate_enigmes(t1);
    for(i=0; i<20; i++)
        t[i]=t1[i];
}
void enigme_taktak_multiplayer(enigme t[20])
{
    enigme t1[20];
    int i;
    for(i=0; i<20; i++)
        {t1[i].type=1;t[i].used=0;}
    generate_enigmes_multiplayer(t1);
    for(i=0; i<20; i++)
        t[i]=t1[i];
}
void generation_auto_reponses_multiplayer(enigme t[20])
{
    int i=0,a,b,random;
    char ch[20];
    srand(time(NULL));
    TTF_Init();
    TTF_Font *fontanswer = NULL;
    SDL_Color textColor = {255,255,255};
    fontanswer = TTF_OpenFont("Orbitron Light.ttf",20);
    while(i<19)
    {
        if(t[i].type!=0)
        {
            random=rand()%4;
            a=t[i].correct/1000;
            b=t[i].correct%1000;
            t[i].correct=random;
            if(t[i].type==1)
                sprintf(ch,"%d",a+b);
            if(t[i].type==2)
                sprintf(ch,"%d",a-b);
            t[i].answers[random]=TTF_RenderText_Blended(fontanswer,ch,textColor);
        }
        i++;
    }
TTF_CloseFont(fontanswer);
fontanswer=NULL;
}
int afficherenigme_multiplayer(int n,SDL_Surface *screen,enigme t[20])
{
    int i=0,j;
    while((t[i].used==1)&&(i<20))
        i++;
    if(t[i].question==NULL)
    {
initialiser_enigme_multiplayer(t);generate_enigmes_multiplayer(t);i=0;cha9_cha9(t);
    }

t[i].pos.y=0;t[i].pos.x=0;
    t[i].pos.y+=270;t[i].pos.x+=960*n;
    SDL_BlitSurface(t[i].background, NULL, screen, &t[i].pos);
    t[i].pos.x=t[i].pos.x+180;
    t[i].pos.y=t[i].pos.y+130;
    SDL_BlitSurface(t[i].question, NULL, screen, &t[i].pos);
    t[i].pos.x-=10;
    t[i].pos.y+=30;
    for(j=0; j<4; j++)
    {
        t[i].pos.y+=50;
        SDL_BlitSurface(t[i].answers[j], NULL, screen, &t[i].pos);
        SDL_Flip(screen);
    }
    t[i].pos.x=0;
    t[i].pos.y=0;
    return i;
}

int afficherenigme(SDL_Surface *screen,enigme t[20])
{
    int i=0,j;
    while((t[i].used==1)&&(i<20))
        i++;
    if(t[i].question==NULL)
    {
        enigme_taktak(t);
        generation_auto_reponses(t);
        i=0;
        while((t[i].used==1)&&(i<20))
            i++;
    }
    SDL_BlitSurface(t[i].background, NULL, screen, &t[i].pos);
    t[i].pos.x=t[i].pos.x+400;
    t[i].pos.y=t[i].pos.y+300;
    SDL_BlitSurface(t[i].question, NULL, screen, &t[i].pos);
    SDL_Delay(250);
    t[i].pos.y=t[i].pos.y+70;
    for(j=0; j<4; j++)
    {
        t[i].pos.y=t[i].pos.y+80;
        SDL_BlitSurface(t[i].answers[j], NULL, screen, &t[i].pos);
        SDL_Flip(screen);
    }
    t[i].pos.x=0;
    t[i].pos.y=0;
    return i;
}
void initialiser_enigme(enigme t[20])
{
    int i,j,k;
    char line[64],question[64];
    FILE *file = NULL;
    TTF_Init();
    TTF_Font *fontquestion = NULL;
    TTF_Font *fontanswer = NULL;
    SDL_Color textColor = {255,255,255};
    fontquestion = TTF_OpenFont("Blanka-Regular.ttf", 60);
    fontanswer = TTF_OpenFont("Orbitron Light.ttf", 40);
    for(i=0; i<10; i++)
    {
        t[i].correct=0;
        t[i].pos.x=0;
        t[i].pos.y=0;
        t[i].used=0;
        t[i].type=0;
        t[i].background=NULL;
        t[i].background=IMG_Load("backenigme.png");
        t[i].question=NULL;
        file=fopen("question.txt","r");
        for(j=0; j<i+1; j++)
            fgets(line,sizeof(line), file);
        sprintf(question,"%s",line);
        t[i].question=TTF_RenderText_Blended(fontquestion,line,textColor);
        fclose(file);
        file=fopen("answer.txt","r");
        for(j=0; j<i+1; j++)
            for(k=0; k<4; k++)
            {
                fgets(line,sizeof(line), file);
                sprintf(question,"%s",line);
                t[i].answers[k]=TTF_RenderText_Blended(fontanswer,question,textColor);
            }
    }
TTF_CloseFont(fontanswer);
fontanswer=NULL;
TTF_CloseFont(fontquestion);
fontquestion=NULL;
}
void correct_enigme(SDL_Surface *ecran)
{SDL_Surface *image;
sound_effect("music/enigme resolved.wav",120);
	image=IMG_Load("correct.png");
        SDL_BlitSurface(image, NULL,ecran, NULL);
        SDL_Flip(ecran);
	SDL_Delay(1000);
SDL_FreeSurface(image);
image=NULL;
}
void wrong_enigme(SDL_Surface *ecran)
{SDL_Surface *image;
sound_effect("music/enigme failed.wav",120);
	image=IMG_Load("wrong.png");
        SDL_BlitSurface(image, NULL,ecran, NULL);
        SDL_Flip(ecran);
	SDL_Delay(1000);
SDL_FreeSurface(image);
image=NULL;
}
void correct_enigme_multiplayer(SDL_Surface *ecran,int n)
{SDL_Surface *image;
SDL_Rect pos;pos.x=0+n*960;pos.y=270;
sound_effect("music/enigme resolved.wav",120);
	image=IMG_Load("enigme/gg2p.png");
        SDL_BlitSurface(image, NULL,ecran,&pos);
        SDL_Flip(ecran);
	SDL_Delay(1000);
SDL_FreeSurface(image);
image=NULL;
}
void wrong_enigme_multiplayer(SDL_Surface *ecran,int n)
{SDL_Surface *image;
SDL_Rect pos;pos.x=0+n*960;pos.y=270;
sound_effect("music/enigme failed.wav",120);
	image=IMG_Load("enigme/false2p.png");
        SDL_BlitSurface(image, NULL,ecran,&pos);
        SDL_Flip(ecran);
	SDL_Delay(1000);
SDL_FreeSurface(image);
image=NULL;
}
void initialiser_enigme_multiplayer(enigme t[20])
{
    int i,j,k;
    char line[64],question[64];
    FILE *file = NULL;
    TTF_Init();
    TTF_Font *fontquestion = NULL;
    TTF_Font *fontanswer = NULL;
    SDL_Color textColor = {255,255,255};
    fontquestion = TTF_OpenFont("Blanka-Regular.ttf",30);
    fontanswer = TTF_OpenFont("Orbitron Light.ttf", 20);
    for(i=0; i<10; i++)
    {
        t[i].correct=0;
        t[i].pos.x=0;
        t[i].pos.y=0;
        t[i].used=0;
        t[i].type=0;
        t[i].background=NULL;
        t[i].background=IMG_Load("enigme/enigme2p.png");
        t[i].question=NULL;
        file=fopen("question.txt","r");
        for(j=0; j<i+1; j++)
            fgets(line,sizeof(line), file);
        sprintf(question,"%s",line);
        t[i].question=TTF_RenderText_Blended(fontquestion,line,textColor);
        fclose(file);
        file=fopen("answer.txt","r");
        for(j=0; j<i+1; j++)
            for(k=0; k<4; k++)
            {
                fgets(line,sizeof(line), file);
                sprintf(question,"%s",line);
                t[i].answers[k]=TTF_RenderText_Blended(fontanswer,question,textColor);
            }
    }
TTF_CloseFont(fontquestion);
fontquestion=NULL;
TTF_CloseFont(fontanswer);
fontanswer=NULL;
}
void cha9_cha9(enigme t[20])
{
    int i,random,random1;
    enigme tri;
    SDL_Surface *answer=NULL;
    srand(time(NULL));
    for(i=0; i<20; i++) //questions
    {
        random=rand() %20;
        random1=rand() %20;
        tri=t[random];
        t[random]=t[random1];
        t[random1]=tri;
        random=rand() %4; //answers
        answer=t[i].answers[random];
        t[i].answers[random]=t[i].answers[0];
        t[i].answers[0]=answer;
        t[i].correct=random;
    }
SDL_FreeSurface(answer);
answer=NULL;
}
unsigned int compteur_enigme(int *exit,int exit_time,int currentTime)
{
    unsigned int lastTime = 0;
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 1000)
    {
        lastTime = currentTime;
    }
    if (currentTime>exit_time*1000)
        (*exit)=1;
    return currentTime;
}
void generate_enigmes(enigme t[20])
{
    int i=0,j,a,b;
    char ch[30];
    TTF_Init();
    TTF_Font *fontquestion = NULL;
    TTF_Font *fontanswer = NULL;
    SDL_Color textColor = {255,255,255};
    fontquestion = TTF_OpenFont("Blanka-Regular.ttf", 60);
    fontanswer = TTF_OpenFont("Orbitron Light.ttf", 40);
    srand(time(NULL));
    while(t[i].type==0)
        i++;
    while(i<20)
    {
        t[i].type=rand()%2 +1;
        t[i].used=0;
        a=rand()%100;
        b=rand()%100;
        t[i].correct=a*1000+b;
        t[i].background=IMG_Load("backenigme.png");
        t[i].pos.x=0;
        t[i].pos.y=0;
        if(t[i].type==1)
            sprintf(ch,"%d%s%d",a,"+",b);
        if(t[i].type==2)
            sprintf(ch,"%d%s%d",a,"-",b);
        t[i].question=TTF_RenderText_Blended(fontquestion,ch,textColor);
        for(j=0; j<4; j++)
        {
            if(t[i].type==1)
                a=rand()%200;
            else
                a=rand() %200 -100;
            sprintf(ch,"%d",a);
            t[i].answers[j]=TTF_RenderText_Blended(fontanswer,ch,textColor);
        }
        i++;
    }
TTF_CloseFont(fontquestion);
fontquestion=NULL;
TTF_CloseFont(fontanswer);
fontanswer=NULL;
}
void generate_enigmes_multiplayer(enigme t[20])
{
    int i=0,j,a,b;
    char ch[64];
    TTF_Init();
    TTF_Font *fontquestion = NULL;
    TTF_Font *fontanswer = NULL;
    SDL_Color textColor = {255,255,255};
    fontquestion = TTF_OpenFont("Blanka-Regular.ttf", 30);
    fontanswer = TTF_OpenFont("Orbitron Light.ttf", 20);
    srand(time(NULL));
    i=7;
    while(i<20)
    {
        t[i].type=rand()%2 +1;
        t[i].used=0;
        a=rand()%100;
        b=rand()%100;
        t[i].correct=a*1000+b;
        t[i].background=IMG_Load("enigme/enigme2p.png");
        t[i].pos.x=0;
        t[i].pos.y=0;
        if(t[i].type==1)
            sprintf(ch,"%d%s%d",a,"+",b);
        if(t[i].type==2)
            sprintf(ch,"%d%s%d",a,"-",b);
        t[i].question=TTF_RenderText_Blended(fontquestion,ch,textColor);
        for(j=0; j<4; j++)
        {
            if(t[i].type==1)
                a=rand()%200;
            else
                a=rand() %200 -100;
            sprintf(ch,"%d",a);
            t[i].answers[j]=TTF_RenderText_Blended(fontanswer,ch,textColor);
        }
        i++;
    }
TTF_CloseFont(fontquestion);
fontquestion=NULL;
TTF_CloseFont(fontanswer);
fontanswer=NULL;
}
void generation_auto_reponses(enigme t[20])
{
    int i=0,a,b,random;
    char ch[20];
    srand(time(NULL));
    TTF_Init();
    TTF_Font *fontanswer = NULL;
    SDL_Color textColor = {255,255,255};
    fontanswer = TTF_OpenFont("Orbitron Light.ttf",40);
    while(i<20)
    {
        if(t[i].type!=0)
        {
            random=rand()%4;
            a=t[i].correct/1000;
            b=t[i].correct%1000;
            t[i].correct=random;
            if(t[i].type==1)
                sprintf(ch,"%d",a+b);
            if(t[i].type==2)
                sprintf(ch,"%d",a-b);
            t[i].answers[random]=TTF_RenderText_Blended(fontanswer,ch,textColor);
        }
        i++;
    }
TTF_CloseFont(fontanswer);
fontanswer=NULL;
}

void zoom_affichage(SDL_Surface *p,SDL_Surface *ecran)
{int i;float ratio,x,y;
SDL_Surface *image;image=p;
SDL_Rect pos;
image=rotozoomSurface(image,0,0.1,SMOOTHING_ON);
for(i=1;i<101;i++)
{
ratio=i*0.01;
x=1920;
y=1200;
x=x/2-(x/2/100)*i;y=y/2-(y/2/100)*i;
pos.x=x;pos.y=y;
image=rotozoomSurface(image,0,ratio,SMOOTHING_ON);
SDL_BlitSurface(image,NULL,ecran,&pos);
SDL_Flip(ecran);
SDL_Delay(5);
SDL_FreeSurface(image);
image=NULL;
image=p;
}
SDL_Delay(500);
}
int resolution_enigmes(SDL_Surface *ecran,enigme t[20],perso p)
{
SDL_Surface *image;image=IMG_Load("backenigme.png");
zoom_affichage(image,ecran);
    int selected=0,exit=0,i;
    SDL_Rect pos;
    SDL_Surface *arrow=IMG_Load("arrow.png");
    unsigned int time_enigme,init_time=0;
    SDL_Event event;
    i=afficherenigme(ecran,t);
    pos.x=t[i].pos.x+350;
    pos.y=t[i].pos.y+455;
    SDL_BlitSurface(arrow, NULL, ecran,&pos);
    SDL_Flip(ecran);
    while(exit==0)
    {
        while( SDL_PollEvent( &event ) )
        {
            if(event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym==SDLK_UP)
                    selected--;
                if(event.key.keysym.sym==SDLK_DOWN)
                    selected++;
                if(selected==-1)
                    selected=3;
                if(selected==4)
                    selected=0;
                if(event.key.keysym.sym==SDLK_RETURN)
                {
                    t[i].used=1;
                    if(selected==t[i].correct)
                        {correct_enigme(ecran);return t[i].type+5;}
                    {wrong_enigme(ecran);return -1;}
                }
                pos.y=t[i].pos.y+455+(selected*80);
                afficherenigme(ecran,t);
                SDL_BlitSurface(arrow, NULL, ecran,&pos);
                if(init_time!=0)
                    afficher_temps_with_ticks(ecran,time_enigme-init_time+100,10);
                time_enigme=compteur_enigme(&exit,init_time+10000,time_enigme);
                SDL_Flip(ecran);
            }
        }
        if(init_time!=0)
            afficher_temps_with_ticks(ecran,time_enigme-init_time+100,10);
        time_enigme=compteur_enigme(&exit,init_time+10000,time_enigme);
        if(init_time==0)
            init_time=time_enigme;
        if(time_enigme>init_time+10000)
        {
            t[i].used=1;
            exit=1;
        }
        SDL_Flip(ecran);
    }
    return -1;
}
int resolution_enigmes_multiplayer(SDL_Surface *ecran,enigme t[20],perso p)
{
    int selected=0,exit=0,i;
    SDL_Rect pos;
    SDL_Surface *arrow=IMG_Load("arrow.png");
    unsigned int time_enigme,init_time=0;
    SDL_Event event;
    i=afficherenigme_multiplayer(p.number-1,ecran,t);
    pos.x=t[i].pos.x+120+(p.number-1)*960;
    SDL_BlitSurface(arrow, NULL, ecran,&pos);
    SDL_Flip(ecran);
    while(exit==0)
    {
        while( SDL_PollEvent( &event ) )
        {
            if(event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym==SDLK_UP)
                    selected--;
                if(event.key.keysym.sym==SDLK_DOWN)
                    selected++;
                if(selected==-1)
                    selected=3;
                if(selected==4)
                    selected=0;
                if(event.key.keysym.sym==SDLK_RETURN)
                {
                    t[i].used=1;
                     if(selected==t[i].correct)
                        {correct_enigme_multiplayer(ecran,p.number-1);return t[i].type+5;}
                    {wrong_enigme_multiplayer(ecran,p.number-1);return -1;}
                }
                pos.y=t[i].pos.y+472+(selected*50);
                afficherenigme_multiplayer(p.number-1,ecran,t);
                SDL_BlitSurface(arrow, NULL, ecran,&pos);
                if(init_time!=0)
                    afficher_temps_with_ticks(ecran,time_enigme-init_time+100,5);
                time_enigme=compteur_enigme(&exit,init_time+10000,time_enigme);
                SDL_Flip(ecran);
            }
        }
        if(init_time!=0)
            afficher_temps_with_ticks(ecran,time_enigme-init_time+100,5);
        time_enigme=compteur_enigme(&exit,init_time+10000,time_enigme);
        if(init_time==0)
            init_time=time_enigme;
        if(time_enigme>init_time+10000)
        {
            t[i].used=1;
            exit=1;
        }
        SDL_Flip(ecran);
    }
    return -1;
}
perso gravity(perso p,SDL_Surface *ecran)
{
    if(roof_test(ecran,p)==1)
        p.jump=0;
    else if(p.jump<1)
        p.pos.y=p.pos.y+15;
    do
    {
        p.pos.y=p.pos.y-1;
    }
    while(ground_test(p.background[1],p)==1);
    p.pos.y++;
    return p;
}
perso jump(perso p)
{
    if(p.jump>0)
    {
        p.jump++;
        if(p.jump>=15)
            p.jump=0;
        if(p.jump<15)
            p.pos.y=p.pos.y-(25-p.jump);
    }
    return p;
}
int restart(perso p)
{
    if(p.hp[0]==0)
        return 1;
    if(p.pos.y>1000)
        return 1;
    return 0;
}

int test_enemies(test t[8],perso p)
{
    int i;
    for(i=0; i<3; i++)
	{if(p.number==2) if(t[i].num==1)t[i].pos.x-=960;
	if(t[i].num==1)
            if(collision_trigo(p.pos,t[i].pos)==1)
            {
                t[i].num=-1;
                return 1;
            }
if(p.number==2) t[i].pos.x+=960;}
    return 0;
}

int trigger_chase(SDL_Rect t1,SDL_Rect t2)
{
    if(t1.x-t2.x<600)
        return 1;
    return 0;
}
SDL_Rect chase(SDL_Rect t1,SDL_Rect t2)
{
    t2.y+=40;
    if(((t1.y-t2.y)>50)||((t2.y-t1.y)>50))
    {
        if(t1.y<t2.y)
            t1.y+=10;
        else if(t1.y>t2.y)
            t1.y-=10;
    }
    t1.x-=10;
    return t1;
}
void chasing_enemies(test t[8],perso p)
{
    int i;
    for(i=0; i<3; i++)
    {if(p.number==2) if(t[i].num==1)t[i].pos.x-=960;
        if(trigger_chase(t[i].pos,p.pos)==1)
            t[i].triggered=1;
        if(t[i].triggered==1)
            t[i].pos=chase(t[i].pos,p.pos);
	if(p.number==2) t[i].pos.x+=960;
    }
}
void init_test_enigmes(enigmes t[3])
{int i;
for(i=0;i<3;i++) t[i].state=1;
t[0].x=1563;
t[1].x=4400;
t[2].x=5406;
}
int test_enigme(perso p,enigmes t[3])
{
    int i;
for(i=0;i<3;i++)
if((t[i].x-1<p.pos.x-p.bg.x)&&(t[i].x+25>p.pos.x-p.bg.x)&&(t[i].state==1))
{t[i].state=0;return 1;}
    return 0;
}

int compteur_maze(int difficulty)
{
    unsigned int lastTime = 0, currentTime=0;
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime +1000)
    {
        lastTime=currentTime;
    }
    if(currentTime%(10000/difficulty)<10)
        return 1;
    return 0;
}

int test_enemies_dodged(test t[8],perso p)
{
    int i;
    for(i=0; i<3; i++)
        if(t[i].num==1)
            if(t[i].pos.x<20)
            {
                t[i].num=0;
                return 1;
            }
    return 0;
}
int test_enemies_dodged_multiplayer(test t[8],perso p)
{
    int i;
    for(i=0; i<3; i++)
        if(t[i].num==1)
            if(t[i].pos.x<(-940+960*p.number))
            {
                t[i].num=0;
                return 1;
            }
    return 0;
}
int input(SDL_keysym k,char nom[30],int i)
{
    if(k.sym==SDLK_a)
        strcat(nom,"a");
    if(k.sym==SDLK_b)
        strcat(nom,"b");
    if(k.sym==SDLK_c)
        strcat(nom,"c");
    if(k.sym==SDLK_d)
        strcat(nom,"d");
    if(k.sym==SDLK_e)
        strcat(nom,"e");
    if(k.sym==SDLK_f)
        strcat(nom,"f");
    if(k.sym==SDLK_g)
        strcat(nom,"g");
    if(k.sym==SDLK_h)
        strcat(nom,"h");
    if(k.sym==SDLK_i)
        strcat(nom,"i");
    if(k.sym==SDLK_j)
        strcat(nom,"j");
    if(k.sym==SDLK_k)
        strcat(nom,"k");
    if(k.sym==SDLK_l)
        strcat(nom,"l");
    if(k.sym==SDLK_m)
        strcat(nom,"m");
    if(k.sym==SDLK_n)
        strcat(nom,"n");
    if(k.sym==SDLK_o)
        strcat(nom,"o");
    if(k.sym==SDLK_p)
        strcat(nom,"p");
    if(k.sym==SDLK_q)
        strcat(nom,"q");
    if(k.sym==SDLK_r)
        strcat(nom,"r");
    if(k.sym==SDLK_s)
        strcat(nom,"s");
    if(k.sym==SDLK_t)
        strcat(nom,"t");
    if(k.sym==SDLK_u)
        strcat(nom,"u");
    if(k.sym==SDLK_v)
        strcat(nom,"v");
    if(k.sym==SDLK_w)
        strcat(nom,"w");
    if(k.sym==SDLK_x)
        strcat(nom,"x");
    if(k.sym==SDLK_y)
        strcat(nom,"y");
    if(k.sym==SDLK_z)
        strcat(nom,"z");
    if(k.sym==SDLK_SPACE)
        strcat(nom," ");
    return i+1;
}
int cpt_afficheur(int min,int max,SDL_Surface *ecran,perso p,int y,SDL_Color textcolor,TTF_Font *font)
{
    SDL_Surface *text;
    char your_time[20];
    SDL_Rect pos;
    pos.x=400;
    pos.y=y;
    while(min<max)
    {
        min++;
        SDL_Delay(50);
        sprintf(your_time,"%d",min);
        text=TTF_RenderText_Blended(font,your_time,textcolor);
        SDL_BlitSurface(p.background[2],NULL,ecran,&pos);
        SDL_BlitSurface(text,NULL,ecran,&pos);
        SDL_Flip(ecran);
    }
SDL_FreeSurface(text);
text=NULL;
    return max;
}
void highscores(perso p,SDL_Surface *ecran,unsigned int time1)
{
    SDL_Event event;
    SDL_Surface *text;
    char noun[30]="",your_time[30]="";
    int time,cpt_noun=0,exit=0;
    int var=0,score;
    SDL_Rect pos;
    pos.x=100;
    pos.y=100;
    FILE *file = NULL;
    TTF_Font *font = NULL;
    SDL_Color textColor = {255,255,255};
    SDL_SetAlpha(p.background[2],SDL_SRCALPHA,255);
    font = TTF_OpenFont("Blanka-Regular.ttf", 80);
    file=fopen("scores.txt","a+");
    while(fscanf(file,"%d%s\n",&time,noun)!=-1)
    {
        score=time%1000;
        time=time/1000;
        sprintf(your_time,"%d%s%d%s%d ",time/3600,":",time%3600 /60,":",time%60);
        text=TTF_RenderText_Blended(font,your_time,textColor);
        SDL_BlitSurface(text,NULL,ecran,&pos);
        pos.x+=300;
        sprintf(your_time,"%d",score);
        text=TTF_RenderText_Blended(font,your_time,textColor);
        SDL_BlitSurface(text,NULL,ecran,&pos);
        pos.x+=200;
        text=TTF_RenderText_Blended(font,noun,textColor);
        SDL_BlitSurface(text,NULL,ecran,&pos);
        SDL_Flip(ecran);
        SDL_Delay(300);
        pos.y+=100;
        pos.x=100;
    }
    textColor.r=0;
    textColor.b=0;
    textColor.g=200;
    strcpy(noun,"");
    while(var<time1)
    {
        var++;
        SDL_Delay(50);
        sprintf(your_time,"%d%s%d%s%d",var/3600,":",var%3600 /60,":",var%60);
        text=TTF_RenderText_Blended(font,your_time,textColor);
        pos.x=0;
        SDL_BlitSurface(p.background[2],NULL,ecran,&pos);
        pos.x=100;
        SDL_BlitSurface(text,NULL,ecran,&pos);
        SDL_Flip(ecran);
    }
    pos.x+=300;
    var=0;
    cpt_afficheur(0,p.score[0],ecran,p,pos.y,textColor,font);
    pos.x+=200;
    if(p.s.e_d>0)
    {
        sprintf(noun,"%s%d%s","+",p.s.e_d," Enemies dodged");
        text=TTF_RenderText_Blended(font,noun,textColor);
        SDL_BlitSurface(text,NULL,ecran,&pos);
        SDL_Flip(ecran);
        SDL_Delay(1300);
    }
    p.score[0]=cpt_afficheur(p.score[0],p.score[0]+(10*p.s.e_d),ecran,p,pos.y,textColor,font);
    SDL_BlitSurface(p.background[2],NULL,ecran,&pos);
    if(p.s.r_s)
    {
        sprintf(noun,"%s%d%s","+",p.s.r_s," Riddles solved");
        text=TTF_RenderText_Blended(font,noun,textColor);
        SDL_BlitSurface(text,NULL,ecran,&pos);
        SDL_Flip(ecran);
        SDL_Delay(1300);
        p.score[0]=cpt_afficheur(p.score[0],p.score[0]+(5*p.s.r_s),ecran,p,pos.y,textColor,font);
        SDL_BlitSurface(p.background[2],NULL,ecran,&pos);
    }
    if(p.s.l_r)
    {
        sprintf(noun,"%s%d%s","+",p.s.l_r," Lives remaining");
        text=TTF_RenderText_Blended(font,noun,textColor);
        SDL_BlitSurface(text,NULL,ecran,&pos);
        SDL_Flip(ecran);
        SDL_Delay(1300);
        p.score[0]=cpt_afficheur(p.score[0],p.score[0]+(5*p.s.l_r),ecran,p,pos.y,textColor,font);
        p.pos.x=400;
        SDL_BlitSurface(p.background[2],NULL,ecran,&pos);
    }
    strcpy(noun,"");
    while(exit==0)
    {
        while( SDL_PollEvent( &event ) )
        {
            if(event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym==SDLK_RETURN)
                    exit=1;
                else
                    cpt_noun=input(event.key.keysym,noun,cpt_noun);
                text=TTF_RenderText_Blended(font,noun,textColor);
                SDL_BlitSurface(text,NULL,ecran,&pos);
                SDL_Flip(ecran);
            }
        }
    }
    fprintf(file,"%d%s\n",time1*1000+p.score[0],noun);
    fclose(file);
TTF_CloseFont(font);
font=NULL;
}

//01:01:01=60+1+60/1=3600+60+1=3661


void ref(SDL_Surface *ecran,int y)
{
    SDL_Rect pos;
    pos.x=0;
    pos.y=0;
    pos.w=y;
    pos.h=y;
    SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,255,255,255));
}
void affichage_bloc(SDL_Surface *ecran,SDL_Rect pos,int type,int rot)
{
    int x1=pos.x,x2=pos.x+pos.w,y1=pos.y,y2=pos.y+pos.h;
    SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,255,255,255));
    if(type==2)
    {
        pos.w=(y2-y1)/3;
        pos.x=x1+((x2-x1)/3);
        SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
        pos.h=(y2-y1)/3;
        pos.x=x1;
        pos.w=x2-x1;
        pos.y=y1+((y2-y1)/3);
        SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
    }
    else if(type==3)
    {
        if(rot==0)
        {
            pos.w=(x2-x1)/3;
            pos.x=x1+((x2-x1)/3);
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
        }
        else
        {
            pos.w=y2-y1;
            pos.x=x1;
            pos.h=(y2-y1)/3;
            pos.y=y1+((y2-y1)/3);
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
        }
    }
    else if(type==1)
    {
        if(rot==0)
        {
            pos.h=(y2-y1)/3;
            pos.w=(y2-y1)/3;
            pos.x=x1+((x2-x1)/3);
            pos.y=y1;
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
            pos.h=(y2-y1)/3;
            pos.w=((y2-y1)/3)*2;
            pos.x=x1;
            pos.y=y1+((y2-y1)/3);
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
        }
        if(rot==1)
        {
            pos.h=(y2-y1)/3;
            pos.w=(y2-y1)/3;
            pos.y=y1+((y2-y1)/3);
            pos.x=x1+((x2-x1)/3)*2;
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
            pos.h=((y2-y1)/3)*2;
            pos.w=((y2-y1)/3);
            pos.y=y1;
            pos.x=x1+((x2-x1)/3);
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
        }
        if(rot==2)
        {
            pos.h=(y2-y1)/3;
            pos.w=(y2-y1)/3;
            pos.y=y1+((y2-y1)/3);
            pos.x=x1+((x2-x1)/3)*2;
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
            pos.h=((y2-y1)/3)*2;
            pos.w=((y2-y1)/3);
            pos.y=y1+((y2-y1)/3);
            pos.x=x1+((x2-x1)/3);
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
        }
        if(rot==3)
        {
            pos.h=(y2-y1)/3;
            pos.w=(y2-y1)/3;
            pos.x=x1+((x2-x1)/3);
            pos.y=y1+((y2-y1)/3)*2;
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
            pos.h=(y2-y1)/3;
            pos.w=((y2-y1)/3)*2;
            pos.x=x1;
            pos.y=y1+((y2-y1)/3);
            SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,0,0,0));
        }
    }
}
int rot_change(int type,int rot)
{
    if(type==3)
    {
        if(rot<1)
            rot++;
        else
            rot=0;
    }
    if(type==1)
    {
        if(rot<3)
            rot++;
        else
            rot=0;
    }
    return rot;
}
int enigme_plumber(int size)
{
    int i,j,k,lghadi,p1=size,exit=0,cpt=size*3;
    SDL_Surface *ecran;
    ecran = SDL_SetVideoMode(1000,1000, 32, SDL_HWSURFACE);
    int t[p1][p1],rot[p1][p1],crt[p1][p1];
    SDL_Rect pos,pos_score;
    pos.w=800/size;
    pos.h=800/size;
    pos_score.x=600;
    pos_score.y=940;
    SDL_Event event;
    SDL_Surface *text=NULL;
    SDL_Color color= {0,0,0};
    char tt[30];
    TTF_Font *font = TTF_OpenFont("hemi head bd it.ttf", 50);
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            t[i][j]=0;
            rot[i][j]=0;
            crt[i][j]=0;
        }
    j=0;
    i=rand()%size;
    t[j][i]=2;
    rot[j][i]=0;
    crt[j][i]=1;
    while(j<size-2)
    {
        lghadi=i;
        j++;
        j++;
        i=rand()%size;
        t[j][i]=2;
        for(k=i; k<=lghadi; k++)
            t[j-1][k]=2;
        for(k=i; k>=lghadi; k--)
            t[j-1][k]=2;
    }
    t[j+1][i]=2;
    crt[j+1][i]=1;
    ref(ecran,size*100);
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            if((t[j][i]>=2)&&(t[j-1][i]>=2)&&(t[j+1][i]>=2))
            {
                t[j][i]=3;
                crt[j][i]=1;
            }
            if((t[j][i-1]>=2)&&(t[j][i]>=2)&&(t[j][i+1]>=2))
            {
                t[j][i]=3;
                crt[j][i]=0;
            }
        }
    for(i=0; i<size; i++)
        for(j=1; j<size-1; j++)
            if(t[j][i]==2)
                t[j][i]=1;
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
            if(t[j][i]==2)
                t[j][i]=3;
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            pos.x=100*j;
            pos.y=100*i;
            affichage_bloc(ecran,pos,t[j][i],rot[i][j]);
            SDL_Flip(ecran);
        }
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            if((t[j][i+1]!=0)&&(t[j][i]==1)&&(t[j+1][i]!=0))
                crt[j][i]=2;
            else if((t[j-1][i]!=0)&&(t[j][i]==1)&&(t[j][i-1]!=0))
                crt[j][i]=0;
            if((t[j][i-1]!=0)&&(t[j][i]==1)&&(t[j+1][i]!=0))
                crt[j][i]=1;
            if((t[j-1][i]!=0)&&(t[j][i]==1)&&(t[j][i+1]!=0))
                crt[j][i]=3;
            if(t[j][i]==0)
                crt[j][i]=-1;
        }
    for(k=0; k<10;)
    {
        i=rand()%10;
        j=rand()%10;
        if(t[j][i]==0)
        {
            k++;
            t[j][i]=rand()%4;
        }
    }
    SDL_BlitSurface(text,NULL,ecran,&pos_score);
    SDL_Flip(ecran);
    while(exit==0)
    {
        while( SDL_PollEvent( &event ) )
        {
            if(event.type==SDL_KEYDOWN)
                if(event.key.keysym.sym==SDLK_ESCAPE)
                    exit=1;
            if(event.type==SDL_MOUSEBUTTONDOWN)
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    sprintf(tt,"%s%d","Moves Left: ",cpt);
                    cpt--;
                    text=TTF_RenderText_Blended(font,tt,color);
                    rot[event.motion.x/100][event.motion.y/100]=rot_change(t[event.motion.x/100][event.motion.y/100],rot[event.motion.x/100][event.motion.y/100]);//printf("\n\n\n");
                    exit=1;
                    for(i=0; i<size; i++)
                        for(j=0; j<size; j++)
                        {
                            if((crt[j][i]!=rot[j][i])&&(crt[j][i]!=-1))
                            {
                                /*printf("x%dy%d",j,i);*/exit=0;/*printf("crt %d rot %d\n",crt[j][i],rot[j][i]);*/
                            }
                            pos.x=100*j;
                            pos.y=100*i;
                            affichage_bloc(ecran,pos,t[j][i],rot[j][i]);
                            SDL_FillRect(ecran,&pos_score,SDL_MapRGB(ecran->format,255,255,255));
                            SDL_BlitSurface(text,NULL,ecran,&pos_score);
                            SDL_Flip(ecran);
                        }
                }
        }
    }
    return cpt*3;
TTF_CloseFont(font);
font=NULL;
}
int bounding_box_laser(SDL_Rect t1,SDL_Rect t2)
{
    if((t1.x+t1.w>t2.x)&&(t1.x<t2.x))
        return 1;
    return 0;
}
void animation_laser(SDL_Surface *ecran,int x,int y)
{
    SDL_Rect pos;
    pos.x=x;
    pos.y=y;
    char chaine[40];
    SDL_Surface *i;
    sprintf(chaine,"%s%d%s","laser_animation/Layer ",rand()%5 +1,".png");
    i=IMG_Load(chaine);
    pos.x-=i->w/2;
    SDL_BlitSurface(i,NULL,ecran,&pos);
}
perso laser(SDL_Surface *ecran,unsigned int time,int pos_absolue,perso p)
{
    SDL_Rect pos[6];
    int i,t=0;
    for(i=0; i<2; i++)
    {
        pos[i].x=pos_absolue+2000+i*3600;
        pos[i].y=351;
        pos[i].h=513;
        pos[i].w=10;
    }
    for(i=2; i<6; i++)
    {
        pos[i].x=pos_absolue+1500+i*700;
        pos[i].y=351-127;
        pos[i].h=640;
        pos[i].w=10;
    }
    if(time%2==0)
        for(i=0; i<2; i++)
        {
            SDL_FillRect(ecran,&pos[i],SDL_MapRGB(ecran->format,255,10,10));
            if(bounding_box_laser(p.pos,pos[i])==1)
                t=1;
        }
    if(time%3<2)
        for(i=2; i<6; i++)
        {
            SDL_FillRect(ecran,&pos[i],SDL_MapRGB(ecran->format,255,10,10));
            if(bounding_box_laser(p.pos,pos[i])==1)
                t=1;
        }
    if(t==1)
    {
        animation_laser(ecran,p.pos.x+(p.pos.w/2),p.pos.y-2);
        p=gestion_vie_et_score(p,-1,0);
    }
    return p;
}
// Initialize FPS_Fn( )
void FPS_Initial(int *NextTick,int *interval,int FPS)
{
    (*NextTick) = 0 ;
    (*interval) = 1 * 1000 / FPS ;
    return;
}
// Frame Per Second Function
void FPS_Fn(int *NextTick,int *interval)
{
    if ( (*NextTick) > SDL_GetTicks( ) )
        SDL_Delay( (*NextTick) - SDL_GetTicks( ) );
    (*NextTick) = SDL_GetTicks( ) + (*interval) ;
    return;
}

perso init_controls(perso p)
{
    p.k.move_left=SDLK_LEFT;
    p.k.move_right=SDLK_RIGHT;
    p.k.jumping=KMOD_ALT;
    p.k.sprinting=KMOD_RSHIFT;
    return p;
}
perso init_controls_p2(perso p)
{
    p.k.move_left=SDLK_q;
    p.k.move_right=SDLK_d;
    p.k.jumping=KMOD_LCTRL;
    p.k.sprinting=KMOD_LSHIFT;
    return p;
}
void sound_effect(char ch[40],int volume)
{
Mix_Chunk* sound=NULL;
Mix_FreeChunk(sound);
sound = Mix_LoadWAV(ch);
Mix_AllocateChannels(16);
Mix_VolumeChunk(sound,volume);
Mix_PlayChannel(1,sound,0);
}
void music(char ch[40],int volume)
{
Mix_Music *music;
Mix_FreeMusic(music);
music = Mix_LoadMUS(ch);
Mix_PlayMusic(music, -1);
Mix_VolumeMusic(volume);
}

void affichage_jeu_ia2(SDL_Surface *ecran,int t[7][7])
{SDL_Surface *table,*yellow,*red;
red=IMG_Load("red dot.png");
yellow=IMG_Load("yellow dot.png");
table=IMG_Load("ia2_tab(1).png");
yellow=rotozoomSurface(yellow,0,0.8,SMOOTHING_ON);
red=rotozoomSurface(red,0,0.8,SMOOTHING_ON);
int i;int j;SDL_Rect pos;
pos.x=0;pos.y=0;
SDL_BlitSurface(table,NULL,ecran,&pos);
for(i=0;i<7;i++)
for(j=0;j<7;j++)
{pos.x=56+j*328;pos.y=i*185;
if(t[i][j]==1) SDL_BlitSurface(yellow,NULL,ecran,&pos);
if(t[i][j]==2) SDL_BlitSurface(red,NULL,ecran,&pos);
}
SDL_Flip(ecran);
SDL_FreeSurface(yellow);
yellow=NULL;
SDL_FreeSurface(red);
red=NULL;
SDL_FreeSurface(table);
table=NULL;
}
void waiting(SDL_Surface *ecran,int t[7][7],int joueur)
{SDL_Event event;int done=0;int choix=-2,i,j;
while(done==0)
{
while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_KEYDOWN)
                {
			if(event.key.keysym.sym==SDLK_a)
			choix=0;
			if(event.key.keysym.sym==SDLK_z)
			choix=1;
			if(event.key.keysym.sym==SDLK_e)
			choix=2;
			if(event.key.keysym.sym==SDLK_r)
			choix=3;
			if(event.key.keysym.sym==SDLK_t)
			choix=4;
			if(event.key.keysym.sym==SDLK_y)
			choix=5;
                    	if(choix!=-2)if(t[0][choix]==0) {t[0][choix]=joueur;done=1;}
        	}
	}
if(choix==6) choix=0;
if(choix==-1) choix=5;
affichage_jeu_ia2(ecran,t);
}
}
void ia_2_(int t[7][7])
{int i,j;
for(i=0;i<5;i++)
for(j=0;j<7;j++)
if(t[i+1][j]==0) {t[i+1][j]=t[i][j];t[i][j]=0;}
}
int test_done(int t[7][7])
{int done=0,i,j,cpt_red_dots,cpt_yellow_dots;
for(i=0;i<5;i++)
{cpt_red_dots=0;cpt_yellow_dots=0;
for(j=0;j<5;j++)
{if(t[j][i]==1) {cpt_yellow_dots++;cpt_red_dots=0;}if(t[j][i]==2) {cpt_red_dots++;cpt_yellow_dots=0;}if(cpt_yellow_dots==4)return 2;if(cpt_red_dots==4) return 3;}}
for(i=0;i<5;i++)
for(j=0;j<5;j++)
if(t[i][j]==0) return 1;
return 0;
}
void ia2_thinking(int t[7][7])
{int i,j,choix[6],choix_sup,r;
for(i=0;i<5;i++) choix[i]=0;
for(i=0;i<5;i++)
for(j=0;j<5;j++)
{if(t[j][i]==1)choix[i]++;if(t[i][j]==2)choix[i]=0;}
choix_sup=choix[0];
for(i=0;i<5;i++)
{if(choix[i]>choix_sup) choix_sup=choix[i];}
do{r=rand()%6;}while(choix[r]!=choix_sup);
if(t[0][r]==0)t[0][r]=2;else {do {r=rand()%6;}while(t[0][r]!=0); t[0][r]=2;}
}
int  ia_2_joueur_contre_l_ordinateur(SDL_Surface *ecran)
{
ecran = SDL_SetVideoMode(1920,1200,32,SDL_HWSURFACE);
int t[7][7];
int i,j;
int done=1;
int joueur=1;
for(i=0;i<7;i++)
for(j=0;j<7;j++)
{
t[i][j]=0;
}
while(done==1)
{
waiting(ecran,t,joueur);
ia_2_(t);
SDL_Delay(200);
affichage_jeu_ia2(ecran,t);
done=test_done(t);
ia2_thinking(t);
ia_2_(t);
done=test_done(t);
affichage_jeu_ia2(ecran,t);
SDL_Delay(200);
}
return done;
}
saving save(perso p,test t[8],saving s)
{
int i;
s.pos_perso=p.pos;
s.pos_bg=p.bg;
for(i=0;i<3;i++) s.t[i]=t[i];
return s;
}
void save_to_file(saving s)
{
    FILE *file = NULL;
    file=fopen("save.txt","w+");
    fprintf(file,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",s.level,s.pos_perso.x,s.pos_perso.y,s.pos_bg.x,s.pos_bg.y,s.hp,s.t[0].num,s.t[1].num,s.t[2].num);
    fclose(file);
}
saving load_from_file()
{saving s;int x1,y1,x2,y2,hp,e1,e2,e3;
    FILE *file = NULL;
    file=fopen("save.txt","r+");
    fscanf(file,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",&s.level,&x1,&y1,&x2,&y2,&hp,&e1,&e2,&e3);
s.pos_perso.x=x1;
s.pos_perso.y=y1-15;
s.pos_bg.x=x2;
s.pos_bg.y=y2;
s.hp=hp;
s.t[0].num=e1;
s.t[1].num=e2;
s.t[2].num=e3;
    fclose(file);
return s;
}
void load_last_game(saving s,perso *p,test t[8])
{
int i;
p->pos.x=s.pos_perso.x;
p->pos.y=s.pos_perso.y;
p->bg=s.pos_bg;
p->hp[0]=s.hp;
for(i=0;i<3;i++) t[i].num=s.t[i].num;
}
int choose_saved_or_no(SDL_Surface *ecran)
{int done=0;
SDL_Event e;
SDL_Surface *bg;
bg=IMG_Load("backgrounds/continu-new.png");
while(done==0)
{
SDL_BlitSurface(bg,NULL,ecran,NULL);
SDL_Flip(ecran);
while(SDL_PollEvent(&e))
{if(e.type==SDL_KEYDOWN)
                {
			if(e.key.keysym.sym==SDLK_s)
			return 1;
			if(e.key.keysym.sym==SDLK_c)
			return 0;
		}
}
}
return 0;
}
int save_or_no(SDL_Surface *ecran)
{int done=0;
SDL_Event e;
SDL_Surface *bg;
bg=IMG_Load("backgrounds/save-exit.png");
while(done==0)
{
SDL_BlitSurface(bg,NULL,ecran,NULL);
SDL_Flip(ecran);
while(SDL_PollEvent(&e))
{if(e.type==SDL_KEYDOWN)
                {
			if(e.key.keysym.sym==SDLK_s)
			return 1;
			if(e.key.keysym.sym==SDLK_n)
			return 0;
		}
}
}
return 0;
}
void minimap_singleplayer(perso p,SDL_Surface *screen)
{
SDL_Rect pos;pos.x=0;pos.y=1000;pos.w=2000;pos.h=10;
Uint32 couleur = SDL_MapRGB(screen->format,0,255,255);
SDL_FillRect(screen,&pos,couleur);
pos.x=p.pos.x-p.bg.x*1080/8000;pos.y=1000;pos.w=10;pos.h=10;
couleur = SDL_MapRGB(screen->format,255,0,0);
SDL_FillRect(screen,&pos,couleur);
}
void minimap_multiplayer(perso p,perso p1,SDL_Surface *screen)
{
SDL_Rect pos;pos.x=0;pos.y=1000;pos.w=2000;pos.h=10;
Uint32 couleur = SDL_MapRGB(screen->format,0,255,255);
SDL_FillRect(screen,&pos,couleur);
pos.x=p.pos.x-p.bg.x*1080/8000;pos.y=1000;pos.w=10;pos.h=10;
couleur = SDL_MapRGB(screen->format,255,0,0);
SDL_FillRect(screen,&pos,couleur);
pos.x=p1.pos.x-p.bg.x*1080/8000;pos.y=1000;pos.w=10;pos.h=10;
couleur = SDL_MapRGB(screen->format,0,200,0);
SDL_FillRect(screen,&pos,couleur);
}
void player_one_won(SDL_Surface *ecran)
{SDL_Surface *image;
sound_effect("music/enigme resolved.wav",120);
	image=IMG_Load("P1.png");
        SDL_BlitSurface(image, NULL,ecran, NULL);
        SDL_Flip(ecran);
	SDL_Delay(1000);
SDL_FreeSurface(image);
image=NULL;
}
void player_two_won(SDL_Surface *ecran)
{SDL_Surface *image;
sound_effect("music/enigme resolved.wav",120);
	image=IMG_Load("P2.png");
        SDL_BlitSurface(image, NULL,ecran, NULL);
        SDL_Flip(ecran);
	SDL_Delay(1000);
SDL_FreeSurface(image);
image=NULL;
}


















