#include <SDL.h>
#include <stdio.h>
#include <stdarg.h>

/* Size of the window */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

/* Size of the grass texture picture */
#define GRASS_SIZE    32

/* Size of one image: */
#define SPRITE_SIZE     32
#define BLOC_SIZE       39

/* Order of the different directions in the picture: */
#define DIR_RIGHT       1
#define DIR_LEFT        3

#define SAUT 1
#define PASSAUT 0

#define HSAUT 50
#define SOL 448

#define NB_SOL 2
#define NB_PLATEFORME 1

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     1