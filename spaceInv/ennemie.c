#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<time.h>
#include "ennemie.h"
#include "vaisseau.h"
#include "missile.h"
#define TAILLE_CHAR 1000




char * megatron_png = "textures/ennemies/megatron.png";
char * shockwave_png = "textures/ennemies/shockwave.png";
char * galvatron_png = "textures/ennemies/galvatron.png";
char * starscream_png = "textures/ennemies/starscream.png";

SDL_Texture* score = NULL;
SDL_Rect score_rect;
char score_chaine[TAILLE_CHAR];
int ennemie_tuer = 0;
TTF_Font *font = NULL;
/**************************** ENNEMIE STRUCT ******************************/

Ennemie InitEnnemieStruct(SDL_Renderer *renderer,int xpos,int ypos,Mouvement mouv,Decepticon type){
   Ennemie temp;
   temp.ennemie_txt = createTexture(renderer,DecepticonLoader(type));
   temp.ennemie_rect.x = xpos;
   temp.ennemie_rect.y = ypos;
   temp.ennemie_rect.w = LARGEUR_ENNEMIE;
   temp.ennemie_rect.h = HAUTEUR_ENNEMIE;
   temp.direction = mouv;
   temp.mort = 0;
   return temp;
}

char *DecepticonLoader(Decepticon type){
  switch(type){
      case megatron:
            return megatron_png;
             break;
      case shockwave:
            return shockwave_png;
            break;
      case galvatron:
            return galvatron_png;
            break;
      default:
          return starscream_png;
  }
}

void afficheEnnemieStruct(SDL_Renderer *renderer,Ennemie e){
 SDL_RenderCopy(renderer,e.ennemie_txt,NULL,&e.ennemie_rect);
}

void afficheEnnemieTabStruct(SDL_Renderer *renderer,Ennemie ennemies[],int taille){
     for(int i=0;i<taille;i++){
            if(!ennemies[i].mort)SDL_RenderCopy(renderer,ennemies[i].ennemie_txt,NULL,&(ennemies[i].ennemie_rect));
     }
 }

void ennemieGenerateur(SDL_Renderer *renderer,Ennemie ennemies[],int nombre,int xposInit,int yposInit){
    srand(time(NULL));
    for(int i=0;i<nombre;i++){
          int ennemie_hasard  = rand()%ENNEMIE_TYPE;
        ennemies[i] = InitEnnemieStruct(renderer,xposInit,yposInit,DIRECTION_INITIALE,ennemie_hasard);
         xposInit = xposInit+X_SPACE;
         yposInit = yposInit+Y_SPACE;

    }
}

void deplacementsEnnemies(Ennemie ennemies[],int taille){
    srand(time(NULL));
    for(int i=0;i<taille;i++){
    if(ennemies[i].ennemie_rect.x>=610){
      ennemies[i].ennemie_rect.x =610;
      ennemies[i].direction = rand()%CHOISIE_DIRECTION;
    }
    if(ennemies[i].ennemie_rect.x<=0){
      ennemies[i].ennemie_rect.x = 0;
      ennemies[i].direction = rand()%CHOISIE_DIRECTION;
    }
    if(ennemies[i].ennemie_rect.y<=0){
      ennemies[i].ennemie_rect.y =0;
      ennemies[i].direction = rand()%CHOISIE_DIRECTION;
    }
    if(ennemies[i].ennemie_rect.y>=400){
      ennemies[i].ennemie_rect.y = 400;
      ennemies[i].direction = rand()%CHOISIE_DIRECTION;
    }

switch(ennemies[i].direction){
     case nord:
 ennemies[i].ennemie_rect.y = ennemies[i].ennemie_rect.y-Y_VITESSE;
        break;

     case est:
 ennemies[i].ennemie_rect.x = ennemies[i].ennemie_rect.x+X_VITESSE;
        break;
//s
     case sud:
 ennemies[i].ennemie_rect.y = ennemies[i].ennemie_rect.y+Y_VITESSE;
        break;

     case ouest:
 ennemies[i].ennemie_rect.x = ennemies[i].ennemie_rect.x-X_VITESSE;
        break;

     case nordest:
 ennemies[i].ennemie_rect.y = ennemies[i].ennemie_rect.y-Y_VITESSE;
 ennemies[i].ennemie_rect.x = ennemies[i].ennemie_rect.x+X_VITESSE;
        break;

     case nordouest:
 ennemies[i].ennemie_rect.y = ennemies[i].ennemie_rect.y-Y_VITESSE;
 ennemies[i].ennemie_rect.x = ennemies[i].ennemie_rect.x-X_VITESSE;
        break;

     case sudest:
 ennemies[i].ennemie_rect.y = ennemies[i].ennemie_rect.y+Y_VITESSE;
 ennemies[i].ennemie_rect.x = ennemies[i].ennemie_rect.x+X_VITESSE;
        break;

     case sudouest:
 ennemies[i].ennemie_rect.y = ennemies[i].ennemie_rect.y+Y_VITESSE;
 ennemies[i].ennemie_rect.x = ennemies[i].ennemie_rect.x-X_VITESSE;
        break;

     default:
          break;
         }
detecteCollision(ennemies,taille);

}

}

void detecteCollision(Ennemie ennemies[],int taille){
    taille = taille - totalMort(ennemies,taille);
    if(!taille)return;
    for(int i=0;i<taille;i++){
    if(missileLancer()){
        if(SDL_HasIntersection(missile_Rect(),&(ennemies[i].ennemie_rect))==SDL_TRUE){
                 ennemies[i].mort = 1;
                 ennemie_tuer+=10;
                 supprimeEnnemieMort(ennemies,taille,i);
                                                                                     }
                       }
                            }
    }


int totalMort(Ennemie ennemie[],int taille){
   int mort = 0;
   for(int i=0;i<taille;i++){
       if(ennemie[i].mort) mort++;
   }
   return mort;
}

void supprimeEnnemieMort(Ennemie ennemies[],int taille,int indice){
  for(int i=indice;i<taille-1;i++){
        ennemies[i] = ennemies[i+1];
  }
}

SDL_Texture *createTexture(SDL_Renderer *renderer,char *chemin){
 SDL_Surface *temp = IMG_Load(chemin);
 SDL_SetColorKey(temp,1,SDL_MapRGB(temp->format,255,0,255));
 SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,temp);
 SDL_FreeSurface(temp);
 return texture;
 }

 void chargementFont(){
font = TTF_OpenFont("angelina.ttf",100);
    if(font==NULL) printf("Erreur Lors du chargement de style Angelina Fun NouveauMessage\n");
 }

 void closeFont(){
  TTF_CloseFont(font);
 }


 SDL_Texture* nouveauMessage(SDL_Renderer *renderer,char *message,SDL_Color fg){
    SDL_Surface *temp = TTF_RenderText_Solid(font,message,fg);
    SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer,temp);
    SDL_FreeSurface(temp);
    return txt;
 }

 void afficheScore(SDL_Renderer *renderer,int x,int y,int l,int h){
 SDL_Color color;
  color.a = 255; color.r = 255; color.b = 0; color.g = 0;
  score_rect.x = x; score_rect.y = y; score_rect.w = l; score_rect.h = h;
  sprintf(score_chaine,"score %d",ennemie_tuer);
  score = nouveauMessage(renderer,score_chaine,color);
  SDL_RenderCopy(renderer,score,NULL,&score_rect);
 }



