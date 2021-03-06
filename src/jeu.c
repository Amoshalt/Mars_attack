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
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

const int TAILLE_X_MAP = 27;
const int TAILLE_Y_MAP = 29;

const int VIE_VAISSEAU = 3;

const int NB_X_ALIEN = 10;
const int NB_Y_ALIEN = 5;
const int VIE_ALIEN = 1;
const int POS_X_ALIEN1 = 7;/*7*/
const int POS_Y_ALIEN1 = 5;/*5*/

const int VIE_PROTECTION = 1;
const int LARGEUR_PROTECTION = 3;
const int HAUTEUR_PROTECTION = 2;
const int POS_X_PROTECTION1 = 0;
const int POS_Y_PROTECTION1 = 25;
const int ESPACE_PROTECTION = 3;

void initJeu(jeu *j)
{
    j->niveau = 1;
    j->supermissile = 1;
    initMap(&(j->Map),TAILLE_X_MAP,TAILLE_Y_MAP);
    initEnsembleAlien(&(j->EA));
    initEnsembleProtection(&(j->EP));
    initEnsembleMissile(&(j->EMV));
    initEnsembleMissile(&(j->EMA));
    initVaisseau(&(j->Vaisseau));
    initScores(&(j->Scores));
    mapinitial(j);
}

void freeJeu(jeu *j)
{
    freeEnsembleAlien(&(j->EA));
    freeEnsembleProtection(&(j->EP));
    freeEnsembleMissile(&(j->EMV));
    freeEnsembleMissile(&(j->EMA));
    freeMap(&(j->Map));
}

void afficherinformation (jeu *j)
{
    int i,k,l,m;

    printf("Informations sur la map :\n");
    printf("X : %d \nY : %d\n",j->Map.dimx,j->Map.dimy);

    printf("\nInformations sur ensemble d'alien :\n");
    printf("Capacite : %d \nTaille : %d\n",j->EA.capacite, j->EA.taille);
    for(i=0;i<j->EA.taille;i++)
    {
        printf("\nAlien %d\n", i+1);
        printf("id : %d \nVie : %d\nX : %d \nY : %d \n",j->EA.tab[i].idAlien,j->EA.tab[i].vieAlien,j->EA.tab[i].posAlien.x,j->EA.tab[i].posAlien.y);
    }

    printf("\nInformations sur ensemble de protection :\n");
    printf("Capacite : %d \nTaille : %d\n",j->EP.capacite, j->EP.taille);
    for(k=0;k<j->EP.taille;k++)
    {
        printf("\nProtection %d\n", k+1);
        printf("id : %d \nVie : %d\nX : %d \nY : %d \n",j->EP.tab[k].idProtection,j->EP.tab[k].vieProtection,j->EP.tab[k].posProtection.x,j->EP.tab[k].posProtection.y);
    }

    printf("\nInformations sur le vaisseau :\n");
    printf("id : %d \nX : %d \nY : %d \nVie : %d\n\n",j->Vaisseau.idVaisseau,j->Vaisseau.posVaisseau.x,j->Vaisseau.posVaisseau.y,j->Vaisseau.vieVaisseau);

    printf("Informations sur le scores : \n");
    printf("Meilleur score : %d\nScore : %d\n\n",j->Scores.MeilleurScore, j->Scores.Score);

    printf("\nInformations sur ensemble de missile du vaisseau:\n");
    printf("Capacite : %d \nTaille : %d\n",j->EMV.capacite, j->EMV.taille);
    for(l=0;l<j->EMV.taille;l++)
    {
        printf("\nMissile %d\n", l+1);
        printf("id : %d \nX : %d \nY : %d \nNiveau : %d\n",j->EMV.tab[l].idMissile,j->EMV.tab[l].posMissile.x,j->EMV.tab[l].posMissile.y, j->EMV.tab[l].nivMissile);
    }

    printf("\nInformations sur ensemble de missile des aliens:\n");
    printf("Capacite : %d \nTaille : %d\n",j->EMA.capacite, j->EMA.taille);
    for(m=0;m<j->EMA.taille;m++)
    {
        printf("\nMissile %d\n", m+1);
        printf("id : %d \nX : %d \nY : %d \nNiveau : %d\n",j->EMA.tab[m].idMissile,j->EMA.tab[m].posMissile.x,j->EMA.tab[m].posMissile.y, j->EMA.tab[m].nivMissile);
    }
}

void deplacementVaisseau (jeu *j, int direction)
{
    int posXVaisseau, posYVaisseau, dimX;
    posXVaisseau = getPosXVaisseau(j->Vaisseau);
    posYVaisseau = getPosYVaisseau(j->Vaisseau);
    /*si la direction est droite (0), on verifie que ça ne sorte pas de la map,si ça sort on le laisse à la même position*/
    if(direction == 0)
    {
        dimX = getDimXMap(j->Map);
        if(posXVaisseau+1 < dimX)
        {
            setCaractMap(&(j->Map), posXVaisseau, posYVaisseau, '#');
            setPosXVaisseau(&(j->Vaisseau), posXVaisseau+1);
            setCaractMap(&(j->Map), posXVaisseau+1, posYVaisseau, 'V');
        }
    }
    /*si la direction est gauche (1), on verifie que ça ne sorte pas de la map,si ça sort on le laisse à la même position*/
    else if(direction == 1)
    {
        if(posXVaisseau-1 >= 0)
        {
            setCaractMap(&(j->Map), posXVaisseau, posYVaisseau, '#');
            setPosXVaisseau(&(j->Vaisseau), posXVaisseau-1);
            setCaractMap(&(j->Map), posXVaisseau-1, posYVaisseau, 'V');
        }
    }
    else
    {
        printf("erreur, la direction demandé n'existe pas.\n");
    }
}

