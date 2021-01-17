#ifndef ___VAISSEAU___
#define ___VAISSEAU___



void chargementVaisseau(SDL_Renderer **renderer);
void deplacementVaisseau(int direction);
void tire(void);
void miseAjourVaisseau(void);
void afficheVaisseau(SDL_Renderer **renderer);
int vaisseauXcord(void);
int vaisseauYcord(void);
void destroyVaisseauTexture(void);
SDL_Rect *vaisseauRect(void);
#endif // ___VAISSEAU___


