#include "fonction.h"
  
//Gestion des evenements
void HandleEvent(SDL_Event event, VarS* varS, VarG* var){
  switch (event.type) {
    /* close button clicked */
    case SDL_QUIT:
	setGameOver(var, 1);
	break;

    /* handle the keyboard */
    case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	    case SDLK_ESCAPE:
	    case SDLK_q:
		setGameOver(var, 1);
		break;
		
	    case SDLK_UP:
	      if (getGameOver(var) !=1) {
		if (getFinSaut(varS) != 0) {
		  setNoFinSaut(varS);
		  setSaut(varS);
		  setDebutSaut(varS, getHeight(varS));
		}
	      }
	      setHaut(var, 1);
	      break;
	      
	    case SDLK_DOWN:
	      setBas(var, 1);
	      break;
		
	    case SDLK_LEFT:
	      setGauche(varS);
	      break;
		
	    case SDLK_RIGHT:
	      setDroite(varS);
	      break;
	    
	    case SDLK_SPACE:
	      setSpace(var, 1);
	      break;
	    
	    default:
	      break;
	}
	break;
	
    case SDL_KEYUP:
	switch (event.key.keysym.sym) {
	    case SDLK_UP:
	      setHaut(var, 0);
	      break;
	    
	    case SDLK_DOWN:
	      setBas(var, 0);
	      break;
	    
	    case SDLK_LEFT:
	      setNoGauche(varS);
	      break;
		
	    case SDLK_RIGHT:
	      setNoDroite(varS);
	      break;
		
	    case SDLK_SPACE:
	      setSpace(var, 0);
	      break;
		
	    default :
	      break;
	}
	break;	
	
    case SDL_MOUSEBUTTONDOWN:
      //Si on clique sur recommencer
      //Si on clique sur reprendre
//       if (pause == 0){
// 	if (event.motion.x <= pausePosition.x + 72 && event.motion.x >= pausePosition.x && event.motion.y >= pausePosition.y && event.motion.y <= pausePosition.y + 20){
// 	  printf("gna\n");
// 	} 
//       }
      break;
  }
}
  
void HandleEventStart(SDL_Event event, VarG* var)
{
  switch (event.type) {
    /* close button clicked */
    case SDL_QUIT:
	setGameOver(var, 1);
	break;

    /* handle the keyboard */
    case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	    case SDLK_ESCAPE:
	    case SDLK_q:
		setGameOver(var, 1);
		break;
		
	    case SDLK_UP:
	      setHaut(var, 1);
	      break;
	      
	    case SDLK_DOWN:
	      setBas(var, 1);
	      break;
	      
	    case SDLK_RETURN:
	      setEntree(var, 1);
	      break;
	    
	    default:
	      break;
	}
	break;
	
    case SDL_KEYUP:
	switch (event.key.keysym.sym) {
	    case SDLK_UP:
	      setHaut(var, 0);
	      break;
	    
	    case SDLK_DOWN:
	      setBas(var, 0);
	      break;
	      
	    case SDLK_RETURN:
	      setEntree(var, 0);
	      break;
		
	    default :
	      break;
	}
	break;
  }
}

int start (int *finsaut, Image *skyL, Image *spriteDem, Image *spriteQuit, Image *spriteTitre, SDL_Surface *screen, Image *font, VarG* var){
  
  int changhaut, changbas;
  int select = 0;
  while (getGameOver(var) == 2){  
    
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      HandleEventStart(event, var);
    }
    
    if (getHaut(var) == 0) {
	changhaut = 1;
    }
    
    if (changhaut == 1 && getHaut(var) == 1) {
      changhaut = 0;
      select = 1 - select;
    }
    
    if (getBas(var) == 0) {
	changbas = 1;
    }
    
    if (changbas == 1 && getBas(var) == 1) {
      changbas = 0;
      select = 1 - select;
    }
    
    /* draw the background */
    SDL_BlitSurface(skyL->image, NULL, screen, NULL);
    
    SDL_BlitSurface(spriteTitre->image, NULL, screen, &spriteTitre->position);
    
    SDL_BlitSurface(spriteDem->image, NULL, screen, &spriteDem->position);
    
    SDL_BlitSurface(spriteQuit->image, NULL, screen, &spriteQuit->position);
    
    if (select == 0) {
      setPosX(font, 190);
      setPosY(font, 90);
      SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

    }
    
    if (select == 1) {
      setPosX(font, 190);
      setPosY(font, 120);
      SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

    }
    
    /* update the screen */
     SDL_UpdateRect(screen, 0, 0, 0, 0);
     
    if (getEntree(var) == 1) {
      
      if (select == 0) {
	
	/* clean up */
	destroyImage(skyL);
	destroyImage(spriteDem);
	destroyImage(spriteQuit);
	
	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);
	/* set the title bar */
	SDL_WM_SetCaption("SDL Animation", "SDL Animation");
	/* create window */
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	/* set keyboard repeat */
	SDL_EnableKeyRepeat(10, 10);
	
	setGameOver(var, 0);
    }
          
      if (select == 1) {
	  
	/* clean up */
	destroyImage(skyL);
	destroyImage(spriteDem);
	destroyImage(spriteQuit);
	setGameOver(var, 1);
	SDL_Quit();
	return 0;
      }
      
    }    
  }
  return 1;
}