void ajoutEnsembleAlien (jeu *j)
{
    int i=0,k,l, vie;
    alien A;
    for(k=0;k<NB_Y_ALIEN;k++)
    {
        for(l=0;l<NB_X_ALIEN;l++)
        {
            vie = (j->niveau+2-j->niveau%2)/2;
            A = creationAlien(i, vie, POS_X_ALIEN1+l, POS_Y_ALIEN1+k);
            ajoutAlien(&(j->EA),A);
            if (vie == 1)
            {
                setCaractMap(&(j->Map), POS_X_ALIEN1+l, POS_Y_ALIEN1+k, 'A');
            }
            else if (vie == 2)
            {
                setCaractMap(&(j->Map), POS_X_ALIEN1+l, POS_Y_ALIEN1+k, 'a');
            }
            else
            {
                setCaractMap(&(j->Map), POS_X_ALIEN1+l, POS_Y_ALIEN1+k, 's');
            }
            i++;
        }
    }
}

int alienBordMap(jeu *j)
{
    int i, reponse=0,nbAlien, posXAlien;
    nbAlien = getNombreAlien(j->EA); 
    for (i=0; i<nbAlien; i++)
    {
        posXAlien = getPosXIemeAlien(j->EA, i);
        if (posXAlien == TAILLE_X_MAP-1 || posXAlien == 0)
        {
            reponse = 1;
        }
    }
    return reponse;
}

