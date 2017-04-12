#ifndef PROTECTION_H
#define PROTECTION_H

#include "position.h"

/**
 * \file          protection.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       09 mars 2016
 *
 */



/**
 * \stuct sprotection protection.h
 * \brief Represente une protection
 */
struct sprotection
{
    int idProtection; /*!< identifiant de la protection               */
    position posProtection; /*!< position de la protection               */
    int vieProtection; /*!< nombre de vie de la protection              */
};

/**
 * \typedef protection: la structure sprotection
 */
typedef struct sprotection protection;


/** \brief initProtection initialise identifiant, la vie et position de la protection
 *  \param p pointeur sur protection
 */
void initProtection(protection *p);


/** \brief setIdProtection modifie l'identifiant de la protection
 *  \param p pointeur sur protection
 *  \param i entier positif
 */
void setIdProtection(protection *p, int i);


/** \brief getIdProtection renvoie l'identifiant de la protection
 *  \param p protection
 *  \return un entier, l'identifiant de la protection
 */
int getIdProtection(protection p);


/** \brief getPosProtection renvoie la position de la protection
 *  \param p protection
 *  \return la position de la protection
 */
position getPosProtection(protection p);


/** \brief setPosProtection modifie les coordonnées de la protection
 *  \param p pointeur sur protection
 *  \param x entier positif pour modifier l'abscisse
 *  \param y entier positif pour modifier l'ordonnée
 */
void setPosProtection(protection *p, int X, int Y);


/** \brief getVieProtection renvoie le nombre de vie de la protection
 *  \param p protection
 *  \return le nombre de vie de la protection un entier
 */
int getVieProtection(protection p);


/** \brief setVieProtection modifie le nombre de vie de la protection
 *  \param p pointeur sur protection
 *  \param V entier positif pour modifier
 */
void setVieProtection(protection *p, int V);


/** \brief creationProtection renvoie un alien avec ses carateristiques
 *  \param id un entier positif 
 *  \param vie un entier positif
 *  \param x un entier positif
 *  \param y un entier positif
 *  \return une nouvelle protection
 */
protection creationProtection(int id, int vie, int x, int y);


/** \brief testProtection teste les différentes fonctions et procedures sur les protections
 */
void testProtection();


#endif /* PROTECTION_H*/

