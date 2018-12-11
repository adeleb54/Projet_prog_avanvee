#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "constante.h"

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
  int pause;
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
//   int change;
  int est_passe;
}VarG;
VarG* createVarG(SDL_Surface* screen);
int getColorKey(VarG* var);
int getGameOver(VarG* var);
int getTimer(VarG* var);
int getPause(VarG* var);
int getSpace(VarG* var);
int getChangeSp(VarG* var);
int getVie(VarG* var);
int getSecondes(VarG* var);
int getMinutes(VarG* var);
int getHeure(VarG* var);
int getItem(VarG* var);
int getTpsItem(VarG* var);
int getClef(VarG* var);
int getHaut(VarG* var);
int getBas(VarG* var);
int getNiveau(VarG* var);
// int getChange(VarG* var);
int getPass(VarG* var);

void destroyVarG(VarG* var);

#endif 