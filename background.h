#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h> // consacrer aux booleens: est un type de varibles à deux etats vrai ou faux
#include <math.h> // permet d'utiliser un ensembles de fonctions mathematiques 
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "perso.h" 

typedef struct background
{
int x_relative,y_relative;
SDL_Surface * bg,* mask;
SDL_Rect cam, posecran1;

SDL_Rect camera,posecran2;
}background;
void initialiser_background(background *b);
void afficher_background2( SDL_Surface *ecran,background * b);
void afficher_background(SDL_Surface * ecran,background  * b);
void scrolling_right (background *b,perso *p,SDL_Surface *ecran);
void scrolling_left (background *b,perso *p,SDL_Surface *ecran);

