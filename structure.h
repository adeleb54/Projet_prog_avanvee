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
  int secondes;
  int minutes;
  int heures;
  int timer;
  int item;
  int tempsItem;
  int clef;  
  int haut;
  int bas; 
  int entree;
  int select;
  int niveau;
  int pause;
  int space;
  int changeSpace;
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
  int here;
  SDL_Rect posStart;
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
int getPresence(Sprite* sprite);
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
void isHere(Sprite* sprite);
void initHere(Sprite* sprite);
void initPosStart(Sprite* sprite);
void setPosStart(Sprite* sprite, SDL_Rect pos);

VariablesG* createVarG();
int getGameOver(VariablesG* var);
int getHaut(VariablesG* var);
int getBas(VariablesG* var);
int getEntree(VariablesG* var);
int getSelect(VariablesG* var);
int getItem(VariablesG* var);
int getTempsIt(VariablesG* var);
int getSpace(VariablesG* var);
int getChangeSp(VariablesG* var);
int getPause(VariablesG* var);
int getTimer(VariablesG* var);
int getHeures(VariablesG* var);
int getMinutes(VariablesG* var);
int getSecondes(VariablesG* var);
int getClef(VariablesG* var);
int getNiveau(VariablesG* var);
void setSelect(VariablesG* var, int select);
void setGameOver(VariablesG* var, int gameO);
void setHaut(VariablesG* var, int haut);
void setBas(VariablesG* var, int bas);
void setEntree(VariablesG* var, int entree);
void setPause(VariablesG* var, int pause);
void incrTempsIt(VariablesG* var);
void initItem(VariablesG* var);
void setChangeSp(VariablesG* var, int change);
void setHeures(VariablesG* var, int heure);
void setMinutes(VariablesG* var, int minute);
void setSecondes(VariablesG* var, int seconde);
void incrTimer(VariablesG* var);
void desincrClef(VariablesG* var);
void incrClef(VariablesG* var);
void handleIt(VariablesG* var, int item);
void incrNiveau(VariablesG* var);

#endif 