#ifndef JEU_H
#define JEU_H

#include "position.h"
#include "protection.h"
#include "ensembleprotection.h"
#include "map.h"
#include "alien.h"
#include "ensemblealien.h"
#include "ensemblemissile.h"
#include "missile.h"
#include "vaisseau.h"
#include "scores.h"
/**
 * \file          jeu.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       09 mars 2016
 *
 */


/**
 * \struct sjeu jeu.h
 * \brief Represente un jeu
 */
struct sjeu
{
    map Map; /*!< carte               */
    ensemblealien EA; /*!< Ensemble d'alien               */
    ensembleprotection EP; /*!< Ensemble de protection               */
    ensemblemissile EMV; /*!< Ensemble de missile du vaisseau              */
    ensemblemissile EMA; /*!< Ensemble de missile des aliens              */
    vaisseau Vaisseau; /*!<  vaisseau               */
    scores Scores; /*!< Scores               */
    int niveau; /*!< niveau 				*/
    int supermissile; /*!< le nombre de supermissile                 */
};

/**
 * \typedef jeu: la structure sjeu
 */
typedef struct sjeu jeu;


/** \brief initJeu initialise la structure jeu
 *  \param j pointeur sur jeu
 */
void initJeu(jeu *j);


/** \brief freeJeu libère la memoire de jeu
 *  \param j pointeur sur jeu
 */
void freeJeu(jeu *j);


/** \brief afficherinformation affiche les inforamtions sur le jeu
 *  \param j pointeur sur jeu
 */
void afficherinformation (jeu *j);


/** \brief deplacementVaisseau deplace le vaisseau suivant la direction demandé (1 gauche, 0 droite)
 *  \param j pointeur sur jeu
 *  \param direction entier , 0 ou 1
 */
void deplacementVaisseau (jeu *j, int direction);


/** \brief ajoutEnsembleAlien créé le nombre d'aliens (demandé par les constantes), et les places sur la carte
 *  \param j pointeur sur jeu
 */
void ajoutEnsembleAlien (jeu *j);


/** \brief alienBordMap renvoie 1 si un alien est présent sur le bord de la map et 0 sinon
 *  \param j pointeur sur jeu
 *  \return un entier 0 ou 1
 */
int alienBordMap(jeu *j);


/** \brief deplacementAliens deplace le vaisseau suivant la direction demandé (1 gauche, 0 droite, 2 bas)
 *  \param j pointeur sur jeu
 *  \return un entier 0 ou 1 pour savoir s'il reste des aliens
 */
int deplacementAliens (jeu *j);


/** \brief ajoutEnsembleprotection créé le nombre de protection (demandé par les constantes), et les places sur la carte à interval régulier.
 *  \param j pointeur sur jeu
 */
void ajoutEnsembleprotection(jeu *j);

/** \brief ajoutVaisseau créé le vaisseau, le place en bas et au centre de la carte
 *  \param j pointeur sur jeu
 */
void ajoutVaisseau(jeu *j);


/** \brief defaite vérifie si la partie est perdue
 *  \param j pointeur sur jeu
 *  \return un entier (0 ou 1)
 */
int defaite(jeu j);


/** \brief  tirerMissileVaisseau lance un missile vers le haut à partir du vaisseau
 *  \param j pointeur sur jeu
 */
void tirerMissileVaisseau(jeu *j);


/** \brief  tirerMissileAlien lance un missile vers le bas à partir d'un alien aleatoire
 *  \param j pointeur sur jeu
 */
void tirerMissileAlien(jeu *j);
 

/** \brief deplacementMissileVaisseau deplace le missile vers le haut
 *  \param j pointeur sur jeu
 *  \return un entier 0 ou 1 pour savoir s'il reste des aliens
 */
int deplacementMissileVaisseau(jeu *j);


/** \brief deplacementMissileAlien deplace le missile vers le bas
 *  \param j pointeur sur jeu
 *  \return un entier 0 ou 1 pour savoir s'il reste dela vie au vaisseau
 */
int deplacementMissileAlien(jeu *j);


/** \brief collision renvoie si un missile rentre en collision avec une objet
 *  \param m un missile
 *  \param j un  jeu
 *  \return un entier entre 1 et 6
 */
int collision(missile m, jeu j);


/** \brief ajoutvie affiche un coeur sur la map 
 *  \param j jeu
 */
void ajoutvie(jeu *j);


/** \brief ajoutSuperMissile affiche un bonus pour obtenir un supermissile sur la map 
 *  \param j jeu
 */
void ajoutSuperMissile(jeu *j);


/** \brief tirerSuperMissile permets de tirer un supermissile 
 *  \param j jeu
 */
void tirerSuperMissile(jeu *j);


/** \brief afficherMap affiche la map avec les differents objets dessus
 *  \param j jeu
 */
void afficherMap(jeu  j);


/** \brief mapinitial ajoute les aliens, les protections, le vaisseau au jeu et rempli le reste de la map avec de #
 *  \param j pointeur sur jeu
 */
void mapinitial(jeu *j);


/** \brief regenererMap supprime tout sur la map et regenerer la map initial
 *  \param j pointeur sur jeu
 */
void regenererMap(jeu *j);


/** \brief sauvegardeJeu sauvegarde une partie
 *  \param j pointeur sur jeu
 */
void sauvegardeJeu(jeu * j);


/** \brief void decodeFichierSauvegardeMap creer un jeu à partir d'une sauvegarde
 *  \param jeu pointeur sur jeu
 */
void decodeFichierSauvegardeMap(jeu * jeu);


/** \brief void supprimeSauvegardeMap
 */
void supprimeSauvegardeMap();


/** \brief setSuperMissile modifie le nombre de supermissile du jeu
 *  \param j pointeur sur jeu
 *	\param i un entier positif
 */
void setSuperMissile(jeu *j, int i);


/** \brief getNiveauJeu renvoie le niveau du jeu
 *  \param j un jeu
 *	\return un entier
 */
int getNiveauJeu(jeu j);

/** \brief getSuperMissile renvoie le nombre de supermissile du jeu
 *  \param j un jeu
 *	\return un entier
 */
int getSuperMissile(jeu j);


/** \brief augmenterNiveau augmente le niveau de 1
 *  \param j pointeur sur jeu
 */
void augmenterNiveau(jeu *j);

#endif /* JEU_H*/