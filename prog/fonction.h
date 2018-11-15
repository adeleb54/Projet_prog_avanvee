#ifndef FONCTION_H
#define FONCTION_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

/* Size of the window */
#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 608

/* Size of the grass texture picture */
#define SKY_WIDTH    500
#define SKY_HEIGHT   190

/* Size of one image: */
#define SPRITE_SIZE 	32
#define BLOC_SIZE       32
#define FONT_SIZE 	32

/* Order of the different directions in the picture: */
#define DIR_RIGHT       1
#define DIR_LEFT        3

#define EN_DIR_RIGHT   	3
#define EN_DIR_LEFT	2

#define SAUT 1
#define PASSAUT 0

#define HSAUT 50
#define SOL 576

#define NB_SOL 2
#define NB_PLATEFORME 570

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     1

int collision(SDL_Rect A, SDL_Rect B, int *saut);

void HandleEvent(SDL_Event event,
        int *quit, int *currDirection, int *animFlip, int *saut, int *debutsaut, 
	int *hperso, int *finsaut, int *droite, int *gauche, int *space );

void afficher_bloc(const char* nomFichier, int *plat_array, SDL_Rect *plateformePos);

int pause (int *space, int *changspace, int *pause, SDL_Rect pausePosition, SDL_Surface *spritePause, SDL_Surface *screen);

void move (int *droite, int *gauche, SDL_Rect *spritePosition, int *currentDirection, int *finsaut, int *delai, int *animationFlip);

void enemyMove(SDL_Rect *enemyPosition, int *enDirection, int *enAnimFlip, int *delaiEN);

void replacement (SDL_Rect *spritePosition, SDL_Rect *plateformePos, int *plat_array, int saut, int *vie, int *item, int *clef, int *tempsItem);

void fTimer (int* timer, int* heures, int* minutes, int* secondes);

void Saut (int *hperso, SDL_Rect *spritePosition, int *saut, int *plat_array, SDL_Rect *plateformePos, int *debutsaut, int *finsaut);

void drawSky (SDL_Surface *sky, SDL_Surface *screen);

void drawFont (SDL_Surface *font, SDL_Surface *screen, SDL_Rect *fontImage, SDL_Rect *fontPosition, int *heures, int *minutes, int *secondes, int *vie, int *clef);

void drawBloc(SDL_Surface **plateforme, SDL_Surface *screen, SDL_Rect *blocImage, SDL_Rect *plateformePos, int *plat_array);

void drawSprite (SDL_Surface *sprite, SDL_Surface *screen, SDL_Rect *spriteImage, SDL_Rect *spritePosition, int *currentDirection, int *animationFlip);

void drawEnemy (SDL_Surface *enemy, SDL_Surface *screen, SDL_Rect *enemyImage, SDL_Rect *enemyPosition, int *enDirection, int *enAnimFlip);

void drawBonus (SDL_Surface *oneup, SDL_Surface *screen, SDL_Rect *upImage, SDL_Rect *upPosition, int *item, int *tempsItem, SDL_Rect *spritePosition);

#endif 