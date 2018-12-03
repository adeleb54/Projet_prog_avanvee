#ifndef FONCTION_H
#define FONCTION_H


#include "structure.h"

int collision(SDL_Rect A, SDL_Rect B, int *saut, char* type);

void HandleEvent(SDL_Event event,
        int *quit, Sprite* sprite, VariablesG* var);

int start (VariablesG* var, Image *skyL, Image *spriteDem, Image *spriteQuit, SDL_Surface *screen, Image *font);

void afficher_bloc(const char* nomFichier, int *plat_array, SDL_Rect *plateformePos, int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart );

int pause (VariablesG *var, Image *spritePause, SDL_Surface *screen);

void move (Sprite* sprite);

void ennemyMove(SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, int *ennemy_array, int *enDirection, int *enAnimFlip, int *change, int *delaiEN, SDL_Rect *plateformePos, int *plat_array, Sprite* sprite,
		 int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage);

void spriteCollide (Sprite *sprite, SDL_Rect *plateformePos, int *plat_array, int *ennemy_array, int *item, 
		    int *clef, int *tempsItem, int *niveau, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart);

void lose_life (Sprite* sprite);

void stopEnnemy (int *EnDamage, int *enTempsDamage);

void fTimer (int* timer, int* heures, int* minutes, int* secondes);

void Saut (Sprite *sprite, int *plat_array, SDL_Rect *plateformePos);

int game_over (Sprite *sprite, Image *spriteGameover, SDL_Surface *screen);

void drawSky (Image *sky, SDL_Surface *screen);

void drawFont (Image *font, SDL_Surface *screen, int *heures, int *minutes, int *secondes, int *clef, Sprite* sprite);

void drawBloc(SDL_Surface **plateforme, SDL_Surface *screen, SDL_Rect *blocImage, SDL_Rect *plateformePos, int *plat_array);

void drawSprite (Sprite *sprite, SDL_Surface *screen);

void drawEnnemy (SDL_Surface **ennemy, SDL_Surface *screen, SDL_Rect *ennemyImage, SDL_Rect *ennemyPosition, int *enDirection, int *enAnimFlip, 
		 int *ennemy_array, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage);

void drawBonus (Image *oneup, SDL_Surface *screen,VariablesG* var, Sprite *sprite);

#endif 