//Gestion des collisions
int collision(SDL_Rect A, SDL_Rect B, int *saut, char* type){
    if(A.x >= B.x + B.w || A.x + A.w <= B.x || A.y >= B.y + B.h || A.y + A.h <= B.y){
      return 0;
    }
    //collision avec le bas du sprite
    if(A.y + A.h > B.y && A.y + A.h < B.y + 5){
      if (strcmp(type, "perso") == 0){
	*saut = 0;
      }
      return 3;
    }
    
    //collision avec le haut du sprite
    if(A.y < B.y + B.h  && A.y + 5 > B.y + B.h){
      return 4;
    }
    
    //collision avec la gauche du sprite
    if(A.x <= B.x + B.w && A.x > B.x && A.y + A.h >= B.y && A.y <= B.y + B.h){
      return 2;
    }
    
    //collision avec la droite du sprite
    if(A.x + A.w > B.x && A.x < B.x && A.y + A.h >= B.y && A.y <= B.y + B.h){
      return 1;
    }
    
    return 0;
}
  

//Affichage du décor
void afficher_bloc(const char* nomFichier, int *plat_array, SDL_Rect *plateformePos, int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart ){
  for (int i = 0; i<NB_PLATEFORME; i++){
    plat_array[i] = 0;
  }
  for (int i = 0; i<NB_ENNEMY; i++){
    ennemy_array[i] = 0;
    ennemyPosStart[i] = ennemyPosition[i];
  }
  FILE* pFile;
  int c, i = 0;
  int j = 0;
  int posX = 0, posY = BLOC_SIZE;
  pFile = fopen(nomFichier, "r");
  if (pFile==NULL)  perror ("Error opening file"); 
  else {
    c = fgetc(pFile);
    while(c != EOF && i < NB_PLATEFORME){
      switch (c){
	
	case 49 :
	  plat_array[i] = 1;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	  break;
	case 50 :
	  plat_array[i] = 2;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	  break;
	case 51 :
	  plat_array[i] = 3;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	  break;
	case 52 :
	  plat_array[i] = 4;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	  break;
	case 53 :
	  plat_array[i] = 5;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	break;
	case 54 :
	  plat_array[i] = 6;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	break;
	case 55 :
	  plat_array[i] = 7;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	break;
	case 56 :
	  plat_array[i] = 8;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	break;
	case 57 :
	  plat_array[i] = 9;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	break;
	case 97:
	  plat_array[i] = 10;
	  plateformePos[i].x = posX;
	  plateformePos[i].y = posY;
	  i ++;
	break;
	case 101:
	  if (j < NB_ENNEMY){
	    ennemy_array[j] = 1;
	    ennemyPosStart[j].x = posX;
	    ennemyPosStart[j].y = posY;
	    ennemyPosition[j].x = posX;
	    ennemyPosition[j].y = posY + SPRITE_SIZE/2;
	    plat_array[i] = 0;
	    j++;
	  }
	  i++;
	  break;
	default:
	  i++;
	  break;
      }
      posX += BLOC_SIZE;
      if (posX > SCREEN_WIDTH){
	posX = 0;
	posY += BLOC_SIZE;
      }
      c = fgetc(pFile);
    }
    fclose(pFile);
  } 
}
    
