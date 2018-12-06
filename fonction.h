#ifndef FONCTION_H
#define FONCTION_H


#include "structure.h"

int collision(SDL_Rect A, SDL_Rect B, int *saut, char* type);

void HandleEvent(SDL_Event event,
        int *quit, Sprite* sprite, VariablesG* var);

int start (VariablesG* var, Image *skyL, Image *spriteDem, Image *spriteQuit, SDL_Surface *screen, Image *font);

void afficher_bloc(const char* nomFichier, int *plat_array, SDL_Rect *plateformePos, Sprite *ennemy[]);

int pause (VariablesG *var, Image *spritePause, SDL_Surface *screen);

void move (Sprite* sprite);

void ennemyMove(Sprite **ennemy, SDL_Rect *plateformePos, int *plat_array, Sprite* sprite);

void spriteCollide (Sprite *sprite, SDL_Rect *plateformePos, int *plat_array, Sprite** ennemy, VariablesG* var);

void lose_life (Sprite* sprite);

void stopEnnemy (int *EnDamage, int *enTempsDamage);

void fTimer (VariablesG* var);

void Saut (Sprite *sprite, int *plat_array, SDL_Rect *plateformePos);

int game_over (Sprite *sprite, Image *spriteGameover, SDL_Surface *screen);

void drawSky (Image *sky, SDL_Surface *screen);

void drawFont (Image *font, SDL_Surface *screen, VariablesG* var, Sprite* sprite);

void drawBloc(SDL_Surface **plateforme, SDL_Surface *screen, SDL_Rect *blocImage, SDL_Rect *plateformePos, int *plat_array);

void drawSprite (Sprite *sprite, SDL_Surface *screen);

void drawEnnemy (Sprite **ennemy, SDL_Surface *screen);

void drawBonus (Image *oneup, SDL_Surface *screen,VariablesG* var, Sprite *sprite);

#endif 
