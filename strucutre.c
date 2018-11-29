#include "structure.h"

Image* createImage(char* nom, int x, int y, int width, int height, int imX, int imY){
	
	Image* picture = malloc(sizeof(Image*));	
  	SDL_Surface* temp   = SDL_LoadBMP(nom);
	picture-> image =  SDL_DisplayFormat(temp);
  	SDL_FreeSurface(temp);
  	picture->position.x = x;
  	picture->position.y = y;
  	picture->taille.w = width;
  	picture->taille.h = height;
  	picture->taille.x = imX;
  	picture->taille.y = imY;  
  	return picture;		
}

void destroyImage(Image* picture){
	SDL_FreeSurface(picture->image);
	free(picture);
	picture = NULL;
}