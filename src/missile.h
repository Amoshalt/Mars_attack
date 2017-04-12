#ifndef MISSILE_H
#define MISSILE_H

#include "position.h"

/**
 * \file          missile.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       09 mars 2016
 *
 */



/**
 *\struct smissile missile.h
 * \brief Represente un missile
 */
struct smissile
{
    int idMissile; /*!< identifiant               */
    position posMissile; /*!< position du missile               */
    int nivMissile; /*!< niveau du missile               */
};

/**
 * \typedef missile: la structure smissile
 */
typedef struct smissile missile;


/** \brief initMissile initialise l'identifiant du missile puis la position (apres verification) de la structure missile
 *  \param m pointeur sur missile
 */
void initMissile (missile * m);


/** \brief setPosXMissile modifie la position x du missile 
 *  \param m pointeur sur missile
 *  \param x un entier  positif pour modifier
 */
void setPosXMissile(missile * m, int x);


/** \brief setPosYMissile modifie la position x du missile 
 *  \param m pointeur sur missile
 *  \param y un entier positif pour modifier
 */
void setPosYMissile(missile * m, int y);


/** \brief getPosMissile récupère la position d'un missile
 *  \param m un missile
 *  \return la position du missile 
 */
position getPosMissile(missile m);


/** \brief getPosXMissile récupère la postion x d'un missile
 *  \param m pointeur sur missile
 *  \return la position X du missile un entier
 */
int getPosXMissile(missile m);


/** \brief getPosYMissile récupère la postion Y d'un missile
 *  \param m pointeur sur missile
 *  \return la position Y du missile un entier
 */
int getPosYMissile(missile m);


/** \brief getIdMissile récupère l'identifiant d'un missile
 *  \param m pointeur sur missile
 *  \return l'identifiant du missile un entier
 */
int getIdMissile(missile m);


/** \brief setIdMissile modifie l'identifiant d'un missile
 *  \param m pointeur sur missile
 *  \param i un entier positif pour modifier
 */
void setIdMissile(missile *m , int i);


/** \brief getNivMissile récupère le niveau d'un missile
 *  \param m un missile
 *  \return le niveau du missile 
 */
int getNivMissile(missile m);


/** \brief setNivMissile modifie le niveau du missile 
 *  \param m pointeur sur missile
 *  \param i un entier positif pour modifier
 */
void setNivMissile(missile *m, int i);


/** \brief suppMissile supprime le missile,il met son identifiant à 0, le niveau à 1, et sa position est alors (-1,-1)
 *  \param m pointeur sur missile
 */
void suppMissile(missile *m);


/** \brief testMissile teste l'ensemble des fonctions et procedures sur les missiles
 */
void testMissile();


#endif /* MISSILE_H*/