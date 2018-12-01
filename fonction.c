#include "fonction.h"
  
//Gestion des evenements
void HandleEvent(SDL_Event event,
        int *quit, Sprite* sprite, int *space, int *bas, int pause)
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
	      	printf("finsaut %d\n",getVar(sprite)->finSaut);
	      	printf("saut %d\n",getVar(sprite)->saut);
		    if (getVar(sprite)->finSaut && getVar(sprite)->saut == PASSAUT) {
		      setSaut(sprite, 0, getVar(sprite)->hperso, SAUT);
		    }
	      }
	      break;
	      
	    case SDLK_DOWN:
	      *bas = 1;
	      break;
		
	    case SDLK_LEFT:
	      getVar(sprite)->gauche = 1;
	      break;
		
	    case SDLK_RIGHT:
	      getVar(sprite)->droite = 1;
	      break;
	    
	    case SDLK_SPACE:
	      *space = 1;
	      break;
	    
	    default:
	      break;
	}
	break;
	
    case SDL_KEYUP:
	switch (event.key.keysym.sym) {
	    
	    case SDLK_DOWN:
	      *bas = 0;
	      break;
	    
	    case SDLK_LEFT:
	      getVar(sprite)->gauche = 0;
	      break;
		
	    case SDLK_RIGHT:
	      getVar(sprite)->droite = 0;
	      break;
		
	    case SDLK_SPACE:
	      *space = 0;
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
  
void HandleEventStart(SDL_Event event, int *quit, int *haut, int *bas, int *entree)
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
	      *haut = 1;
	      break;
	      
	    case SDLK_DOWN:
	      *bas = 1;
	      break;
	      
	    case SDLK_RETURN:
	      *entree = 1;
	      break;
	    
	    default:
	      break;
	}
	break;
	
    case SDL_KEYUP:
	switch (event.key.keysym.sym) {
	    case SDLK_UP:
	      *haut = 0;
	      break;
	    
	    case SDLK_DOWN:
	      *bas = 0;
	      break;
	      
	    case SDLK_RETURN:
	      *entree = 0;
	      break;
		
	    default :
	      break;
	}
	break;
  }
}

