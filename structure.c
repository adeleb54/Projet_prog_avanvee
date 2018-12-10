#include "structure.h"

Image* createImage(char* nom, int x, int y, int width, int height, int imX, int imY){
	
	Image* picture = malloc(sizeof(Image));	
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
SDL_Rect getPos(Image* picture){
  return picture->position;
}
int getPosX(Image* picture){
  return picture->position.x;
}
int getPosY(Image* picture){
  return picture->position.y;
}

VarG* createVarG(SDL_Surface * screen){
  VarG* var = malloc(sizeof(VarG));
  var->colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  var->gameover = 2;
  var->timer = 0;
  var->pause = 1;
  var->space = 0;
  var->changspace = 1;
  var->vie = 3;
  var->item = 0;
  var->tempsItem = 0;
  var->clef = 0;  
  var->haut = 0;
  var->bas =  0; 
  var->niveau = 1;
  var->est_passe = 0;
  return var;
}
int getColorKey(VarG* var){
  return var->colorkey;
}
int getGameOver(VarG* var){
  return var->gameover;
}
int getTimer(VarG* var){
  return var->timer;
}
int getPause(VarG* var){
  return var->pause;
}
int getSpace(VarG* var){
  return var->space;
}
int getChangeSp(VarG* var){
  return var->changspace;
}
int getVie(VarG* var){
  return var->vie;
}
int getSecondes(VarG* var){
  return var->secondes;
}
int getMinutes(VarG* var){
  return var->minutes;
}
int getHeure(VarG* var){
  return var->heures;
}
int getItem(VarG* var){
  return var->item;
}
int getTpsItem(VarG* var){
  return var->tempsItem;
}
int getClef(VarG* var){
  return var->clef;
}
int getHaut(VarG* var){
  return var->haut;
}
int getBas(VarG* var){
  return var->bas;
}
int getNiveau(VarG* var){
  return var->niveau;
}
// int getChange(VarG* var);
int getPass(VarG* var){
  return var->est_passe;
}

void destroyVarG(VarG* var){
  free(var);
  var = NULL;
}