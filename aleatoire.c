#include "aleatoire.h"

enigme GenEN(char *nomfichier){
    FILE* f;
    enigme en;
    srand( time( NULL ) );
    int al = rand() % 4,li=0;
    en.background=IMG_Load("background.jpg");
    f=fopen(nomfichier,"r");
    while (li<al)
    {
        if (fgetc(f)=='\n')
        {
            li++;
        }
        
    }    
    fscanf(f,"%s %s %s %s %d\n",en.question,en.rp1,en.rp2,en.rp3,&en.solution);
    fclose(f);
    return en;
    
}

void afficherEnigme(enigme *en, SDL_Surface * ecran){
    SDL_Surface  *quest = NULL ,*rp1 = NULL ,*rp2 = NULL , *rp3 = NULL;
    SDL_Rect posq,pos1,pos2,pos3;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};    
    TTF_Init();
    police = TTF_OpenFont("horror.ttf", 32);
    quest = TTF_RenderText_Blended(police, en->question, couleurNoire);
    rp1 = TTF_RenderText_Blended(police, en->rp1, couleurNoire);
    rp2 = TTF_RenderText_Blended(police, en->rp2, couleurNoire);
    rp3 = TTF_RenderText_Blended(police, en->rp3, couleurNoire);
    posq.x=50;
    posq.y=50;
    pos1.x=50;
    pos1.y=300;
    pos2.x=300;
    pos2.y=300;
    pos3.x=550;
    pos3.y=300;

    SDL_BlitSurface(en->background, NULL, ecran, NULL); 
    SDL_BlitSurface(quest, NULL, ecran, &posQ); 
    SDL_BlitSurface(rp1, NULL, ecran, &pos1); 
    SDL_BlitSurface(rp2, NULL, ecran, &pos2); 
    SDL_BlitSurface(rp3, NULL, ecran, &pos3); 





}


