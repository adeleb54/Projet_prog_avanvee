#ifndef FONCTION_H
#define FONCTION_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

/* Size of the window */
#define SCREEN_WIDTH  930
#define SCREEN_HEIGHT 589

/* Size of the grass texture picture */
#define SKY_WIDTH    500
#define SKY_HEIGHT   190

/* Size of one image: */
#define SPRITE_SIZE 	32
#define BLOC_SIZE       31
#define FONT_SIZE 	32

/* Order of the different directions in the picture: */
#define DIR_RIGHT       1
#define DIR_LEFT        3

#define SAUT 1
#define PASSAUT 0

#define HSAUT 50
#define SOL 557

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


#endif 