#ifndef ___ENNEMIE___
#define ___ENNEMIE___

#define DEBUT_POS_ENNEMIEX 150
#define DEBUT_POS_ENNEMIEY 400
#define LARGEUR_ENNEMIE 32
#define HAUTEUR_ENNEMIE 32
#define X_SPACE 50
#define Y_SPACE 50
#define Y_VITESSE 1
#define X_VITESSE 1
#define CHOISIE_DIRECTION 7  //0-7{NORD|EST|SUD|OUEST|NORDEST|NORDOUEST|SUDEST|SUDOUEST}
#define DIRECTION_INITIALE 3
#define ENNEMIE_TYPE 4




typedef enum{nord,est,sud,ouest,nordest,nordouest,sudest,sudouest,repos}Mouvement;
typedef enum{megatron,shockwave,galvatron,starscream}Decepticon;


typedef struct enmi{
 SDL_Texture *ennemie_txt;
 SDL_Rect ennemie_rect;
 int vie;
 int mort;
 Mouvement direction;
}Ennemie;




/**************************** ENNEMIE STRUCT ******************************/

char *DecepticonLoader(Decepticon type);
Ennemie InitEnnemieStruct(SDL_Renderer *renderer,int xpos,int ypos,Mouvement mouve,Decepticon type);
void afficheEnnemieStruct(SDL_Renderer *renderer,Ennemie e);
void afficheEnnemieTabStruct(SDL_Renderer *renderer,Ennemie ennemies[],int taille);
SDL_Texture *createTexture(SDL_Renderer *renderer,char *chemin);
void ennemieGenerateur(SDL_Renderer *renderer,Ennemie ennemies[],int nombre,int xposInit,int yposInit);
void deplacementsEnnemies(Ennemie ennemies[],int taille);
void detecteCollision(Ennemie ennemies[],int taille);
int totalMort(Ennemie ennemie[],int taille);
void supprimeEnnemieMort(Ennemie ennemies[],int taille,int indice);
void chargementFont(void);
void closeFont(void);
SDL_Texture *nouveauMessage(SDL_Renderer *renderer,char *message,SDL_Color fg);
void afficheScore(SDL_Renderer *renderer,int x,int y,int l,int h);








#endif // ___ENNEMIE___


