#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include "jeuSDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include "assert.h"


const int MARGE_HAUT = 60;
const int MARGE_MENU = 35;
const int TAILLE_FENETRE_X = 540;
const int TAILLE_FENETRE_Y = 660;
const int TAILLE_OBJET = 20;


void initSDL(jeusdl *jsdl)
{
    TTF_Init();

	/* Initialisation de la SDL*/
    if(SDL_VideoInit(NULL) != 0) 
    {
        printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
        SDL_Quit();
    }

    /* Création de la fenêtre :*/
    jsdl->fenetre = SDL_CreateWindow("Mars_attack V1.0" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , TAILLE_FENETRE_X , TAILLE_FENETRE_Y , SDL_WINDOW_RESIZABLE);
    if(jsdl->fenetre == NULL)
    {
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
        SDL_Quit();
    }

    /* Création du renderer*/
    jsdl->renderer = SDL_CreateRenderer(jsdl->fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    if(jsdl->renderer == NULL)
    {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        SDL_Quit();
    }

    /*Initialisation de SDL_image*/
    IMG_Init(IMG_INIT_JPG);
    IMG_Init(IMG_INIT_PNG);

    /*chargement des images pour le jeu*/
    chargementimage("./data/images/soucoupe.xcf", jsdl , &(jsdl->imageAlien1));
    assert(jsdl->imageAlien1.texture != NULL);
    chargementimage("./data/images/soucoupe2.png", jsdl , &(jsdl->imageAlien2));
    assert(jsdl->imageAlien2.texture != NULL);
    chargementimage("./data/images/soucoupe3.png", jsdl , &(jsdl->imageAlien3));
    assert(jsdl->imageAlien3.texture != NULL);
    chargementimage("./data/images/missilealien.png", jsdl , &(jsdl->imageMissileAlien));
    assert(jsdl->imageMissileAlien.texture != NULL);
    chargementimage("./data/images/missilevaisseau1.png", jsdl , &(jsdl->imageMissileVaisseau));
    assert(jsdl->imageMissileVaisseau.texture != NULL);
    chargementimage("./data/images/missilevaisseau2.png", jsdl , &(jsdl->imageSuperMissile));
    assert(jsdl->imageSuperMissile.texture != NULL);
    chargementimage("./data/images/vaisseau.xcf", jsdl , &(jsdl->imageVaisseau));
    assert(jsdl->imageVaisseau.texture != NULL);
    chargementimage("./data/images/vie.png", jsdl , &(jsdl->imageVie));
    assert(jsdl->imageVie.texture != NULL);
    chargementimage("./data/images/etoile.xcf", jsdl , &(jsdl->imageBonus));
    assert(jsdl->imageVie.texture != NULL);
    chargementimage("./data/images/protection.png", jsdl , &(jsdl->imageProtection));
    assert(jsdl->imageVie.texture != NULL);
    chargementimage("./data/images/fond.JPG", jsdl, &(jsdl->fond));
    assert (jsdl->fond.texture != NULL);

    /*initialisation du jeu*/
    initJeu(&(jsdl->J));

    /* initialise TTF*/
    TTF_Init();
    /* Chargement de la police */
    jsdl->police = TTF_OpenFont("./data/police.ttf", 10);
    assert(jsdl->police!=NULL);

    
    /* initialisation de SDL mixer*/
    SDL_Init(SDL_INIT_AUDIO) ;

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) /*Initialisation de l'API Mixer*/
    {
       printf("%s", Mix_GetError());
    }

    /*initialisation des volumes*/
    jsdl->volumeMus = 64;
    jsdl->volumeBrui = 64;
}


void chargementimage(const char* nomfichier, jeusdl *jsdl, image * IM)
{
	IM->surface = IMG_Load(nomfichier);
	if(!IM->surface)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        SDL_Quit();
    }

    IM->texture = SDL_CreateTextureFromSurface(jsdl->renderer,IM->surface);
    if(!IM->texture)
    {
        printf("Erreur de creation de la texture : %s",SDL_GetError());
        SDL_Quit();
    }
}


void afficherimage(image *IM, jeusdl *jsdl, int positionX, int positionY, int largeurX, int largeurY )
{
	SDL_Rect rect;
	rect.x = positionX;
	rect.y = positionY;
	rect.w = largeurX;
	rect.h = largeurY;
	if (IM->texture == NULL)
    {
        IM->texture = SDL_CreateTextureFromSurface(jsdl->renderer, IM->surface);
    }
    SDL_RenderCopy(jsdl->renderer, IM->texture, NULL, &rect);
}