//Replacement du personnage
void set_pos (SDL_Rect *spritePosition, int a, int b) {
  spritePosition->x = a;
  spritePosition->y = b;
}

//Gestion de la pause
int pause (VarG* var, Image *spritePause, SDL_Surface *screen){
  
  if (!getSpace(var)) {
      setChangeSp(var,  1);  
  }
  
  if (getChangeSp(var) && getSpace(var) ) {
    setChangeSp(var,  0);
    setPause(var, 1 - getPause(var));
  }
  
  if (getPause(var) == 1) {
    SDL_BlitSurface(spritePause->image, NULL, screen, &spritePause->position);
  }
  
  return getPause(var);
}

//Gestion des déplacements
void move (int *droite, int *gauche, SDL_Rect *spritePosition, int *currentDirection, int *finsaut, int *delai, int *animationFlip){
  if (*droite == 1){
    spritePosition->x += SPRITE_STEP;
    *currentDirection = DIR_RIGHT;
    if (finsaut != 0) {
      *delai = *delai + 1;
    }
    if (*delai == 15) {
      *animationFlip = 1 - *animationFlip;
      *delai = 0;
    }
  }
  if (*gauche == 1) {
    spritePosition->x -= SPRITE_STEP;
    *currentDirection = DIR_LEFT;
    if (*finsaut != 0) {
      *delai = *delai + 1;
    }
    if (*delai == 15) {
      *animationFlip = 1 - *animationFlip;
      *delai = 0;
    }
  }
}

//Replacement de l'ennemi lors de collisions
void ennemyCollide (SDL_Rect *spritePosition, SDL_Rect *ennemyPosition, int *ennemy_array, SDL_Rect *plateformePos, int *plat_array, int* enDirection, 
			int *damage, int *tempsDamage, int *saut, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage, VarG* var){
  for (int i = 0; i<NB_ENNEMY; i++){  
    if ( ennemyPosition[i].x <= 0)
      ennemyPosition[i].x = 0;
    if ( ennemyPosition[i].x >= SCREEN_WIDTH - SPRITE_SIZE) 
      ennemyPosition[i].x = SCREEN_WIDTH - SPRITE_SIZE;
    if ( ennemyPosition[i].y >= SCREEN_HEIGHT - SPRITE_SIZE/2) 
      ennemyPosition[i].y = SCREEN_HEIGHT - SPRITE_SIZE/2;
      
    //collision avec une plateforme
    for (int j = 0; j <NB_PLATEFORME; j++){
      if (plat_array[j] < 5 && plat_array[j] != 0) {
	if (collision(ennemyPosition[i],plateformePos[j], saut, "ennemi")==1){
	  enDirection[i] = EN_DIR_LEFT;
	}
	if (collision(ennemyPosition[i],plateformePos[j], saut, "ennemi")==2){
	  enDirection[i] = EN_DIR_RIGHT;
	}
      }
    }
    //collison avec le perso
    if (collision(ennemyPosition[i], *spritePosition, saut, "ennemi")==1 /*|| collision(ennemyPosition[i], *spritePosition, saut, "ennemi")== 2 || collision(ennemyPosition[i], *spritePosition, saut, "ennemi")== 4*/){
      if(ennemy_array[i] != 0){
	if(*damage == 0 && enDamage[i] == 0){
	  *damage = 1;
	  ennemyPosDamage[i].x = ennemyPosition[i].x;
	  ennemyPosDamage[i].y = ennemyPosition[i].y;
	  enDamage[i] = 1;
	}
      }
    }
  }
}

