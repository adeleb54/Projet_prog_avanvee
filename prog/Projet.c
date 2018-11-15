#include "fonction.h"

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *sprite, *sky, *font, *spritePause, 
	      *enemy, *spriteGameover,
	      *oneup, *plateforme[NB_PLATEFORME];
  int colorkey;
  int currentDirection = DIR_RIGHT;
  int enDirection = EN_DIR_LEFT;
  int animationFlip = 0;
  int enAnimFlip = 0;
  SDL_Rect spritePosition;
  SDL_Rect enemyPosition;
  SDL_Rect pausePosition;
  SDL_Rect fontPosition;
  SDL_Rect upPosition;
  SDL_Rect gameoverPosition;
  int gameover = 0;
  int hperso = spritePosition.y;
  int debutsaut;
  int finsaut = 1;
  int saut = 0;
  int droite = 0;
  int gauche = 0;
  int delai = 0;
  int delaiEn = 0;
  int timer = 0;
  int pauseV = 1;
  int space = 0;
  int changspace = 1;
  int vie = 5;
  int secondes, minutes, heures;
  int item = 0;
  int tempsItem = 0;
  int clef = 0;
  int damage = 0;
  int tempsDamage = 0;
  
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  
  /*Sprites*/
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
  
  /*Enemi*/
  temp   = SDL_LoadBMP("enemy.bmp");
  enemy = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Rect enemyImage;
  enemyImage.w = SPRITE_SIZE/2;
  enemyImage.h = SPRITE_SIZE/2;
  enemyPosition.w = SPRITE_SIZE/2;
  enemyPosition.h = SPRITE_SIZE/2;
  enemyPosition.x = 500;
  enemyPosition.y = SOL + SPRITE_SIZE/2;
  SDL_SetColorKey(enemy, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Font*/
  temp   = SDL_LoadBMP("franklin.bmp");
  font = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Rect fontImage;
  fontImage.w = FONT_SIZE;
  fontImage.h = FONT_SIZE; 
  fontPosition.y = 0;
  SDL_SetColorKey(font, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);  
  
  /*Sky*/
  temp  = SDL_LoadBMP("ciel.bmp");
  sky = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
      
  /*Pause*/
  temp  = SDL_LoadBMP("Pause.bmp");
  spritePause = SDL_DisplayFormat(temp);
  pausePosition.x = (SCREEN_WIDTH - 72)/2;
  pausePosition.y = (SCREEN_HEIGHT - 20)/2;
  SDL_FreeSurface(temp);
  SDL_SetColorKey(spritePause, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Game Over*/
  temp  = SDL_LoadBMP("gameover.bmp");
  spriteGameover = SDL_DisplayFormat(temp);
  gameoverPosition.x = (SCREEN_WIDTH - 126)/2;
  gameoverPosition.y = (SCREEN_HEIGHT - 20)/2;
  SDL_FreeSurface(temp);
  SDL_SetColorKey(spriteGameover, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*1up*/
  temp  = SDL_LoadBMP("items.bmp");
  oneup = SDL_DisplayFormat(temp);
  SDL_Rect upImage;
  upImage.w = 31;
  upImage.h = 30;
  upImage.y = 0;
  SDL_FreeSurface(temp);
  SDL_SetColorKey(oneup, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
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
  
  
  afficher_bloc("test.txt", plat_array, plateformePos);
  

  while (!gameover)
  {
    SDL_Event event;
	
    if (SDL_PollEvent(&event)) {
      HandleEvent(event, &gameover, &currentDirection,
		  &animationFlip, &saut, &debutsaut, &hperso, &finsaut, &droite, &gauche, &space);
    }
    
    //Pause
    if ((pause (&space, &changspace, &pauseV, pausePosition, spritePause, screen) == 1)  && (game_over(&vie, gameoverPosition, spriteGameover, screen) == 0)){
    
      
    //Jeu
      //Handle timer
      timer += 1;
      fTimer (&timer, &heures, &minutes, &secondes);

      enemyMove(&enemyPosition, &enDirection, &enAnimFlip, &delaiEn);
      
      /*handle the movement of the sprite*/
      move (&droite, &gauche, &spritePosition, &currentDirection, &finsaut, &delai, &animationFlip);
      
      /*Collisions*/      
      replacement (&spritePosition, plateformePos, plat_array, saut, &vie, &item, &clef, &tempsItem, &damage);
      
      /*Gestion des dégâts*/
      lose_life (&damage, &tempsDamage, &vie);

      /*Saut*/
      Saut (&hperso, &spritePosition, &saut, plat_array, plateformePos, &debutsaut, &finsaut, &damage);
      
		    /******Affichage*******/
		    
		    
	      /* draw the background */
      drawSky(sky, screen);
      
	    /*Dans bandeau noir*/
     drawFont (font, screen, &fontImage, &fontPosition, &heures, &minutes, &secondes, &vie, &clef);     
	  
	    /*draw blocs*/
      drawBloc(plateforme, screen, &blocImage, plateformePos, plat_array);
      
	    //draw sprites
      drawSprite (sprite, screen, &spriteImage, &spritePosition, &currentDirection, &animationFlip);
      
      drawEnemy (enemy, screen, &enemyImage, &enemyPosition, &enDirection, &enAnimFlip);
      
      drawBonus (oneup, screen, &upImage, &upPosition, &item, &tempsItem, &spritePosition);
      
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