void afficherjeu(jeusdl jsdl)
{
	int k, i;
    char  scores[100];
    SDL_Rect rectScore;
    SDL_Texture * textScore;
    SDL_Surface * texte;
    SDL_Color couleurRouge ;

    couleurRouge.r = 255;
    couleurRouge.g = 0;
    couleurRouge.b = 0;

    /* affichage du score en haut*/
    sprintf(scores, "Score: %d  Meilleur score: %d Niveau : %d ", jsdl.J.Scores.Score , jsdl.J.Scores.MeilleurScore, jsdl.J.niveau);
    assert (scores != NULL);

    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Solid(jsdl.police, scores, couleurRouge);
    assert(texte!=NULL);
   
    /* affichage du reste de la map*/


    afficherimage(&(jsdl.fond), &jsdl,0,0,TAILLE_FENETRE_X, TAILLE_FENETRE_Y);

    rectScore.x = 0;
    rectScore.y = 0;
    rectScore.h = MARGE_HAUT/2;
    rectScore.w = jsdl.J.Map.dimx*TAILLE_OBJET;

    SDL_SetRenderDrawColor(jsdl.renderer, 0,0,0,0);
    SDL_RenderFillRect(jsdl.renderer, &rectScore);

    textScore = SDL_CreateTextureFromSurface(jsdl.renderer, texte);
    SDL_RenderCopy(jsdl.renderer, textScore, NULL, &rectScore);

	for (k=0;k<jsdl.J.Map.dimy;k++)
    {
        for (i=0;i<jsdl.J.Map.dimx;i++)
        {
            if (jsdl.J.Map.tab[i][k] =='A')
            {
            	afficherimage(&(jsdl.imageAlien1), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );
            }
            if (jsdl.J.Map.tab[i][k] =='a')
            {
                afficherimage(&(jsdl.imageAlien2), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );
            }
            if (jsdl.J.Map.tab[i][k] =='s')
            {
                afficherimage(&(jsdl.imageAlien3), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );
            }
            else if (jsdl.J.Map.tab[i][k] =='M')
            {
                afficherimage(&(jsdl.imageMissileVaisseau), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );            	
            }
            else if (jsdl.J.Map.tab[i][k] =='m')
            {
                afficherimage(&(jsdl.imageMissileAlien), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );
            }
            else if (jsdl.J.Map.tab[i][k] =='N')
            {
                afficherimage(&(jsdl.imageSuperMissile), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );
            }
            else if (jsdl.J.Map.tab[i][k] =='B')
            {
                afficherimage(&(jsdl.imageVie), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET);
            }
            else if (jsdl.J.Map.tab[i][k] =='C')
            {
                afficherimage(&(jsdl.imageBonus), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );
            }
            else if (jsdl.J.Map.tab[i][k] =='V')
            {
            	afficherimage(&(jsdl.imageVaisseau), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, 2*TAILLE_OBJET );
            }
            else if (jsdl.J.Map.tab[i][k] =='P')
            {
                afficherimage(&(jsdl.imageProtection), &jsdl, i*TAILLE_OBJET, k*TAILLE_OBJET+MARGE_HAUT, TAILLE_OBJET, TAILLE_OBJET );
            }
        }
    }

    for (i = 0; i < jsdl.J.Vaisseau.vieVaisseau; i++)
    {
        afficherimage(&(jsdl.imageVie), &jsdl, i*TAILLE_OBJET, MARGE_HAUT/2, TAILLE_OBJET, TAILLE_OBJET);
    }

    for (k = 1; k<= jsdl.J.supermissile; k++)
    {
        afficherimage(&(jsdl.imageSuperMissile), &jsdl, TAILLE_FENETRE_X-k*TAILLE_OBJET,MARGE_HAUT/2, TAILLE_OBJET, TAILLE_OBJET );
    }

    SDL_DestroyTexture(textScore);
    SDL_FreeSurface(texte);
}


