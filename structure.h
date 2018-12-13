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
  int entree;
  int est_passe;
  int claquettes;
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
int getHeures(VarG* var);
int getItem(VarG* var);
int getTpsItem(VarG* var);
int getClef(VarG* var);
int getHaut(VarG* var);
int getBas(VarG* var);
int getNiveau(VarG* var);
int getPass(VarG* var);
int getEntree(VarG* var);
int getClaquettes(VarG* var);

void destroyVarG(VarG* var);
void setGameOver(VarG* var, int gameO);
void incrTimer(VarG* var);
void setPause(VarG* var, int pause);
void setSpace(VarG* var, int space);
void setChangeSp(VarG* var, int changspace);
void incrVie(VarG* var);
void decrVie(VarG* var);
void setSecondes(VarG* var, int seconde);
void setMinutes(VarG* var, int minute);
void setHeures(VarG* var, int heure);
void setItem(VarG* var, int item);
void incrTpsItem(VarG* var);
void initTpsItem(VarG* var);
void incrClef(VarG* var);
void decrClef(VarG* var);
void setHaut(VarG* var, int haut);
void setBas(VarG* var, int bas);
void incrNiveau(VarG* var);
void incrPass(VarG* var);
void initPass(VarG* var);
void setEntree(VarG* var, int entree);
void incrItem(VarG* var, int item);
void incrClaquettes(VarG* var);
void resetClaquettes(VarG* var);

typedef struct VariablesSprite{
  int dir;
  int anim;
  int height;
  int debutSaut;
  int finSaut;
  int saut;
  int droite;
  int gauche;
  int delai;
  int damage;
}VarS;

VarS* createVarS();
int getDir(VarS* var);
int getAnim(VarS* var);
int getHeight(VarS* var);
int getDebutSaut(VarS* var);
int getFinSaut(VarS* var);
int getSaut(VarS* var);
int getDroite(VarS* var);
int getGauche(VarS* var);
int getDelai(VarS* var);
int getDamage(VarS* var);

void destroyVarS(VarS* var);
void setDir(VarS* var, int val);
void setAnim(VarS* var, int val);
void setHeight(VarS* var, int val);
void setDebutSaut(VarS* var, int val);
void setFinSaut(VarS* var);
void setSaut(VarS* var);
void setDroite(VarS* var);
void setGauche(VarS* var);
void setDamage(VarS* var);
void setNoFinSaut(VarS* var);
void setNoSaut(VarS* var);
void setNoDroite(VarS* var);
void setNoGauche(VarS* var);
void setNoDamage(VarS* var);

#endif 