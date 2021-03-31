//PARTIE AFFICHAGE DE BACKGROUND::#include "perso.h"
#include "background.h"

#define GRAVITY 10
#define SPEED 5
#define MAX_SPEED 10
#define MAX_JUMP_SPEED 30

int ground=330; //480


void main()
{
SDL_Init(SDL_INIT_VIDEO);
SDL_Surface *ecran;
SDL_Surface *back;
back=IMG_Load("background.png");
ecran=SDL_SetVideoMode (1000,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

SDL_WM_SetCaption("personnage\t1",NULL);//titre de la fenetre

background b;
Input I;
perso p;
SDL_Event event;
initialiser_perso (&p);
initialiser_input (&I);
initialiser_background (&b);
bool running=true;



SDL_EnableKeyRepeat(200,0);


while(running)
{


while(SDL_PollEvent(&event))
	{

		switch(event.type)
		{
		case SDL_QUIT:
		// (*action)=0;
			running=false;
		break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			/*	case SDLK_ESCAPE:

				pause(ecran,&next,nb_stage,action);
				read_volume (&vm,&vsfx);
				Mix_VolumeMusic(vm);
			Mix_PlayMusic(musique, -1);
				break;
			case SDLK_RIGHT:
				I.right=1;

			break; */
			case SDLK_LEFT :
				I.left=1;



      		break;
      		case SDLK_RIGHT :
				I.right=1;
				


      		break;
			case SDLK_SPACE :
				I.jump=1;
				if(p.rect.y==ground)//collision with ground
								p.speedY = -60;
			 //collision with stairs -1 au lieu de -30
					p.speedX=MAX_JUMP_SPEED;
			break; 
			/*case SDLK_DOWN :
				I.down=1;
				    p.yvelocity =  1;
			break;*/
			}
		break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				I.right=0;
			break;
			case SDLK_LEFT :
				I.left=0;
      		break;
			case SDLK_SPACE :
			I.jump=0; 

			break;
			//case SDLK_DOWN :
			//	I.down=0;
			//	if( p.yvelocity > 0 )
			//			p.yvelocity = 0;
		//	break;
			}
		break;
		}
	}


 if (I.right==1)
{
	p.speedX+=1;
	animation_right(&p);
	if (I.jump==0) mouvementright (&p);
	 else if (I.jump==1) jumpright (&p);
scrolling_right (&b,&p,ecran);
}
else if (I.left==1 )
{
	p.speedX+=SPEED;
	animation_left(&p);
	if (I.jump==0)  mouvementleft (&p);
	else if (I.jump==1) jumpleft (&p);
		scrolling_left (&b,&p,ecran);

}
/*else if (I.left==0 && I.jump==0 && I.right==0 )
{
	animation_stable(&p);
}*/
p.speedY+=GRAVITY;
 p.rect.y += p.speedY;
 p.rect_relative.y += p.speedY;
 if(p.rect.y >= ground)
 	 {
 		 p.rect.y= ground;
		 p.rect_relative.y= ground;
 		 p.speedY = 0;
}
    //SDL_BlitSurface(back,NULL,ecran,NULL);
	afficher_background(ecran,&b);
	afficher_perso (&p,ecran);
	SDL_Flip(ecran);
	SDL_Delay(16);
}
TTF_Quit();




}


