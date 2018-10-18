#include <SDL.h>
#include <stdio.h>

/* Size of the window */
#define SCREEN_WIDTH  1020
#define SCREEN_HEIGHT 646

/* Size of one image: */
#define SPRITE_SIZE 	32
#define BLOC_SIZE       34

/* Order of the different directions in the picture: */
#define DIR_RIGHT       1
#define DIR_LEFT        3

#define SAUT 1
#define PASSAUT 0

#define HSAUT 50
#define SOL 615

#define NB_SOL 2
#define NB_PLATEFORME 540

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     1

int collision(SDL_Rect A, SDL_Rect B);

void plateforme_test();