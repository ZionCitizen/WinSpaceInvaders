#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "vaisseau.h"

#define LARGEUR_VAISSEAU  64
#define HAUTEUR_VAISSEAU 64
#define DEBUT_VAISSEAU_POSX  150
#define DEBUT_VAISSEAU_POSY  400
#define vitesse_vaisseau 1

 SDL_Rect vaisseau_rect;
 SDL_Texture *vaisseau_txt = NULL;


void chargementVaisseau(SDL_Renderer **renderer){
  SDL_Surface *temp = IMG_Load("textures/vaisseau.png");
  SDL_SetColorKey(temp,1,SDL_MapRGB(temp->format,255,0,255));
  vaisseau_txt = SDL_CreateTextureFromSurface(*renderer,temp);
  SDL_FreeSurface(temp);

//creation du rectangle le skullette du vaisseau + son initialisation position xY largeur hauteur
  vaisseau_rect.x = DEBUT_VAISSEAU_POSX;
  vaisseau_rect.y = DEBUT_VAISSEAU_POSY;
  vaisseau_rect.w = LARGEUR_VAISSEAU;
  vaisseau_rect.h = HAUTEUR_VAISSEAU;
}


void deplacementVaisseau(int direction){
   if(direction==1&&vaisseau_rect.x>=580)direction = -1;  // gauche
   if(direction==0&&vaisseau_rect.x<=-5)direction = -1; // droite

   if(direction==0) vaisseau_rect.x = vaisseau_rect.x - vitesse_vaisseau;  // gauche
   if(direction==1) vaisseau_rect.x = vaisseau_rect.x + vitesse_vaisseau;  // droite

}

void tire(){}



int vaisseauXcord(){
return vaisseau_rect.x;}

int vaisseauYcord(){
return vaisseau_rect.y;}

void afficheVaisseau(SDL_Renderer **renderer){
  SDL_RenderCopy(*renderer,vaisseau_txt,NULL,&vaisseau_rect);
}

void destroyVaisseauTexture(){
  SDL_DestroyTexture(vaisseau_txt);
  vaisseau_txt = NULL;
}
SDL_Rect* vaisseauRect(){

 return (&vaisseau_rect);
}


