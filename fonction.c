#include "fonction.h"
  
//Gestion des evenements
void HandleEvent(SDL_Event event,
        int *quit, int *saut, int *debutsaut, int *hperso, int *finsaut, 
	int *droite, int *gauche, int *space, int *haut, int *bas, int pause)
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
		if (*finsaut != 0) {
		  *finsaut = 0;
		  *saut = SAUT;
		  *debutsaut = *hperso;
		}
	      }
	      *haut = 1;
	      break;
	      
	    case SDLK_DOWN:
	      *bas = 1;
	      break;
		
	    case SDLK_LEFT:
	      *gauche = 1;
	      break;
		
	    case SDLK_RIGHT:
	      *droite = 1;
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
	    case SDLK_UP:
	      *haut = 0;
	      break;
	    
	    case SDLK_DOWN:
	      *bas = 0;
	      break;
	    
	    case SDLK_LEFT:
	      *gauche = 0;
	      break;
		
	    case SDLK_RIGHT:
	      *droite = 0;
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
    while(c != EOF){
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
void set_pos (SDL_Rect *spritePosition, int a, int b) {
  spritePosition->x = a;
  spritePosition->y = b;
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
			int *damage, int *tempsDamage, int *vie, int *saut, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage){
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
void ennemyMove(SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart, int *ennemy_array, int *enDirection, int *enAnimFlip, int *change, int *delaiEN, SDL_Rect *plateformePos, int *plat_array, 
		SDL_Rect *spritePosition, int *damage, int *tempsDamage, int *vie, int *saut, int *enDamage, int *enTempsDamage, SDL_Rect *ennemyPosDamage){
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
  ennemyCollide (spritePosition, ennemyPosition, ennemy_array, plateformePos, plat_array, enDirection, damage, tempsDamage, vie, saut, enDamage, enTempsDamage, ennemyPosDamage);
}  


// Gestion des items
void gestion_items (int collision, int *plat_array, int bloc, SDL_Rect *spritePosition, SDL_Rect *plateformePos, int *vie, int *item, int *clef, 
		    int *tempsItem, int i, int *damage, int *niveau, int *ennemy_array, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart) {
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
	  spritePosition->x = plateformePos[i].x - SPRITE_SIZE ;
	}
	if (collision == 2) {
	  spritePosition->x = plateformePos[i].x + BLOC_SIZE ;
	}
	if (collision ==3) {
	  spritePosition->y = plateformePos[i].y - BLOC_SIZE ;
	}
      }
    }
    //Si c'est un bloc à pics
    if (bloc == 4) {
      if (collision == 1) {
	spritePosition->x = plateformePos[i].x - SPRITE_SIZE ;
      }
      if (collision == 2) {
	spritePosition->x = plateformePos[i].x + BLOC_SIZE ;
      }
      if (collision ==3) {
	spritePosition->y = plateformePos[i].y - BLOC_SIZE ;
	*damage = 1;
      }
    }
    //Si c'est un coeur
    if (bloc == 5) {
      plat_array[i] = 0;
      if (*item == 1) {
	*vie += 1;
	*tempsItem = 0;
      }
      else {
	*vie += 1;
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
	set_pos(spritePosition, 0, SOL);
	niveau += 1;
      }
      else if (*niveau == 2) {
	afficher_bloc("niveau3.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
	set_pos(spritePosition, 50, 50);
	niveau += 1;
      }
      else if (*niveau == 1) {
	afficher_bloc("niveau2.txt", plat_array, plateformePos, ennemy_array, ennemyPosition, ennemyPosStart);
	set_pos(spritePosition, 50, 50);
	niveau += 1;
      }
    }
  }
}

  
//Replacement du sprite lors de collisions
void spriteCollide (SDL_Rect *spritePosition, SDL_Rect *plateformePos, int *plat_array, int *ennemy_array, int saut, int *vie, int *item, 
		    int *clef, int *tempsItem, int *damage, int *niveau, SDL_Rect *ennemyPosition, SDL_Rect *ennemyPosStart){
  
  if (spritePosition->x <= 0)
    spritePosition->x = 0;
  if (spritePosition->x >= SCREEN_WIDTH - SPRITE_SIZE) 
    spritePosition->x = SCREEN_WIDTH - SPRITE_SIZE;
  if (spritePosition->y >= SCREEN_HEIGHT - SPRITE_SIZE) 
    spritePosition->y = SCREEN_HEIGHT - SPRITE_SIZE;
    
  for (int i = 0; i <NB_PLATEFORME; i++){
    if (plat_array[i] < 3 && plat_array[i] != 0) {
      if (collision(*spritePosition,plateformePos[i], &saut, "perso")==1){
	spritePosition->x = plateformePos[i].x - SPRITE_SIZE ;	
      }
      if (collision(*spritePosition,plateformePos[i], &saut, "perso")==2){
	spritePosition->x = plateformePos[i].x + BLOC_SIZE;	
      }
    }
    else{
       gestion_items(collision(*spritePosition,plateformePos[i], &saut, "perso"), plat_array, plat_array[i], spritePosition, plateformePos, 
		     vie, item, clef, tempsItem, i, damage, niveau, ennemy_array, ennemyPosition, ennemyPosStart);
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
void lose_life (int *damage, int *tempsDamage, int *vie) {
    if (*damage == 1) {
      if (*tempsDamage == 0) {
	*vie -= 1;
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
void fTimer (int* timer, int* heures, int* minutes, int* secondes){
  *heures = *timer/(200*3600);
  *minutes = (*timer/200 - 3600 * *heures)/ 60;
  *secondes = *timer/200 - 60 * *minutes;
}

//Gestion du saut
void Saut (int *hperso, SDL_Rect *spritePosition, int *saut, int *plat_array, SDL_Rect *plateformePos, int *debutsaut, int *finsaut, int *damage){
  *hperso = spritePosition->y;
  int col_haut = 0;
  //Si on a demandé au perso de sauter
  if (*saut == SAUT) {
    for (int i = 0; i < NB_PLATEFORME; i++){
      if (plat_array[i] != 0){
	//Gestion de la collision avec le haut du perso
	if (collision(*spritePosition, plateformePos[i], saut, "perso")==4){
	  col_haut = 1;
	}
	if (*debutsaut - SPRITE_SIZE == plateformePos[i].y){
	  
	}
      }
    }
    if ((spritePosition->y >= *debutsaut - HSAUT) && (spritePosition->y != BLOC_SIZE) && !col_haut){
	
      spritePosition->y -= 1;
    }
    
    
    else { *saut = PASSAUT; }
  }
  
  if (spritePosition->y != SOL) {
    if (*saut == PASSAUT) {
      spritePosition->y += 1;
    }
  }
  
  for (int i = 0; i <NB_PLATEFORME; i++){
    if (plat_array[i] != 0 && plat_array[i]<= 4){
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
int game_over (int *vie, Image *spriteGameover, SDL_Surface *screen){
  if (*vie == 0) {
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

void drawFont (SDL_Surface *font, SDL_Surface *screen, SDL_Rect *fontImage, SDL_Rect *fontPosition, int *heures,
	       int *minutes, int *secondes, int *vie, int *clef){
  
  fontImage->y = FONT_SIZE*3;
  
  //Affichage du timer
  fontImage->x = 32 * (*heures/10);
  fontPosition->x = 10;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);

  fontImage->x = 32 * (*heures%10);
  fontPosition->x += 20;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);

  fontImage->x = 320;
  fontPosition->x += 30;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);

  fontImage->x = 32 * (*minutes/10);
  fontPosition->x += 20;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);

  fontImage->x = 32 * (*minutes%10);
  fontPosition->x += 20;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);

  fontImage->x = 320;
  fontPosition->x += 30;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);

  fontImage->x = 32 * (*secondes/10);
  fontPosition->x += 20;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);

  fontImage->x = 32 * (*secondes%10);
  fontPosition->x += 20;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);
  
  /***Clef***/
  /*Affichage de la clef*/
  fontPosition->x = SCREEN_WIDTH - 180;
  fontImage->x = 31;
  fontImage->y = 0;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);
  
  /*Affichage du x*/
  fontPosition->x += 32;
  fontImage->x = FONT_SIZE*8;
  fontImage->y = FONT_SIZE*7;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);
  
  /*Affichage du nombre de clefs*/
  fontImage->x = *clef * 32;
  fontImage->y = FONT_SIZE*3;
  fontPosition->x += 20;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);
  
  /***Vie***/
  /*Affichage du coeur*/
  fontPosition->x = SCREEN_WIDTH - 90;
  fontImage->x = 0;
  fontImage->y = 0;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);


  /*Affichage du x*/
  fontPosition->x += 32;
  fontImage->x = FONT_SIZE*8;
  fontImage->y = FONT_SIZE*7;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);   

  /*Affichage de la vie restante*/
  fontImage->x = *vie * 32;
  fontImage->y = FONT_SIZE*3;
  fontPosition->x += 20;
  SDL_BlitSurface(font, fontImage, screen, fontPosition);
}

