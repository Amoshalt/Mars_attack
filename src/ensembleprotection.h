#ifndef ENSEMBLEPROTECTION_H
#define ENSEMBLEPROTECTION_H

#include "protection.h"
#include "position.h"
/**
 * \file          ensembleprotection.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       09 mars 2016
 *
 */



/**
 * \struct sensembleprotection ensembleprotection.h
 * \brief Represente un ensemble de protection
 */
struct sensembleprotection
{
    int taille; /*!< taille du tableau utilisé               */
    protection *tab; /*!< pointeur sur la première case du tableau de protection               */
    int capacite; /*!< capacité du tableau               */
};

/**
 * \typedef ensembleprotection: la structure sensembleprotection
 */
typedef struct sensembleprotection ensembleprotection;


/** \brief initEnsembleProtection initialise la taille, la capacité puis alloue le tableau de protection dans le tas
 *  \param EP pointeur sur la premiere case de ensembleprotection
 */
void initEnsembleProtection(ensembleprotection *EP);


/** \brief freeEnsembleProtection libere la mémoire du tableau de protection et met à zéro la capacité et la taille
 *  \param EP pointeur sur la premiere case de ensembleprotection
 */
void freeEnsembleProtection(ensembleprotection *EP);


/** \brief ajoutProtection ajoute une protection à l'ensemble de protection
 *  \param EP pointeur sur la premiere case de ensembleprotection
 *  \param p protection à ajouter
 */
void ajoutProtection(ensembleprotection *EP, protection p);


/** \brief suppProtection supprime la protection, dont l'identifiant est ID, à l'ensemble de protection
 *  \param EP pointeur sur la premiere case de ensembleprotection
 *  \param ID un entier positif
 */
void suppProtection(ensembleprotection *EP, int ID);


/** \brief suppEnsembleProtection supprime l'ensemble de protection
 *  \param EP un ensembleprotection
 */
void suppEnsembleProtection(ensembleprotection *EP);


/** \brief getIdProtectionPosition renvoie l'identifiant de la protection, dont la position est P
 *  \param EP un ensembleprotection
 *  \param P position
 *  \return l'identifiant de la protection un entier
 */
int getIdProtectionPosition(ensembleprotection EP, position P);


/** \brief suppVieProtectionID supprime une vie à la protection, dont l'identifiant est ID, et retourne 1 si la protection est supprimée sinon 0 
 *  \param EP pointeur sur la premiere case de ensembleprotection
 *  \param ID un entier positif
 *  \return un entier : 1 si la protection est supprimée et 0 sinon 
 */
int suppVieProtectionID (ensembleprotection *EP, int ID);


/** \brief suppVieProtectionPosition supprime une vie à la protection, dont la position est P, et retourne 1 si la protection est supprimée sinon 0
 *  \param EP pointeur sur la premiere case de ensembleprotection
 *  \param P une position
 *  \return un entier : 1 si la protection est supprimée et 0 sinon 
 */
int suppVieProtectionPosition(ensembleprotection *EP, position P);


/** \brief testEnsembleProtecion teste toutes les fonctions et procédures sur les ensembles de protection
 */
void testEnsembleProtection();


#endif /* ENSEMBLEPROTECTION_H*/