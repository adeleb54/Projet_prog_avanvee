#include <SDL.h>
#include <stdio.h>
#include <stdarg.h>

/* Size of the window */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

/* Size of the grass texture picture */
#define GRASS_SIZE    32

/* Size of one image: */
#define SPRITE_SIZE     32
#define BLOC_SIZE       39

/* Order of the different directions in the picture: */
#define DIR_RIGHT       1
#define DIR_LEFT        3

#define SAUT 1
#define PASSAUT 0

#define HSAUT 50
#define SOL 448

#define NB_SOL 2
#define NB_PLATEFORME 1

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     1

void HandleEvent(SDL_Event event,
        int *quit, int *currDirection, int *animFlip, SDL_Rect *position, int *saut, int *debutsaut, int *hperso, int *finsaut, int *droite, int *gauche, int *space)
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
		    break;
		    
		default :
		    break;
	    }
	    break;
    }
}

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *sprite, *grass, *temps, *plateforme[NB_PLATEFORME];
  int colorkey;
  int currentDirection = DIR_RIGHT;
  int animationFlip = 0;
  SDL_Rect spritePosition;
  SDL_Rect tempsPosition;
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
  spritePosition.x = 20;
  spritePosition.y = 440;
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Grass */
  temp  = SDL_LoadBMP("grass.bmp");
  grass = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
    
  /*Bloc*/
  temp   = SDL_LoadBMP("bubex_black.bmp");
  temps = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Rect tempsImage;
  tempsImage.x = 0;
  tempsImage.w = 54;
  tempsImage.h = 54;
  tempsPosition.w = 54;
  tempsPosition.h = 54;
  tempsPosition.x = 5;
  tempsPosition.y = 5;
  SDL_SetColorKey(temps, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Initialisation du tableau plat_array qui enregistre la présence des plateformes affichées*/
  int plat_array[NB_PLATEFORME];
  for(int i=0; i < NB_PLATEFORME; i++){
    plat_array[i] = 0;
  }
  
  /*Initialisation de plateforme[] qui contient les images des blocs*/
  for (int i=0; i<NB_PLATEFORME; i++){
    temp = SDL_LoadBMP("bloc.bmp"); 
    plateforme[i] = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp); 
  }
  

  SDL_Rect plateformePos [NB_PLATEFORME];
  plateformePos[0].x = 500;
  plateformePos[0].y = 440;
  plat_array[0] = 1;
 
  int collision(SDL_Rect A, SDL_Rect B){
    if(A.x >= B.x + B.w || A.x + A.w <= B.x || A.y >= B.y + B.h || A.y + A.h <= B.y){
      return 0;
    }
    if(A.y > B.y - B.h + 1 && A.y < B.y - 30){
      saut = PASSAUT;
      return 3;
    }
    if(A.x + A.w >= B.x && A.x < B.x){
      return 1;
    }
    if(A.x <= B.x + B.w && A.x > B.x){
      return 2;
    }
    return 0;
  }
  
  
  while (!gameover)
  {
    SDL_Event event;
	
    //printf ("y= %u\n",spritePosition.y)
    if (SDL_PollEvent(&event)) {
      HandleEvent(event, &gameover, &currentDirection,
		  &animationFlip, &spritePosition, &saut, &debutsaut, &hperso, &finsaut, &droite, &gauche, &space);
    }
    /*printf("blocx - taille sprite %d\n",blocPosition.x - SPRITE_SIZE);
      printf("spritex %d\n",spritePosition.x);*/
    
    if (space == 0) {
      changspace = 1;
    }
    
    if (changspace == 1 && space == 1) {
      changspace = 0;
      pause = 1 - pause;
    }
    
    
    if (pause == 1) {
    
      timer += 1;
      
      int secondes = timer/200;
      int heures = secondes/3600;
      secondes = secondes - 3600*heures;
      int minutes = secondes / 60;
      secondes = secondes - 60*minutes;
      /*printf("%d : %d : %d\n", heures, minutes, secondes);*/
      
      
      
      
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
      
	  
      if (spritePosition.x <= 0)
	spritePosition.x = 0;
      if (spritePosition.x >= SCREEN_WIDTH - SPRITE_SIZE) 
	spritePosition.x = SCREEN_WIDTH - SPRITE_SIZE;
      
      if (spritePosition.y <= 0)
	spritePosition.y = 0;
      if (spritePosition.y >= SCREEN_HEIGHT - SPRITE_SIZE)
	spritePosition.y = SCREEN_HEIGHT - SPRITE_SIZE;
      
      for (int i = 0; i <NB_PLATEFORME; i++){
	if (collision(spritePosition,plateformePos[i])==1){
	  spritePosition.x = plateformePos[i].x - SPRITE_SIZE;
	}
	if (collision(spritePosition,plateformePos[i])==2){
	  spritePosition.x = plateformePos[i].x + BLOC_SIZE;
	    }
	if (collision(spritePosition,plateformePos[i])==3){
	  spritePosition.y = plateformePos[i].y - BLOC_SIZE;
	}
      }
      
      
      /* draw the background */
      for (int x = 0; x < SCREEN_WIDTH / GRASS_SIZE; x++) {
	for (int y = 0; y < SCREEN_HEIGHT / GRASS_SIZE; y++) {
	  SDL_Rect position;
	  position.x = x * GRASS_SIZE;
	      position.y = y * GRASS_SIZE;
	      SDL_BlitSurface(grass, NULL, screen, &position);
	}
      }
      
      tempsImage.y = 51 * (heures/10);
      tempsPosition.x = 0;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);
      
      tempsImage.y = 51 * (heures%10);
      tempsPosition.x += 54;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);
      
      tempsImage.y = 51 * (minutes/10);
      tempsPosition.x += 54;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);
      
      tempsImage.y = 51 * (minutes%10);
      tempsPosition.x += 54;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);
      
      tempsImage.y = 51 * (secondes/10);
      tempsPosition.x += 54;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);
      
      tempsImage.y = 51 * (secondes%10);
      tempsPosition.x += 54;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);
      
      /*Saut*/
      hperso = spritePosition.y;
      
      
      if (saut == SAUT) {
	if ((spritePosition.y >= debutsaut - HSAUT) && (spritePosition.y != 0)){
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
	if (collision(spritePosition,plateformePos[i]) == 3) {
	  spritePosition.y -= 1;
	  finsaut = 1;
	}
      }
      if (spritePosition.y == SOL) {
	finsaut = 1;      
      }

      /* Draw the selected image of the sprite at the right position */
	  
	  
      /* choose image according to direction and animation flip: */
      spriteImage.x = SPRITE_SIZE*(2*currentDirection + animationFlip);
	  
      SDL_BlitSurface(sprite, &spriteImage, screen, &spritePosition);
	  
	  
      SDL_Delay(4);
	  
      for (int i=0; i < NB_PLATEFORME; i++){ 
	if (plat_array[i] == 1){
	  SDL_BlitSurface(plateforme[i],NULL, screen, &plateformePos[i]);
	}  
      }
    }

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
    
  /* clean up */
  SDL_FreeSurface(sprite);
  SDL_FreeSurface(grass);
  SDL_Quit();
    
  return 0;
}
