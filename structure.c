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
  var->pause = 0;
  var->space = 0;
  var->changspace = 1;
  var->vie = 8;
  var->item = 0;
  var->tempsItem = 0;
  var->clef = 0;  
  var->haut = 0;
  var->bas =  0; 
  var->niveau = 1;
  var->est_passe = 0;
  var->entree = 0;
  var->claquettes = 0;
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
int getHeures(VarG* var){
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
int getPass(VarG* var){
  return var->est_passe;
}
int getEntree(VarG* var){
  return var->entree;
}
int getClaquettes(VarG* var) {
  return var->claquettes;
}

void destroyVarG(VarG* var){
  free(var);
  var = NULL;
}
void setGameOver(VarG* var, int gameO){
  var->gameover = gameO;
}
void incrTimer(VarG* var){
  var->timer++;
}
void setPause(VarG* var, int pause){
  var->pause = pause;
}
void setSpace(VarG* var, int space){
  var->space = space;
}
void setChangeSp(VarG* var, int changspace){
  var->changspace = changspace;
}
void incrVie(VarG* var){
  var->vie++;
}
void decrVie(VarG* var){
  var->vie--;
}
void setSecondes(VarG* var, int seconde){
  var->secondes = seconde;
}
void setMinutes(VarG* var, int minute){
  var->minutes = minute;
}
void setHeures(VarG* var, int heure){
  var->heures = heure;
}
void setItem(VarG* var, int item){
  var->item = item;
}
void incrTpsItem(VarG* var){
  var->tempsItem++;
}
void initTpsItem(VarG* var){
  var->tempsItem = 0;
}
void incrClef(VarG* var){
  var->clef++;
}
void decrClef(VarG* var){
  var->clef--;
}
void setHaut(VarG* var, int haut){
  var->haut = haut;
}
void setBas(VarG* var, int bas){
  var->bas = bas;
}
void incrNiveau(VarG* var){
  var->niveau++;
}
void incrPass(VarG* var){
  var->est_passe++;
}
void initPass(VarG* var){
  var->est_passe = 0;
}
void setEntree(VarG* var, int entree){
  var->entree = entree;
}
void incrItem(VarG* var, int item){
  if (getItem(var) == item){
    initTpsItem(var);
  }
  else{
    setItem(var, item);
  }
}
void incrClaquettes(VarG* var){
  var->claquettes++;
}
void resetClaquettes(VarG* var) {
  var->claquettes = 0;
}


VarS* createVarS(){
  VarS* var = malloc(sizeof(VarS));
  var-> dir = DIR_RIGHT;
  var-> anim = 0;
  var-> height = 0;
  var-> debutSaut = 0;
  var-> finSaut = 1;
  var-> saut = 0;
  var-> droite = 0;
  var-> gauche = 0;
  var-> delai = 0;
  var-> damage = 0;
  var-> tpsDamage = 0;
  return var;
}
int getDir(VarS* var){
  return var->dir;
}
int getAnim(VarS* var){
  return var->anim;
}
int getHeight(VarS* var){
  return var->height;
}
int getDebutSaut(VarS* var){
  return var->debutSaut;
}
int getFinSaut(VarS* var){
  return var->finSaut;
}
int getSaut(VarS* var){
  return var->saut;
}
int getDroite(VarS* var){
  return var->droite;
}
int getGauche(VarS* var){
  return var->gauche;
}
int getDelai(VarS* var){
  return var->delai;
}
int getDamage(VarS* var){
  return var->damage;
}
int getTpsDamage(VarS* var){
  return var->tpsDamage;
}
int* getPtSaut(VarS* var){
  return &var->saut;
}

void destroyVarS(VarS* var){
  free(var);
  var = NULL;
}
void setDir(VarS* var, int val){
  var->dir = val;
}
void setHeight(VarS* var, int val){
  var->height = val;
}
void setDebutSaut(VarS* var, int val){
  var->debutSaut = val;
}
void setAnim(VarS* var){
  var->anim = 1 - var->anim;
}
void initDelai(VarS* var){
  var->delai = 0;
}
void incrDelai(VarS* var){
  var->delai++;
}
void setFinSaut(VarS* var){
  var->finSaut = 1;
}
void setSaut(VarS* var){
  var->saut = 1;
}
void setDroite(VarS* var){
  var->droite = 1;
}
void setGauche(VarS* var){
  var->gauche = 1;
}
void setDamage(VarS* var){
  var->damage = 1;
}
void setNoFinSaut(VarS* var){
  var->finSaut = 0;
}
void setNoSaut(VarS* var){
  var->saut = 0;
}
void setNoDroite(VarS* var){
  var->droite = 0;
}
void setNoGauche(VarS* var){
  var->gauche = 0;
}
void setNoDamage(VarS* var){
  var->damage = 0;
}
void initTpsDamage(VarS* var){
  var->tpsDamage = 0;
}
void incrTpsDamage(VarS* var){
  var->tpsDamage ++;
}