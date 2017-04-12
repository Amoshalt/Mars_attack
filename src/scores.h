#ifndef SCORES_H
#define SCORES_H


/**
 * \file          scores.h
 * \author    RUILLAT Clara 1406009 / TARDY Martial 11407179 / RAINOUARD Fabian 11406132
 * \version   1.0
 * \date       13 mars 2016
 *
 */



/**
 * \struct sscores scores.h
 * \brief Represente des scores
 */
struct sscores
{
    int MeilleurScore; /*!< meilleur score               */
    int Score; /*!< score actuel               */
};
/**
 * \typedef scores: la structure sscores
 */
typedef struct sscores scores;


/** \brief initMeilleurScore initialise le meilleur score
 *  \param s pointeur sur scores
 */
 void initMeilleurScore(scores * s);

/** \brief initScore initialise le score actuel
 *  \param s pointeur sur scores
 */
 void initScore(scores * s);

/** \brief initScores initialise les scores
 *  \param s pointeur sur scores
 */
 void initScores(scores * s);

/** \brief setMeilleurScore modifie le meilleur score
 *  \param s pointeur sur scores
 */
 void setMeilleurScore(scores * s);

/** \brief setScore modifie le score actuel
 *  \param s pointeur sur scores
 *  \param i entier positif pour modifier score actuel
 */
void setScore(scores * s, int i);

/** \brief ajoutScore ajoute i au score actuel
 *  \param s pointeur sur scores
 *  \param i entier positif pour ajouter au score actuel
 */
void ajoutScore(scores * s, int i);

/** \brief getMeilleurScore revoie le meilleur score
 *  \param s un scores
 *  \return le meilleur score un entier
 */
 int getMeilleurScore(scores s);

/** \brief getScore renvoie le score actuel
 *  \param s un scores
 *  \return un entier, le score actuel
 */
 int getScore(scores s);

/** \brief initSauvegarde initialise le meilleur score sauvegardé à zero
 */
 void initSauvegarde();

  /** \brief testScores teste toutes les fonctions et procedures sur les scores
 */
 void testScores();

 #endif /* SCORES_H*/