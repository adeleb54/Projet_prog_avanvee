#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Image{
	char* nom;
	SDL_Surface* image;
	SDL_Rect position;
	SDL_Rect taille;
}Image;

Image* createImage(char* nom, int x, int y, int width, int height, int imX, int imY);
void destroyImage(Image* picture);

#endif 