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
int getPosX(Image* picture){
  return picture->position.x;
}
int getPosY(Image* picture){
  return picture->position.y;
}
void destroyImage(Image* picture){	
  printf("picture : %p\n", picture);
  SDL_FreeSurface(picture->image);
  free(picture);
  picture = NULL;
}


VariablesS* createVarS(int debutSaut, int saut, int finSaut, int hperso, int droite, int gauche, int delai, int damage, int tempsDam, int anim, int dir){
  VariablesS* var = malloc(sizeof(VariablesS*));
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
  var->dir = dir;
  return var;
}

Sprite* createSprite(Image* image){
  Sprite* sprite = malloc(sizeof(Sprite*));
  sprite->image = image;  
  sprite->var = createVarS(0,0,1,getPosY(image), 0, 0, 0, 0, 0, 0, 0);
  return sprite;
}
void setSaut(Sprite* sprite, int finSaut, int debutSaut, int saut){
  sprite->var->finSaut = finSaut;
  sprite->var->debutSaut = debutSaut;
  sprite->var->saut = saut;
}
void setDamage(Sprite* sprite, int dam){
  sprite->var->damage = dam;
}
void setDir (Sprite* sprite, int dir){
  sprite->var->dir = dir;
}
void incrDelai(Sprite* sprite){
  sprite->var->delai = sprite->var->delai + 1;
}
void initDelai(Sprite* sprite){
  sprite->var->delai = 0;
}
void anim(Sprite* sprite, int animation){
  sprite->var->anim = animation;
}
Image* getImage(Sprite* sprite){
  return sprite->image;
}
VariablesS* getVar(Sprite* sprite){
  return sprite->var;
}
int main(){
  return 0;
}
