#include "structure.h"

Image* createImage(char* nom, int x, int y, int width, int height, int imX, int imY){
  
  Image* picture = malloc(sizeof(Image*));	
//   printf("picture : %p\n", picture);
  SDL_Surface* temp   = SDL_LoadBMP(nom);
  picture->image =  SDL_DisplayFormat(temp);
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
  printf("picture : %p\n", picture);
  SDL_FreeSurface(picture->image);
  free(picture);
  picture = NULL;
}

void setPosX (Image* picture, int x){
  picture->position.x = x;  
}

void setPosY (Image* picture, int y){
  picture->position.y = y;  
}

void setIm(Image* picture, int x, int y){
  picture->taille.x = x;
  picture->taille.y = y;
}

void setImX (Image* picture, int x){
  picture->taille.x = x;  
}

void setImY (Image* picture, int y){
  picture->taille.y = y;  
}