int deplacementAliens (jeu *j)
{
    int aliensupprime=0, nbAlien,nbaliensupprime=0, i, k, l, direction_aleatoire=1, victoire=0, protecspprime=0, posXAlien, posYAlien, vieAlien;
    char caractMap;
    position posAlien;
    nbAlien = getNombreAlien(j->EA);
    if( getDescenduAlien(j->EA) == 2 )
    {
        direction_aleatoire = getDirectionAlien(j->EA);
        setDescenduAlien(&(j->EA), 0);
    }
    else
    {
        if (alienBordMap(j) == 1)
        {
            for (i=0; i<nbAlien;i++)
            {
                if (getPosXIemeAlien(j->EA, i) == TAILLE_X_MAP-1)
                {
                    direction_aleatoire=2;
                    setDescenduAlien(&(j->EA), 2);
                    setDirectionAlien(&(j->EA), 1);
                }
                else if (getPosXIemeAlien(j->EA, i) == 0 )
                {
                    direction_aleatoire = 2;
                    setDescenduAlien(&(j->EA), 2);
                    setDirectionAlien(&(j->EA), 0);
                }   
            }
        }
        else
        {
            direction_aleatoire = getDirectionAlien(j->EA);
        }
    }
    /*deplacement vers la droite*/
    if(direction_aleatoire == 0)
    {
        for(i=nbAlien-1;i>=0;i--)
        {
            posXAlien = getPosXIemeAlien(j->EA, i);
            posYAlien = getPosYIemeAlien(j->EA, i);
            posAlien = getPosIemeAlien(j->EA, i);
            if (MissilePosition(j->EMV, posAlien) == 1)
            {
                setCaractMap(&(j->Map),posXAlien, posYAlien, 'N');
            }
            else
            {
                setCaractMap(&(j->Map),posXAlien, posYAlien, '#');
            }
            setPosXIemeAlien(&(j->EA),i, posXAlien+1);
            posAlien = getPosIemeAlien(j->EA, i);
            posXAlien = getPosX(posAlien);
            posYAlien = getPosY(posAlien);

            caractMap = getCaractMap(j->Map, posXAlien, posYAlien);
            vieAlien = getVieIemeAlien(j->EA, i);
            /*Si un missile est présent sur la nouvelle position de l'alien*/
            if (caractMap == 'M' || caractMap == 'N')
            {
                /*enleve vie à l'alien touché*/
                aliensupprime = suppVieAlienPosition(&(j->EA), posAlien);
                /*si l'alien n'est pas supprimé (encore de la vie) on affiche un A sur la map*/
                if (aliensupprime == 0)
                {
                    if (getVieIemeAlien(j->EA, i) == 1)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                    }
                    else if (getVieIemeAlien(j->EA, i) == 2)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                    }
                    else
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                    }
                }
                else if (caractMap == 'M')
                {
                    /*On efface le missile */
                    supprimerMissilePosition(&(j->EMV), posAlien);
                    /*On affiche # qur la map*/
                    setCaractMap(&(j->Map),posXAlien, posYAlien, '#');
                    ajoutScore(&(j->Scores), 100*j->niveau);
                }
                /*sinon, on affiche le super missile*/
                else
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'N');
                    ajoutScore(&(j->Scores), 100*j->niveau);
                }
            }
            else if (caractMap == 'P')
            {
                protecspprime =0;
                while (protecspprime == 0)
                {
                    protecspprime = suppVieProtectionPosition(&(j->EP), posAlien);
                }
                if (vieAlien == 1)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                }
                else if (vieAlien == 2)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                }
                else
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                }
            }
            else
            {
                if (vieAlien == 1)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                }
                else if (vieAlien == 2)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                }
                else
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                }
            }  
        }
    }
    /*deplacement vers la gauche*/
    else if (direction_aleatoire == 1)
    {
        nbAlien = getNombreAlien(j->EA);
        for(k=0;k<nbAlien;k++)
        {
            posXAlien = getPosXIemeAlien(j->EA, k-nbaliensupprime);
            posYAlien = getPosYIemeAlien(j->EA, k-nbaliensupprime);
            posAlien = getPosIemeAlien(j->EA, k-nbaliensupprime);
            if (MissilePosition(j->EMV, posAlien) == 1)
            {
                setCaractMap(&(j->Map),posXAlien, posYAlien, 'N');
            }
            else
            {
                setCaractMap(&(j->Map),posXAlien, posYAlien, '#');
            }
            setPosXIemeAlien(&(j->EA),k-nbaliensupprime, posXAlien-1);

            posAlien = getPosIemeAlien(j->EA, k-nbaliensupprime);
            posXAlien = getPosX(posAlien);
            posYAlien = getPosY(posAlien);

            caractMap = getCaractMap(j->Map, posXAlien, posYAlien);
            vieAlien = getVieIemeAlien(j->EA, k-nbaliensupprime);
            /*Si un missile est présent sur la nouvelle position de l'alien*/
            if (caractMap == 'M' || caractMap == 'N')
            {
                /*enleve vie à l'alien touché*/
                aliensupprime = suppVieAlienPosition(&(j->EA), posAlien);
                /*si l'alien n'est pas supprimé (encore de la vie) on affiche un A sur la map*/
                if (aliensupprime == 0)
                {
                    if (getVieIemeAlien(j->EA, k-nbaliensupprime) == 1)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                    }
                    else if (getVieIemeAlien(j->EA, k-nbaliensupprime) == 2)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                    }
                    else
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                    }
                }
                else if (caractMap == 'M')
                {
                    nbaliensupprime++;
                    /*On efface le missile */
                    supprimerMissilePosition(&(j->EMV), posAlien);
                    /*On affiche # qur la map*/
                    setCaractMap(&(j->Map), posXAlien, posYAlien, '#');
                    ajoutScore(&(j->Scores), 100*j->niveau);
                }
                /*sinon, on affiche le super missile*/
                else
                {
                    nbaliensupprime++;
                    setCaractMap(&(j->Map), posXAlien, posYAlien, 'N');
                    ajoutScore(&(j->Scores), 100*j->niveau);
                }
            }
            else if (caractMap == 'P')
            {
                protecspprime=0;
                while (protecspprime == 0)
                {
                    protecspprime = suppVieProtectionPosition(&(j->EP), posAlien);
                }
                if (vieAlien == 1)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                }
                else if (vieAlien == 2)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                }
                else
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                }
            }
            else
            {
                if (vieAlien == 1)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                }
                else if (vieAlien == 2)
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                }
                else
                {
                    setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                }
            }
        }
        
    }
    /*deplacement vers le bas*/
    else if (direction_aleatoire == 2)
    {
        if(getPosYIemeAlien(j->EA, nbAlien-1)+1 < getDimYMap(j->Map)-1)
        {
            for(l=nbAlien-1;l>=0;l--)
            {
                posXAlien = getPosXIemeAlien(j->EA, l);
                posYAlien = getPosYIemeAlien(j->EA, l);
                setCaractMap(&(j->Map), posXAlien, posYAlien, '#');
                setPosYIemeAlien(&(j->EA), l, posYAlien+1);
                posAlien = getPosIemeAlien(j->EA, l);
                posXAlien = getPosXIemeAlien(j->EA, l);
                posYAlien = getPosYIemeAlien(j->EA, l);
                caractMap = getCaractMap(j->Map, posXAlien, posYAlien);
                vieAlien = getVieIemeAlien(j->EA, l);
                /*Si un missile est présent sur la nouvelle position de l'alien*/
                if(caractMap == 'M' || caractMap == 'N')
                {
                    /*enleve vie à l'alien touché*/
                    aliensupprime = suppVieAlienPosition(&(j->EA), posAlien);
                    /*si l'alien n'est pas supprimé (encore de la vie) on affiche un A sur la map*/
                    if (aliensupprime == 0)
                    {
                        if (vieAlien == 1)
                        {
                            setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                        }
                        else if (vieAlien == 2)
                        {
                            setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                        }
                        else
                        {
                            setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                        }
                    }
                    else if (caractMap == 'M')
                    {
                        /*On efface le missile */
                        supprimerMissilePosition(&(j->EMV), posAlien);
                        /*On affiche # sur la map*/
                        setCaractMap(&(j->Map),posXAlien, posYAlien, '#');
                        ajoutScore(&(j->Scores), 100*j->niveau);
                    }
                    /*sinon, on affiche le super missile*/
                    else
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'N');
                        ajoutScore(&(j->Scores), 100*j->niveau);
                    }
                }
                else if (caractMap == 'P')
                {
                    protecspprime =0;
                    while (protecspprime == 0)
                    {
                        protecspprime = suppVieProtectionPosition(&(j->EP), posAlien);
                    }
                    if (vieAlien == 1)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                    }
                    else if (vieAlien == 2)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                    }
                    else
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                    }
                }
                else
                {
                    if (vieAlien == 1)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'A');
                    }
                    else if (vieAlien == 2)
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 'a');
                    }
                    else
                    {
                        setCaractMap(&(j->Map),posXAlien, posYAlien, 's');
                    }
                }
            }
        }
    }
    else
    {
        printf("erreur, la direction demandé n'existe pas.\n");
    }
    nbAlien = getNombreAlien(j->EA);
    if (nbAlien == 0)
    {
        victoire = 1;
    }
    return victoire;
}