void menuSDL(jeusdl * jsdl)
{
    SDL_Event e;
    FILE *f;
    int stop=0 , id_app = 0 , i ,k ,size;
    SDL_Rect rectTitre ;
    SDL_Color couleurRouge, couleurBlanche;
    SDL_Surface * surf_titre;
    SDL_Texture * text_titre;
    char texteTitre[100] ;
    bouton tab_b [7];
    Mix_Music *  musique_menu;

    musique_menu = Mix_LoadMUS("./data/musiques/Dijelyo_-_dijelyo_-_my_drum_n_bass_court.mp3");
    assert(musique_menu != NULL);
    Mix_PlayMusic(musique_menu, -1);

    tab_b[0].appuyer=1;
    tab_b[1].appuyer=0;
    tab_b[2].appuyer=0;
    tab_b[3].appuyer=0;
    tab_b[4].appuyer=0;
    tab_b[5].appuyer=0;
    tab_b[6].appuyer=0;


    while (stop == 0) 
    {

         /*verification si le fichier de sauvegarde de la derniere partie est vide ou non*/
        f= fopen("./data/sauvegardeMap.txt","r");
        fseek ( f , 0 , SEEK_END );
        size = ftell(f);
        /*printf("%d\n", size );*/
        fclose(f);
        
        while (SDL_PollEvent(&e))
        {
            Mix_VolumeMusic(jsdl->volumeMus );

            if (e.type == SDL_QUIT)
                stop=1;
            else if ( e.type == SDL_KEYDOWN )
            {
                switch ( e.key.keysym.scancode )
                {
                    case SDL_SCANCODE_DOWN:
                    {

                        if( id_app != 6)
                        {
                            if( id_app == 0 && size == 0)
                            {
                                tab_b[id_app].appuyer=0;
                                id_app = id_app + 2;
                                assert( id_app < 6 || id_app >=0);
                                tab_b[id_app].appuyer=1 ;
                            }
                            else
                            {    
                                tab_b[id_app].appuyer=0;
                                id_app ++;
                                assert( id_app < 6 || id_app >=0);
                                tab_b[id_app].appuyer=1 ;
                            }
                        }
                    }
                    break;

                    case SDL_SCANCODE_UP:
                    {
                        if(id_app != 0)
                        {
                            if( id_app == 2 && size == 0)
                            {
                                tab_b[id_app].appuyer=0;
                                id_app = id_app - 2;
                                assert( id_app < 6 || id_app >=0);
                                tab_b[id_app].appuyer=1 ;
                            }
                            else
                            {
                                tab_b[id_app].appuyer=0;
                                id_app --;
                                assert( id_app < 6 || id_app >=0);
                                tab_b[id_app].appuyer=1;
                            }
                        }
                    }
                    break;

                    case SDL_SCANCODE_RETURN:
                    {
                        switch (id_app)
                        {
                            case 0: 
                            { 
                                if (size == 0)
                                {
                                    initJeu(&(jsdl->J));
                                }
                                else
                                {
                                    decodeFichierSauvegardeMap(&(jsdl->J));
                                }

                                /*afficherinformation(&(jsdl->J));*/
                                Mix_PauseMusic();
                                jouer(*jsdl);
                                Mix_PlayMusic(musique_menu, -1);
                                Mix_VolumeMusic(jsdl->volumeMus );
                            }
                            break;

                            case 1:
                            {
                                if (size != 0)
                                {
                                    supprimeSauvegardeMap();
                                    tab_b[id_app].appuyer=0;
                                    assert(id_app == 1);
                                    id_app = id_app - 1;
                                    tab_b[id_app].appuyer=1 ;
                                }
                            }
                            break;

                            case 2:
                            {
                                commandes(jsdl);
                            }
                            break;

                            case 3:
                    		{
                    		    volumesMusique(jsdl );                                
                                Mix_VolumeMusic(jsdl->volumeMus );
                                Mix_PlayMusic(musique_menu, -1);
                    		}
                            break;

                            case 4:
                            {
                                volumesBruitage(jsdl);
                                Mix_PlayMusic(musique_menu, -1);
                            }
                            break;

                            case 5:
                            {
                                initSauvegarde();
                            }
                            break;

                            case 6: stop = 1;
                            break;

                            default: stop = 0;
                            break;
                        }
                    }
                    break;
                    
                    case SDL_SCANCODE_A:
                    {
                      stop = 1;
                    }
                    break;

                    default : stop = 0;
                    break;
                }
            }
        }

        /*on affiche le fond*/
        assert(jsdl->fond.texture != NULL);
        afficherimage(&(jsdl->fond), jsdl,0,0,TAILLE_FENETRE_X, TAILLE_FENETRE_Y);

        /*definition de la couleur rouge*/
        couleurRouge.r = 255;
        couleurRouge.g = 0;
        couleurRouge.b = 0;

        couleurBlanche.r = 255;
        couleurBlanche.g = 255;
        couleurBlanche.b = 255;


        /*définition du titre*/
        sprintf(texteTitre," Mars Attack ");

        surf_titre = TTF_RenderText_Solid(jsdl->police, texteTitre, couleurRouge);
        assert(surf_titre!=NULL);

        /*creation du rectangle du titre*/
        rectTitre.x = MARGE_MENU*0.75;
        rectTitre.y = 0;
        rectTitre.h = TAILLE_FENETRE_Y / 4.5 ;
        rectTitre.w = TAILLE_FENETRE_X - rectTitre.x ;

        text_titre = SDL_CreateTextureFromSurface(jsdl->renderer, surf_titre);
        assert(text_titre != NULL);

        SDL_RenderCopy(jsdl->renderer, text_titre, NULL, &rectTitre);

        /*définition du bouton Jouer*/
        if (size == 0)
        {
            sprintf(tab_b[0].texte," Nouvelle Partie ");
            sprintf(tab_b[1].texte," ----------- ");
        }
        else
        {
            sprintf(tab_b[0].texte," Continuer Partie ");
            sprintf(tab_b[1].texte," Recommencer ");
        }
        /*définition du bouton Commandes*/
        sprintf(tab_b[2].texte," Commandes ");
        /*définition du bouton volumesMusique*/
        sprintf(tab_b[3].texte," Volume Musiques ");

        /*définition du bouton VolumeBruitage*/
        sprintf(tab_b[4].texte," Volume Bruitages ");
        /*définition du bouton reinitialiser MS*/
        sprintf(tab_b[5].texte," Initialiser Meilleur Score ");

        /*définition du bouton quitter*/
        sprintf(tab_b[6].texte," Quitter ");

        for(k = 0 ;k< 7 ; k++)
        {
            /*creation de la surface du bouton plusieurs , cas bouton appuyé ou non*/
            if (tab_b[k].appuyer == 0)
            {
                tab_b[k].surface = TTF_RenderText_Solid(jsdl->police, tab_b[k].texte, couleurRouge);
                assert(tab_b[k].surface != NULL);
            }
            else
            {
                tab_b[k].surface = TTF_RenderText_Solid(jsdl->police, tab_b[k].texte, couleurBlanche);
                assert(tab_b[k].surface != NULL);
            }


            /*creation du rectangle */
            tab_b[k].rect.x = MARGE_MENU * 2 ;
            tab_b[k].rect.y =   MARGE_MENU *0.20*k + tab_b[0].rect.x *(k+1.75) ;
            tab_b[k].rect.h = TAILLE_FENETRE_Y / 15 ;
            tab_b[k].rect.w = TAILLE_FENETRE_X - tab_b[k].rect.x*2 ;

            SDL_RenderCopy(jsdl->renderer, jsdl->fond.texture, NULL, &tab_b[k].rect);

            /*creation de la texture du bouton*/
            tab_b[k].texture = SDL_CreateTextureFromSurface(jsdl->renderer, tab_b[k].surface);
            assert(tab_b[k].texture != NULL);

            SDL_RenderCopy(jsdl->renderer, tab_b[k].texture, NULL, &tab_b[k].rect);

        }

        SDL_RenderPresent(jsdl->renderer);
        SDL_RenderClear(jsdl->renderer);

        for (i=0;i<=6;i++)
        {
            freebouton(&tab_b[i]);
        }
        SDL_FreeSurface(surf_titre);
        SDL_DestroyTexture(text_titre);
    
    }
    Mix_FreeMusic(musique_menu); 
}

