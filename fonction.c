#include "fonction.h"
  
//Gestion des evenements
void HandleEvent(SDL_Event event,
        int *quit, int *currDirection, int *animFlip, int *saut, int *debutsaut, 
	int *hperso, int *finsaut, int *droite, int *gauche, int *space )
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
		    if (*finsaut != 0) {
		      *finsaut = 0;
		      *saut = SAUT;
		      *debutsaut = *hperso;
		    }
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
		case SDLK_LEFT:
		    *gauche = 0;
		    break;
		    
		case SDLK_RIGHT:
		    *droite = 0;
		    break;
		    
		case SDLK_SPACE:
		    *space = 0;
		    
		default :
		    break;
	    }
	    break;
    }
}

//Gestion des collisions
int collision(SDL_Rect A, SDL_Rect B, int *saut){
    if(A.x >= B.x + B.w || A.x + A.w <= B.x || A.y >= B.y + B.h || A.y + A.h <= B.y){
      return 0;
    }
    //collision avec le bas du sprite
    if(A.y + A.h > B.y && A.y + A.h < B.y + 5){
      *saut = PASSAUT;
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
void afficher_bloc(const char* nomFichier, int *plat_array, SDL_Rect *plateformePos){
    FILE* pFile;
    int c, i = 0;
    int posX = 0, posY = BLOC_SIZE;
    pFile = fopen(nomFichier, "r");
    if (pFile==NULL)  perror ("Error opening file"); 
    else {
      c = fgetc(pFile);
      while(c != EOF){
	switch (c){
	  case 48 :
	    plat_array[i] = 0;
	    i ++;
	    break;
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
	  default:
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
  
  
//Gestion de la pause
int pause (int *space, int *changspace, int *pause, SDL_Rect pausePosition, SDL_Surface *spritePause, SDL_Surface *screen){
  
  if (*space == 0) {
      *changspace = 1;  
  }
  
  if (*changspace == 1 && *space == 1) {
    *changspace = 0;
    *pause = 1 - *pause;
  }
  
  if (*pause == 0) {
    SDL_BlitSurface(spritePause, NULL, screen, &pausePosition);
  }
  
  return *pause;
}

//Gestion des déplacements
void move (int *droite, int *gauche, SDL_Rect *spritePosition, int *currentDirection, int *finsaut, int *delai,
	    int *animationFlip){
  
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

//Replacement du sprite lors de collisions
void replacement (SDL_Rect *spritePosition, SDL_Rect *plateformePos, int *plat_array, int saut){
  if (spritePosition->x <= 0)
    spritePosition->x = 0;
  if (spritePosition->x >= SCREEN_WIDTH - SPRITE_SIZE) 
    spritePosition->x = SCREEN_WIDTH - SPRITE_SIZE;
  if (spritePosition->y >= SCREEN_HEIGHT - SPRITE_SIZE) 
    spritePosition->y = SCREEN_HEIGHT - SPRITE_SIZE;
    
  for (int i = 0; i <NB_PLATEFORME; i++){
    if (plat_array[i] != 0) {
      if (collision(*spritePosition,plateformePos[i], &saut)==1){
	spritePosition->x = plateformePos[i].x - SPRITE_SIZE ;	
      }
      if (collision(*spritePosition,plateformePos[i], &saut)==2){
	spritePosition->x = plateformePos[i].x + BLOC_SIZE;	
      }
      if (collision(*spritePosition,plateformePos[i], &saut)==3){
	spritePosition->y = plateformePos[i].y - BLOC_SIZE;
      }	
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
void Saut (int *hperso, SDL_Rect *spritePosition, int *saut, int *plat_array, SDL_Rect *plateformePos, int *debutsaut, int *finsaut){
  *hperso = spritePosition->y;
  int col_haut = 0;
  
  if (*saut == SAUT) {
    for (int i = 0; i < NB_PLATEFORME; i++){
      if (plat_array[i] != 0){
	if (collision(*spritePosition, plateformePos[i], saut)==4){
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
    if (plat_array[i] != 0){
      if (collision(*spritePosition,plateformePos[i], saut) == 3) {
	  spritePosition->y -= 1;
	  *finsaut = 1;
	}
    }
  }
  if (spritePosition->y == SOL) {
    *finsaut = 1;      
  }
}


//Affichages

void drawSky (SDL_Surface *sky, SDL_Surface *screen){
  SDL_BlitSurface(sky, NULL, screen, NULL);
}

void drawFont (SDL_Surface *font, SDL_Surface *screen, SDL_Rect *fontImage, SDL_Rect *fontPosition, int *heures, int *minutes, int *secondes, int *vie){
  
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

void drawSprite (SDL_Surface *sprite, SDL_Surface *screen, SDL_Rect *spriteImage, SDL_Rect *spritePosition, int *currentDirection, int *animationFlip){
  spriteImage->x = SPRITE_SIZE*(2* *currentDirection + *animationFlip);	  
  SDL_BlitSurface(sprite, spriteImage, screen, spritePosition);
}