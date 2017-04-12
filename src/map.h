#ifndef MAP_H
#define MAP_H


/**
 * \file          map.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       12 mars 2016
 *
 */



/**
 * \struct smap map.h
 * \brief Represente une carte
 */
struct smap
{
    int dimx; /*!< largeur               */
    int dimy; /*!< hauteur               */
    char **tab; /*!< tableau de caracteres           */
};
/**
 * \typedef map: la structure smap
 */
typedef struct smap map;

/** \brief initMap initialise dimx et dimy de la structure map puis alloue le tableau de caractères dans le tas
 *  \param m pointeur sur map
 */
void initMap (map * m, int x,int y);

/** \brief freeMap met dimx et dimy de la structure map à 0 puis libère la mémoire du tableau de caractères
 *  \param m pointeur sur map
 */
void freeMap(map * m);

/** \brief getCaractMap récupère le caractère de coordonnées (x,y) en vérifiant leur validité
 *  \param m une map
 *  \param x entier positif
 *  \param y entier positif
 *  \return un caractère 
 */
char getCaractMap(map m,int x, int y);


/** \brief setCaractMap modifie le caractère de coordonnées (x,y)
 *  \param m pointeur sur map
 *  \param x entier positif pour modifier
 *  \param y entier positif pour modifier
 *  \param c caractere
 */
void setCaractMap(map *m, int x, int y, char c);

/** \brief getDimXMap récupère la dimx de map
 *  \param m  une map
 *  \return entier positif, la largeur de la map
 */
int getDimXMap(map m);

/** \brief getDimYMap récupère la dimy de map
 *  \param m  une map
 *  \return entier positif, la hauteur de la map
 */
int getDimYMap(map m);

/** \brief setDimXMap modifie la dimx de map
 *  \param m pointeur sur map
 *  \param x entier positif pour modifier
 */
void setDimXMap(map * m, int x);

/** \brief setDimYMap modifie la dimy de map
 *  \param m pointeur sur map
 *  \param y entier positif pour modifier
 */
void setDimYMap(map * m, int y);

/** \brief testMap test toutes les fonctions et procédures sur la map
 */
 void testMap();

#endif /* MAP_H*/