//Deplacement ennemi
void ennemyMove(SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, int *ennemy_array, int *enDirection, int *enAnimFlip, int *enChange, int *delaiEN, SDL_Rect *plateformePos, int *plat_array, 
		SDL_Rect *spritePosition, int *damage, int *tempsDamage, int *saut, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage, VarG* var){
  for (int i = 0; i<NB_ENNEMY; i++){  
    if (ennemy_array[i] != 0){
      if (enDirection[i] == EN_DIR_LEFT){
	ennemyPosition[i].x -= SPRITE_STEP;
	if((ennemyPosition[i].x <= ennemyPosStart[i].x - 300 || ennemyPosition[i].x <= 0) && enChange[i]){
	  enDirection[i] = EN_DIR_RIGHT;
	}
      }
      else {
	ennemyPosition[i].x += SPRITE_STEP;
	if ((ennemyPosition[i].x >= ennemyPosStart[i].x || ennemyPosition[i].x >= SCREEN_WIDTH) && enChange[i]){
	  enDirection[i] = EN_DIR_LEFT;
	}
      }
      *delaiEN += 1;
      if (*delaiEN == 50){
	*enAnimFlip += 1;
	if (*enAnimFlip == 3){
	  *enAnimFlip = 0;
	}
	*delaiEN = 0;
      }
      
      //Chute
      if (ennemyPosition[i].y != SOL + SPRITE_SIZE/2) {
	  ennemyPosition[i].y += 1;
	  enChange[i] = 0;
      }      
      for (int j = 0; j <NB_PLATEFORME; j++){
	if (plat_array[j] != 0 && plat_array[j] <= 4){
	  if (collision(ennemyPosition[i],plateformePos[j], saut, "ennemi") == 3) {
	      ennemyPosition[i].y -= 1;
	      enChange[i] = 1;
	  }
	}
      }
    }
  }
  ennemyCollide (spritePosition, ennemyPosition, ennemy_array, plateformePos, plat_array, enDirection, damage, tempsDamage, saut, enDamage, enTempsDamage, ennemyPosDamage, var);
}  

void repositionnement(int collision, int i, SDL_Rect *spritePosition, SDL_Rect *plateformePos){
  switch (collision){
    case 1 : 
      spritePosition->x = plateformePos[i].x - SPRITE_SIZE ;
      break;
    case 2 :
      spritePosition->x = plateformePos[i].x + BLOC_SIZE ;
      break;
    case 3 :
      spritePosition->y = plateformePos[i].y - BLOC_SIZE ;
      break;
  }
}