int start (int *haut, int *finsaut, int *select, int *bas, int *entree, int *gameover, SDL_Surface *skyL, SDL_Surface *spriteDem, SDL_Surface *spriteQuit, 
	    SDL_Surface *screen, SDL_Surface *font, SDL_Rect *demPosition, SDL_Rect *quitPosition, SDL_Rect *fontPosition, SDL_Rect *selectImage){
  
  int changhaut, changbas;
  while (*gameover == 2){  
    
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      HandleEventStart(event, gameover, haut, bas, entree);
    }
    
    if (*haut == 0) {
	changhaut = 1;
    }
    
    if (changhaut == 1 && *haut == 1) {
      changhaut = 0;
      *select = 1 - *select;
    }
    
    if (*bas == 0) {
	changbas = 1;
    }
    
    if (changbas == 1 && *bas == 1) {
      changbas = 0;
      *select = 1 - *select;
    }
    
    /* draw the background */
    SDL_BlitSurface(skyL, NULL, screen, NULL);
    
    
    demPosition->y = 90;
    SDL_BlitSurface(spriteDem, NULL, screen, demPosition);
    
    quitPosition->y = 120;
    SDL_BlitSurface(spriteQuit, NULL, screen, quitPosition);
    
    if (*select == 0) {
      fontPosition->x = 190;
      fontPosition->y = 90;
      SDL_BlitSurface(font, selectImage, screen, fontPosition);

    }
    
    if (*select == 1) {
      fontPosition->x = 190;
      fontPosition->y = 120;
      SDL_BlitSurface(font, selectImage, screen, fontPosition);

    }
    
    /* update the screen */
     SDL_UpdateRect(screen, 0, 0, 0, 0);
     
    if (*entree == 1) {
      
      if (*select == 0) {
	
	/* clean up */
	SDL_FreeSurface(skyL);
	SDL_FreeSurface(spriteDem);
	SDL_FreeSurface(spriteQuit);
	
	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);
	/* set the title bar */
	SDL_WM_SetCaption("SDL Animation", "SDL Animation");
	/* create window */
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	/* set keyboard repeat */
	SDL_EnableKeyRepeat(10, 10);
	
	*gameover = 0;
      }
          
      if (*select == 1) {
	  
	/* clean up */
	SDL_FreeSurface(skyL);
	*gameover = 1;
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
void set_pos (Sprite* sprite, int a, int b) {
  setPosX(getImage(sprite),a);
  setPosY(getImage(sprite),b);
}

//Gestion de la pause
int pause (int *space, int *changspace, int *pause, Image *spritePause, SDL_Surface *screen){
  
  if (*space == 0) {
      *changspace = 1;  
  }
  
  if (*changspace == 1 && *space == 1) {
    *changspace = 0;
    *pause = 1 - *pause;
  }
  
  if (*pause == 0) {
    SDL_BlitSurface(spritePause->image, NULL, screen, &spritePause->position);
  }
  
  return *pause;
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
void ennemyCollide (Sprite *sprite, SDL_Rect *ennemyPosition, int *ennemy_array, SDL_Rect *plateformePos, int *plat_array, int* enDirection, 
			int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage){
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
	if (collision(ennemyPosition[i],plateformePos[j], PASSAUT, "ennemi")==1){
	  enDirection[i] = EN_DIR_LEFT;
	}
	if (collision(ennemyPosition[i],plateformePos[j], PASSAUT, "ennemi")==2){
	  enDirection[i] = EN_DIR_RIGHT;
	}
      }
    }
    //collison avec le perso
    if (collision(ennemyPosition[i], getImage(sprite)->position, pointeurSaut(sprite), "ennemi")==1 /*|| collision(ennemyPosition[i], *spritePosition, saut, "ennemi")== 2 || collision(ennemyPosition[i], *spritePosition, saut, "ennemi")== 4*/){
      if(ennemy_array[i] != 0){
	if(getVar(sprite)->damage == 0 && enDamage[i] == 0){
	  setDamage(sprite);
	  ennemyPosDamage[i].x = ennemyPosition[i].x;
	  ennemyPosDamage[i].y = ennemyPosition[i].y;
	  enDamage[i] = 1;
	}
      }
    }
  }
}

