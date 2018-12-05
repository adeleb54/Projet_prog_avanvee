#include "fonction.h"
#include "structure.h"

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp,
	      /*ennemy[NB_ENNEMY], *spriteDem, *spriteQuit, *skyL,*/
	       *plateforme[NB_PLATEFORME];
  int colorkey;
  // int currentDirection = DIR_RIGHT;
  // int animationFlip = 0;
  //int enAnimFlip = 0;
  //SDL_Rect ennemyPos [NB_ENNEMY];
  SDL_Rect plateformePos [NB_PLATEFORME];
//   SDL_Rect demPosition;
//   SDL_Rect quitPosition;
  int gameover = 2;
  //int delaiEn = 0;
  //int timer = 0;
  //int pauseV = 1;
  //int space = 0;
  //int changspace = 1;
  // int vie = 5;
  //int secondes, minutes, heures;
  //int item = 0;
  //int tempsItem = 0;
  //int clef = 0;  
  //int enTempsDamage = 0;
//   int haut = 0;
//   int bas =  0; 
//   int entree = 0;
//   int select = 0;
  //int niveau = 1;
  //int change = 1;
  
  VariablesG* varGlobal = createVarG();
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH_START, SCREEN_HEIGHT_START, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);

  
  /*Sprites*/
  Image* spriteIm = createImage("sprite.bmp", 0, SOL, SPRITE_SIZE, SPRITE_SIZE, 0, 0);
  Sprite* sprite = createSprite(spriteIm);
  SDL_SetColorKey(getImage(sprite)->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Font*/
  Image * font = createImage("franklin.bmp",0,0,FONT_SIZE, FONT_SIZE, FONT_SIZE*14, FONT_SIZE*3);
  SDL_SetColorKey(font->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);   
  
 /*Sky Launcher*/
  Image * skyL = createImage("ciel1.bmp",0,0,0,0,0,0);

  /*Sky*/
  Image* sky = createImage("ciel.bmp",0,0,0,0,0,0);
      
  /*Start*/
  Image * spriteDem = createImage("dem2.bmp",217,90,0,0,0,0);
  SDL_SetColorKey(spriteDem->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey); 
  
  /*Quit*/
  Image * spriteQuit = createImage("quit2.bmp",225,120,0,0,0,0);
  SDL_SetColorKey(spriteQuit->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey); 

  /*Pause*/
  Image * spritePause = createImage("Pause.bmp", (SCREEN_WIDTH - 72)/2, (SCREEN_HEIGHT - 20)/2, 0, 0, 0, 0);
  SDL_SetColorKey(spritePause->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
  /*Game Over*/
  Image* spriteGameover = createImage("gameover.bmp", (SCREEN_WIDTH - 126)/2, (SCREEN_HEIGHT - 20)/2, 0, 0, 0, 0);
  SDL_SetColorKey(spriteGameover->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  /*1up*/
  Image* oneUp = createImage("items.bmp", 0, 0, 31, 30, 0, 0);
  SDL_SetColorKey(oneUp->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
//   temp  = SDL_LoadBMP("items.bmp");
//   oneup = SDL_DisplayFormat(temp);
//   SDL_Rect upImage;
//   upImage.w = 31;
//   upImage.h = 30;
//   upImage.y = 0;
//   SDL_FreeSurface(temp);
//   SDL_SetColorKey(oneup, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
    /*Enemi*/  
  /*Initialisation du tableau ennemy_array[] qui enregistre la présence des enemis affichés*/
  
//   int ennemy_array[NB_ENNEMY];
//   for(int i=0; i < NB_ENNEMY; i++){
//     ennemy_array[i] = 0;
//   }    
  /*Initialisation de ennemy[] qui contient les images des enemis*/  
  Sprite* ennemi[NB_ENNEMY];
  for(int i = 0; i<NB_ENNEMY; i++){
    Image* imEnnemy = createImage("enemy.bmp", 0, 0, SPRITE_SIZE/2, SPRITE_SIZE/2, 0, 0);
    ennemi[i] = createSprite(imEnnemy);
    SDL_SetColorKey(getImage(ennemi[i])->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  }
  
//   for (int i=0; i<NB_ENNEMY; i++){
//     temp   = SDL_LoadBMP("enemy.bmp");
//     ennemy[i] = SDL_DisplayFormat(temp);
//     SDL_SetColorKey(ennemy[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
//     SDL_FreeSurface(temp);
//   }
//   SDL_Rect ennemyImage;
//   ennemyImage.w = SPRITE_SIZE/2;
//   ennemyImage.h = SPRITE_SIZE/2; 
//   SDL_Rect ennemyPosDamage[NB_ENNEMY];
  
  /*Initialisation de ennemyPosStart[] qui enregistre la position de depart des ennemis*/
//   SDL_Rect ennemyPosStart[NB_ENNEMY];
//   for (int i =0; i<NB_ENNEMY; i++){
//     ennemyPosStart[i] = ennemyPos[i];
//   }  
  
  /*Initialisation de ennemyDir[] qui enregistre la direction de chaque ennemi*/
//   int ennemyDir[NB_ENNEMY];
//   for (int i =0; i<NB_ENNEMY; i++){
//     ennemyDir[i] = EN_DIR_LEFT;
//   }
//   
//   int enDamage[NB_ENNEMY];
//   for (int i =0; i<NB_ENNEMY; i++){
//     enDamage[i] = 0;
//   }
  
  /******************Bloc******************/
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
  
  
  afficher_bloc("test.txt", plat_array, plateformePos, ennemi);
  

  if (start (varGlobal, skyL, spriteDem, spriteQuit, screen, font) == 1){
  while (gameover != 1)
    {
      setPosY(font, 0);
      
      SDL_Event event;
	  
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover, sprite, varGlobal);
      }
      
      //Pause
      if ((pause (varGlobal, spritePause, screen) == 0) && (game_over(sprite, spriteGameover, screen) == 0)){

	
      //Jeu
	//Handle timer
	incrTimer(varGlobal);
	fTimer (varGlobal);
	
// 	ennemyMove(ennemi, plateformePos, plat_array, sprite)
// 	ennemyMove(ennemyPos, ennemyPosStart, ennemy_array, ennemyDir, &enAnimFlip, &change, &delaiEn, plateformePos, 
// 		  plat_array, sprite, enDamage, &enTempsDamage, ennemyPosDamage);
	
	/*handle the movement of the sprite*/
	move (sprite);
	
	/*Collisions*/      
	//spriteCollide (sprite, plateformePos, plat_array, ennemi, varGlobal);
	//spriteCollide (sprite, plateformePos, plat_array, ennemy_array, varGlobal, ennemyPos, ennemyPosStart);
  
	/*Gestion des dégâts*/
	lose_life (sprite);
	
// 	stopEnnemy (ennemi);
// 	stopEnnemy (enDamage, &enTempsDamage);

	/*Saut*/
	Saut (sprite, plat_array, plateformePos);
	
		      /******Affichage*******/
		      
		      
		/* draw the background */
      drawSky(sky, screen);
	
	      /*Dans bandeau noir*/
      drawFont (font, screen, varGlobal, sprite);     
	    
	      /*draw blocs*/
      drawBloc(plateforme, screen, &blocImage, plateformePos, plat_array);
	
	      /*draw sprites*/
      drawSprite (sprite, screen);
      
      //drawEnnemy (ennemi, screen);
      //drawEnnemy (ennemy, screen, &ennemyImage, ennemyPos, ennemyDir, &enAnimFlip, ennemy_array, enDamage, &enTempsDamage, ennemyPosDamage);
	
      drawBonus (oneUp, screen, varGlobal, sprite);
  
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
      //SDL_FreeSurface(ennemy[i]);
      destroyImage(getImage(ennemi[i]));
    }
    destroyImage(getImage(sprite));
    destroyImage(sky);
    destroyImage(spritePause);
    destroyImage(spriteGameover);
    destroyImage(font);
    destroyImage(oneUp);
    SDL_Quit();
    return 0;
  }
  else {
    return 0;
  }
    
}
