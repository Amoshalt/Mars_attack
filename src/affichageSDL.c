#include "position.h"
#include "protection.h"
#include "ensembleprotection.h"
#include "map.h"
#include "alien.h"
#include "ensemblealien.h"
#include "missile.h"
#include "ensemblemissile.h"
#include "vaisseau.h"
#include "scores.h"
#include "jeu.h"
#include "jeuSDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>



/*
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./bin/prog
*/
int main()
{ 
    jeusdl JS;
     

    

    initSDL(&JS);

    menuSDL(&JS);

    detruireSDL(&JS);

    

    /* On quitte la SDL  */
    IMG_Quit();
    SDL_Quit(); 
    TTF_Quit();
	Mix_CloseAudio();
    
    return 0; 
}
