#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "missile.h"
#include "vaisseau.h"

#define LARGEUR_MISSILE 64
#define HAUTEUR_MISSILE 32
#define VITESSE_MISSILE 2
#define ADJUSTEMENT_MISSILE_X 3
#define ADJUSTEMENT_MISSILE_Y


SDL_Texture *missile_txt=NULL;
SDL_Rect missile_rect;
int detruit = 0;
int feu = 0;


void chargementMissile(SDL_Renderer **renderer){
   SDL_Surface *temp = IMG_Load("textures/missiles/laser0.png");
   SDL_SetColorKey(temp,1,SDL_MapRGB(temp->format,255,0,255));
   missile_txt = SDL_CreateTextureFromSurface(*renderer,temp);
   SDL_FreeSurface(temp);
 // creation du skulette du missile
   missile_rect.x = vaisseauXcord()+ADJUSTEMENT_MISSILE_X;
   missile_rect.y = vaisseauYcord();
   missile_rect.w = LARGEUR_MISSILE;
   missile_rect.h = HAUTEUR_MISSILE;
}

void deplacementMissile(){
    if(feu){
    missile_rect.y = missile_rect.y - VITESSE_MISSILE;
    if(missile_rect.y==0) {
            detruit = 1;
              if(detruit){
                 detruit = 0;
                 feu = 0;
                 missile_rect.x = vaisseauXcord()+ADJUSTEMENT_MISSILE_X;
                 missile_rect.y = vaisseauYcord();
              }
    }
    }else{
    missile_rect.x = vaisseauXcord()+ADJUSTEMENT_MISSILE_X;
    }
}

void afficheMissile(SDL_Renderer **renderer){
  if(feu&&!detruit) SDL_RenderCopy(*renderer,missile_txt,NULL,&missile_rect);
}

void joueurApresserTirer(int presser){
    if(presser){
        feu =  1;}
 }

void destroyMissileTexture(){
     SDL_DestroyTexture(missile_txt);
}


SDL_Rect* missile_Rect(){
return (&missile_rect);}

int missileLancer(){
return feu;}




