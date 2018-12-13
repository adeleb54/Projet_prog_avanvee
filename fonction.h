
#ifndef FONCTION_H
#define FONCTION_H


#include "structure.h"

int collision(SDL_Rect A, SDL_Rect B, int *saut, char* type);

void HandleEvent(SDL_Event event, int *saut, int *debutsaut, int *hperso, int *finsaut,	int *droite, int *gauche, VarG* var);

int start (int *finsaut, Image *skyL, Image *spriteDem, Image *spriteQuit, Image *spriteTitre, SDL_Surface *screen, Image *font, VarG* var);

void afficher_bloc(const char* nomFichier, int *plat_array, SDL_Rect *plateformePos, int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart );

int pause (VarG* var, Image *spritePause, SDL_Surface *screen);

void move (int *droite, int *gauche, SDL_Rect *spritePosition, int *currentDirection, int *finsaut, int *delai, int *animationFlip);

void ennemyMove(SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, int *ennemy_array, int *enDirection, int *enAnimFlip, int *enChange, int *delaiEN, SDL_Rect *plateformePos, int *plat_array, 
		SDL_Rect *spritePosition, int *damage, int *tempsDamage, int *saut, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage, VarG* var);

void spriteCollide (SDL_Rect *spritePosition, SDL_Rect *plateformePos, int *plat_array, int *ennemy_array, int saut, int *damage, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, VarG* var);

void lose_life (int *damage, int *tempsDamage, VarG* var);

void stopEnnemy (int *EnDamage, int *enTempsDamage);

void fTimer (VarG* var);

void Saut (int *hperso, SDL_Rect *spritePosition, int *saut, int *plat_array, SDL_Rect *plateformePos, int *debutsaut, int *finsaut, int *damage, 
	   int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, VarG* var);

int game_over (VarG* var, Image *spriteGameover, SDL_Surface *screen, SDL_Surface *sprite, SDL_Rect *spriteImage, SDL_Rect *spritePosition);

void drawSky (Image *sky, SDL_Surface *screen);

void drawFont (Image *font, SDL_Surface *screen, VarG* var);

void drawBloc(SDL_Surface **plateforme, SDL_Surface *screen, SDL_Rect *blocImage, SDL_Rect *plateformePos, int *plat_array);

void drawSprite (SDL_Surface *sprite, SDL_Surface *screen, SDL_Rect *spriteImage, SDL_Rect *spritePosition, int *currentDirection, int *animationFlip, int *damage, int *tempsDamage, VarG* var);

void drawEnnemy (SDL_Surface **ennemy, SDL_Surface *screen, SDL_Rect *ennemyImage, SDL_Rect *ennemyPosition, int *enDirection, int *enAnimFlip, 
		 int *ennemy_array, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage);

void drawBonus (Image *oneup, SDL_Surface *screen, SDL_Rect *spritePosition, VarG* var);

void drawEndG (SDL_Surface *sprite, SDL_Surface *screen, SDL_Rect *spriteImage, SDL_Rect *spritePosition, Image *font, Image *spriteEndG, Image *spriteWP, int *currentDirection, int *animationFlip, VarG *var);

#endif 