#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constante.h"

typedef struct Image{
  char* nom;
  SDL_Surface* image;
  SDL_Rect position;
  SDL_Rect taille;
}Image;

typedef struct VariablesGenerales{
  int gameOver;
  int vie;
  int secondes;
  int minutes;
  int heures;
  int item;
  int tempsItem;
  int clef;  
  int haut;
  int bas; 
  int entree;
  int select;
  int niveau;
  int change;
}VariablesG;

typedef struct VariablesSprite{
  int debutSaut;
  int finSaut;
  int saut;
  int hperso;
  int droite;
  int gauche;
  int delai;
  int damage;
  int tempsDam;
  int anim;
  int dir;
  int vie;
}VariablesS;

typedef struct Sprite{
  Image* image;
  VariablesS* var;  
}Sprite;

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

VariablesS* createVarS(int debutSaut, int saut, int finSaut, int hperso, int droite, int gauche, int delai, int damage, int tempsDam, int anim);

Sprite* createSprite(Image* image);
Image* getImage(Sprite* sprite);
VariablesS* getVar(Sprite* sprite);
int getEtatSaut(Sprite* sprite);
int getVie(Sprite* sprite);
int* pointeurSaut(Sprite* sprite);
void setSaut(Sprite* sprite, int finSaut, int debutSaut, int saut);
void initDam(Sprite* sprite);
void setDamage(Sprite* sprite);
void incrTempsDam(Sprite* sprite);
void setDir(Sprite* sprite, int dir);
void anim(Sprite* sprite, int animation);
void initDelai(Sprite* sprite);
void incrDelai(Sprite* sprite);
void incrVie(Sprite* sprite);
void desincrVie(Sprite* sprite);
void initHPerso(Sprite* sprite);

#endif 