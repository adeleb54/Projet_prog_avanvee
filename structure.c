#include "structure.h"

Image* createImage(char* nom, int x, int y, int width, int height, int imX, int imY){
  
  Image* picture = malloc(sizeof(Image));	
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
void destroyImage(Image* picture){
  SDL_FreeSurface(picture->image);
  free(picture);
  picture = NULL;
}


VariablesS* createVarS(int debutSaut, int saut, int finSaut, int hperso, int droite, int gauche, int delai, int damage, int tempsDam, int anim){
  VariablesS* var = malloc(sizeof(VariablesS));
  var->debutSaut = debutSaut;
  var->saut = saut;
  var->finSaut = finSaut;
  var->hperso = hperso;
  var->droite = droite;
  var->gauche = gauche;
  var->delai = delai;
  var->damage = damage;
  var->tempsDam = tempsDam;
  var->anim = anim;
  var->dir = DIR_RIGHT;
  var->vie = 5;
  return var;
}
VariablesG* createVarG(){
  VariablesG* var = malloc(sizeof(VariablesG));
  var->gameOver = 2;
  var->timer = 0;
  var->secondes = 0;
  var->minutes = 0;
  var->heures = 0;
  var->item = 0;
  var->tempsItem = 0;
  var->clef = 0;
  var->haut = 0;
  var->bas = 0;
  var->entree = 0;
  var->select = 0;
  var->niveau = 1;
  var->pause = 0;
  var->space = 0;
  var->changeSpace = 1;
  return var;
}
void setSelect(VariablesG* var, int select){
  var->select = select;
}
void setGameOver(VariablesG* var, int gameO){
  var->gameOver = gameO;
}
void setHaut(VariablesG* var, int haut){
  var->haut = haut;
}
void setBas(VariablesG* var, int bas){
  var->bas = bas;
}
void setEntree(VariablesG* var, int entree){
  var->entree = entree;
}
void incrTempsIt(VariablesG* var){
  var->tempsItem++;
}
void initItem(VariablesG* var){
  var->tempsItem = 0;
  var->item = 0;
}
void setPause(VariablesG* var, int pause){
  var->pause = pause;
}
void setChangeSp(VariablesG* var, int change){
	var->changeSpace = change;
}
void setHeures(VariablesG* var, int heure){
	var->heures = heure;
}
void setMinutes(VariablesG* var, int minute){
	var->minutes = minute;
}
void setSecondes(VariablesG* var, int seconde){
	var->secondes = seconde;
}
void incrTimer(VariablesG* var){
  var->timer++;
}
void desincrClef(VariablesG* var){
	var->clef--;
}
void incrClef(VariablesG* var){
	var->clef++;
}
void handleIt(VariablesG* var, int item){
	if (var->item == item) {
		var->tempsItem = 0;
	}
	else {
		var->item = item;
	}
}
void incrNiveau(VariablesG* var){
	var->niveau++;
}
int getGameOver(VariablesG* var){
  return var->gameOver;
}
int getHaut(VariablesG* var){
  return var->haut;
}
int getBas(VariablesG* var){
  return var->bas;
}
int getEntree(VariablesG* var){
  return var->entree;
}
int getSelect(VariablesG* var){
  return var->select;
}
int getItem(VariablesG* var){
  return var->item;
}
int getTempsIt(VariablesG* var){
    return var->tempsItem;
}
int getSpace(VariablesG* var){
    return var->space;
}
int getChangeSp(VariablesG* var){
	return var->changeSpace;
}
int getPause(VariablesG* var){
    return var->pause;
}
int getTimer(VariablesG* var){
    return var->timer;
}
int getHeures(VariablesG* var){
    return var->heures;
}
int getMinutes(VariablesG* var){
    return var->minutes;
}
int getSecondes(VariablesG* var){
    return var->secondes;
}
int getClef(VariablesG* var){
	return var->clef;
}
int getNiveau(VariablesG* var){
	return var->niveau;
}

Sprite* createSprite(Image* image){
  Sprite* sprite = malloc(sizeof(Sprite));
  sprite->image = image;  
  sprite->var = createVarS(0,0,1,getPosY(image), 0, 0, 0, 0, 0, 0);
  return sprite;
}
void setSaut(Sprite* sprite, int finSaut, int debutSaut, int saut){
  sprite->var->finSaut = finSaut;
  sprite->var->debutSaut = debutSaut;
  sprite->var->saut = saut;
}
void initDam(Sprite* sprite){
  sprite->var->damage = 0;
  sprite->var->tempsDam = 0;
}
void setDamage(Sprite* sprite){
  sprite->var->damage = 1;
}
void incrTempsDam(Sprite* sprite){
  sprite->var->tempsDam++;
}
void setDir (Sprite* sprite, int dir){
  sprite->var->dir = dir;
}
void incrDelai(Sprite* sprite){
  sprite->var->delai++;
}
void initDelai(Sprite* sprite){
  sprite->var->delai = 0;
}
void anim(Sprite* sprite, int animation){
  sprite->var->anim = animation;
}
void incrVie(Sprite* sprite){
  sprite->var->vie++;
}
void desincrVie(Sprite* sprite){
  sprite->var->vie--;
}
void initHPerso(Sprite* sprite){
  sprite->var->hperso = getPosY(getImage(sprite));
}
Image* getImage(Sprite* sprite){
  return sprite->image;
}
VariablesS* getVar(Sprite* sprite){
  return sprite->var;
}
int getEtatSaut(Sprite* sprite){
  return sprite->var->saut;
}
int getVie(Sprite* sprite){
  return sprite->var->vie;
}
int* pointeurSaut(Sprite* sprite){
  int* pSaut;
  pSaut = &sprite->var->saut;
  return pSaut;
}
// int main(){
//   return 0;
// }