//Deplacement ennemi
void ennemyMove(SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, int *ennemy_array, int *enDirection, int *enAnimFlip, 
	            int *change, int *delaiEN, SDL_Rect *plateformePos, int *plat_array, Sprite* sprite, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage){
  for (int i = 0; i<NB_ENNEMY; i++){  
    if (ennemy_array[i] != 0){
      if (enDirection[i] == EN_DIR_LEFT){
	ennemyPosition[i].x -= SPRITE_STEP;
	if((ennemyPosition[i].x <= ennemyPosStart[i].x - 300 || ennemyPosition[i].x <= 0) && *change){
	  enDirection[i] = EN_DIR_RIGHT;
	}
      }
      else {
	ennemyPosition[i].x += SPRITE_STEP;
	if ((ennemyPosition[i].x >= ennemyPosStart[i].x || ennemyPosition[i].x >= SCREEN_WIDTH) && *change){
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
	  *change = 0;
      }      
      for (int j = 0; j <NB_PLATEFORME; j++){
	if (plat_array[j] != 0 && plat_array[j] <= 4){
	  if (collision(ennemyPosition[i],plateformePos[j], PASSAUT, "ennemi") == 3) {
	      ennemyPosition[i].y -= 1;
	      *change = 1;
	  }
	}
      }
    }
  }
  ennemyCollide (sprite, ennemyPosition, ennemy_array, plateformePos, plat_array, enDirection, enDamage, enTempsDamage, ennemyPosDamage);
}  


// Gestion des items
void gestion_items (int collision, int *plat_array, int bloc, Sprite *sprite, SDL_Rect *plateformePos, int *item, int *clef, 
		    int *tempsItem, int i, int *niveau, int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart) {
  if (collision == 1 || collision == 2 || collision == 3 ){
    //Si c'est une porte
    if (bloc == 3) {
      //Si on a une clef pour l'ouvrir
      if (*clef >= 1) {
	    *clef -= 1;
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
	  printf("vie : %d\n", getVar(sprite)->vie);
      if (*item == 1) {
	*tempsItem = 0;
      }
      else {
	*item = 1;
      }
    }
    //Si c'est une clef
    if (bloc == 6) {
      plat_array[i] = 0;
      if (*item == 2) {
	*clef += 1;
	*tempsItem = 0;
      }
      else {
	*clef += 1;
	*item = 2;
      }
    }
    
    if (bloc == 7 /*&& passNiv == 0*/) {
      if (*niveau == 3) {	
	afficher_bloc("niveau4.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
	set_pos(sprite, 0, SOL);
	niveau += 1;
      }
      else if (*niveau == 2) {
	afficher_bloc("niveau3.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
	set_pos(sprite, 50, 50);
	niveau += 1;
      }
      else if (*niveau == 1) {
	afficher_bloc("niveau2.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
	set_pos(sprite, 0, SOL);
	niveau += 1;
      }
    }
  }
}

  
//Replacement du sprite lors de collisions
void spriteCollide (Sprite *sprite, SDL_Rect *plateformePos, int *plat_array, int *ennemy_array, int *item, 
		    int *clef, int *tempsItem, int *niveau, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart){
  
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
		  item, clef, tempsItem, i, niveau, ennemy_array, ennemyPosition, ennemyPosStart);
    }
  }
  for (int i = 0; i<NB_ENNEMY; i++){
     if (ennemy_array[i] != 0){       
      if (collision(getPos(getImage(sprite)),plateformePos[i], pointeurSaut(sprite), "perso")==3){
	setPosY(getImage(sprite),plateformePos[i].y - BLOC_SIZE/2);
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
void fTimer (int* timer, int* heures, int* minutes, int* secondes){
  *heures = *timer/(200*3600);
  *minutes = (*timer/200 - 3600 * *heures)/ 60;
  *secondes = *timer/200 - 60 * *minutes;
}

//Gestion du saut
void Saut (Sprite* sprite, int *plat_array, SDL_Rect *plateformePos){
  initHPerso(sprite);
  int col_haut = 0;
  // printf("debut saut = %d\n", getVar(sprite)->debutSaut);
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
    
    
    else {setSaut(sprite, 1, SOL, PASSAUT); }
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

void drawFont (Image *font, SDL_Surface *screen,int *heures, int *minutes, int *secondes, int *clef, Sprite* sprite){
  
  setImY(font, FONT_SIZE*3);
  
  /***Timer***/
  
  //Affichage heures
  //Dizaines
  setImX(font, FONT_SIZE * (*heures/10));
  setPosX(font, 10);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

  //Unités
  setImX(font, FONT_SIZE * (*heures%10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  //Deux points
  setImX(font, 320);
  setPosX(font, font->position.x + 30);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);

  
  //Affichage minutes
  //Dizaines
  setImX(font, FONT_SIZE * (*minutes/10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Unités
  setImX(font, FONT_SIZE * (*minutes%10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Deux points
  setImX(font, 320);
  setPosX(font, font->position.x + 30);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Affichage secondes
  //Dizaines
  setImX(font, FONT_SIZE * (*secondes/10));
  setPosX(font, font->position.x + 20);
  SDL_BlitSurface(font->image, &font->taille, screen, &font->position);
  
  
  //Unités
  setImX(font, FONT_SIZE * (*secondes%10));
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
  setIm(font, FONT_SIZE* *clef, FONT_SIZE*3);
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

void drawBonus (SDL_Surface *oneup, SDL_Surface *screen, SDL_Rect *upImage, SDL_Rect *upPosition, int *item, int *tempsItem, Sprite *sprite){
  /*Draw bonus*/
  if (*item != 0){
    upPosition->x = getPosX(getImage(sprite));
    upPosition->y = getPosY(getImage(sprite)) - 40;
    upImage->x = (*item - 1)*31;
    *tempsItem += 1;
    SDL_BlitSurface(oneup, upImage, screen, upPosition);
    if (*tempsItem == 150) {
      *item = 0;
      *tempsItem = 0;      
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