void ajoutEnsembleprotection(jeu *j)
{
    int k,l,i=0,n;
    protection P;
    /*Attention, bien choisir ses constantes pour evite "segmentation fault" (ne pas tenter de mettre des protections hors de la map)*/
    /*Place des ensembles de protections à intervalles regulier*/
    for(n=0;n<TAILLE_X_MAP;n=n+LARGEUR_PROTECTION+ESPACE_PROTECTION)
    {
        for(k=0;k<HAUTEUR_PROTECTION;k++)
        {
            for(l=0;l<LARGEUR_PROTECTION;l++)
            {
                /*Place les protections en forme de U à l'envers*/
                if(k==0 || l==0 || l==LARGEUR_PROTECTION-1)
                {
                    P = creationProtection(i, VIE_PROTECTION, POS_X_PROTECTION1+l+n, POS_Y_PROTECTION1+k);
                    ajoutProtection(&(j->EP), P);
                    setCaractMap(&(j->Map), POS_X_PROTECTION1+l+n, POS_Y_PROTECTION1+k, 'P');
                    i++;
                }
            }
        }
    }
}

void ajoutVaisseau(jeu *j)
{
    int vie, dimX, dimY;
    if (j->niveau == 1)
    {
        vie = VIE_VAISSEAU;
    }
    else
    {
        vie = getVieVaisseau(j->Vaisseau);
    }
    dimX = getDimXMap(j->Map);
    dimY = getDimYMap(j->Map);
    j->Vaisseau = creationVaisseau(1,vie,dimX/2,dimY-1);
    setCaractMap(&(j->Map), dimX/2,dimY-1, 'V');
}

void ajoutvie(jeu *j)
{
    int position_x_aleatoire = 0, position_y_aleatoire = 0;
    char caractMap;
    position_x_aleatoire = rand()%TAILLE_X_MAP;
    position_y_aleatoire = rand()%(POS_Y_ALIEN1-1);
    caractMap = getCaractMap(j->Map, position_x_aleatoire, position_y_aleatoire);
    if(caractMap == '#')
    {
        setCaractMap(&(j->Map), position_x_aleatoire, position_y_aleatoire, 'B');
    }
}

void ajoutSuperMissile(jeu *j)
{
    int posit_x_aleatoire = 0, posit_y_aleatoire = 0;
    char caractMap;
    posit_x_aleatoire = rand()%TAILLE_X_MAP;
    posit_y_aleatoire = rand()%(POS_Y_ALIEN1-1);
    caractMap = getCaractMap(j->Map, posit_x_aleatoire, posit_y_aleatoire);
    if(caractMap == '#')
    {
        setCaractMap(&(j->Map), posit_x_aleatoire, posit_y_aleatoire, 'C');
    }
}
void tirerSuperMissile(jeu *j)
{
    int posXVaisseau, posYVaisseau;
    missile m;
    setIdMissile(&m, getNombreMissile(j->EMV));
    setNivMissile(&m, 2);
    posXVaisseau = getPosXVaisseau(j->Vaisseau);
    posYVaisseau = getPosYVaisseau(j->Vaisseau);
    setPosXMissile(&m, posXVaisseau);
    setPosYMissile(&m, posYVaisseau-1);
    setCaractMap(&(j->Map), posXVaisseau, posYVaisseau-1, 'N');
    ajoutMissile(&(j->EMV), m);
}

int defaite (jeu j)
{
    int i=0,res=0, dimX, dimY;
    char caractMap;
    dimX = getDimXMap(j.Map);
    dimY = getDimYMap(j.Map);
    while (i< dimX && res != 1)
    {
        caractMap = getCaractMap(j.Map, i, dimY-2);
        if(caractMap == 'A' || caractMap == 'a' || caractMap == 's')
        {
            res = 1;
        }
        else
        {
            res = 0;
        }
        i++;
    }
    return res;
}

void tirerMissileVaisseau(jeu *j)
{
    int posXVaisseau, posYVaisseau;
    missile m;
    setIdMissile(&m, getNombreMissile(j->EMV));
    setNivMissile(&m, 1);
    posXVaisseau = getPosXVaisseau(j->Vaisseau);
    posYVaisseau = getPosYVaisseau(j->Vaisseau);
    setPosXMissile(&m, posXVaisseau);
    setPosYMissile(&m, posYVaisseau-1);
    setCaractMap(&(j->Map), posXVaisseau, posYVaisseau-1, 'M');
    ajoutMissile(&(j->EMV), m);
}

void tirerMissileAlien(jeu *j)
{
    int alien_aleatoire=0, posXAlien, posYAlien;
    missile m;
    srand(time(NULL));
    alien_aleatoire = rand()%(getNombreAlien(j->EA));

    setIdMissile(&m, getNombreMissile(j->EMA));
    setNivMissile(&m, 1);
    posXAlien = getPosXIemeAlien(j->EA, alien_aleatoire);
    posYAlien = getPosYIemeAlien(j->EA, alien_aleatoire);
    setPosXMissile(&m, posXAlien);
    setPosYMissile(&m, posYAlien);
    ajoutMissile(&(j->EMA), m);
}

