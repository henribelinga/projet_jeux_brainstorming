

#ifndef fonction_H_INCLUDED
#define fonction_H_INCLUDED
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
/**
* @struct Background_perso
* @brief struct for backround
*/
typedef struct
{
	SDL_Rect position_perso;   /*!<Rectangle*/
	SDL_Surface *sprite;     /*!< Surface. */
} Personne;


/**
* @struct Background_minimap
* @brief struct for backround
*/
typedef struct
{
	SDL_Rect position_mini;   /*!<Rectangle*/
	SDL_Surface *sprite;     /*!< Surface. */
} minimap;

/**
* @struct Background_temps
* @brief struct for display time
*/
typedef struct temps
{
	SDL_Surface *texte;     /*!< Surface. */
	SDL_Rect position;     /*!<Rectangle*/

	TTF_Font *police;   /*!<police*/

	char entree[100];   /*!< caractere*/
	int secondesEcoulees;  
	SDL_Color couleurBlanche;
	time_t t1, t2; /*!<recupere_le_temps_ecoule_depuis_l_appel_de_la_fonction*/
	int min, sec;
} temps;

void initmap(minimap *m);
void afficherminimap(minimap m, SDL_Surface *screen);
void free_minimap(minimap *m);
void majminimap (Personne *p, minimap *m ,SDL_Rect camera ,int redimensionnement);

void initialiser_temps(temps *t);
void afficher_temps(temps *t, SDL_Surface *ecran);
void free_temps(temps *t, SDL_Surface *ecran);

SDL_Color GetPixel(SDL_Surface *Background, int x, int y);
int collisionPP(Personne p, SDL_Surface *Masque);



#endif