void drawBloc(SDL_Surface **plateforme, SDL_Surface *screen, SDL_Rect *blocImage, SDL_Rect *plateformePos, int *plat_array){
  for (int i=0; i < NB_PLATEFORME; i++){ 
    if (plat_array[i] != 0){
      blocImage->x = (plat_array[i] - 1)* BLOC_SIZE;
      SDL_BlitSurface(plateforme[i],blocImage, screen, &plateformePos[i]);   
    }
  }
}

void drawBonus (SDL_Surface *oneup, SDL_Surface *screen, SDL_Rect *upImage, SDL_Rect *upPosition, int *item, int *tempsItem, SDL_Rect *spritePosition){
  /*Draw bonus*/
  if (*item != 0){
    upPosition->x = spritePosition->x;
    upPosition->y = spritePosition->y - 40;
    upImage->x = (*item - 1)*31;
    *tempsItem += 1;
    SDL_BlitSurface(oneup, upImage, screen, upPosition);
    if (*tempsItem == 150) {
      *item = 0;
      *tempsItem = 0;      
    }    
  }
}

void drawSprite (SDL_Surface *sprite, SDL_Surface *screen, SDL_Rect *spriteImage, SDL_Rect *spritePosition, int *currentDirection, int *animationFlip, int *damage, int *tempsDamage){
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