int deplacementMissileVaisseau(jeu *j)
{
    int protecspprime=0, aliensupprime=0, missilesupprime=0, victoire=0, i, t, a, col=0, posXMissile, posYMissile, nivMissile, vieVaisseau;
    position posMissile, posAlien, P;
    missile miss, IemeMissile;

    a = getNombreMissile(j->EMV);
    for(i=0;i<a;i++)
    {
        posXMissile = getPosXIemeMissile(j->EMV, i-missilesupprime);
        posYMissile = getPosYIemeMissile(j->EMV, i-missilesupprime);
        setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
        if(posYMissile == 0)
        {
            /*On efface le missile */
            supprimerIemeMissile(&(j->EMV), i-missilesupprime);
            missilesupprime++;
        }
        else
        {
            setPosYIemeMissile(&(j->EMV), i-missilesupprime, posYMissile-1);
            posXMissile = getPosXIemeMissile(j->EMV, i-missilesupprime);
            posYMissile = getPosYIemeMissile(j->EMV, i-missilesupprime);
            IemeMissile = getIemeMissile(j->EMV, i-missilesupprime);
            col = collision(IemeMissile, *j);
            setPosX(&posMissile, posXMissile);
            setPosY(&posMissile, posYMissile);
            /*Collision avec une protection*/
            if(col == 1)
            {
                nivMissile = getNiveauIemeMissile(j->EMV, i-missilesupprime);
                /*enleve vie à la protection touché*/
                protecspprime = suppVieProtectionPosition(&(j->EP), posMissile);
                /*si la protection n'est pas supprimé (encore de la vie) on affiche un P sur la map*/
                if (protecspprime == 0)
                {
                    setCaractMap(&(j->Map), posXMissile, posYMissile, 'P');
                }
                /*sinon on affiche le #*/
                else
                {
                    setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
                }
                /*Si c'est un missile de niveau 1, on le supprime*/
                if (nivMissile == 1)
                {
                    supprimerIemeMissile(&(j->EMV), i-missilesupprime);
                    missilesupprime++;
                }
                /*Sinon on affiche le missile*/
                else
                {
                    setCaractMap(&(j->Map), posXMissile, posYMissile, 'N');
                }
            }
            /*Si collision avec un alien*/
            else if (col == 2)
            {
                /*enleve vie à l'alien touché*/
                aliensupprime = suppVieAlienPosition(&(j->EA), posMissile);
                nivMissile = getNiveauIemeMissile(j->EMV, i-missilesupprime);
                /*si l'alien n'est pas supprimé (encore de la vie) on affiche un A sur la map*/
                if (aliensupprime == 0)
                {
                    P.x = posXMissile;
                    P.y = posYMissile+1;
                    for(t=0;t<j->EA.taille;t++)
                    {
                        posAlien = getPosIemeAlien(j->EA, t);
                        if(comparePostion(posAlien, P)==1)
                        {
                            if (getVieAlienPosition(j->EA, posXMissile, posYMissile+1) == 1)
                            {
                                setCaractMap(&(j->Map), posXMissile, posYMissile+1, 'A');
                            }
                            else if (getVieAlienPosition(j->EA, posXMissile, posYMissile+1) == 2)
                            {
                                setCaractMap(&(j->Map), posXMissile, posYMissile+1, 'a');
                            }
                            else
                            {
                                setCaractMap(&(j->Map), posXMissile, posYMissile+1, 's');
                            }
                        }
                    }
                    /*Si c'est un missile de niveau 1 on le supprime*/
                    if (nivMissile == 1)
                    {
                        setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
                        supprimerIemeMissile(&(j->EMV), i-missilesupprime);
                        missilesupprime++;
                    }
                    else
                    {
                        setCaractMap(&(j->Map), posXMissile, posYMissile, 'N');
                    }
                    if (getVieAlienPosition(j->EA, posXMissile, posYMissile) == 1)
                    {
                        setCaractMap(&(j->Map), posXMissile, posYMissile, 'A');
                    }
                    else if (getVieAlienPosition(j->EA, posXMissile, posYMissile) == 2)
                    {
                        setCaractMap(&(j->Map), posXMissile, posYMissile, 'a');
                    }
                    else
                    {
                        setCaractMap(&(j->Map), posXMissile, posYMissile, 's');
                    }
                }
                /*sinon on affiche le #*/
                else
                {
                    /*Si c'est un missile de niveau 1 on le supprime*/
                    if (nivMissile == 1)
                    {
                        setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
                        supprimerIemeMissile(&(j->EMV), i-missilesupprime);
                        missilesupprime++;
                    }
                    else
                    {
                        setCaractMap(&(j->Map), posXMissile, posYMissile, 'N');
                    }
                    ajoutScore(&(j->Scores), 100*j->niveau);
                }
                if (getNombreAlien(j->EA) == 0)
                {
                    victoire = 1;
                }
            }
            /*Si collision avec un autre missile et que le niveau du jeu est 1 ou 2*/
            else if (col == 3)
            {
                nivMissile = getNiveauIemeMissile(j->EMV, i-missilesupprime);
                if (j->niveau <= 2 && nivMissile == 1)
                {
                    supprimerMissilePosition(&(j->EMA),posMissile );
                    setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
                    supprimerIemeMissile(&(j->EMV), i-missilesupprime);
                    missilesupprime++;
                }
                else if (nivMissile == 2)
                {
                    supprimerMissilePosition(&(j->EMA),posMissile );
                    setCaractMap(&(j->Map), posXMissile, posYMissile, 'N');
                }
                else
                {
                    supprimerIemeMissile(&(j->EMV), i-missilesupprime);
                    missilesupprime++;
                }

            }
            /*si collision avec un bonus*/
            else if (col == 5)
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
                supprimerIemeMissile(&(j->EMV), i-missilesupprime);
                missilesupprime++;
                vieVaisseau = getVieVaisseau(j->Vaisseau);
                setVieVaisseau(&(j->Vaisseau), vieVaisseau+1);
            }
            /*Si collision avec un bonus super missile*/
            else if (col == 6)
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
                supprimerIemeMissile(&(j->EMV), i-missilesupprime);
                missilesupprime++;
                j->supermissile++;
            }
            /*Si il n'y a pas de collision*/
            else
            {
                P.x = posXMissile;
                P.y = posYMissile+1;
                for(t=0;t<getNombreAlien(j->EA);t++)
                {
                    posAlien = getPosIemeAlien(j->EA, t);
                    if(comparePostion(posAlien, P)==1)
                    {
                        if (getVieAlienPosition(j->EA, posXMissile, posYMissile+1) == 1)
                        {
                            setCaractMap(&(j->Map), posXMissile, posYMissile+1, 'A');
                        }
                        else if (getVieAlienPosition(j->EA, posXMissile, posYMissile+1) == 2)
                        {
                            setCaractMap(&(j->Map), posXMissile, posYMissile+1, 'a');
                        }
                        else
                        {
                            setCaractMap(&(j->Map), posXMissile, posYMissile+1, 's');
                        }
                    } 
                }
                miss = getMissilePosition((j->EMV), posMissile);
                if (miss.nivMissile == 2)
                {
                    setCaractMap(&(j->Map), posXMissile, posYMissile, 'N');
                }
                else
                {
                    setCaractMap(&(j->Map), posXMissile, posYMissile, 'M');
                }            
            }
        }
    }
    return victoire;
}

