#include "fonction.h"
  
//Gestion des evenements
void HandleEvent(SDL_Event event,
        int *quit, Sprite* sprite, VariablesG* var)
{
  switch (event.type) {
    /* close button clicked */
    case SDL_QUIT:
	*quit = 1;
	break;

    /* handle the keyboard */
    case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	    case SDLK_ESCAPE:
	    case SDLK_q:
		*quit = 1;
		break;
	    case SDLK_UP:
	      if (*quit != 1) {
		    if (getVar(sprite)->finSaut && getVar(sprite)->saut == PASSAUT) {
		      setSaut(sprite, 0, getVar(sprite)->hperso, SAUT);
		    }
	      }
	      break;
		
	    case SDLK_LEFT:
	      getVar(sprite)->gauche = 1;
	      break;
		
	    case SDLK_RIGHT:
	      getVar(sprite)->droite = 1;
	      break;
	    
	    case SDLK_SPACE:
	      var->space = 1;
	      break;
	    
	    default:
	      break;
	}
	break;
	
    case SDL_KEYUP:
	switch (event.key.keysym.sym) {
	    
	    case SDLK_LEFT:
	      getVar(sprite)->gauche = 0;
	      break;
		
	    case SDLK_RIGHT:
	      getVar(sprite)->droite = 0;
	      break;
		
	    case SDLK_SPACE:
	      var->space = 0;
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
  
void HandleEventStart(SDL_Event event, VariablesG* var)
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
	      setBas(var,  1);
	      break;
	      
	    case SDLK_RETURN:
	      setEntree(var,  1);
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
	      setBas(var,  0);
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

int start (VariablesG* var, Image *skyL, Image *spriteDem, Image *spriteQuit, SDL_Surface *screen, Image *font){
  
  int changhaut, changbas;
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
      setSelect(var, 1 - getSelect(var));
    }
    
    if (getBas(var) == 0) {
	changbas = 1;
    }
    
    if (changbas == 1 && getBas(var) == 1) {
      changbas = 0;
      setSelect(var, 1 - getSelect(var));
    }
    
    /* draw the background */
    SDL_BlitSurface(skyL->image, NULL, screen, NULL);
    
    SDL_BlitSurface(spriteDem->image, NULL, screen, &spriteDem->position);
    
    SDL_BlitSurface(spriteQuit->image, NULL, screen, &spriteQuit->position);
    
    setPosX(font, 190);
    if (getSelect(var) == 0) {
      setPosY(font, 90);
      SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

    }
    
    if (getSelect(var) == 1) {
      setPosY(font, 120);
      SDL_BlitSurface(font->image,  &font->taille, screen, &font->position);
    }
    
    /* update the screen */
     SDL_UpdateRect(screen, 0, 0, 0, 0);
     
    if (getEntree(var) == 1) {
      
      if (getSelect(var) == 0) {
	
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
          
      if (getSelect(var) == 1) {
	  
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
	*saut = PASSAUT;
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
void afficher_bloc(const char* nomFichier, int *plat_array, SDL_Rect *plateformePos, Sprite *ennemy[]){
  for (int i = 0; i<NB_PLATEFORME; i++){
    plat_array[i] = 0;
  }
  for (int i = 0; i<NB_ENNEMY; i++){
    initHere(ennemy[i]);
    initPosStart(ennemy[i]);
//     ennemy_array[i] = 0;
//     ennemyPosStart[i] = ennemyPosition[i];
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
	case 101:
	  if (j < NB_ENNEMY){
	    isHere(ennemy[j]);
	    setPosX(getImage(ennemy[j]), posX);
	    setPosY(getImage(ennemy[j]), posY + SPRITE_SIZE/2);
	    setPosStart(ennemy[j], getPos(getImage(ennemy[j])));
// 	    ennemyPosStart[j].x = posX;
// 	    ennemyPosStart[j].y = posY;
// 	    ennemyPosition[j].x = posX;
// 	    ennemyPosition[j].y = posY + SPRITE_SIZE/2;
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
void set_pos (Sprite* sprite, int a, int b) {
  setPosX(getImage(sprite),a);
  setPosY(getImage(sprite),b);
}

//Gestion de la pause
int pause (VariablesG *var, Image *spritePause, SDL_Surface *screen){
  

  if (getSpace(var) == 0) {
      setChangeSp(var, 1);  
  }
  
  if (getChangeSp(var) == 1 && getSpace(var) == 1) {
    setChangeSp(var, 0);
    setPause(var, 1 - getPause(var));
  }
  
  //printf("pause : %d\n", getPause(var)); 
  if (getPause(var) == 1) {
    SDL_BlitSurface(spritePause->image, NULL, screen, &spritePause->position);
  }
  
  return getPause(var);
}

//Gestion des déplacements
void move (Sprite* sprite){
  if (getVar(sprite)->droite == 1){
    setPosX(getImage(sprite), getImage(sprite)->position.x + SPRITE_STEP);
    setDir(sprite, DIR_RIGHT);
    if (getVar(sprite)->finSaut != 0) {
      incrDelai(sprite);
    }
    if (getVar(sprite)->delai == 15) {
      anim(sprite, 1 - getVar(sprite)->anim);
      initDelai(sprite);
    }
  }
  if (getVar(sprite)->gauche == 1) {
    setPosX(getImage(sprite), getImage(sprite)->position.x - SPRITE_STEP);
    setDir(sprite, DIR_LEFT);
    if (getVar(sprite)->finSaut != 0) {
      incrDelai(sprite);
    }
    if (getVar(sprite)->delai == 15) {
      anim(sprite, 1 - getVar(sprite)->anim);
      initDelai(sprite);
    }
  }
}

//Replacement de l'ennemi lors de collisions
void ennemyCollide (Sprite *sprite, Sprite** ennemy, SDL_Rect *plateformePos, int *plat_array){
  for (int i = 0; i<NB_ENNEMY; i++){  
    if (getPosX(getImage(ennemy[i])) <= 0)
      setPosX(getImage(ennemy[i]), 0);
    if ( getPosX(getImage(ennemy[i])) >= SCREEN_WIDTH - SPRITE_SIZE) 
      setPosX(getImage(ennemy[i]), SCREEN_WIDTH - SPRITE_SIZE);
    if ( getPosY(getImage(ennemy[i])) >= SCREEN_HEIGHT - SPRITE_SIZE/2) 
      setPosY(getImage(ennemy[i]), SCREEN_HEIGHT - SPRITE_SIZE/2);
      
    //collision avec une plateforme
    for (int j = 0; j <NB_PLATEFORME; j++){
      if (plat_array[j] < 5 && plat_array[j] != 0) {
		if (collision(getPos(getImage(ennemy[i])),plateformePos[j], PASSAUT, "ennemi")==1){
		  setDir(ennemy[i], EN_DIR_LEFT);
		}
		if (collision(getPos(getImage(ennemy[i])),plateformePos[j], PASSAUT, "ennemi")==2){
		  setDir(ennemy[i], EN_DIR_RIGHT);
		}
      }
    }
    //collison avec le perso
    if (collision(getPos(getImage(ennemy[i])), getPos(getImage(sprite)), pointeurSaut(sprite), "ennemi")==1){
      
      if(getPresence(ennemy[i])){
		if(getVar(sprite)->damage == 0 && getVar(ennemy[i])->damage == 0){
		  setDamage(sprite);
		  setPosDamage(ennemy[i], getPosX(getImage(ennemy[i])), getPosY(getImage(ennemy[i])));
		  // ennemyPosDamage[i].x = ennemyPosition[i].x;
		  // ennemyPosDamage[i].y = ennemyPosition[i].y;
		  setDamage(ennemy[i]);
		}
      }
    }
  }
}

//Deplacement ennemi
void ennemyMove(Sprite **ennemy, SDL_Rect *plateformePos, int *plat_array, Sprite* sprite){
  for (int i = 0; i<NB_ENNEMY; i++){  
    if (getPresence(ennemy[i]) == 1){
    	printf("la\n");
      if (getVar(ennemy[i])->dir == EN_DIR_LEFT){
      	setPosX(getImage(ennemy[i]), getPosX(getImage(ennemy[i])) - SPRITE_STEP);
		//ennemyPosition[i].x -= SPRITE_STEP;
		if(getPosX(getImage(ennemy[i])) <= getPosStartX(ennemy[i]) - 300 || getPosX(getImage(ennemy[i])) <= 0){
		  	//enDirection[i] = EN_DIR_RIGHT;
			setDir(ennemy[i], EN_DIR_LEFT);
		}
      }

      else {
		setPosX(getImage(ennemy[i]), getPosX(getImage(ennemy[i])) + SPRITE_STEP);
		if (getPosX(getImage(ennemy[i])) <= getPosStartX(ennemy[i]) || getPosX(getImage(ennemy[i])) >= SCREEN_WIDTH){
		//if ((ennemyPosition[i].x >= ennemyPosStart[i].x || ennemyPosition[i].x >= SCREEN_WIDTH) && *change){
		  setDir(ennemy[i], EN_DIR_LEFT);
		  //enDirection[i] = EN_DIR_LEFT;
		}
      }
  //     *delaiEN += 1;
  //     if (*delaiEN == 50){
		// *enAnimFlip += 1;
		// if (*enAnimFlip == 3){
		//   *enAnimFlip = 0;
		// }
		// *delaiEN = 0;
  //     }
      //animation(ennemy[i]);
      //Chute
      if (getPosY(getImage(ennemy[i])) != SOL + SPRITE_SIZE/2) {
		  setPosY(getImage(ennemy[i]), getPosY(getImage(ennemy[i])) + 1);
		  //ennemyPosition[i].y += 1;
		  change(ennemy[i]);
		  //*change = 0;
      }      
      for (int j = 0; j <NB_PLATEFORME; j++){
		if (plat_array[j] != 0 && plat_array[j] <= 4){
	  		if (collision(getPos(getImage(ennemy[i])),plateformePos[j], PASSAUT, "ennemi") == 3) {
		      setPosY(getImage(ennemy[i]), getPosY(getImage(ennemy[i])) - 1);
		      change(ennemy[i]);
		      //*change = 1;
	  		}
		}
      }
    }
  }
  ennemyCollide (sprite, ennemy, plateformePos, plat_array);
}  


//Gestion des items
void gestion_items (int collision, int *plat_array, int bloc, Sprite *sprite, SDL_Rect *plateformePos, int i, 
					VariablesG *var, Sprite **ennemy) {
  if (collision == 1 || collision == 2 || collision == 3 ){
    //Si c'est une porte
    if (bloc == 3) {
      //Si on a une clef pour l'ouvrir
      if (getClef(var) >= 1) {
      	desincrClef(var);
	    plat_array[i] = 0;
      }
      else {
	    if (collision == 1) {
	      setPosX(getImage(sprite), plateformePos[i].x - SPRITE_SIZE) ;
	    }
	    if (collision == 2) {
	      setPosX(getImage(sprite), plateformePos[i].x + BLOC_SIZE) ;
	    }
	    if (collision ==3) {
	      setPosY(getImage(sprite), plateformePos[i].y - BLOC_SIZE) ;
	    }
      }
    }
    //Si c'est un bloc à pics
    if (bloc == 4) {
      if (collision == 1) {
	    setPosX(getImage(sprite), plateformePos[i].x - SPRITE_SIZE) ;
      }
      if (collision == 2) {
	    setPosX(getImage(sprite), plateformePos[i].x + BLOC_SIZE) ;
      }
      if (collision ==3) {
	    setPosY(getImage(sprite), plateformePos[i].y - BLOC_SIZE) ;
	    setDamage(sprite);
      }
    }
    //Si c'est un coeur
    if (bloc == 5) {
      plat_array[i] = 0;      
	  incrVie(sprite);
	  handleIt(var, 1);
    }
    //Si c'est une clef
    if (bloc == 6) {
      plat_array[i] = 0;
      incrClef(var);
      handleIt(var, 2);
    }
    
    if (bloc == 7 ) {
      if (getNiveau(var) == 3) {	
	afficher_bloc("niveau4.txt", plat_array, plateformePos, ennemy);
	set_pos(sprite, 0, SOL);
	incrNiveau(var);
      }
      else if (getNiveau(var) == 2) {
	afficher_bloc("niveau3.txt", plat_array, plateformePos, ennemy);
	set_pos(sprite, 50, 50);
	incrNiveau(var);
      }
      else if (getNiveau(var) == 1) {
	afficher_bloc("niveau2.txt", plat_array, plateformePos, ennemy);
	set_pos(sprite, 0, SOL);
	incrNiveau(var);
      }
    }
  }
}

  
//Replacement du sprite lors de collisions
void spriteCollide (Sprite *sprite, SDL_Rect *plateformePos, int *plat_array, Sprite** ennemy, VariablesG* var){
  
  if (getPosX(getImage(sprite)) <= 0)
    setPosX(getImage(sprite),0);

  if (getPosX(getImage(sprite)) >= SCREEN_WIDTH - SPRITE_SIZE) 
    setPosX(getImage(sprite), SCREEN_WIDTH - SPRITE_SIZE);

  if (getPosY(getImage(sprite)) >= SCREEN_HEIGHT - SPRITE_SIZE) 
    setPosY(getImage(sprite),SCREEN_HEIGHT - SPRITE_SIZE);
    
  for (int i = 0; i <NB_PLATEFORME; i++){
    if (plat_array[i] < 3 && plat_array[i] != 0) {
      if (collision(getPos(getImage(sprite)), plateformePos[i], pointeurSaut(sprite), "perso")==1){
	setPosX(getImage(sprite),plateformePos[i].x - SPRITE_SIZE) ;	
      }
      if (collision(getPos(getImage(sprite)), plateformePos[i], pointeurSaut(sprite), "perso")==2){
	setPosX(getImage(sprite),plateformePos[i].x + BLOC_SIZE);	
      }
    }
    else{
       gestion_items(collision(getPos(getImage(sprite)),plateformePos[i], pointeurSaut(sprite), "perso"), plat_array, plat_array[i], sprite, plateformePos, 
		  i, var, ennemy);
    }
  }
  for (int i = 0; i<NB_ENNEMY; i++){
     if (getPresence(ennemy[i])){    
      if (collision(getPos(getImage(sprite)),plateformePos[i], pointeurSaut(sprite), "perso")==3){
	setPosY(getImage(sprite),plateformePos[i].y - BLOC_SIZE/2);
      }	
    }
  }
}

/*Gestion de la perte de vie*/
// void stopEnnemy (int *EnDamage, int *enTempsDamage) {
//   for (int i = 0; i<NB_ENNEMY; i++){
//     if (EnDamage[i] == 1) {
//       if (*enTempsDamage == 0) {
// 	*enTempsDamage += 1;
//       }
//       if (*enTempsDamage == 350) {
// 	EnDamage[i] = 0;
// 	*enTempsDamage = 0;
//       }
//       else {
// 	*enTempsDamage += 1;
//       }
//     }
//   }
// }

/*Gestion de la perte de vie*/
void lose_life (Sprite* sprite) {
    if (getVar(sprite)->damage == 1) {
      if (getVar(sprite)->tempsDam == 0) {
	desincrVie(sprite);
	incrTempsDam(sprite);
      }
      if (getVar(sprite)->tempsDam == 350) {
	initDam(sprite);
      }
      else {
	incrTempsDam(sprite);
      }
    }
}

//Gestion du timer
void fTimer (VariablesG* var){
	setHeures(var, getTimer(var)/(200*3600));
	setMinutes(var, (getTimer(var) / 200 - 3600 * getHeures(var)) / 60);
	setSecondes(var, getTimer(var)/200 - 60 * getMinutes(var));
}

//Gestion du saut
void Saut (Sprite* sprite, int *plat_array, SDL_Rect *plateformePos){
  initHPerso(sprite);
  int col_haut = 0;
  //Si on a demandé au perso de sauter
  if (getVar(sprite)->saut == SAUT) {
    for (int i = 0; i < NB_PLATEFORME; i++){
      if (plat_array[i] != 0){
		//Gestion de la collision avec le haut du perso
		if (collision(getPos(getImage(sprite)), plateformePos[i], pointeurSaut(sprite), "perso")==4){
		  col_haut = 1;
		}
      }
    }
    if ((getPosY(getImage(sprite)) >= getVar(sprite)->debutSaut - HSAUT) && (getPosY(getImage(sprite)) != BLOC_SIZE) && !col_haut){
	
      setPosY(getImage(sprite), getPosY(getImage(sprite))-1);
      setSaut(sprite, 0, getVar(sprite)->debutSaut, SAUT);
    }
    
    
    else {setSaut(sprite, getVar(sprite)->finSaut, getVar(sprite)->debutSaut, PASSAUT); }
  }
  
  if (getPosY(getImage(sprite)) != SOL) {
    if (getEtatSaut(sprite) == PASSAUT) {
      setPosY(getImage(sprite), getPosY(getImage(sprite))+1);
    }
  }
  
  for (int i = 0; i <NB_PLATEFORME; i++){
    if (plat_array[i] != 0 && plat_array[i]<= 4){
      if (collision(getPos(getImage(sprite)),plateformePos[i], pointeurSaut(sprite), "perso") == 3) {
	    if (plat_array[i] == 4) {
	      setDamage(sprite);
	    }
	    setPosY(getImage(sprite), getPosY(getImage(sprite))-1);
	    setSaut(sprite, 1, 0, PASSAUT);
	  }
    }
  }
  if (getPosY(getImage(sprite)) == SOL) {
    setSaut(sprite, 1, 0, PASSAUT);      
  }
}
 
  /*Gestion du game over*/
int game_over (Sprite* sprite, Image *spriteGameover, SDL_Surface *screen){
  if (getVie(sprite) == 0) {
    SDL_BlitSurface(spriteGameover->image, NULL, screen, &spriteGameover->position);
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

void drawFont (Image *font, SDL_Surface *screen, VariablesG* var, Sprite* sprite){
  
  setImY(font, FONT_SIZE*3);
  
  /***Timer***/
  
  //Affichage heures
  //Dizaines
  setImX(font, FONT_SIZE * (getHeures(var)/10));
  setPosX(font, 10);
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
  setIm(font, FONT_SIZE* getVar(sprite)->vie, FONT_SIZE*3);
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

void drawBonus (Image *oneup, SDL_Surface *screen,VariablesG* var, Sprite *sprite){
  /*Draw bonus*/
  if (getItem(var) != 0){
    setPosX(oneup, getPosX(getImage(sprite)));
    setPosY(oneup, getPosY(getImage(sprite)) - 40);
    setImX(oneup, (getItem(var) - 1)*31);
    incrTempsIt(var);
    SDL_BlitSurface(oneup->image, &oneup->taille, screen, &oneup->position);
    if (getTempsIt(var) == 150) {
      initItem(var);      
    }    
  }
}

void drawSprite (Sprite *sprite, SDL_Surface *screen){
  setImX(getImage(sprite), SPRITE_SIZE * (2 * getVar(sprite)->dir + getVar(sprite)->anim));
  if(!getVar(sprite)->damage) { 
    SDL_BlitSurface(getImage(sprite)->image, &getImage(sprite)->taille, screen, &getImage(sprite)->position);
  }
  else{
    if ((getVar(sprite)->tempsDam/20)%2 == 1) {
      SDL_BlitSurface(getImage(sprite)->image, &getImage(sprite)->taille, screen, &getImage(sprite)->position);
    }
  }
}

void drawEnnemy (Sprite **ennemy, SDL_Surface *screen){
  for (int i = 0; i<NB_ENNEMY; i++){
    if (getPresence(ennemy[i])){
      if (!getVar(ennemy[i])->damage){
      	setImX(getImage(ennemy[i]), SPRITE_SIZE/2 * getVar(ennemy[i])->dir);
      	setImY(getImage(ennemy[i]), SPRITE_SIZE/2 * getVar(ennemy[i])->anim);    
		SDL_BlitSurface(getImage(ennemy[i])->image, &getImage(ennemy[i])->taille, screen, &getImage(ennemy[i])->position);
      }
    else {
		if ((getVar(ennemy[i])->tempsDam/20)%2 == 1) {
	  		SDL_BlitSurface(getImage(ennemy[i])->image, &getImage(ennemy[i])->taille, screen, &ennemy[i]->posDamage);
		}
		setPosX(getImage(ennemy[i]), getPosDam(ennemy[i]).x);
		setPosY(getImage(ennemy[i]), getPosDam(ennemy[i]).y);
      }
    }
  }
}