void commandes(jeusdl * jsdl)
{
    SDL_Event e;
    int stop=0 ,i;
    SDL_Color couleurBlanche, couleurGrise;
    bouton retour;
    bouton tab_b[6];
    
    while (stop == 0) 
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                stop=1;
            else if ( e.type == SDL_KEYDOWN )
            {
                switch ( e.key.keysym.scancode )
                {
                    case SDL_SCANCODE_RETURN:
                    {
                        stop = 1;
                    }
                    break;

                    default : stop = 0;
                    break;
                }
            }
        }

        /*on affiche le fond*/
        assert(jsdl->fond.texture != NULL);
        afficherimage(&(jsdl->fond), jsdl,0,0,TAILLE_FENETRE_X, TAILLE_FENETRE_Y);

        /*definition des couleurs*/
       

        couleurGrise.r =100;
        couleurGrise.g =100;
        couleurGrise.b =100;

        couleurBlanche.r = 255;
        couleurBlanche.g = 255;
        couleurBlanche.b = 255;

        /*affichage des commandes*/
        sprintf(tab_b[0].texte," Commandes:  ");
        sprintf(tab_b[1].texte, " Barre espace : tirer missile");
        sprintf(tab_b[2].texte, " Fleche gauche: deplacement gauche");
        sprintf(tab_b[3].texte, " Fleche droite: deplacement droite");
        sprintf(tab_b[4].texte, " Touche E: super missile");
        sprintf(tab_b[5].texte, " Touche P: pause");


        for (i=0 ;i<=5;i++)
        {
            tab_b[i].surface = TTF_RenderText_Solid(jsdl->police,tab_b[i].texte, couleurGrise);
            assert(tab_b[i].surface != NULL);

            /*creation des rectangle */
            tab_b[i].rect.x = MARGE_MENU ;
            tab_b[i].rect.y = MARGE_MENU * 1.5 + tab_b[0].rect.x * 2.5 *i;
            tab_b[i].rect.h = TAILLE_FENETRE_Y / 7  ;
            tab_b[i].rect.w = TAILLE_FENETRE_X - MARGE_MENU * 2  ;

            tab_b[i].texture = SDL_CreateTextureFromSurface(jsdl->renderer, tab_b[i].surface);
            assert(tab_b[i].texture != NULL);
            SDL_RenderCopy(jsdl->renderer, tab_b[i].texture, NULL, &tab_b[i].rect);
        }
        

        /*définition du bouton Retour*/
        sprintf(retour.texte," Retour ");

        retour.surface = TTF_RenderText_Solid(jsdl->police,retour.texte, couleurBlanche);
        assert(retour.surface != NULL);

        /*creation du rectangle du retour */
        retour.rect.x = MARGE_MENU * 2 ;
        retour.rect.y = MARGE_MENU * 16.5 ;
        retour.rect.h = TAILLE_FENETRE_Y / 8 ;
        retour.rect.w = TAILLE_FENETRE_X - MARGE_MENU * 4  ;

        SDL_RenderCopy(jsdl->renderer, jsdl->fond.texture, NULL, &retour.rect);

        retour.texture = SDL_CreateTextureFromSurface(jsdl->renderer, retour.surface);
        assert(retour.texture != NULL);

        SDL_RenderCopy(jsdl->renderer, retour.texture, NULL, &retour.rect);

        SDL_RenderPresent(jsdl->renderer);
        SDL_RenderClear(jsdl->renderer);

        freebouton(&retour);
    }
}

void volumesMusique(jeusdl * jsdl )
{

    SDL_Event e;
    SDL_Color  couleurBlanche;
    int stop=0, i, nb_vol = jsdl->volumeMus / 12.8;
    bouton tab[3];

    /*definition de la couleur blanche*/
    couleurBlanche.r = 255;
    couleurBlanche.g = 255;
    couleurBlanche.b = 255;

	while (stop == 0) 
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                stop=1;
            else if ( e.type == SDL_KEYDOWN )
            {
                switch ( e.key.keysym.scancode )
                {
                    case SDL_SCANCODE_LEFT:
                    {
                        if (nb_vol != 0)
                        {
                            nb_vol--;
                        }
                    }
                    break;

                    case SDL_SCANCODE_RIGHT:
                    {
                        if (nb_vol != 10)
                        {
                            nb_vol++;
                        }
                    }
                    break;

                    case SDL_SCANCODE_RETURN:
                    {
                        stop = 1;
                    }
                    break;
                    
                    case SDL_SCANCODE_A:
                    {
                      stop = 1;
                    }
                    break;

                    default : stop = 0;
                    break;
                }
            }
        }

        Mix_VolumeMusic(nb_vol*12.8);

        /*on affiche le fond*/
        assert(jsdl->fond.texture != NULL);
        afficherimage(&(jsdl->fond), jsdl,0,0,TAILLE_FENETRE_X, TAILLE_FENETRE_Y);

        /*définition du bouton vol*/
        tab[0].rect.x = MARGE_MENU * 2.5  ;
        tab[0].rect.y = MARGE_MENU * 6.5 ;
        tab[0].rect.h = TAILLE_FENETRE_Y / 5.5 ;
        tab[0].rect.w = TAILLE_FENETRE_X - MARGE_MENU * 5  ;

        SDL_SetRenderDrawColor(jsdl->renderer, 0,0,0, 255);
        SDL_RenderFillRect(jsdl->renderer, &tab[0].rect);

        for (i=1 ;i<=nb_vol;i++)
        {
            /*creation du rectangle du vol*/
            tab[1].rect.x = MARGE_MENU * 2 +MARGE_MENU * i ;
            tab[1].rect.y = MARGE_MENU * 7 ;
            tab[1].rect.h = TAILLE_FENETRE_Y / 8 ;
            tab[1].rect.w = TAILLE_FENETRE_X - MARGE_MENU * 15  ;

            SDL_SetRenderDrawColor(jsdl->renderer, 0,255,0, 255);
            SDL_RenderFillRect(jsdl->renderer, &tab[1].rect);
        }

        /*définition du bouton Retour*/
        sprintf(tab[2].texte," Retour ");

        tab[2].surface = TTF_RenderText_Solid(jsdl->police,tab[2].texte, couleurBlanche);
        assert(tab[2].surface != NULL);

        /*creation du rectangle du retour */
        tab[2].rect.x = MARGE_MENU * 2 ;
        tab[2].rect.y = MARGE_MENU * 12 ;
        tab[2].rect.h = TAILLE_FENETRE_Y / 8 ;
        tab[2].rect.w = TAILLE_FENETRE_X - MARGE_MENU * 4  ;

        SDL_RenderCopy(jsdl->renderer, jsdl->fond.texture, NULL, &tab[2].rect);

        tab[2].texture = SDL_CreateTextureFromSurface(jsdl->renderer, tab[2].surface);
        assert(tab[2].texture != NULL);

        SDL_RenderCopy(jsdl->renderer, tab[2].texture, NULL, &tab[2].rect);

        SDL_RenderPresent(jsdl->renderer);
        SDL_RenderClear(jsdl->renderer);

        freebouton(&tab[2]);
    }

    nb_vol = nb_vol *12.8;
    jsdl->volumeMus = nb_vol;
}

