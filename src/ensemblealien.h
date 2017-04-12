#ifndef ENSEMBLEALIEN_H
#define ENSEMBLEALIEN_H

#include "position.h"
#include "alien.h"
/**
 * \file          ensemblealien.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       09 mars 2016
 *
 */



/**
 * \struct sensemblealien ensemblealien.h
 * \brief Represente un ensemble d'alien
 */
struct sensemblealien
{
    int taille; /*!< taille du tableau utilisé              */
    alien *tab; /*!< pointeur sur la première case du tableau d'alien              */
    int capacite; /*!< capacité du tableau               */
    int direction; /*!< droite ou gauche				*/
    int descendu; /*!< 0 ou 1					*/
};

/**
 * \typedef ensemblealien: la structure sensemblealien
 */
typedef struct sensemblealien ensemblealien;


/** \brief initEnsembleAlien initialise la taille, la capacité puis alloue le tableau de alien dans le tas
 *  \param EA pointeur sur la premiere case de ensemblealien
 */
void initEnsembleAlien(ensemblealien *EA);


/** \brief freeEnsembleAlien libere la mémoire du tableau d'alien et met à zéro la capacité et la taille
 *  \param EA pointeur sur la premiere case de ensemblealien
 */
void freeEnsembleAlien(ensemblealien *EA);


/** \brief ajoutAlien ajoute un alien à l'ensemble d'alien 
 *  \param EA pointeur sur la premiere case de ensemblealien
 *  \param a alien à ajouter
 */
void ajoutAlien(ensemblealien *EA, alien a);


/** \brief getNombreAlien compte le nombre d'alien dans ensemblealien
 *  \param EA un ensemblealien
 *  \return nombre d'alien, un entier
 */
int getNombreAlien(ensemblealien EA);


/** \brief suppAlienId supprime l'alien, dont l'identifiant est ID, dans l'ensemble d'alien 
 *  \param EA pointeur sur la premiere case de ensemblealien
 *  \param ID un entier positif
 */
void suppAlienId(ensemblealien *EA, int ID);


/** \brief suppEnsembleAlien, supprime l'ensemble des aliens
 *  \param EA pointeur sur la premiere case de ensemblealien
 */
void suppEnsembleAlien(ensemblealien *EA);


/** \brief setPosXIemeAlien modifie la l'abscisse du Ieme alien dans ensemblealien
 *  \param EA pointeur sur la premiere case de ensemblealien
 *  \param i entier positif 
 *  \param x entier positif pour modifier
 */
void setPosXIemeAlien(ensemblealien *EA, int i, int x);


/** \brief setPosXIemeAlien modifie la l'ordonnée du Ieme alien dans ensemblealien
 *  \param EA pointeur sur la premiere case de ensemblealien
 *  \param i entier positif
 *  \param y entier positif pour modifier
 */
void setPosYIemeAlien(ensemblealien *EA, int i, int y);


/** \brief getPosIemeAlien récupere la position du Ieme alien dans ensemblealien
 *  \param EA un ensemblealien
 *  \param i entier positif
 *  \return la position de l'alien
 */
position getPosIemeAlien(ensemblealien EA, int i);


/** \brief getPosXIemeAlien renvoie la position X du ieme alien de l'ensemble d'alien 
 *  \param EA un ensemblealien
 *  \param i un entier positif
 *  \return un entier, la position x de l'alien i
 */
int getPosXIemeAlien(ensemblealien EA, int i);


/** \brief getPosYIemeAlien renvoie la position Y du ieme alien de l'ensemble d'alien
 *  \param EA un ensemblealien
 *  \param i un entier positif
 *  \return un entier, la position Y de l'alien i
 */
int getPosYIemeAlien(ensemblealien EA, int i);


/** \brief getVieAlienPosition renvoie la vie de alien dont la position est x et y de l'ensemble d'alien
 *  \param EA un ensemblealien
 *  \param x un entier positif
 *  \param y un entier positif
 *  \return un entier, la vie de l'alien
 */
int getVieAlienPosition(ensemblealien EA, int x, int y);


/** \brief getIdAlienPosition renvoie d'identifiant d'un alien, dont la position est P, dans l'ensemble alien 
 *  \param EA un ensemblealien
 *  \param P  position
 *  \return l'identifiant de l'alien un entier
 */
int getIdAlienPosition(ensemblealien EA, position P);


/** \brief getVieIemeAlien renvoie la vie du ieme alien de l'ensemble d'alien
 *  \param EA pointeur sur la premiere case de ensemblealien
 *  \param i un entier positif
 *  \return vie un entier
 */
int getVieIemeAlien(ensemblealien EA, int i);


/** \brief suppVieAlienID supprime une vie à l'alien, dont l'identifiant est id, et retourne 1 si l'alien est supprimé sinon 0
 *  \param EA pointeur sur la premiere case de ensemblealien
 *  \param id entier positif
 *  \return un entier : 1 si l'alien est supprimé et 0 sinon
 */
int suppVieAlienID (ensemblealien *EA, int id);

/** \brief suppVieAlienPosition supprime une vie à l'alien, dont la position est P, et retourne 1 si l'alien est supprimé sinon 0
 *  \param EA pointeur sur la premiere case de ensemblealien
 *  \param P position
 *  \return un entier : 1 si l'alien est supprimé et 0 sinon 
 */
int suppVieAlienPosition(ensemblealien *EA, position P);


/** \brief getDirectionAlien la direction de l'ensemble d'alien
 *  \param EA un ensemblealien
 *  \return un entier, la direction de l'ensemble d'alien
 */
int getDirectionAlien(ensemblealien EA);


/** \brief getDescenduAlien renvoie la valeur de descendu del'ensemble d'alien
 *  \param EA un ensemblealien
 *  \return un entier, descendu
 */
int getDescenduAlien(ensemblealien EA);


/** \brief setDirectionAlien modifie la direction de l'ensemble d'alien
 *  \param EA un pointeur sur la premiere case de l'ensemblealien
 *  \param i un entier positif
 */
void setDirectionAlien(ensemblealien *EA, int i);


/** \brief setDescenduAlien modifie le descendu de l'ensemble d'alien
 *  \param EA un pointeur sur la premiere case de l'ensemblealien
 *  \param i un entier positif
 */
void setDescenduAlien(ensemblealien *EA, int i);


/** \brief testEnsembleAlien teste toutes les fonctions et procédures sur les ensembles d'aliens
 */
void testEnsembleAlien();

#endif /* ENSEMBLEALIEN_H*/