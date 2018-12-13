#include "fonction.h"

int main(int argc, char* argv[]) {
  
  SDL_Surface *screen, *temp, *sprite, /**font, *spritePause,*/ 
	      *ennemy[NB_ENNEMY], /**spriteGameover, *spriteDem, *spriteQuit, *skyL,
	      *oneUp,*/ *plateforme[NB_PLATEFORME];
  int currentDirection = DIR_RIGHT;
  int animationFlip = 0;
  int enAnimFlip = 0;
  SDL_Rect spritePosition;
  SDL_Rect ennemyPos [NB_ENNEMY];
  SDL_Rect plateformePos [NB_PLATEFORME];
  int hperso = spritePosition.y;
  int debutsaut;
  int finsaut = 1;
  int saut = 0;
  int droite = 0;
  int gauche = 0;
  int delai = 0;
  int delaiEn = 0;
  int damage = 0;
  int tempsDamage = 0;
  int enTempsDamage = 0;
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH_START, SCREEN_HEIGHT_START, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);
  VarG* varGlobal = createVarG(screen);

  
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
  spritePosition.x = 32;
  spritePosition.y = SOL;
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
  
  /*Font*/
  Image* font = createImage("font.bmp", 0, 0, FONT_SIZE, FONT_SIZE, FONT_SIZE * 14, FONT_SIZE * 3);
  SDL_SetColorKey(font->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));  
  
  
 /*Sky Launcher*/
 Image* skyL = createImage("ciel1.bmp",0,0,0,0,0,0);

  /*Sky*/
  Image* sky = createImage("ciel.bmp",0,0,0,0,0,0);
      
  /*Start*/
  Image* spriteDem = createImage("dem.bmp",217,90,0,0,0,0);
  SDL_SetColorKey(spriteDem->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
  
  /*Quit*/
  Image* spriteQuit = createImage("quit.bmp",225,120,0,0,0,0);
  SDL_SetColorKey(spriteQuit->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));

  /*Pause*/
  Image* spritePause = createImage("Pause.bmp", (SCREEN_WIDTH - 72)/2, (SCREEN_HEIGHT - 20)/2,0,0,0,0);
  SDL_SetColorKey(spritePause->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
    
  /*Game Over*/
  Image* spriteGameover = createImage("gameover.bmp", (SCREEN_WIDTH - 126)/2, (SCREEN_HEIGHT - 20)/2,0,0,0,0);
  SDL_SetColorKey(spriteGameover->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));

  /*1up*/
  Image* oneUp = createImage("items.bmp", 0, 0, 31, 30, 0, 0);
  SDL_SetColorKey(oneUp->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
  
    /*Enemi*/ 
  int ennemy_array[NB_ENNEMY]; //presence ennemi
  SDL_Rect ennemyPosDamage[NB_ENNEMY]; //position damage de l'ennemi
  SDL_Rect ennemyPosStart[NB_ENNEMY]; //position de depart de l'ennemi
  int ennemyDir[NB_ENNEMY]; //direction de l'ennemi
  int enDamage[NB_ENNEMY]; //damage de l'ennemi
  int enChange[NB_ENNEMY]; //possibilité pour l'ennemi de changer de direction
  SDL_Rect ennemyImage;
  ennemyImage.w = SPRITE_SIZE/2;
  ennemyImage.h = SPRITE_SIZE/2; 
  
  for(int i=0; i < NB_ENNEMY; i++){
    ennemy_array[i] = 0;
    temp   = SDL_LoadBMP("enemy.bmp");
    ennemy[i] = SDL_DisplayFormat(temp);
    SDL_SetColorKey(ennemy[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
    SDL_FreeSurface(temp);
    ennemyPosStart[i] = ennemyPos[i];
    ennemyDir[i] = EN_DIR_LEFT;
    enDamage[i] = 0;
    enChange[i] = 1;
  }    
  
  /*Bloc*/
  SDL_Rect blocImage;
  blocImage.y = 0;
  blocImage.w = BLOC_SIZE;
  blocImage.h = BLOC_SIZE;
  int plat_array[NB_PLATEFORME];
  for(int i=0; i < NB_PLATEFORME; i++){
    plat_array[i] = 0; //presence d'une plateforme
    temp = SDL_LoadBMP("bloc.bmp"); 
    plateforme[i] = SDL_DisplayFormat(temp);
    SDL_SetColorKey(plateforme[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
    SDL_FreeSurface(temp);
  }  
  
  
  afficher_bloc("niveau1.txt", plat_array, plateformePos, ennemy_array, ennemyPos, ennemyPosStart);
  

  if (start (&finsaut, skyL, spriteDem, spriteQuit,screen, font, varGlobal) == 1){
    while (getGameOver(varGlobal) != 1)
    {
      setPosY(font, 0);
      
      SDL_Event event;
	  
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &saut, &debutsaut, &hperso, &finsaut, &droite, &gauche, varGlobal);
      }
      
      //Pause
      if (!pause (varGlobal, spritePause, screen) && !game_over(varGlobal, spriteGameover, screen, sprite, &spriteImage, &spritePosition)){

      //Jeu
	//Handle timer
	incrTimer(varGlobal);
	fTimer (varGlobal);
	
	ennemyMove(ennemyPos, ennemyPosStart, ennemy_array, ennemyDir, &enAnimFlip, enChange, &delaiEn, plateformePos, 
		  plat_array, &spritePosition, &damage, &tempsDamage, &saut, enDamage, &enTempsDamage, ennemyPosDamage, varGlobal);
	
	/*handle the movement of the sprite*/
	move (&droite, &gauche, &spritePosition, &currentDirection, &finsaut, &delai, &animationFlip);
	
	/*Collisions*/      
	spriteCollide (&spritePosition, plateformePos, plat_array, ennemy_array, saut, &damage, ennemyPos, ennemyPosStart, varGlobal);
  
	/*Gestion des dégâts*/
	lose_life (&damage, &tempsDamage, varGlobal);
	
	stopEnnemy (enDamage, &enTempsDamage);

	/*Saut*/
	Saut (&hperso, &spritePosition, &saut, plat_array, plateformePos, &debutsaut, &finsaut, &damage, ennemy_array, ennemyPos, ennemyPosStart, varGlobal);
	
		      /******Affichage*******/
		      
		      
		/* draw the background */
      drawSky(sky, screen);

	      /*Dans bandeau noir*/
      drawFont (font, screen, varGlobal);     
	    
	      /*draw blocs*/
      drawBloc(plateforme, screen, &blocImage, plateformePos, plat_array);
	
	      /*draw sprites*/
      drawSprite (sprite, screen, &spriteImage, &spritePosition, &currentDirection, &animationFlip, &damage, &tempsDamage);
      
      drawEnnemy (ennemy, screen, &ennemyImage, ennemyPos, ennemyDir, &enAnimFlip, ennemy_array, enDamage, &enTempsDamage, ennemyPosDamage);
	
      drawBonus (oneUp, screen, &spritePosition, varGlobal);
  
      SDL_Delay(4);
      }
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }  
    /* clean up */
    for (int i = 0; i < NB_PLATEFORME; i++){
      SDL_FreeSurface(plateforme[i]);
    }
    for (int i = 0; i <NB_ENNEMY; i++){
      SDL_FreeSurface(ennemy[i]);
    }
    SDL_FreeSurface(sprite);
    destroyImage(font);
    destroyImage(sky);
    destroyImage(spriteGameover);
    destroyImage(spritePause);
    destroyImage(oneUp);
    destroyVarG(varGlobal);
    SDL_Quit();
    return 0;
  }
  else {
    return 0;
  }
    
}