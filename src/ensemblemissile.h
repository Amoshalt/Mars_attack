#ifndef ENSEMBLEMISSILE_H
#define ENSEMBLEMISSILE_H

#include "missile.h"
#include "position.h"

/**
 * \file          ensemblemissile.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       3 avril 2016
 *
 */



/**
 * \struct sensemblemissile ensemblemissile.h
 * \brief Represente un ensemble de missile
 */
struct sensemblemissile
{
    int taille; /*!< taille du tableau utilisé               */
    missile *tab; /*!< pointeur sur la première case du tableau de missile               */
    int capacite; /*!< capacité du tableau               */
};

/**
 * \typedef ensemblemissile: la structure sensemblemissile
 */
typedef struct sensemblemissile ensemblemissile;

/** \brief initEnsembleMissile initialise la taille, la capacité puis alloue le tableau de protection dans le tas
 *  \param EM pointeur sur la premiere case de ensemblemissile
 */
void initEnsembleMissile(ensemblemissile *EM);


/** \brief freeEnsembleMissile initialise la taille, la capacité puis libère la mémoire alloué pour l'ensemble de missile
 *  \param EM pointeur sur la premier case de ensemblemissile
 */
void freeEnsembleMissile(ensemblemissile *EM);


/** \brief ajoutMissile ajout un missile dans l'ensemble de missile 
 *  \param EM pointeur sur la premier case de ensemblemissile
 *  \param m missile à ajouter
 */
void ajoutMissile(ensemblemissile *EM, missile m);


/** \brief getNombreMissile compte le nombre de missile dans ensemblemissile
 *  \param EM un ensemblemissile
 *  \return nombre de missile, un entier
 */
int getNombreMissile(ensemblemissile EM);


/** \brief getPosXIemeMissile renvoie la position X du ieme missile de l'ensemblemissile
 *  \param EM un ensemblemissile
 *	\param i un entier positif
 *  \return la postion X de missile, un entier
 */
int getPosXIemeMissile(ensemblemissile EM, int i);


/** \brief getPosYIemeMissile renvoie la position Y du ieme missile de l'ensemblemissile
 *  \param EM un ensemblemissile
 *  \param i un entier positif
 *  \return la postion Y de missile, un entier
 */
int getPosYIemeMissile(ensemblemissile EM, int i);


/** \brief setPosXIemeMissile modifie la position X du ieme missile de l'ensemblemissile
 *  \param EM un ensemblemissile
 *  \param i un entier positif
 *  \param x un entier positif
 */
void setPosXIemeMissile(ensemblemissile *EM, int i, int x);


/** \brief setPosYIemeMissile modifie la position Y du ieme missile de l'ensemblemissile
 *  \param EM un ensemblemissile
 *  \param i un entier positif
 *  \param y un entier positif
 */
void setPosYIemeMissile(ensemblemissile *EM, int i, int y);


/** \brief getPosIemeMissile renvoie la position du ieme missile de l'ensemblemissile
 *  \param EM un ensemblemissile
 *  \param i un entier positif
 *  \return la postion de missile
 */
position getPosIemeMissile(ensemblemissile EM, int i);


/** \brief getNiveauIemeMissile renvoie le niveau du ieme missile de l'ensemblemissile
 *  \param EM un ensemblemissile
 *  \param i un entier positif
 *  \return le niveau de missile, un entier
 */
int getNiveauIemeMissile(ensemblemissile EM, int i);


/** \brief supprimerIemeMissile supprime le ième missile de l'ensemble de missile
 *  \param EM pointeur sur la premier case de ensemblemissile
 *  \param i un entier  positif, la place dans le tableau des missiles
 */
void supprimerIemeMissile(ensemblemissile *EM, int i);


/** \brief supprimerMissilePosition supprime le missile de l'ensemble de missile dont la position est P
 *  \param EM pointeur sur la premier case de ensemblemissile
 *  \param P une position
 */
void supprimerMissilePosition(ensemblemissile *EM, position P);


/** \brief getNiveauMissilePosition renvoie le niveau du missile, dont la position est P, de l'ensemblemissile
 *  \param EM un ensemblemissile
 *  \param P une position
 *  \return le niveau de missile, un entier
 */
int getNiveauMissilePosition(ensemblemissile EM, position P);


/** \brief suppEnsembleMissile supprime l'ensemble des missiles
 *  \param EM pointeur sur la premier case de ensemblemissile
 */
void suppEnsembleMissile(ensemblemissile *EM);


/** \brief getMissilePosition renvoie un missile, dont la position est P
 *  \param EM un ensemblemissile
 *  \param P position
 *  \return un missile
 */
missile getMissilePosition(ensemblemissile EM, position P);


/** \brief MissilePosition renvoie 1 si un missile est présent sur la position P, sinon il renvoie 0
 *  \param EM un ensemblemissile
 *  \param P position
 *  \return un entier : 1 si presence de missile, 0 sinon
 */
int MissilePosition(ensemblemissile EM, position P);


/** \brief getMissilePosition renvoie le ieme missile de l'ensemblemissile
 *  \param EM un ensemblemissile
 *  \param i un entier positif
 *  \return un missile
 */
missile getIemeMissile(ensemblemissile EM, int i);


/** \brief testEnsembleMissile test toutes les fonctions et procedures sur ensemblemissile
*/
void testEnsembleMissile();

#endif /* ENSEMBLEMISSILE_H*/