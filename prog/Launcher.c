#include "Projet.h"

void HandleEvent(SDL_Event event,
        int *quit, int *haut, int *bas, int *space, int *entree)
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
		    *haut = 1;
		    break;
		    
                case SDLK_DOWN:
                    *bas = 1;
                    break;
		
		case SDLK_SPACE:
		    *space = 1;
		break;
		
		case SDLK_RETURN:
		    *entree = 1;
		break;
		
                default:
                    break;
	    }
	    break;
	    
	case SDL_KEYUP:
	    switch (event.key.keysym.sym) {
		case SDLK_UP:
                    *haut = 0;
                    break;
		    
                case SDLK_DOWN:
                    *bas = 0;
                    break;
		    
		default :
		    break;
	    }
	    break;
    }
}

int main(int argc, char* argv[]) {
  
  SDL_Surface *screen, *temp, *sky, *temps, *spriteDem, *spriteQuit;
  int colorkey;
  SDL_Rect tempsPosition;
  SDL_Rect demPosition;
  SDL_Rect quitPosition;
  int haut = 0;
  int bas = 0;
  int space = 0;
  int entree = 0;
  int changbas = 0;
  int changhaut = 0;
  int select = 0;
  int gameover = 0;
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  /* create window */
  screen = SDL_SetVideoMode(500, 190, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);
  
  /*Sky*/
  temp  = SDL_LoadBMP("ciel1.bmp");
  sky = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
    
  /*Timer*/
  temp   = SDL_LoadBMP("franklin.bmp");
  temps = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Rect tempsImage;
  tempsImage.y = 102;
  tempsImage.x = 446;
  tempsImage.w = 20;
  tempsImage.h = 20;
  tempsPosition.w = 20;
  tempsPosition.h = 20;
  tempsPosition.x = 190;
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(temps, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Pause*/
  temp  = SDL_LoadBMP("dem2.bmp");
  spriteDem = SDL_DisplayFormat(temp);
  demPosition.x = 217;
  SDL_FreeSurface(temp);
  SDL_SetColorKey(spriteDem, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /*Pause*/
  temp  = SDL_LoadBMP("quit2.bmp");
  spriteQuit = SDL_DisplayFormat(temp);
  quitPosition.x = 225;
  SDL_FreeSurface(temp);
  SDL_SetColorKey(spriteQuit, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  while (!gameover) {
    
    SDL_Event event;
	
    if (SDL_PollEvent(&event)) {
      HandleEvent(event, &gameover, &haut, &bas, &space, &entree);
    }
    
    if (haut == 0) {
	changhaut = 1;
    }
    
    if (changhaut == 1 && haut == 1) {
      changhaut = 0;
      select = 1 - select;
    }
    
    if (bas == 0) {
	changbas = 1;
    }
    
    if (changbas == 1 && bas == 1) {
      changbas = 0;
      select = 1 - select;
    }
    
    /* draw the background */
    SDL_BlitSurface(sky, NULL, screen, NULL);
    
    
    demPosition.y = 90;
    SDL_BlitSurface(spriteDem, NULL, screen, &demPosition);
    
    quitPosition.y = 120;
    SDL_BlitSurface(spriteQuit, NULL, screen, &quitPosition);
    
    if (select == 0) {
      tempsPosition.y = 90;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);

    }
    
    if (select == 1) {
      tempsPosition.y = 120;
      SDL_BlitSurface(temps, &tempsImage, screen, &tempsPosition);

    }
    
    if (space == 1 || entree == 1) {
      
      if (select == 0) {
	
	/* clean up */
	SDL_FreeSurface(sky);
	SDL_Quit();
	
	system("./projet");
	
	return 0;
      }
      
      if (select == 1) {
	  
	/* clean up */
	SDL_FreeSurface(sky);
	SDL_Quit();
	  
	return 0;
	
      }
      
    }
    
    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    
  }

}