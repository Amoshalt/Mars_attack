#ifndef VAISSEAU_H
#define VAISSEAU_H

#include "position.h"

/**
 * \file          vaisseau.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       14 mars 2016
 *
 */

/**
 * \struct svaisseau vaisseau.h
 * \brief Represente un vaisseau
 */
struct svaisseau
{
    int idVaisseau;/*!< identifiant du vaisseau             */
    int vieVaisseau;/*!< nombre de vie du vaisseau              */
    position posVaisseau;/*!< position du vaisseau             */
};

/**
 * \typedef vaisseau: la structure vaisseau
 */
typedef struct svaisseau vaisseau;


/** \brief initVaisseau initialise l'identifiant du vaisseau, son nombre de vie, et sa position
 *  \param v pointeur sur vaisseau
 */
 void initVaisseau(vaisseau * v);


/** \brief getVieVaisseau renvoie le nombre de vie du vaisseau
 *  \param v un vaisseau
 *  \return un entier positif, nombre de vie du vaisseau 
 */
 int getVieVaisseau(vaisseau v);


 /** \brief setVieVaisseau modifie le nombre de vie du vaisseau
 *  \param v pointeur sur vaisseau
 *  \param i entier positif pour modifier
 */
 void setVieVaisseau(vaisseau * v, int i);


 /** \brief getPosVaisseau renvoie la  position du vaisseau
 *  \param v un vaisseau
 *  \return la position du vaisseau
 */
 position getPosVaisseau(vaisseau v);


 /** \brief getPosXVaisseau renvoie la position X du vaisseau
 *  \param v un vaisseau
 *  \return un entier positif, la position X du vaisseau
 */
 int getPosXVaisseau(vaisseau v);


 /** \brief getPosYVaisseau renvoie la position Y du vaisseau
 *  \param v un vaisseau
 *  \return un entier positif, la position Y du vaisseau
 */
int getPosYVaisseau(vaisseau v);


 /** \brief setPosXVaisseau modifie la position X du vaisseau
 *  \param v pointeur sur vaisseau
 *  \param x un entier positif
 */
 void setPosXVaisseau(vaisseau * v, int x);


 /** \brief setPosYVaisseau modifie la position Y du vaisseau
 *  \param v pointeur sur vaisseau
 *  \param y un entier positif
 */
void setPosYVaisseau(vaisseau * v, int y);


 /** \brief getIdVaisseau renvoie l'indentifiant du vaisseau
 *  \param v un vaisseau
 *  \return un entier positif, l'identifiant du vaisseau
 */
 int getIdVaisseau(vaisseau v);


  /** \brief setIdVaisseau  modifie l'identifiant du vaisseau
 *  \param v pointeur sur vaisseau
 *  \param i entier positif pour modifier
 */
 void setIdVaisseau(vaisseau * v, int i);


 /** \brief creationVaisseau creer un nouveau vaisseau et renvoie ses caractéristiques
 *  \param id entier positif
 *  \param vie entier positif
 *  \param x entier positif
 *  \param y entier positif
 *  \return un vaisseau et ses caractéristiques
 */
vaisseau creationVaisseau(int id, int vie, int x, int y);


/** \brief suppVieVaisseau supprime une vie au vaisseau, et retourne 1 si le vaisseau est supprimé 
 *  \param v pointeur sur vaisseau
 *  \return un entier : 1 si le vaisseau est supprimé et 0 sinon
 */
int suppVieVaisseau(vaisseau *v);


/** \brief testVaisseau teste toutes les fonctions et procédures sur Vaisseau
 */
 void testVaisseau();

 #endif /*VAISSEAU_H*/
