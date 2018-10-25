#include "Projet.h"

void HandleEvent(SDL_Event event,
        int *quit, int *currDirection, int *animFlip, SDL_Rect *position, int *saut, int *debutsaut, 
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

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *sprite, *sky, *font, *spritePause, 
	      *plateforme[NB_PLATEFORME];
  int colorkey;
  int currentDirection = DIR_RIGHT;
  int animationFlip = 0;
  SDL_Rect spritePosition;
  SDL_Rect pausePosition;
  SDL_Rect fontPosition;
  int gameover = 0;
  int hperso = spritePosition.y;
  int debutsaut;
  int finsaut = 1;
  int saut = 0;
  int droite = 0;
  int gauche = 0;
  int delai = 0;
  int timer = 0;
  int pause = 1;
  int space = 0;
  int changspace = 1;
  int vie = 5;
  
  
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  
  /*Sprite*/
  temp   = SDL_LoadBMP("sprite.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Rect spriteImage;
  spriteImage.y = 0;
  spriteImage.w = SPRITE_SIZE;
  spriteImage.h = SPRITE_SIZE;
  spritePosition.w = SPRITE_SIZE;
  spritePosition.h = SPRITE_SIZE;
  spritePosition.x = 150;
  spritePosition.y = SOL;
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Font*/
  temp   = SDL_LoadBMP("franklin.bmp");
  font = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Rect fontImage;
  fontImage.y = 102;
  fontImage.w = FONT_SIZE;
  fontImage.h = FONT_SIZE;
 
  fontPosition.y = 0;
  
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(font, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);  
  
  /*Sky*/
  temp  = SDL_LoadBMP("ciel.bmp");
  sky = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
      
  /*Pause*/
  temp  = SDL_LoadBMP("Pause.bmp");
  spritePause = SDL_DisplayFormat(temp);
  pausePosition.x = 281;
  pausePosition.y = 235;
  SDL_FreeSurface(temp);
  SDL_SetColorKey(spritePause, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Bloc*/
  /*Initialisation du tableau plat_array qui enregistre la présence des plateformes affichées*/
  int plat_array[NB_PLATEFORME];
  for(int i=0; i < NB_PLATEFORME; i++){
    plat_array[i] = 0;
  }
  
  /*Initialisation de plateforme[] qui contient les images des blocs*/
  
  for (int i=0; i<NB_PLATEFORME; i++){
    temp = SDL_LoadBMP("bloc.bmp"); 
    plateforme[i] = SDL_DisplayFormat(temp);
    SDL_SetColorKey(plateforme[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_FreeSurface(temp);
  }
  SDL_Rect blocImage;
  blocImage.y = 0;
  blocImage.w = BLOC_SIZE;
  blocImage.h = BLOC_SIZE;

  SDL_Rect plateformePos [NB_PLATEFORME];
  
  void afficher_bloc(const char* nomFichier){
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
 
  int collision(SDL_Rect A, SDL_Rect B){
    if(A.x >= B.x + B.w || A.x + A.w <= B.x || A.y >= B.y + B.h || A.y + A.h <= B.y){
      return 0;
    }
    //collision avec le bas du sprite
    if(A.y + A.h > B.y && A.y + A.h < B.y + 5){
      saut = PASSAUT;
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
  
        
  afficher_bloc("test.txt");
  

  while (!gameover)
  {
    SDL_Event event;
	
    if (SDL_PollEvent(&event)) {
      HandleEvent(event, &gameover, &currentDirection,
		  &animationFlip, &spritePosition, &saut, &debutsaut, &hperso, &finsaut, &droite, &gauche, &space);
    }
    
    /*Handle pause*/
    if (space == 0) {
      changspace = 1;
    }
    
    if (changspace == 1 && space == 1) {
      changspace = 0;
      pause = 1 - pause;
    }
    
    if (pause == 0) {
      SDL_BlitSurface(spritePause, NULL, screen, &pausePosition);
    }
    else {
    
      /*Handle timer*/
      timer += 1;
      
      int secondes = timer/200;
      int heures = secondes/3600;
      secondes = secondes - 3600*heures;
      int minutes = secondes / 60;
      secondes = secondes - 60*minutes;


    /*handle the movement of the sprite*/
      if (droite == 1){
	spritePosition.x += SPRITE_STEP;
	currentDirection = DIR_RIGHT;
	if (finsaut != 0) {
	  delai = delai + 1;
	}
	if (delai == 15) {
	  animationFlip = 1 - animationFlip;
	  delai = 0;
	}
      }
      if (gauche == 1) {
	spritePosition.x -= SPRITE_STEP;
	currentDirection = DIR_LEFT;
	if (finsaut != 0) {
	  delai = delai + 1;
	}
	if (delai == 15) {
	  animationFlip = 1 - animationFlip;
	  delai = 0;
	}
      }
      
      /*Collisions*/
      if (spritePosition.x <= 0)
	spritePosition.x = 0;
      if (spritePosition.x >= SCREEN_WIDTH - SPRITE_SIZE) 
	spritePosition.x = SCREEN_WIDTH - SPRITE_SIZE;
      if (spritePosition.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
	spritePosition.y = SCREEN_HEIGHT - SPRITE_SIZE;
    
      for (int i = 0; i <NB_PLATEFORME; i++){
	if (plat_array[i] != 0) {
	  if (collision(spritePosition,plateformePos[i])==1){
	    spritePosition.x = plateformePos[i].x - SPRITE_SIZE ;
	  }
	  if (collision(spritePosition,plateformePos[i])==2){
	    spritePosition.x = plateformePos[i].x + BLOC_SIZE;
	      }
	  if (collision(spritePosition,plateformePos[i])==3){
	    spritePosition.y = plateformePos[i].y - BLOC_SIZE;
	  }
	}
      }
      
      

      /*Saut*/
      hperso = spritePosition.y;
      int col_haut = 0;
      
      if (saut == SAUT) {
	for (int i = 0; i < NB_PLATEFORME; i++){
	  if (plat_array[i] != 0){
	    if (collision(spritePosition, plateformePos[i])==4){
	      col_haut = 1;
	    }
	    if (debutsaut - SPRITE_SIZE == plateformePos[i].y){
	      
	    }
	  }
	}
	if ((spritePosition.y >= debutsaut - HSAUT) && (spritePosition.y != BLOC_SIZE) && !col_haut){
	    
	  spritePosition.y -= 1;
	}
	
	
	else { saut = PASSAUT; }
      }
      
      if (spritePosition.y != SOL) {
	if (saut == PASSAUT) {
	  spritePosition.y += 1;
	}
      }
      
      for (int i = 0; i <NB_PLATEFORME; i++){
	if (plat_array[i] != 0){
	  if (collision(spritePosition,plateformePos[i]) == 3) {
	      spritePosition.y -= 1;
	      finsaut = 1;
	    }
	}
      }
      if (spritePosition.y == SOL) {
	finsaut = 1;      
      }
      
		    /******Affichage*******/
		    
		    
	      /* draw the background */

      SDL_BlitSurface(sky, NULL, screen, NULL);
      
	    /*Dans bandeau noir*/
     
	    /*draw the timer*/
      fontImage.y = FONT_SIZE*3;
	    
      fontImage.x = 32 * (heures/10);
      fontPosition.x = 10;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      fontImage.x = 32 * (heures%10);
      fontPosition.x += 20;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      fontImage.x = 320;
      fontPosition.x += 30;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      fontImage.x = 32 * (minutes/10);
      fontPosition.x += 20;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      fontImage.x = 32 * (minutes%10);
      fontPosition.x += 20;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      fontImage.x = 320;
      fontPosition.x += 30;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      fontImage.x = 32 * (secondes/10);
      fontPosition.x += 20;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      fontImage.x = 32 * (secondes%10);
      fontPosition.x += 20;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      /*Affichage du coeur*/
      fontPosition.x = SCREEN_WIDTH - 90;
      fontImage.x = 0;
      fontImage.y = 0;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
      
      
      /*Affichage du x*/
      fontPosition.x += 32;
      fontImage.x = FONT_SIZE*8;
      fontImage.y = FONT_SIZE*7;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);   
      
      /*Affichage de la vie restante*/
      fontImage.x = vie * 32;
      fontImage.y = FONT_SIZE*3;
      fontPosition.x += 20;
      SDL_BlitSurface(font, &fontImage, screen, &fontPosition);
	  
	    /*draw blocs*/
      for (int i=0; i < NB_PLATEFORME; i++){ 
	if (plat_array[i] != 0){
	  blocImage.x = (plat_array[i] - 1)*34;
	  SDL_BlitSurface(plateforme[i],&blocImage, screen, &plateformePos[i]);
	}
      }
      
       /* choose image according to direction and animation flip: */
      spriteImage.x = SPRITE_SIZE*(2*currentDirection + animationFlip);	  
      SDL_BlitSurface(sprite, &spriteImage, screen, &spritePosition);
      
      
      
       SDL_Delay(4);
    }
    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }  
  /* clean up */
  for (int i = 0; i < NB_PLATEFORME; i++){
    SDL_FreeSurface(plateforme[i]);
  }
  SDL_FreeSurface(font);
  SDL_FreeSurface(sprite);
  SDL_FreeSurface(sky);
  SDL_Quit();
    
  return 0;
}