int deplacementMissileAlien(jeu *j)
{
    /*Dans cette fonction , lorsqu'un missile rentre en collision avec quelque chose (sauf avec les aliens), 
    on le supprime (donc on décale tous les autres aliens dans le tableau), missilesupprime nous permets donc de décaler les i afin
    qu'ils désigne bien la case du tableau de l'alien que l'on veut déplacer*/
    int protecspprime=0, missilesupprime=0,nivMissile, perdu = 0, i, a, col=0, fin=0, posXMissile, posYMissile;
    missile IemeMissile;
    position posMissile;
    a = getNombreMissile(j->EMA);
    /*On parcours tous le tableau de missile des aliens*/
    for(i=0;i<a;i++)
    {
        /*si le missile est au même endroit qu'un alien, on affiche l'alien*/
        IemeMissile = getIemeMissile(j->EMA, i-missilesupprime);
        posXMissile = getPosXIemeMissile(j->EMA, i-missilesupprime);
        posYMissile = getPosYIemeMissile(j->EMA, i-missilesupprime);
        if (collision(IemeMissile, *j) == 2)
        {
            if (getVieAlienPosition(j->EA, posXMissile, posYMissile) == 1)
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'A');
            }
            else if (getVieAlienPosition(j->EA, posXMissile, posYMissile) == 2)
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'a');
            }
            else
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 's');
            }
        }
        else
        {
            setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
        }
        setPosYIemeMissile(&(j->EMA), i-missilesupprime, posYMissile+1);
        posYMissile = getPosYIemeMissile(j->EMA, i-missilesupprime);
        IemeMissile = getIemeMissile(j->EMA, i-missilesupprime);
        if (posYMissile < TAILLE_Y_MAP)
        {
            col = collision(IemeMissile, *j);
        }
        /*si le missile sort de la map*/
        if (posYMissile >= TAILLE_Y_MAP)
        {
            /*On efface le missile */
            supprimerIemeMissile(&(j->EMA), i-missilesupprime);
            missilesupprime++;
        }
        /*Si collision avec protection*/
        else if(col == 1)
        {
            posMissile = getPosIemeMissile(j->EMA, i-missilesupprime);
            /*enleve vie à objet touché*/
            protecspprime = suppVieProtectionPosition(&(j->EP), posMissile);

            /*si la protection n'est pas supprimé (encore de la vie) on affiche un P sur la map*/
            if (protecspprime == 0)
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'P');
            }
            /*sinon on affiche le #*/
            else
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
            }
            /*On efface le missile */
            supprimerIemeMissile(&(j->EMA), i-missilesupprime);
            missilesupprime++;
        }
        /*Si le missile se déplace sur un alien on affiche l'alien*/
        else if (col == 2)
        {
            if (getVieAlienPosition(j->EA, posXMissile, posYMissile) == 1)
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'A');
            }
            else if (getVieAlienPosition(j->EA, posXMissile, posYMissile) == 2)
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'a');
            }
            else
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 's');
            }
        }
        /*Si collision avec vaisseau*/
        else if (col == 4)
        {
            perdu = suppVieVaisseau(&(j->Vaisseau));
            if (perdu == 1)
            {
                fin =1;
            }
            /*On efface le missile */
            else
            {
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'V');
                supprimerIemeMissile(&(j->EMA), i-missilesupprime);
                missilesupprime++;
            }
        }
        /*si il y a collision entre 2 missiles */
        else if (col == 3)
        {
            posMissile = getPosIemeMissile(j->EMA, i-missilesupprime);
            nivMissile = getNiveauMissilePosition(j->EMV, posMissile);
            if (j->niveau <= 2 && nivMissile == 1)
            {
                supprimerMissilePosition(&(j->EMV),posMissile);
                setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
                supprimerIemeMissile(&(j->EMA), i-missilesupprime);
                missilesupprime++;
            }
            else if (nivMissile == 2)
            {
                supprimerIemeMissile(&(j->EMA), i-missilesupprime);
                missilesupprime++;
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'N');
            }
            else
            {
                supprimerMissilePosition(&(j->EMV),posMissile);
                setCaractMap(&(j->Map), posXMissile, posYMissile, 'm');
            }
        }
        /*si il y a collision avec un bonus vie */
        else if (col == 5 || col == 6)
        {
            setCaractMap(&(j->Map), posXMissile, posYMissile, '#');
            supprimerIemeMissile(&(j->EMA), i-missilesupprime);
            missilesupprime++;
        }
        /*Si il n'y a pas de collision*/
        else
        {
            setCaractMap(&(j->Map), posXMissile, posYMissile, 'm');
        }

    }
    return fin;
}