void volumesBruitage(jeusdl * jsdl )
{

    SDL_Event e;
    SDL_Color  couleurBlanche;
    int stop=0, i, nb_vol = jsdl->volumeBrui/ 12.8;
    bouton tab[3];

    Mix_PauseMusic();

  
    /*definition de la couleur blanche*/
    couleurBlanche.r = 255;
    couleurBlanche.g = 255;
    couleurBlanche.b = 255;

    while (stop == 0) 
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                stop=1;
            else if ( e.type == SDL_KEYDOWN )
            {
                switch ( e.key.keysym.scancode )
                {
                    case SDL_SCANCODE_LEFT:
                    {
                        if (nb_vol != 0)
                        {
                            nb_vol--;
                        }
                    }
                    break;

                    case SDL_SCANCODE_RIGHT:
                    {
                        if (nb_vol != 10)
                        {
                            nb_vol++;
                        }
                    }
                    break;

                    case SDL_SCANCODE_RETURN:
                    {
                        stop = 1;
                    }
                    break;
                   
                    case SDL_SCANCODE_A:
                    {
                      stop = 1;
                    }
                    break;

                    default : stop = 0;
                    break;
                }
            }
        }

        
        

        /*on affiche le fond*/
        assert(jsdl->fond.texture != NULL);
        afficherimage(&(jsdl->fond), jsdl,0,0,TAILLE_FENETRE_X, TAILLE_FENETRE_Y);

        /*définition du bouton vol*/
        tab[0].rect.x = MARGE_MENU * 2.5  ;
        tab[0].rect.y = MARGE_MENU * 6.5 ;
        tab[0].rect.h = TAILLE_FENETRE_Y / 5.5 ;
        tab[0].rect.w = TAILLE_FENETRE_X - MARGE_MENU * 5  ;

        SDL_SetRenderDrawColor(jsdl->renderer, 0,0,0, 255);
        SDL_RenderFillRect(jsdl->renderer, &tab[0].rect);

        for (i=1 ;i<=nb_vol;i++)
        {
            /*creation du rectangle du vol*/
            tab[1].rect.x = MARGE_MENU * 2 + MARGE_MENU * i ;
            tab[1].rect.y = MARGE_MENU * 7 ;
            tab[1].rect.h = TAILLE_FENETRE_Y / 8 ;
            tab[1].rect.w = TAILLE_FENETRE_X - MARGE_MENU * 15  ;

            SDL_SetRenderDrawColor(jsdl->renderer, 0,255,0, 255);
            SDL_RenderFillRect(jsdl->renderer, &tab[1].rect);
        }

        /*définition du bouton Retour*/
        sprintf(tab[2].texte," Retour ");

        tab[2].surface = TTF_RenderText_Solid(jsdl->police,tab[2].texte, couleurBlanche);
        assert(tab[2].surface != NULL);

        /*creation du rectangle du retour */
        tab[2].rect.x = MARGE_MENU * 2 ;
        tab[2].rect.y = MARGE_MENU * 12 ;
        tab[2].rect.h = TAILLE_FENETRE_Y / 8 ;
        tab[2].rect.w = TAILLE_FENETRE_X - MARGE_MENU * 4  ;

        SDL_RenderCopy(jsdl->renderer, jsdl->fond.texture, NULL, &tab[2].rect);

        tab[2].texture = SDL_CreateTextureFromSurface(jsdl->renderer, tab[2].surface);
        assert(tab[2].texture != NULL);

        SDL_RenderCopy(jsdl->renderer, tab[2].texture, NULL, &tab[2].rect);

        SDL_RenderPresent(jsdl->renderer);
        SDL_RenderClear(jsdl->renderer);

       
        freebouton(&tab[2]);
    }

    nb_vol = nb_vol *12.8;
   

    jsdl->volumeBrui = nb_vol;  
}

