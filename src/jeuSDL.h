#ifndef _SDLJEU_H
#define _SDLJEU_H

#include "jeu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * \file          jeuSDL.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       09 avril 2016
 *
 */


/**
 * \struct simage jeuSDL.h
 * \brief Represente une image en SDL
 */
struct simage
{
    SDL_Surface* surface;/*!<surface de l'image		*/
    SDL_Texture* texture;/*!<texture de l'image		*/
};

/**
 * \typedef image: la structure simage
 */
typedef struct simage image;

/**
 * \struct sjeusdl jeuSDL.h
 * \brief Represente un jeu en SDL
 */
struct sjeusdl
{

    SDL_Window *fenetre;/*!< fenetre du jeusdl		*/
    SDL_Renderer *renderer;/*!< Renderer		*/
    jeu J;/*!< Jeu		*/
    image imageAlien1;/*!< Image		*/
    image imageAlien2;/*!< Image        */
    image imageAlien3;/*!< Image        */
    image imageMissileAlien; /*!< Image		*/ 
    image imageMissileVaisseau; /*!< Image     */ 
    image imageSuperMissile; /*!< Image     */ 
    image imageVaisseau; /*!< Image		*/
    image imageVie; /*!<Image        */
    image imageBonus; /*!<Image        */
    image imageProtection; /*!<Image        */
    image fond;/*!< Image		*/
    TTF_Font * police; /*!< Police		*/
    int volumeMus; /*!< Entier      */
    int volumeBrui; /*!< Entier     */

};
/**
 * \typedef jeusdl: la structure sjeusdl
 */
typedef struct sjeusdl jeusdl;

/**
 * \struct sbouton jeuSDL.h
 * \brief Represente un bouton en SDL
 */
struct sbouton
{
    int appuyer;/*! int =1 si bouton appuyer    */
    SDL_Surface* surface;/*!<surface du bouton     */
    SDL_Texture* texture;/*!<texture du bouton    */
    char texte [100];
    SDL_Rect rect;
};

/**
 * \typedef bouton: la structure sbouton
 */
typedef struct sbouton bouton;


/** \brief initJeu initialise la SDL, charge les images, et initialise le jeu
 *  \param jsdl pointeur sur jeusdl
 */
void initSDL(jeusdl *jsdl);


/** \brief chargementimage charge une image .
 *  \param nomfichier pointeur sur chaîne de carctère
 *  \param jsdl  pointeur sur jeusdl
 *	\param IM un pointeur sur image 

 */
void chargementimage(const char* nomfichier, jeusdl *jsdl, image * IM);


/** \brief afficherimage une image déja chargé
 *  \param IM pointeur sur image à afficher
 *  \param jsdl pointeur sur jeusdl
 *  \param positionX entier indiquant la position X du coin gauche en haut de l'image
 *  \param positionY entier indiquant la position Y du coin gauche en haut de l'image
 *  \param largeurX entier indiquant la largeur X de l'image
 *  \param largeurY entier indiquant la hauteur Y de l'image
 */
void afficherimage(image *IM, jeusdl *jsdl, int positionX, int positionY, int largeurX, int largeurY );


/** \brief afficherjeu affiche le jeu
 *  \param jsdl jeusdl
 */
void afficherjeu(jeusdl jsdl);


/** \brief menuSDL affiche un menu
 *  \param jsdl pointeur sur un jeusdl
 */
void menuSDL(jeusdl * jsdl);


/** \brief commandes affiche un menu
 *  \param jsdl pointeur sur un jeusdl
 */
void commandes(jeusdl * jsdl);


/** \brief volumesMusique affiche un menu
 *  \param jsdl pointeur sur un jeusdl
 */
void volumesMusique(jeusdl * jsdl);


/** \brief volumesBruitage affiche un menu
 *  \param jsdl pointeur sur un jeusdl
 */
void volumesBruitage(jeusdl * jsdl);


/** \brief gameover affiche le gameover
 *  \param jsdl pointeur sur un jeusdl
 */
void gameover(jeusdl * jsdl);


/** \brief menuPause affiche un menu et renvoie une valeur
 *  \param jsdl pointeur sur un jeusdl
 *  \return un entier 0 ou 1
 */
int menuPause(jeusdl * jsdl);


/** \brief freebouton libere un bouton
 *  \param b pointeur sur un bouton
 */
void freebouton( bouton * b);


/** \brief detruireSDL libère la mémoire de la SDL, des images, et du jeu
 *  \param jsdl pointeur sur jeusdl
 */
void detruireSDL(jeusdl *jsdl);


/** \brief jouer affiche une partie en SDL
 *  \param jsdl jeusdl
 */
void jouer(jeusdl JS);

#endif