#include <SDL.h>
#include <stdio.h>

/* Size of the window */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
/* Size of the grass texture picture */
#define GRASS_SIZE    32

/* In the sprite, we have 8 images of a 32x32 picture,
 * 2 images for each direction. */
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

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     1

/* Handle events coming from the user:
        - quit the game?
        - use of arrows to move the sprite
   In the second case, we modify the current direction and the
   position of the sprite in the window.
   We also change the animation bit used for creating the "walk" effect.
   */
void HandleEvent(SDL_Event event,
        int *quit, int *currDirection, int *animFlip, SDL_Rect *position, int *saut, int *debutsaut, int *hperso, int *finsaut, int *droite, int *gauche )
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
                    *currDirection = DIR_LEFT;
                    *animFlip = 1 - *animFlip;
                    *gauche = 1;
                    break;
                case SDLK_RIGHT:
                    *currDirection = DIR_RIGHT;
                    *animFlip = 1 - *animFlip;
                    *droite = 1;
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
		    
		default :
		    break;
	    }
	    break;
    }
}

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *sprite, *grass, *bloc;
  int colorkey;
  
  /* Information about the current situation of the sprite: */
  int currentDirection = DIR_RIGHT;
  /* Walking in a direction is animated with 2 images; we use a boolean
   * that we flip after each movement to show them in turn and create
   * the illusion */
  int animationFlip = 0;
  
  /* Rectangle to store the position of the sprite in the window.
   * Only the x and y coordinates are used. */
  SDL_Rect spritePosition, blocPosition;
  
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);
  
  /* load sprite */
  temp   = SDL_LoadBMP("sprite.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  /* Define the source rectangle for the BlitSurface */
  SDL_Rect spriteImage;
  spriteImage.y = 0;
  spriteImage.w = SPRITE_SIZE;
  spriteImage.h = SPRITE_SIZE;
  spritePosition.w = SPRITE_SIZE;
  spritePosition.h = SPRITE_SIZE;
  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /* load grass */
  temp  = SDL_LoadBMP("grass.bmp");
  grass = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
    
  /* load bloc */
  temp  = SDL_LoadBMP("bloc.bmp");
  bloc = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  blocPosition.w = BLOC_SIZE;
  blocPosition.h = BLOC_SIZE;
  /* set sprite position in the middle of the window */
  spritePosition.x = 20;
  spritePosition.y = 440;
  
  blocPosition.x = 500;
  blocPosition.y = 440;
  
  int gameover = 0;
  int hperso = spritePosition.y;
  int debutsaut;
  int finsaut = 1;
  int saut = 0;
  int droite = 0;
  int gauche = 0;
  
  
  int collision(SDL_Rect A, SDL_Rect B){
    if(A.x >= B.x + B.w || A.x + A.w <= B.x || A.y >= B.y + B.h || A.y + A.h <= B.y){
      return 0;
    }
    if(A.y > B.y - B.h + 1 && A.y < B.y){
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
  

    
    /* main loop: check events and re-draw the window until the end */
    while (!gameover)
      {
        SDL_Event event;
	
    //printf ("y= %u\n",spritePosition.y);
        /* look for an event; possibly update the position and the shape
         * of the sprite. */
        if (SDL_PollEvent(&event)) {
	  HandleEvent(event, &gameover, &currentDirection,
		      &animationFlip, &spritePosition, &saut, &debutsaut, &hperso, &finsaut, &droite, &gauche);
        }
	/*printf("blocx - taille sprite %d\n",blocPosition.x - SPRITE_SIZE);
	  printf("spritex %d\n",spritePosition.x);*/
        /* collide with edges of screen */
	
	if (droite == 1){
	  spritePosition.x += SPRITE_STEP;
	}
	if (gauche == 1) {
	  spritePosition.x -= SPRITE_STEP;
	}
	
	
	
        if (spritePosition.x <= 0)
	  spritePosition.x = 0;
        if (spritePosition.x >= SCREEN_WIDTH - SPRITE_SIZE) 
	  spritePosition.x = SCREEN_WIDTH - SPRITE_SIZE;
	
        if (spritePosition.y <= 0)
	  spritePosition.y = 0;
        if (spritePosition.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
	  spritePosition.y = SCREEN_HEIGHT - SPRITE_SIZE;
	
        if (collision(spritePosition,blocPosition)==1){
	  spritePosition.x = blocPosition.x - SPRITE_SIZE;
	}
	if (collision(spritePosition,blocPosition)==2){
	  spritePosition.x = blocPosition.x + BLOC_SIZE;
	}
	if (collision(spritePosition,blocPosition)==3){
	  spritePosition.y = blocPosition.y - blocPosition.h;
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
	if (collision(spritePosition,blocPosition) == 3) {
	  spritePosition.y -= 1;
	  finsaut = 1;
	}
	 if (spritePosition.y == SOL) {
	  finsaut = 1;
	}

        /* Draw the selected image of the sprite at the right position */
        
	
	/* choose image according to direction and animation flip: */
	spriteImage.x = SPRITE_SIZE*(2*currentDirection + animationFlip);
	
	SDL_BlitSurface(sprite, &spriteImage, screen, &spritePosition);
        
        
        SDL_Delay(5);
	
	SDL_BlitSurface(bloc,NULL, screen, &blocPosition);
        /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    
    /* clean up */
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(grass);
    SDL_Quit();
    
    return 0;
}