int collision(missile m, jeu j)
{
    int col=0, posXMissile, posYMissile;
    char caractMap;
    posXMissile = getPosXMissile(m);
    posYMissile = getPosYMissile(m);
    caractMap = getCaractMap(j.Map, posXMissile, posYMissile);
    if (caractMap == 'P')
    {
        col = 1;
    }
    else if(caractMap == 'A' || caractMap == 'a' || caractMap == 's')
    {
        col = 2;
    }
    else if(caractMap == 'M' || caractMap == 'N' || caractMap == 'm')
    {
        col = 3;
    }
    else if(caractMap == 'V')
    {
        col = 4;
    }
    else if (caractMap == 'B')
    {
        col = 5;
    }
    else if (caractMap == 'C')
    {
        col = 6;
    }
    return col;
}

void afficherMap(jeu j)
{
    int i,k, dimX, dimY;
    char caractMap;
    dimX = getDimXMap(j.Map);
    dimY = getDimYMap(j.Map);
    for (k=0;k<dimY;k++)
    {
        for (i=0;i<dimX;i++)
        {
            caractMap = getCaractMap(j.Map, i, k);
            printf( " %c ",caractMap);
        }
        printf("\n");
    }
}

void mapinitial(jeu *j)
{
    int i, k, dimX, dimY;
    dimX = getDimXMap(j->Map);
    dimY = getDimYMap(j->Map);
    for (k=0;k<dimY;k++)
    {
        for (i=0;i<dimX;i++)
        {
            setCaractMap(&(j->Map),i,k,'#');
        }
    }
    ajoutVaisseau(j);
    ajoutEnsembleAlien(j);
    ajoutEnsembleprotection(j);
}

void regenererMap(jeu *j)
{
    suppEnsembleMissile(&(j->EMV));
    suppEnsembleMissile(&(j->EMA));
    suppEnsembleProtection(&(j->EP));
    suppEnsembleAlien(&(j->EA));
    mapinitial(j);
}

void sauvegardeJeu(jeu * jeu)
{
    FILE * f=NULL;
    int i,j, vieV;
    char c;
    f= fopen("./data/sauvegardeMap.txt","w+");
    if (f != NULL)
    {   
        for (j=0; j< getDimYMap(jeu->Map); j++)
        {
            for (i=0; i < getDimXMap(jeu->Map) ; i++)
          {
                c = getCaractMap(jeu->Map,i, j);
                
                switch(c)
                {
                    case 'a':
                        fprintf(f, "a%d",getVieAlienPosition(jeu->EA,i,j));
                        break;

                    case 'A':
                        fprintf(f, "A%d",getVieAlienPosition(jeu->EA,i,j));
                        break;

                    case 'V':
                        vieV = getVieVaisseau(jeu->Vaisseau);
                        fprintf(f, "V%d", vieV);
                        break;

                    case'N':
                        fprintf(f, "%c%d", c,2  );

                        break;

                    case'P':
                        fprintf(f, "%c%d", c, VIE_PROTECTION  );

                        break;

                    case 'm':
                        fprintf(f, "%c%d", c,1  );

                        break;

                    case'M':
                        fprintf(f, "%c%d", c,1  );

                        break;

                    case'B':
                        fprintf(f, "%c%d", '#',0  );

                        break;

                    case'C':
                        fprintf(f, "%c%d", '#',0  );

                        break;

                    case '#':
                        fprintf(f, "%c%d", c,0  );
                        break;

                    default: 
                    {
                        fprintf(f, "%c%d",c,getVieAlienPosition(jeu->EA,i,j));
                    }
                        break;
                    
                }
               
            }
            fprintf(f,"\n");
        }
        
        fprintf(f,"sm:%i\n", jeu->supermissile);
        fprintf(f,"niv:%i\n", jeu->niveau);
        fprintf(f,"scr:%i\n", getScore(jeu->Scores));
    }

    
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegardeMap.txt \n");
    }

    fclose(f);
}

