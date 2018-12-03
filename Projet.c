#include "fonction.h"
#include "structure.h"

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp,
	      *ennemy[NB_ENNEMY],/* *spriteDem, *spriteQuit, *skyL,*/
	      *oneup, *plateforme[NB_PLATEFORME];
  int colorkey;
  // int currentDirection = DIR_RIGHT;
  // int animationFlip = 0;
  int enAnimFlip = 0;
  SDL_Rect upPosition;
  SDL_Rect ennemyPos [NB_ENNEMY];
  SDL_Rect plateformePos [NB_PLATEFORME];
//   SDL_Rect demPosition;
//   SDL_Rect quitPosition;
  int gameover = 2;
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
  int enTempsDamage = 0;
  int haut = 0;
  int bas =  0; 
//   int entree = 0;
//   int select = 0;
  int niveau = 1;
  int change = 1;
  
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);

  
  /*Sprites*/
  Image* spriteIm = createImage("sprite.bmp", 0, SOL, SPRITE_SIZE, SPRITE_SIZE, 0, 0);
  Sprite* sprite = createSprite(spriteIm);
//   SDL_Rect spriteImage;
//   spriteImage.y = 0;
//   spriteImage.w = SPRITE_SIZE;
//   spriteImage.h = SPRITE_SIZE;
//   spritePosition.w = SPRITE_SIZE;
//   spritePosition.h = SPRITE_SIZE;
//   spritePosition.x = 50;
//   spritePosition.y = SOL;
  SDL_SetColorKey(getImage(sprite)->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Font*/
  Image * font = createImage("franklin.bmp",0,0,FONT_SIZE,FONT_SIZE,0,0);
  SDL_SetColorKey(font->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);  
    
//   SDL_Rect selectImage;
//   selectImage.w = FONT_SIZE;
//   selectImage.h = FONT_SIZE;
//   selectImage.x = FONT_SIZE * 14;
//   selectImage.y = FONT_SIZE * 3;
//   SDL_SetColorKey(font, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  
//  /*Sky Launcher*/
//   temp  = SDL_LoadBMP("ciel1.bmp");
//   skyL = SDL_DisplayFormat(temp);
//   SDL_FreeSurface(temp);

  /*Sky*/
  Image* sky = createImage("ciel.bmp",0,0,0,0,0,0);
      
//   /*Start*/
//   temp  = SDL_LoadBMP("dem2.bmp");
//   spriteDem = SDL_DisplayFormat(temp);
//   demPosition.x = 217;
//   SDL_FreeSurface(temp);
//   SDL_SetColorKey(spriteDem, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
//   
//   /*Quit*/
//   temp  = SDL_LoadBMP("quit2.bmp");
//   spriteQuit = SDL_DisplayFormat(temp);
//   quitPosition.x = 225;
//   SDL_FreeSurface(temp);
//   SDL_SetColorKey(spriteQuit, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  /*Pause*/
  Image * spritePause = createImage("Pause.bmp", (SCREEN_WIDTH - 72)/2, (SCREEN_HEIGHT - 20)/2, 0, 0, 0, 0);
  SDL_SetColorKey(spritePause->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
  /*Game Over*/
  Image* spriteGameover = createImage("gameover.bmp", (SCREEN_WIDTH - 126)/2, (SCREEN_HEIGHT - 20)/2, 0, 0, 0, 0);
  SDL_SetColorKey(spriteGameover->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  /*1up*/
  temp  = SDL_LoadBMP("items.bmp");
  oneup = SDL_DisplayFormat(temp);
  SDL_Rect upImage;
  upImage.w = 31;
  upImage.h = 30;
  upImage.y = 0;
  SDL_FreeSurface(temp);
  SDL_SetColorKey(oneup, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
    /*Enemi*/  
  /*Initialisation du tableau ennemy_array[] qui enregistre la présence des enemis affichés*/
  int ennemy_array[NB_ENNEMY];
  for(int i=0; i < NB_ENNEMY; i++){
    ennemy_array[i] = 0;
  }    
  /*Initialisation de ennemy[] qui contient les images des enemis*/  
  for (int i=0; i<NB_ENNEMY; i++){
    temp   = SDL_LoadBMP("enemy.bmp");
    ennemy[i] = SDL_DisplayFormat(temp);
    SDL_SetColorKey(ennemy[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_FreeSurface(temp);
  }
  SDL_Rect ennemyImage;
  ennemyImage.w = SPRITE_SIZE/2;
  ennemyImage.h = SPRITE_SIZE/2; 
  SDL_Rect ennemyPosDamage[NB_ENNEMY];
  
  /*Initialisation de ennemyPosStart[] qui enregistre la position de depart des ennemis*/
  SDL_Rect ennemyPosStart[NB_ENNEMY];
  for (int i =0; i<NB_ENNEMY; i++){
    ennemyPosStart[i] = ennemyPos[i];
  }  
  
  /*Initialisation de ennemyDir[] qui enregistre la direction de chaque ennemi*/
  int ennemyDir[NB_ENNEMY];
  for (int i =0; i<NB_ENNEMY; i++){
    ennemyDir[i] = EN_DIR_LEFT;
  }
  
  int enDamage[NB_ENNEMY];
  for (int i =0; i<NB_ENNEMY; i++){
    enDamage[i] = 0;
  }
  
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
  
  
  afficher_bloc("test.txt", plat_array, plateformePos, ennemy_array, ennemyPos, ennemyPosStart);
  

  //if (start (&haut, &finsaut, &select, &bas, &entree, &gameover, skyL, spriteDem, spriteQuit,screen, font, &demPosition, &quitPosition, &fontPosition, &selectImage) == 1){
    while (gameover != 1)
    {
      setPosY(font, 0);
      
      SDL_Event event;
	  
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover, sprite, &space, &bas, pause (&space, &changspace, &pauseV, spritePause, screen));
      }
      
      //Pause
      if ((pause (&space, &changspace, &pauseV, spritePause, screen) == 1) && (game_over(sprite, spriteGameover, screen) == 0)){

	
      //Jeu
	//Handle timer
	timer += 1;
	fTimer (&timer, &heures, &minutes, &secondes);
	
	ennemyMove(ennemyPos, ennemyPosStart, ennemy_array, ennemyDir, &enAnimFlip, &change, &delaiEn, plateformePos, 
		  plat_array, sprite, enDamage, &enTempsDamage, ennemyPosDamage);
	
	/*handle the movement of the sprite*/
	move (sprite);
	
	/*Collisions*/      
	spriteCollide (sprite, plateformePos, plat_array, ennemy_array, &item, &clef, &tempsItem, &niveau, ennemyPos, ennemyPosStart);
  
	/*Gestion des dégâts*/
	lose_life (sprite);
	
	stopEnnemy (enDamage, &enTempsDamage);

	/*Saut*/
	Saut (sprite, plat_array, plateformePos);
	
		      /******Affichage*******/
		      
		      
		/* draw the background */
      drawSky(sky, screen);
	
	      /*Dans bandeau noir*/
      drawFont (font, screen, &heures, &minutes, &secondes, &clef, sprite);     
	    
	      /*draw blocs*/
      drawBloc(plateforme, screen, &blocImage, plateformePos, plat_array);
	
	      /*draw sprites*/
      drawSprite (sprite, screen);
      
      drawEnnemy (ennemy, screen, &ennemyImage, ennemyPos, ennemyDir, &enAnimFlip, ennemy_array, enDamage, &enTempsDamage, ennemyPosDamage);
	
      drawBonus (oneup, screen, &upImage, &upPosition, &item, &tempsItem, sprite);
  
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
    destroyImage(getImage(sprite));
    destroyImage(sky);
    destroyImage(spritePause);
    destroyImage(spriteGameover);
    destroyImage(font);
    SDL_FreeSurface(oneup);
    SDL_Quit();
    return 0;
  // }
  // else {
  //   return 0;
  // }
    
}