void gameover(jeusdl * JS)
{
    char texte[100], texte3[100];
    SDL_Surface * surf_defaite, * surf_score;
    SDL_Texture * text_defaite, * text_score;
    SDL_Rect rectDefaite, rectScore;
    SDL_Color couleurRouge;
    Mix_Music * musique_gameover;

    couleurRouge.r = 255;
    couleurRouge.g = 0;
    couleurRouge.b = 0;

    musique_gameover = Mix_LoadMUS("./data/musiques/SF-Alarmradar.mp3");
    assert(musique_gameover != NULL);

    Mix_PlayMusic(musique_gameover,-1);

    sprintf(texte," Defaite GAME OVER ");
    surf_defaite = TTF_RenderText_Solid(JS->police, texte, couleurRouge);
    assert(surf_defaite!=NULL);

    rectDefaite.x = 0;
    rectDefaite.y = 100;
    rectDefaite.h = 100;
    rectDefaite.w = 540;

    SDL_SetRenderDrawColor(JS->renderer, 0,0,0,0);
    SDL_RenderFillRect(JS->renderer, &rectDefaite);
    text_defaite = SDL_CreateTextureFromSurface(JS->renderer, surf_defaite);
    assert(text_defaite != NULL);
    SDL_RenderCopy(JS->renderer, text_defaite, NULL, &rectDefaite);


    sprintf(texte3," Score : %d ", JS->J.Scores.Score);
    surf_score = TTF_RenderText_Solid(JS->police, texte3, couleurRouge);
    assert(surf_score!=NULL);

    rectScore.x = 0;
    rectScore.y = 300;
    rectScore.h = 100;
    rectScore.w = 540;

    SDL_SetRenderDrawColor(JS->renderer, 0,0,0,0);
    SDL_RenderFillRect(JS->renderer, &rectScore);
    text_score = SDL_CreateTextureFromSurface(JS->renderer, surf_score);
    assert(text_score != NULL);
    SDL_RenderCopy(JS->renderer, text_score, NULL, &rectScore);

    SDL_RenderPresent(JS->renderer);
    SDL_RenderClear(JS->renderer);
    
    SDL_Delay(5000);

    SDL_FreeSurface(surf_defaite);
    SDL_DestroyTexture(text_defaite);
    SDL_FreeSurface(surf_score);
    SDL_DestroyTexture(text_score);

    Mix_PauseMusic();
    Mix_VolumeMusic(50);
    Mix_PlayMusic(musique_gameover,-1);
    Mix_PauseMusic();
}

int menuPause(jeusdl * jsdl)
{
    SDL_Event e;
    int stop=0 , id_app = 0 , i ,pause = 0, k;
    SDL_Rect rectTitre ;
    SDL_Color couleurRouge, couleurBlanche;
    SDL_Surface * surf_titre;
    SDL_Texture * text_titre;
    char texteTitre[100] ;
    bouton tab_b [6];
    Mix_Music *musique_menu;

    musique_menu = Mix_LoadMUS("./data/musiques/Dijelyo_-_dijelyo_-_my_drum_n_bass_court.mp3");
    assert(musique_menu != NULL);
    Mix_PlayMusic(musique_menu, -1);

    tab_b[0].appuyer=1;
    tab_b[1].appuyer=0;
    tab_b[2].appuyer=0;
    tab_b[3].appuyer=0;
    tab_b[4].appuyer=0;
    tab_b[5].appuyer=0;

    while (stop == 0) 
    {
        Mix_VolumeMusic(jsdl->volumeMus );
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                stop=1;
            else if ( e.type == SDL_KEYDOWN )
            {
                switch ( e.key.keysym.scancode )
                {
                    case SDL_SCANCODE_DOWN:
                    {
                        if( id_app != 5)
                        {
                            tab_b[id_app].appuyer=0;
                            id_app ++;
                            assert( id_app < 5 || id_app >=0);
                            tab_b[id_app].appuyer=1 ;
                        }
                    }
                    break;
                    case SDL_SCANCODE_UP:
                    {
                        if(id_app != 0)
                        {
                            tab_b[id_app].appuyer=0;
                            id_app --;
                            assert( id_app < 5 || id_app >=0);
                            tab_b[id_app].appuyer=1;
                        }
                    }
                    break;
                    case SDL_SCANCODE_RETURN:
                    {
                        switch (id_app)
                        {
                            case 0: 
                            { 
                               
                                Mix_PauseMusic();
                                stop = 1;
                                Mix_PlayMusic(musique_menu, -1);
                            }
                            break;
                            case 1:
                            {
                                commandes(jsdl);
                            }
                            break;
                            case 2:
                            {
                                volumesMusique(jsdl);
                                
                                
                                Mix_VolumeMusic(jsdl->volumeMus );
                            }
                            break;
                            case 3:
                            {
                                volumesBruitage(jsdl);
                                Mix_PlayMusic(musique_menu, -1);
                                
                            }
                            break;
                            case 4: 
                            {
                                sauvegardeJeu(&jsdl->J);
                                pause = 1;
                                stop = 1;
                            }
                            break;
                            case 5: 
                            {
                                supprimeSauvegardeMap();
                                pause = 1;
                                stop = 1;
                            }
                            break;
                            default: stop = 0;
                            break;
                        }
                    }
                    break;
                    case SDL_SCANCODE_A:
                    {
                      stop = 1;
                    }
                    break;
                    default : stop = 0;
                    break;
                }
            }
        }

        /*on affiche le fond*/
        assert(jsdl->fond.texture != NULL);
        afficherimage(&(jsdl->fond), jsdl,0,0,TAILLE_FENETRE_X, TAILLE_FENETRE_Y);

        /*definition de la couleur rouge*/
        couleurRouge.r = 255;
        couleurRouge.g = 0;
        couleurRouge.b = 0;

        couleurBlanche.r = 255;
        couleurBlanche.g = 255;
        couleurBlanche.b = 255;

        /*définition du titre*/
        sprintf(texteTitre," PAUSE ");

        surf_titre = TTF_RenderText_Solid(jsdl->police, texteTitre, couleurRouge);
        assert(surf_titre!=NULL);

        /*creation du rectangle du titre*/
        rectTitre.x = MARGE_MENU;
        rectTitre.y = MARGE_MENU *0.25;
        rectTitre.h = TAILLE_FENETRE_Y / 5 ;
        rectTitre.w = TAILLE_FENETRE_X - rectTitre.x*2 ;

        text_titre = SDL_CreateTextureFromSurface(jsdl->renderer, surf_titre);
        assert(text_titre != NULL);

        SDL_RenderCopy(jsdl->renderer, text_titre, NULL, &rectTitre);


        /*définition du bouton Jouer*/
        sprintf(tab_b[0].texte," Continuer ");
        /*définition du bouton Commandes*/
        sprintf(tab_b[1].texte," Commandes ");
         /*définition du bouton volumesMusique*/
        sprintf(tab_b[2].texte," Volume Musiques ");
        /*définition du bouton VolumeBruitage*/
        sprintf(tab_b[3].texte," Volume Bruitages ");
        /*définition du bouton menuprincipal*/
        sprintf(tab_b[4].texte," Menu Principal ");
         /*définition du bouton quitte sans sauvegarder*/
        sprintf(tab_b[5].texte," Quitter sans sauvegarder ");



        for (k =0; k< 6; k++)
        {
            if (tab_b[k].appuyer == 0)
            {
                tab_b[k].surface = TTF_RenderText_Solid(jsdl->police, tab_b[k].texte, couleurRouge);
                assert(tab_b[k].surface != NULL);
            }
            else
            {
                tab_b[k].surface = TTF_RenderText_Solid(jsdl->police, tab_b[k].texte, couleurBlanche);
                assert(tab_b[k].surface != NULL);
            }



            /*creation du rectangle  */
            tab_b[k].rect.x = MARGE_MENU * 2 ;
            tab_b[k].rect.y = MARGE_MENU * k * 0.5 + tab_b[0].rect.x * k + rectTitre.h;
            tab_b[k].rect.h = TAILLE_FENETRE_Y / 10 ;
            tab_b[k].rect.w = TAILLE_FENETRE_X - tab_b[k].rect.x*2 ;

            SDL_RenderCopy(jsdl->renderer, jsdl->fond.texture, NULL, &tab_b[k].rect);

            tab_b[k].texture = SDL_CreateTextureFromSurface(jsdl->renderer, tab_b[k].surface);
            assert(tab_b[k].texture != NULL);

            SDL_RenderCopy(jsdl->renderer, tab_b[k].texture, NULL, &tab_b[k].rect);

        }
        
        SDL_RenderPresent(jsdl->renderer);
        SDL_RenderClear(jsdl->renderer);

        for (i=0;i<=5;i++)
        {
            freebouton(&tab_b[i]);
        }
        SDL_FreeSurface(surf_titre);
        SDL_DestroyTexture(text_titre);
    
    }
    Mix_FreeMusic(musique_menu);
    return pause;
}

