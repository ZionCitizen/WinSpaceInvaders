#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include "vaisseau.h"
#include "missile.h"
#include "ennemie.h"

#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480
#define FENETRE_POSX 50
#define FENETRE_POSY 50
#define FPS 300
#define NOMBRE_ENNEMIE 5
#define SCORE_POSX 10
#define SCORE_POSY 10
#define SCORE_LARGEUR 80
#define SCORE_HAUTEUR 40

/*
*collision implementation
*generate other ennemies
*display score
*
*/


int directionVaisseau = -1; // 0 gauche | 1 droite
int shoot=0;
SDL_Texture *fond;
Ennemie ennemies[NOMBRE_ENNEMIE];



int subSystemInitialisateur(SDL_Window **window,SDL_Renderer **renderer);
void chargementFond(SDL_Renderer **renderer);
void afficheFond(SDL_Renderer **renderer);
void gestionEvenements(int *running);
void freeMemoire(SDL_Renderer **renderer,SDL_Window **window);



void afficheTous(SDL_Renderer **renderer){
SDL_RenderClear(*renderer);
afficheFond(renderer);
afficheVaisseau(renderer);
afficheMissile(renderer);
afficheEnnemieTabStruct(*renderer,ennemies,NOMBRE_ENNEMIE);
afficheScore(*renderer,SCORE_POSX,SCORE_POSY,SCORE_LARGEUR,SCORE_HAUTEUR);
SDL_RenderPresent(*renderer);
}

void miseAjourTous(){
deplacementVaisseau(directionVaisseau);
deplacementMissile();
deplacementsEnnemies(ennemies,NOMBRE_ENNEMIE);

}


int main(int argc,char *argv[]){
  SDL_Window *window =  NULL;
  SDL_Renderer *renderer = NULL;
  int temps_pour_image = 1000/FPS;
  Uint32 debut_programme;
  int temps_fin_programme;
  int running=0;
  running = subSystemInitialisateur(&window,&renderer);
    chargementFond(&renderer);
    chargementVaisseau(&renderer);
    chargementMissile(&renderer);
    chargementFont();
    ennemieGenerateur(renderer,ennemies,NOMBRE_ENNEMIE,50,100);
    while(running){
     debut_programme = SDL_GetTicks();
     gestionEvenements(&running);
     miseAjourTous();
     afficheTous(&renderer);

     temps_fin_programme = SDL_GetTicks() - debut_programme;
     if(temps_pour_image>temps_fin_programme){
        SDL_Delay(temps_pour_image-temps_fin_programme);
     }
    }

  freeMemoire(&renderer,&window);


   return EXIT_SUCCESS;
}



int subSystemInitialisateur(SDL_Window **window,SDL_Renderer **renderer){
  if(SDL_Init(SDL_INIT_EVERYTHING)==0){
     printf("Initialisation des subsystemes reussi !\n");

  }else{
     printf("Echec Lors de  L initialisations des subsystemes !\n");
     return 0;
   }
   if ( IMG_Init( IMG_INIT_PNG )<0 )
            {
                printf( "Echec lors de L initialisation de IMG_INIT\n" );
            }else{
             printf("Initialisation de IMG_INIT Reussi !\n");
            }

    if(TTF_Init()<0){
           printf("Echec lors de L Initialisation de TTF !\n");
           return 0;
    }else{
           printf("Initialisation de TTF Reussi !\n");
    }

  *window = SDL_CreateWindow("SpaceInvaders |",FENETRE_POSX,FENETRE_POSY,LARGEUR_FENETRE,HAUTEUR_FENETRE,0);
  if(window) printf("Creation de la Fenetre Reussi !\n");
   else{
    printf("Echec lors de  la creation de la Fenetre !\n");
    return 0;
    }

    *renderer = SDL_CreateRenderer(*window,-1,0);
    if(renderer)printf("Creation du renderer Reussi !\n");
    else{
        printf("Echec lors de la creation du Renderer ! \n");
        return 0;
    }
    return 1;
}


void chargementFond(SDL_Renderer **renderer){
     SDL_Surface *surface = IMG_Load("textures/fond.png");
     fond = SDL_CreateTextureFromSurface(*renderer,surface);
     SDL_FreeSurface(surface);
}

void afficheFond(SDL_Renderer **renderer){
  SDL_RenderCopy(*renderer,fond,NULL,NULL);
}

void gestionEvenements(int *running){
SDL_Event event;
SDL_PollEvent(&event);
switch(event.key.keysym.sym){


     break;
case SDLK_RIGHT:
     directionVaisseau = 1;


     break;
case SDLK_LEFT:
     directionVaisseau = 0;

     break;


case SDLK_SPACE:
     shoot = 1;
     joueurApresserTirer(shoot);
    break;

 default:

    break;
}

if(event.type==SDL_QUIT) *running = 0;
}



void freeMemoire(SDL_Renderer **renderer,SDL_Window **window){
 destroyMissileTexture();
 destroyVaisseauTexture();
 SDL_DestroyTexture(fond);
 SDL_DestroyRenderer(*renderer);
 SDL_DestroyWindow(*window);
 IMG_Quit();
 closeFont();
 TTF_Quit();
 SDL_Quit();
 printf("Memoire Liberer !\n");
 printf("Au-Revoir \n");
}



