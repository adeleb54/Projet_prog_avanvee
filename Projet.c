#include "fonction.h"

int main(int argc, char* argv[]) {
  
  SDL_Surface *screen, *temp, *sprite,*ennemy[NB_ENNEMY], *plateforme[NB_PLATEFORME];
  int currentDirection = DIR_RIGHT;
  int animationFlip = 0;
  int enAnimFlip = 0;
  SDL_Rect spritePosition;
  SDL_Rect ennemyPos [NB_ENNEMY];
  SDL_Rect plateformePos [NB_PLATEFORME];
  int saut = 0;
  int delaiEn = 0;
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
  VarS* varSprite = createVarS();

  
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
  
  /*Game name*/
  Image* spriteTitre = createImage("titre.bmp",151,40,0,0,0,0);
  SDL_SetColorKey(spriteTitre->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
      
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
  
  /*End Game Screen*/
  Image* spriteEndG = createImage("endgame.bmp",333,176,0,0,0,0);
  SDL_SetColorKey(spriteEndG->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));
  
  Image* spriteWP = createImage("wp.bmp",411,464,0,0,0,0);
  SDL_SetColorKey(spriteWP->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, getColorKey(varGlobal));

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
  

  if (start (skyL, spriteDem, spriteQuit, spriteTitre,screen, font, varGlobal) == 1){
    while (getGameOver(varGlobal) != 1)
    {
      setPosY(font, 0);
      
      SDL_Event event;
	  
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, varSprite, varGlobal, &saut);
      }
      
      //Pause
      if (!pause (varGlobal, spritePause, screen) && !game_over(varGlobal, spriteGameover, screen, sprite, &spriteImage, &spritePosition)){

      //Jeu
	//Handle timer
	if (getNiveau(varGlobal) < MAX_NIVEAU) {
	  incrTimer(varGlobal);
	  fTimer (varGlobal);
	}
	
	ennemyMove(ennemyPos, ennemyPosStart, ennemy_array, ennemyDir, &enAnimFlip, enChange, &delaiEn, plateformePos, 
		  plat_array, &spritePosition, enDamage, &enTempsDamage, ennemyPosDamage, varSprite, varGlobal);
	
	/*handle the movement of the sprite*/
	move (&spritePosition, varSprite);
	
	/*Collisions*/      
	spriteCollide (&spritePosition, plateformePos, plat_array, ennemy_array, ennemyPos, ennemyPosStart, varSprite, varGlobal);
  
	/*Gestion des dégâts*/
	lose_life (varSprite, varGlobal);
	
	stopEnnemy (enDamage, &enTempsDamage);

	/*Saut*/
	Saut ( &spritePosition, plat_array, plateformePos,ennemy_array, ennemyPos, ennemyPosStart, varGlobal, varSprite, &saut);
	
		      /******Affichage*******/
		      
		      
		/* draw the background */
      drawSky(sky, screen);

	      /*Dans bandeau noir*/
      drawFont (font, screen, varGlobal);     
	    
	      /*draw blocs*/
      drawBloc(plateforme, screen, &blocImage, plateformePos, plat_array);
	
	      /*draw sprites*/
      drawSprite (sprite, screen, &spriteImage, &spritePosition, varSprite, varGlobal);
      
      drawEnnemy (ennemy, screen, &ennemyImage, ennemyPos, ennemyDir, &enAnimFlip, ennemy_array, enDamage, &enTempsDamage, ennemyPosDamage);
	
      drawBonus (oneUp, screen, &spritePosition, varGlobal);
      
      if(getNiveau(varGlobal) == MAX_NIVEAU) {
	drawEndG (sprite, screen, &spriteImage, &spritePosition, font, spriteEndG, spriteWP, &currentDirection, &animationFlip, varGlobal);
      }
  
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
    destroyImage(spriteEndG);
    destroyImage(spriteWP);
    destroyImage(spriteTitre);
    destroyVarG(varGlobal);
    destroyVarS(varSprite);
    SDL_Quit();
    return 0;
  }
  else {
    return 0;
  }
    
}