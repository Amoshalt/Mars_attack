#ifndef ALIEN_H
#define ALIEN_H

#include "position.h"

/**
 * \file          alien.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       3 avril 2016
 *
 */

/**
 * \struct salien alien.h 
 * \brief Represente un alien
 */
struct salien
{
    int idAlien;   /*!< identifiant de l'alien               */
    int vieAlien;  /*!< nombre de vie de l'alien             */
    position posAlien;   /*!< position de l'alien             */
};

/**
 * \typedef alien: la structure alien
 */
typedef struct salien alien;

/** \brief initAlien initialise l'identifiant de l'alien, son nombre de vie et sa position dans la structure alien
 *  \param a  pointeur sur un alien
 */
 void initAlien(alien * a);

/** \brief getVieAlien renvoie le nombre de vie de l'alien
 *  \param a un alien
 *  \return le nombre de vie l'alien un entier
 */
 int getVieAlien(alien a);

/** \brief setVieAlien modifie le nombre de vie de l'alien
 *  \param a pointeur sur alien
 *  \param i entier positif pour modifier
 */
 void setVieAlien(alien *a, int i);

/** \brief getPosAlien renvoie la  position de l'alien
 *  \param a un alien
 *  \return la position de l'alien
 */
 position getPosAlien(alien a);

/** \brief getPosXAlien renvoie la position X de l'alien
 *  \param a un alien
 *  \return un entier, la position X de l'alien
 */
 int getPosXAlien(alien a);

/** \brief getPosYAlien renvoie la position Y de l'alien
 *  \param a un alien
 *  \return un entier, la position Y de l'alien
 */
 int getPosYAlien(alien a);

/** \brief setPosAlien modifie la position X de l'alien
 *  \param a pointeur sur alien
 *  \param x un entier positif
 */
 void setPosXAlien(alien * a, int x);

/** \brief setPosAlien modifie la position Y de l'alien
 *  \param a pointeur sur alien
 *  \param y un entier positif
 */
 void setPosYAlien(alien * a, int y);

/** \brief getIdAlien renvoie l'indentifiant de l'alien
 *  \param a un alien
 *  \return un entier, l'identifiant de l'alien
 */
 int getIdAlien(alien a);

/** \brief setIdAlien  modifie l'identifiant de l'alien
 *  \param a un pointeur sur alien
 *  \param i un entier positif pour modifier
 */
 void setIdAlien(alien * a, int i);

/** \brief creationAlien renvoie un alien avec ses caractéristiques
 *  \param id un entier positif 
 *  \param vie un entier positif
 *  \param x un entier positif
 *  \param y un entier positif
 *  \return un alien
 */
alien creationAlien(int id, int vie, int x, int y);

/** \brief testAlien teste toutes les fonctions et procédures sur alien
 */
 void testAlien();

 #endif /* ALIEN_H*/

 