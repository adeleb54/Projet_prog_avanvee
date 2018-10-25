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