/**
 *@file fonction.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"

/**
* @brief To initialize the minimap m .
* @param m the minimap
* @return Nothing
*/
void initmap(minimap *m)
{
    m->position_mini.x = 0;
    m->position_mini.y = 0;
    m->sprite = NULL;
    m->sprite = IMG_Load("minimap1.png");
}
/**
* @brief To show the minimap m .
* @param m the minimap
* @param screen the screen 
* @return Nothing
*/
void afficherminimap(minimap m, SDL_Surface *screen)
{

    SDL_BlitSurface(m.sprite, NULL, screen, &m.position_mini);
}
/**
* @brief To delete the minimap m.
* @param m the minimap
* @return Nothing
*/
void free_minimap(minimap *m)
{
    SDL_FreeSurface(m->sprite);
}
/**
* @brief To initialize the time t .
* @param t the time
* @return Nothing
*/
void initialiser_temps(temps *t)
{
    t->texte = NULL;
    t->position.x = 0;
    t->position.y = 100;
    t->police = NULL;
    t->police = TTF_OpenFont("avocado.ttf", 40);
    strcpy(t->entree, "");
    (t->secondesEcoulees) = 0;
    time(&(t->t1)); //temps du debut
}
/**
* @brief To show the time t .
* @param t the time
* @param screen the screen
* @return Nothing
*/
void afficher_temps(temps *t, SDL_Surface *screen)
{
    SDL_Color couleurnoir = {0, 0, 0};
    
    time(&(t->t2)); // temps actuel

    t->secondesEcoulees = t->t2 - t->t1;

    t->min = ((t->secondesEcoulees / 60) % 60);
    t->sec = ((t->secondesEcoulees) % 60);
    int millisecondes=SDL_GetTicks()%60;
    
    sprintf(t->entree, "%02d:%02d:%02d", t->min, t->sec, millisecondes);

    t->texte = TTF_RenderText_Blended(t->police, t->entree, couleurnoir);

    SDL_BlitSurface(t->texte, NULL, screen, &(t->position)); /* Blit du texte */
}
/**
* @brief To delete the time t.
* @param t the time
* @param screen the screen
* @return Nothing
*/
void free_temps(temps *t, SDL_Surface *screen)
{
    SDL_FreeSurface(t->texte);
    TTF_CloseFont(t->police);
}
/**
* @brief To convert the pixel of background in color .
* @param Background the screen
* @param x the position of image
* @param y the position of image 
* @return a color
*/
SDL_Color GetPixel(SDL_Surface *Background, int x, int y)
{

    SDL_Color color;
    Uint32 col = 0;
    //Determine position

    char *pixelPosition = (char *)Background->pixels;
    
    pixelPosition += (Background->pitch * y);
    
    pixelPosition += (Background->format->BytesPerPixel * x);
    
    memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
    
    SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);

    return (color);
}
/**
* @brief To convert the pixel of background in color .
* @param p the Personne 
* @param Masque the screen 
* @return a int
*/
int collisionPP(Personne p, SDL_Surface *Masque)
{
    SDL_Color test, couleurnoir = {0, 0, 0};

    SDL_Rect pos[8];
    pos[0].x = p.position_perso.x;
    pos[0].y = p.position_perso.y;
    pos[1].x = p.position_perso.x + p.position_perso.w / 2;
    pos[1].y = p.position_perso.y;
    pos[2].x = p.position_perso.x + p.position_perso.w;
    pos[2].y = p.position_perso.y;
    pos[3].x = p.position_perso.x;
    pos[3].y = p.position_perso.y + p.position_perso.h / 2;
    pos[4].x = p.position_perso.x;
    pos[4].y = p.position_perso.y + p.position_perso.h;
    pos[5].x = p.position_perso.x + p.position_perso.w / 2;
    pos[5].y = p.position_perso.y + p.position_perso.h;
    pos[6].x = p.position_perso.x + p.position_perso.w;
    pos[6].y = p.position_perso.y + p.position_perso.h;
    pos[7].x = p.position_perso.x + p.position_perso.w;
    pos[7].y = p.position_perso.y + p.position_perso.h / 2;
    int collision = 0, x, y;

    for (int i = 0; i < 8 && collision == 0; i++)
    {
        x = pos[i].x;
        y = pos[i].y;
        test = GetPixel(Masque, x, y);
        if (test.r == 0 && test.g == 0 && test.b == 0)
            collision = 1;
    }
    return collision;
}
/**
* @brief To show a minimap update's .
* @param p the Personne
* @param m the minimap
* @param camera the camera of screen
* @param redimensionnement the redimension of image
* @return Nothing
*/
void majminimap (Personne *p, minimap *m ,SDL_Rect camera ,int redimensionnement){
  if (camera.x==0)
  p->position_perso.x += redimensionnement;

  if (camera.x==1)
  p->position_perso.x -= redimensionnement;

  if (camera.x==2)
  p->position_perso.y += redimensionnement;

  if (camera.x==3)
  p->position_perso.y -= redimensionnement;

}