void changeLevel(int *plat_array, SDL_Rect *plateformePos, int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, SDL_Rect *spritePosition, VarG* var){
  switch(getNiveau(var)){
    case 4:      
      afficher_bloc("niveau5.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
      incrNiveau(var);
      break;
    case 3 :
      afficher_bloc("niveau4.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
      set_pos(spritePosition, 32, SOL);
      incrNiveau(var);
      break;
    case 2:
      afficher_bloc("niveau3.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
      set_pos(spritePosition, 0, 64);
      incrNiveau(var);
      break;    
    case 1:
      afficher_bloc("niveau2.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
      set_pos(spritePosition, 32, 64);
      incrNiveau(var);
      break;   
  }
}

// Gestion des items
void gestion_items (int collision, int *plat_array, int bloc, SDL_Rect *spritePosition, SDL_Rect *plateformePos, int i, int *damage, int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, VarG* var) {
  if (collision == 1 || collision == 2 || collision == 3 ){
    switch (bloc){
      
      case 3:
	//Si on a une clef pour l'ouvrir
	if (getClef(var) >= 1) {
	  decrClef(var);
	  plat_array[i] = 0;
	}
	else {
	  repositionnement(collision, i, spritePosition, plateformePos);
	  }
	break;
	
      //Si c'est un bloc à pics
      case 4:
	repositionnement(collision, i, spritePosition, plateformePos);
	if(collision == 3) *damage = 1;
	break;	
      case 5:
	repositionnement(collision, i, spritePosition, plateformePos);
	break;
	
      //Si c'est un coeur
      case 6:
	if (getVie(var) < MAX_VIE) {
	  plat_array[i] = 0;
	  incrVie(var) ;
	  incrItem(var, 1);
	}
	break;
	
      //Si c'est une clef
      case 7 :
	plat_array[i] = 0;
	incrClef(var);
	incrItem(var, 2);
	break;
	
      //Si c'est une porte
      case 8:
	changeLevel(plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart, spritePosition, var);
	break;
	
      //Si c'est un portail
      case 9:
	for (int i = 0; i < NB_PLATEFORME; i++) {
	  if (plat_array[i]==10) {
	    if(getPass(var) == 0){
	      set_pos(spritePosition, plateformePos[i].x, plateformePos[i].y);
	      incrPass(var);
	    }
	  }
	}
	break;
      case 10 :
	for (int i = 0; i < NB_PLATEFORME; i++) {
	  if (plat_array[i]==9) {
	    if(getPass(var) == 0){
	      set_pos(spritePosition, plateformePos[i].x, plateformePos[i].y);
	      incrPass(var);
	    }
	  }
	}
	break;
      default:
	break;
    }
  }
}
  
//Replacement du sprite lors de collisions
void spriteCollide (SDL_Rect *spritePosition, SDL_Rect *plateformePos, int *plat_array, int *ennemy_array, int saut, int *damage, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, VarG* var){
  
  if (spritePosition->x <= 0)
    spritePosition->x = 0;
  if (spritePosition->x >= SCREEN_WIDTH - SPRITE_SIZE) 
    spritePosition->x = SCREEN_WIDTH - SPRITE_SIZE;
  if (spritePosition->y >= SCREEN_HEIGHT - SPRITE_SIZE) 
    spritePosition->y = SCREEN_HEIGHT - SPRITE_SIZE;
    
  if(getPass(var) > 0) {
    incrPass(var);
    if (getPass(var) == 150) {
      initPass(var);
    }
  }
  
  for (int i = 0; i <NB_PLATEFORME; i++){
    if (plat_array[i] < 3 && plat_array[i] != 0) {
      repositionnement(collision(*spritePosition,plateformePos[i], &saut, "perso"), i, spritePosition, plateformePos);
    }
    else{
       gestion_items(collision(*spritePosition,plateformePos[i], &saut, "perso"), plat_array, plat_array[i], spritePosition, plateformePos, 
		     i, damage, ennemy_array, ennemyPosition, ennemyPosStart, var);
    }
  }
  for (int i = 0; i<NB_ENNEMY; i++){
     if (ennemy_array[i] != 0){       
      if (collision(*spritePosition,plateformePos[i], &saut, "perso")==3){
	spritePosition->y = plateformePos[i].y - BLOC_SIZE/2;
      }	
    }
  }
}


/*Gestion de la perte de vie*/
void stopEnnemy (int *EnDamage, int *enTempsDamage) {
  for (int i = 0; i<NB_ENNEMY; i++){
    if (EnDamage[i] == 1) {
      if (*enTempsDamage == 0) {
	*enTempsDamage += 1;
      }
      if (*enTempsDamage == 350) {
	EnDamage[i] = 0;
	*enTempsDamage = 0;
      }
      else {
	*enTempsDamage += 1;
      }
    }
  }
}

/*Gestion de la perte de vie*/
void lose_life (int *damage, int *tempsDamage, VarG* var) {
    if (*damage == 1) {
      if (*tempsDamage == 0) {
	decrVie(var);
	*tempsDamage += 1;
      }
      if (*tempsDamage == 350) {
	*damage = 0;
	*tempsDamage = 0;
      }
      else {
	*tempsDamage += 1;
      }
    }
}

//Gestion du timer
void fTimer (VarG* var){
  setHeures(var, getTimer(var)/(200*3600));
  setMinutes(var, (getTimer(var)/200 - 3600 * getHeures(var))/ 60);
  setSecondes(var, getTimer(var)/200 - 60 * getMinutes(var));
}

//Gestion du saut
void Saut (int *hperso, SDL_Rect *spritePosition, int *saut, int *plat_array, SDL_Rect *plateformePos, int *debutsaut, int *finsaut, int *damage, 
	   int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, VarG* var){
  //setHeight(varS, spritePosition->y);
  *hperso = spritePosition->y;
  int col_haut = 0;
  //Si on a demandé au perso de sauter
  if (*saut) {
    for (int i = 0; i < NB_PLATEFORME; i++){
      if (plat_array[i] != 0){
	//Gestion de la collision avec le haut du perso
	if (collision(*spritePosition, plateformePos[i], saut, "perso")==4){
	  switch (plat_array[i]){
	    //Si c'est un bloc a clef
	    case 3:
	      //Si on a une clef pour l'ouvrir
	      if (getClef(var) >= 1) {
		decrClef(var);
		plat_array[i] = 0;
	      }
	      else {
		col_haut = 1;
	      }
	      break;
	    
	    //Si c'est un bloc à pics vers le bas
	    case 5:
	      *damage = 1;;
	      col_haut = 1;
	      break;
	      
	    //Si c'est un coeur
	    case 6:
	      if (getVie(var) < MAX_VIE) {
		plat_array[i] = 0;
		incrVie(var);
		incrItem(var, 1);
	      }
	      break;
	      
	    //Si c'est une clef
	    case 7 :
	      plat_array[i] = 0;
	      incrClef(var);
	      incrItem(var, 2);
	      break;
	      
	    //Si c'est une porte
	    case 8:	
	      changeLevel(plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart, spritePosition, var);
	      break;
	      
	    //Si c'est un portail
	    case 9:
	      for (int i = 0; i < NB_PLATEFORME; i++) {
		if (plat_array[i]==10) {
		  if(getPass(var) == 0){
		    set_pos(spritePosition, plateformePos[i].x, plateformePos[i].y);
		    incrPass(var);
		  }
		}
	      }
	      break;
	    case 10 :
	      for (int i = 0; i < NB_PLATEFORME; i++) {
		if (plat_array[i]==9) {
		  if(getPass(var) == 0){
		    set_pos(spritePosition, plateformePos[i].x, plateformePos[i].y);
		    incrPass(var);
		  }
		}
	      }
	      break;
	    default :
	      col_haut = 1;
	      break;
	  }
	}
      }
    }
    if ((spritePosition->y >= *debutsaut - HSAUT) && (spritePosition->y != BLOC_SIZE) && !col_haut){
	
      spritePosition->y -= 1;
    }
    
    
    else { *saut = 0; }
  }
  
  if (spritePosition->y != SOL) {
    if (!*saut) {
      spritePosition->y += 1;
    }
  }
  
  for (int i = 0; i <NB_PLATEFORME; i++){
    if (plat_array[i] != 0 && plat_array[i]<= 5){
      if (collision(*spritePosition,plateformePos[i], saut, "perso") == 3) {
	  if (plat_array[i] == 4) {
	    *damage = 1;
	  }
	  spritePosition->y -= 1;
	  *finsaut = 1;
	}
    }
  }
  if (spritePosition->y == SOL) {
    *finsaut = 1;      
  }
}
 
  /*Gestion du game over*/
int game_over (VarG* var, Image *spriteGameover, SDL_Surface *screen, SDL_Surface *sprite, SDL_Rect *spriteImage, SDL_Rect *spritePosition){
  if (getVie(var) == 0) {
    SDL_BlitSurface(spriteGameover->image, NULL, screen, &spriteGameover->position);
    spriteImage->x = 0;
    SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
    return 1;
  }
  else {
    return 0;
  }
}

//Affichages

void drawSky (Image *sky, SDL_Surface *screen){
  SDL_BlitSurface(sky->image, NULL, screen, NULL);
}

void drawTimer(Image *font, SDL_Surface *screen, VarG* var){
  
  //Affichage heures
  //Dizaines
  setImX(font, FONT_SIZE * (getHeures(var)/10));
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

  //Unités
  setImX(font, FONT_SIZE * (getHeures(var)%10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  //Deux points
  setImX(font, 320);
  setPosX(font, font->position.x + 30);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

  
  //Affichage minutes
  //Dizaines
  setImX(font, FONT_SIZE * (getMinutes(var)/10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Unités
  setImX(font, FONT_SIZE * (getMinutes(var)%10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Deux points
  setImX(font, 320);
  setPosX(font, font->position.x + 30);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Affichage secondes
  //Dizaines
  setImX(font, FONT_SIZE * (getSecondes(var)/10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Unités
  setImX(font, FONT_SIZE * (getSecondes(var)%10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
}

void drawFont (Image *font, SDL_Surface *screen, VarG* var){
  
  setImY(font, FONT_SIZE*3);
  
  /***Timer***/
  
  setPosX(font, 10);
  setPosY(font, 0);
  drawTimer(font, screen, var);
  
  /***Clef***/
  
  /*Affichage de la clef*/
  setPosX(font, SCREEN_WIDTH - 180);
  setIm(font, 31, 0);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
   
   /*Affichage du x*/
  setPosX(font, font->position.x + FONT_SIZE);
  setIm(font, FONT_SIZE*8, FONT_SIZE*7);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  /*Affichage du nombre de clefs*/
  setPosX(font, font->position.x + 20);
  setIm(font, FONT_SIZE* getClef(var), FONT_SIZE*3);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  /***Vie***/
  
  /*Affichage du coeur*/
  setPosX(font, SCREEN_WIDTH - 90);
  setIm(font, 0, 0);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

  /*Affichage du x*/ 
  setPosX(font, font->position.x + FONT_SIZE);
  setIm(font, FONT_SIZE*8, FONT_SIZE*7);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position); 

  /*Affichage de la vie restante*/
  setPosX(font, font->position.x + 20);
  setIm(font, FONT_SIZE* getVie(var), FONT_SIZE*3);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
}

void drawBloc(SDL_Surface **plateforme, SDL_Surface *screen, SDL_Rect *blocImage, SDL_Rect *plateformePos, int *plat_array){
  for (int i=0; i < NB_PLATEFORME; i++){ 
    if (plat_array[i] != 0){
      blocImage->x = (plat_array[i] - 1)* BLOC_SIZE;
      SDL_BlitSurface(plateforme[i],blocImage, screen, &plateformePos[i]);   
    }
  }
}

void drawBonus (Image *oneup, SDL_Surface *screen, SDL_Rect *spritePosition, VarG* var){
  /*Draw bonus*/
  if (getItem(var) != 0){
    setPosX(oneup,spritePosition->x);
    setPosY(oneup,spritePosition->y - 40);
    setImX(oneup,(getItem(var) - 1)*31);
    incrTpsItem(var);
    SDL_BlitSurface(oneup->image, &oneup->taille, screen, &oneup->position);
    if (getTpsItem(var) == 150) {
      setItem(var, 0);
      initTpsItem(var);  
    }    
  }
}

void drawSprite (SDL_Surface *sprite, SDL_Surface *screen, SDL_Rect *spriteImage, SDL_Rect *spritePosition, int *currentDirection, int *animationFlip, int *damage, int *tempsDamage, VarG *var){
  if (getNiveau(var) < 5) {
    spriteImage->x = SPRITE_SIZE * (2 * *currentDirection + *animationFlip);
    if(*damage == 0) { 
      SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
    }
    if(*damage == 1) {
      if ((*tempsDamage/20)%2 == 1) {
	SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
      }
    }
  }
}


void drawEnnemy (SDL_Surface **ennemy, SDL_Surface *screen, SDL_Rect *ennemyImage, SDL_Rect *ennemyPosition, int *enDirection, int *enAnimFlip, 
		 int *ennemy_array, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage){
  for (int i = 0; i<NB_ENNEMY; i++){
    if (ennemy_array[i] != 0){
      if (enDamage[i] == 0){
	ennemyImage->y = SPRITE_SIZE/2 * enDirection[i];
	ennemyImage->x = SPRITE_SIZE/2 * *enAnimFlip;	  
	SDL_BlitSurface(ennemy[i], ennemyImage, screen, &ennemyPosition[i]);
      }
      if(enDamage[i] == 1) {
	if ((*enTempsDamage/20)%2 == 1) {
	  SDL_BlitSurface(ennemy[i], ennemyImage, screen, &ennemyPosDamage[i]);
	}
	ennemyPosition[i].x = ennemyPosDamage[i].x;
	ennemyPosition[i].y = ennemyPosDamage[i].y;
      }
    }
  }
}
void drawEndG (SDL_Surface *sprite, SDL_Surface *screen, SDL_Rect *spriteImage, SDL_Rect *spritePosition, Image *font, Image *spriteEndG, Image *spriteWP, int *currentDirection, int *animationFlip, VarG *var) {
  if (getClaquettes(var) < 30) {
    incrClaquettes(var);
  }
  if (getClaquettes(var) == 30) {
    *animationFlip = 1 - *animationFlip;
    resetClaquettes(var);
  }
  
  *currentDirection = DIR_RIGHT;
  spriteImage->x = SPRITE_SIZE * (2 * *currentDirection + *animationFlip);
  
  spritePosition->x = 32;
  
  spritePosition->y = 64;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 160;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 256;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 352;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 448;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 544;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  
  
  *currentDirection = DIR_LEFT;
  spriteImage->x = SPRITE_SIZE * (2 * *currentDirection + *animationFlip);
  
  spritePosition->x = 896;
  
  spritePosition->y = 64;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 160;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 256;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 352;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 448;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  spritePosition->y = 544;
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
  
  SDL_BlitSurface(spriteEndG->image, NULL, screen, &spriteEndG->position);
  
  setPosY(font, 320);
  setPosX(font, 384);
  drawTimer(font, screen, var);
  
  SDL_BlitSurface(spriteWP->image, NULL, screen, &spriteWP->position);
}