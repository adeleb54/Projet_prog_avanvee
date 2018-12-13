#ifndef CONSTANTE_H
#define CONSTANTE_H

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

/* Size of the window */
#define SCREEN_WIDTH_START  500
#define SCREEN_HEIGHT_START  190
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

#define HSAUT 70
#define SOL 576

#define NB_ENNEMY  10
#define NB_PLATEFORME 570

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     1
#define MAX_VIE		6

/*Number of levels*/
#define MAX_NIVEAU 6

#endif