void decodeFichierSauvegardeMap(jeu * jeu)
{
    FILE * f;
    int i,j,num;
    int idP=0,idm=0,idM=0,idA=0;
    char c;
    alien a;
    missile m;
    protection p;
    position pos;
    
    f= fopen("./data/sauvegardeMap.txt","r");

    freeJeu(jeu);
    
    initMap(&(jeu->Map),TAILLE_X_MAP,TAILLE_Y_MAP);
    initEnsembleAlien(&(jeu->EA));
    initEnsembleProtection(&(jeu->EP));
    initEnsembleMissile(&(jeu->EMV));
    initEnsembleMissile(&(jeu->EMA));
    initVaisseau(&(jeu->Vaisseau));
    initScores(&(jeu->Scores));
    
  
    if (f != NULL)
    {   
        rewind(f);
        for (i=0; i<  getDimYMap(jeu->Map) ; i++)
        {
            for (j=0; j<  getDimXMap(jeu->Map) ; j++)
            {
                fscanf(f, "%c%d", &c,&num);
                
                switch (c)
                {   
                    case 'P':
                    {
                        initProtection(&p);

                        setCaractMap( &(jeu->Map), j, i, c);

                        setPosProtection(&p,j,i);
                        setVieProtection(&p, num);                        
                        setIdProtection(&p,idP);
                        ajoutProtection(&(jeu->EP),p);
                        idP++;
                    }
                    break;

                    case 'A':
                    {
                        initAlien(&a);
                        
                        setPosXAlien(&a, j);
                        setPosYAlien(&a, i);
                        
                        if (num > 0)
                        {
                            setVieAlien(&a, num);
                            setIdAlien(&a,idA);
                            ajoutAlien(&(jeu->EA),a);
                            setCaractMap( &(jeu->Map), j, i, c);
                            idA++;
                        }
                        
                    }
                    break;

                    case 'a':
                    {
                        initAlien(&a);
                        
                        setPosXAlien(&a, j);
                        setPosYAlien(&a, i);
                        
                        if (num > 0)
                        {
                            setVieAlien(&a, num);
                            setIdAlien(&a,idA);
                            ajoutAlien(&(jeu->EA),a);
                            setCaractMap( &(jeu->Map), j, i, c);
                            idA++;
                        }
                        
                    }
                    break;

                    case 's':
                    {
                        initAlien(&a);
                        
                        setPosXAlien(&a, j);
                        setPosYAlien(&a, i);
                        
                        if (num > 0)
                        {
                            setVieAlien(&a, num);
                            setIdAlien(&a,idA);
                            ajoutAlien(&(jeu->EA),a);
                            setCaractMap( &(jeu->Map), j, i, c);
                            idA++;
                        }
                        
                    }
                    break;

                    case 'V':
                    {
                        setIdVaisseau(&(jeu->Vaisseau),0);
                        setPosX(&pos, j);
                        setPosY(&pos, i);
                        setPosXVaisseau(&jeu->Vaisseau, pos.x);
                        setPosYVaisseau(&jeu->Vaisseau, pos.y);
                        setVieVaisseau(&(jeu->Vaisseau),num);
                        setCaractMap( &(jeu->Map), j , i , c);
                        

                    }
                    break;

                    case 'm':
                    {
                        initMissile(&m);
                        setCaractMap( &(jeu->Map), j , i , c);
                        setNivMissile(&m,num);
                        setPosXMissile(&m, j);
                        setPosYMissile(&m, i);
                        setIdMissile(&m,idm);
                        ajoutMissile(&(jeu->EMA), m);
                        idm++;
                    }
                    break;

                    case 'M':
                    {   initMissile(&m);
                        setIdMissile(&m,idM);
                        setCaractMap( &(jeu->Map), j , i , c);
                        setNivMissile(&m,num);
                        setPosXMissile(&m, j);
                        setPosYMissile(&m, i);
                        ajoutMissile(&(jeu->EMV), m);
                        idM++;

                    }
                    break;

                    case 'N':
                    {
                        initMissile(&m);
                        setIdMissile(&m,idM);
                        setCaractMap( &(jeu->Map), j , i , c);
                        setNivMissile(&m,num);
                        setPosXMissile(&m, j);
                        setPosYMissile(&m, i);
                        ajoutMissile(&(jeu->EMV), m);
                        idM++;
                    }
                    break;

                    case 13:
                    case 10:
                        printf("\nRetFichier\n");
                        break;

                    default: 
                        setCaractMap( &(jeu->Map), j, i , c);
                        break;
                }
               }
              
            fscanf(f,"%c", &c);
        }

        fscanf(f,"sm:%d", &num);
        jeu->supermissile = num;

        fscanf(f,"%c", &c);
        fscanf(f,"niv:%d", &num);
        jeu->niveau = num;

        fscanf(f,"%c", &c);
        fscanf(f,"scr:%d", &num);
        setScore(&(jeu->Scores),num);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegardeMap.txt \n");
    }
    fclose(f);
}

void supprimeSauvegardeMap()
{
    FILE * f;

    f= fopen("./data/sauvegardeMap.txt","w+");

    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier sauvegardeMap.txt \n");
    }
    fclose(f);   
}

void setSuperMissile(jeu *j, int i)
{
    assert(i>=0);
    j->supermissile = i;
}

int getSuperMissile(jeu j)
{
    assert(j.supermissile>=0);
    return j.supermissile;
}

int getNiveauJeu(jeu j)
{
    assert(j.niveau>=0);
    return j.niveau;
}

void augmenterNiveau(jeu *j)
{
    j->niveau++;;
}