void freebouton(bouton * b)
{
    if ( b->surface != NULL)
    {
        SDL_FreeSurface(b->surface);
    }
    if ( b->texture != NULL)
        SDL_DestroyTexture(b->texture);
}

void detruireSDL(jeusdl *jsdl)
{
	SDL_DestroyRenderer(jsdl->renderer); 

    SDL_DestroyWindow(jsdl->fenetre);
    
    SDL_FreeSurface(jsdl->imageAlien1.surface);
    SDL_DestroyTexture(jsdl->imageAlien1.texture);

    SDL_FreeSurface(jsdl->imageAlien2.surface);
    SDL_DestroyTexture(jsdl->imageAlien2.texture);

    SDL_FreeSurface(jsdl->imageAlien3.surface);
    SDL_DestroyTexture(jsdl->imageAlien3.texture);

    SDL_FreeSurface(jsdl->imageVaisseau.surface);
    SDL_DestroyTexture(jsdl->imageVaisseau.texture);

    SDL_FreeSurface(jsdl->imageMissileAlien.surface);
    SDL_DestroyTexture(jsdl->imageMissileAlien.texture);

    SDL_FreeSurface(jsdl->imageMissileVaisseau.surface);
    SDL_DestroyTexture(jsdl->imageMissileVaisseau.texture);

    SDL_FreeSurface(jsdl->imageSuperMissile.surface);
    SDL_DestroyTexture(jsdl->imageSuperMissile.texture);

    SDL_FreeSurface(jsdl->fond.surface);
    SDL_DestroyTexture(jsdl->fond.texture);

    freeJeu(&(jsdl->J));

    TTF_CloseFont(jsdl->police);
}

