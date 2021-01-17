#ifndef ___MISSILE___
#define ___MISSILE___


void chargementMissile(SDL_Renderer **renderer);
void deplacementMissile(void);
void afficheMissile(SDL_Renderer **renderer);
void joueurApresserTirer(int presser);
void destroyMissileTexture();
SDL_Rect* missile_Rect(void);
int missileLancer(void);





#endif // ___MISSILE___


