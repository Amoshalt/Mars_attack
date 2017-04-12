#ifndef POSITION_H
#define POSITION_H


/**
 * \file          position.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       09 mars 2016
 *
 */



/**
 * \struct sposition position.h
 * \brief Represente une position
 */
struct sposition
{
    int x; /*!< largeur               */
    int y; /*!< hauteur               */
};

/**
 * \typedef position: la structure sposition
 */
typedef struct sposition position;


/** \brief initPosition initialise x et y de la structure position
 *  \param p pointeur sur position
 */
void initPosition(position *p);


/** \brief getPosX renvoie la coordonnée x de la position
 *  \param p une position
 *  \return un entier, la largeur 
 */
int getPosX(position p);


/** \brief getPosY renvoie la coordonnée y de la position
 *  \param p une position
 *  \return un entier ,la hauteur
 */
int getPosY(position p);


/** \brief setPosX modifie la coordonnée x de la position
 *  \param p pointeur sur position
 *  \param x un entier pour modifier
 */
void setPosX(position *p, int x);


/** \brief setPosY modifie la coordonnée y de la position
 *  \param p pointeur sur position
 *  \param y un entier pour modifier
 */
void setPosY(position *p, int y);

/** \brief comparePostion compare deux positions, il renvoie 1 si elles sont égales, sinon 0
 *  \param p1 une position
 *  \param p2 une position
    \return un entier : 1 si p1=p2, 0 sinon 
 */
int comparePostion (position p1, position p2);

/** \brief testPosition teste les différentes fonctions et procedures sur les positions
 */
void testPosition();

#endif /* POSITION_H*/