void jouer(jeusdl JS)
{
    SDL_Event e;
    SDL_Rect  rectNiveau;
    int i=0, stop = 0, defaitej = 0, victoire=0, victoire2=0, bonusvie=0, bonussuper=0 ;
    int keyup =0;
    char  texte2[100];
    SDL_Surface  * surf_niveau;
    SDL_Texture  * text_niveau;
    long int sdltime = 0 , sdlduree = 1000/15, sdlecoule = 0;
    SDL_Color couleurRouge;
    Mix_Music * musique_jeu ;
    Mix_Chunk  *son_tir , *son_tir_spe;

    Mix_AllocateChannels(2);
    musique_jeu = Mix_LoadMUS("./data/musiques/AlexZavesa_-_Progressive_Trance_court.mp3");
    assert(musique_jeu != NULL);
    son_tir_spe = Mix_LoadWAV("./data/musiques/SF-bullet-time_04sf.wav");

    if(!son_tir_spe) 
    {
        printf("Mix_LoadWAV: %s\n", Mix_GetError()); 
    }
    son_tir  = Mix_LoadWAV("data/musiques/sf_canon_01_court.wav");   
    if(!son_tir) 
    {
        printf("Mix_LoadWAV: %s\n", Mix_GetError()); 
    }

    Mix_VolumeChunk(son_tir_spe, JS.volumeBrui);
    Mix_VolumeChunk(son_tir, JS.volumeBrui);
    Mix_PlayMusic(musique_jeu, -1);

    couleurRouge.r = 255;
    couleurRouge.g = 0;
    couleurRouge.b = 0;

    while (stop == 0) 
    {
        afficherjeu(JS);

        if (Mix_PausedMusic())
        {
            Mix_PlayMusic(musique_jeu,-1);
        }
        sdltime = SDL_GetTicks();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                stop=1;
            else if ( e.type == SDL_KEYDOWN )
            {
                switch ( e.key.keysym.scancode )
                {

                    case SDL_SCANCODE_LEFT:
                    {
                        deplacementVaisseau(&(JS.J),1);
                    }
                    break;
                    
                    case SDL_SCANCODE_RIGHT:
                    {
                        deplacementVaisseau(&(JS.J),0);
                    }
                    break;
                    
                    case SDL_SCANCODE_SPACE:
                    {
                        if (keyup)
                        {
                            Mix_PlayChannel(1, son_tir, 0);
                            tirerMissileVaisseau(&(JS.J));
                            keyup = 0;
                        }
                    }
                    break;
                    
                    case SDL_SCANCODE_E:
                    {
                        if (JS.J.supermissile >= 1 && keyup )
                        {
                            Mix_PlayChannel(1, son_tir_spe, 0);
                            tirerSuperMissile(&(JS.J));
                            JS.J.supermissile--;
                            keyup = 0 ;
                        }
                    }
                    break;
                    
                    case SDL_SCANCODE_W:
                    {
                        augmenterNiveau(&(JS.J));
                        regenererMap(&(JS.J));
                        bonusvie = 0;
                        bonussuper = 0;
                    }
                    break;
                    
                    case SDL_SCANCODE_I:
                    {
                        afficherinformation(&(JS.J));
                    }
                    break;
                    
                    case SDL_SCANCODE_R:
                    {
                        printf("Ajout de supermissile \n");
                        setSuperMissile(&(JS.J), getSuperMissile(JS.J)+10);
                    }
                    break;
                    
                    case SDL_SCANCODE_P:
                    {
                        stop = menuPause(&JS);
                        Mix_PlayMusic(musique_jeu,-1);
                        Mix_VolumeChunk(son_tir_spe, JS.volumeBrui);
                        Mix_VolumeChunk(son_tir, JS.volumeBrui);
                    }
                    break;
                    
                    case SDL_SCANCODE_A:
                    {
                        stop = 1;
                        sauvegardeJeu(&(JS.J));
                    }
                    break;
                    
                    default : stop = 0;
                    break;
                }
            }
            else if ( e.type == SDL_KEYUP )
            {
                keyup = 1;
            }
        }

        if (defaitej == 0 && victoire == 0 && victoire2 == 0)
        {
            afficherjeu(JS);
        }
        else if (victoire == 1 || victoire2 ==1)
        {
            augmenterNiveau(&(JS.J));

            sprintf(texte2," Niveau %d ",JS.J.niveau);
            surf_niveau = TTF_RenderText_Solid(JS.police, texte2, couleurRouge);
            assert(surf_niveau!=NULL);

            rectNiveau.x = 0;
            rectNiveau.y = 100;
            rectNiveau.h = 100;
            rectNiveau.w = 540;

            SDL_SetRenderDrawColor(JS.renderer, 0,0,0,0);
            SDL_RenderFillRect(JS.renderer, &rectNiveau);

            text_niveau = SDL_CreateTextureFromSurface(JS.renderer, surf_niveau);
            SDL_RenderCopy(JS.renderer, text_niveau, NULL, &rectNiveau);

            SDL_RenderPresent(JS.renderer);
            SDL_RenderClear(JS.renderer);

            SDL_FreeSurface(surf_niveau);
            SDL_DestroyTexture(text_niveau);

            SDL_Delay(1000);

            regenererMap(&(JS.J));
            bonusvie = 0;
            bonussuper = 0;
        }
        else if (defaitej == 1)
        {
            Mix_PauseMusic();
            gameover(&JS);
            supprimeSauvegardeMap();
            stop=1;
        }
        if (i%10==0)
        {
            tirerMissileAlien(&(JS.J));
        }
        defaitej = (deplacementMissileAlien(&(JS.J)) || defaite(JS.J));
        victoire = deplacementMissileVaisseau(&(JS.J));
        victoire2 = victoire;

        if (i%4==0)
        {
            victoire2 = deplacementAliens(&(JS.J));
        }
        
        if (JS.J.niveau%2 == 0)
        {
            if (bonusvie==0)
            {
                ajoutvie(&(JS.J));
                bonusvie = 1;
            }
            if (i%150 ==0 && bonussuper==0)
            {
                ajoutSuperMissile(&(JS.J));
                bonussuper =1;
            }
        }
        i++;
        sdlecoule = (SDL_GetTicks() - sdltime);

        if(sdlecoule < sdlduree)
        {
            SDL_Delay(sdlduree - sdlecoule);
        }
        SDL_RenderPresent(JS.renderer);
        SDL_RenderClear(JS.renderer); 
    }
    setMeilleurScore(&(JS.J.Scores));
    Mix_FreeChunk(son_tir);
    Mix_FreeChunk(son_tir_spe);
    Mix_FreeMusic(musique_jeu);
}
