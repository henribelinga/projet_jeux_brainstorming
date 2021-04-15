#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

typedef struct 
{
    SDL_Surface *background;
    char question[50],rp1[15],rp2[15],rp3[15];
    int solution;
}enigme;   

enigme GenEN(char *nomfichier);
void afficherEnigme(enigme *ayoub, SDL_Surface * ecran);
