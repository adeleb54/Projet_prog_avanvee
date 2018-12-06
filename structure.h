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
int getPosX(Image* picture);
int getPosY(Image* picture);
SDL_Rect getPos(Image* picture);
void destroyImage(Image* picture);
void setImX (Image* picture, int x);
void setImY (Image* picture, int y);
void setIm(Image* picture, int x, int y);
void setPosX (Image* picture, int x);
void setPosY (Image* picture, int y);

  
typedef struct VariablesGlobales{
  int colorkey;
  int gameover;
  int timer;
  int pauseV;
  int space;
  int changspace;
  int vie;
  int secondes, minutes, heures;
  int item;
  int tempsItem;
  int clef; 
  int haut;
  int bas; 
  int niveau;
  int change;
  int est_passe;
}VarG;
  

#endif 