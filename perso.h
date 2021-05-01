#ifndef perso_H_INCLUDED
#define perso_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


typedef struct perso
{

SDL_Surface *personnage;
SDL_Rect rect,rect_relative;
SDL_Surface *mvtright[10]; // des tableauw contenant les frames
SDL_Surface *mvtleft[10]; 
SDL_Surface *jumpright[15];
SDL_Surface *jumpleft[15];
//SDL_Surface *jumpright[15];0
SDL_Surface *runright[11];
SDL_Surface *runleft[11];
SDL_Surface *die[10];
SDL_Surface *frame;
float speedX,speedY;
int fr;
float x1 , x2 , x3 , x4 , x5 , x6 , x7 , x8 , x9 , x10 , x11 , x12 , x13 , x14 , x15 , x16 ;  //points de verification de collision parfaite
float y1 , y2 , y3 , y4 , y5 , y6 , y7 , y8 , y9 , y10 , y11 , y12 , y13 , y14 , y15 , y16 ;  // points de verification de collision parfaite
}perso;


typedef struct Input
{
 int left,right,jump,action,down;

} Input;



void init_input (Input *I);
void initialiser_perso(perso *p);
void initialiser_joueur(perso * p);
void initialiser_input(Input * I);
void afficher_joueur(perso *p,SDL_Surface *ecran);
void afficher_perso (perso *p,SDL_Surface *ecran);
void animation_right (perso *p);
void animation_left (perso *p);
void animation_stable (perso *p);
void mouvementright (perso *p);
void mouvementleft (perso *p);
void jumpright(perso *p);
void jumpleft(perso *p);


 #endif
