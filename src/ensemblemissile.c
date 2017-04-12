#include "position.h"
#include "missile.h"
#include "ensemblemissile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initEnsembleMissile(ensemblemissile *EM)
{
    EM->taille = 0;
    EM->capacite = 100;
    EM->tab = (missile*)malloc(sizeof(missile)*(EM->capacite));
}

void freeEnsembleMissile(ensemblemissile *EM)
{
    EM->capacite = 100;
    EM->taille = 0;
    free(EM->tab);
}

void ajoutMissile(ensemblemissile *EM, missile m)
{
    assert(EM->capacite >= 0);
    assert(EM->taille >= 0);
    if((EM->capacite)>(EM->taille))
    {
        EM->tab[(EM->taille)] = m;
        (EM->taille)++;
    }
    else
    {
        printf("augmenter la capacité\n");
    }
}

int getNombreMissile(ensemblemissile EM)
{
    assert(EM.taille >= 0);
    return EM.taille;
}

int getPosXIemeMissile(ensemblemissile EM, int i)
{
    int x;
    x = getPosXMissile(EM.tab[i]);
    return x;
}

int getPosYIemeMissile(ensemblemissile EM, int i)
{
    int y;
    y = getPosYMissile(EM.tab[i]);
    return y;
}

void setPosXIemeMissile(ensemblemissile *EM, int i, int x)
{
    setPosXMissile(&(EM->tab[i]), x);
}

void setPosYIemeMissile(ensemblemissile *EM, int i, int y)
{
    setPosYMissile(&(EM->tab[i]), y);
}

position getPosIemeMissile(ensemblemissile EM, int i)
{
    position pos;
    pos = getPosMissile(EM.tab[i]);
    return pos;
}

int getNiveauIemeMissile(ensemblemissile EM, int i)
{
    int y;
    y = getNivMissile(EM.tab[i]);
    return y;
}
void supprimerIemeMissile(ensemblemissile *EM, int i)
{
    int j;
    for(j=i;j<(EM->taille)-1;j++)
    {
        (EM->tab[i])=(EM->tab[j+1]);
        i++;
    }
    suppMissile(&EM->tab[j]);
    EM->taille--;
}

void supprimerMissilePosition(ensemblemissile *EM, position P)
{
    int j;
    position posMissile;

    for(j=0;j<(EM->taille);j++)
    {
        posMissile = getPosMissile(EM->tab[j]);
        if (comparePostion(posMissile, P))
        {
            supprimerIemeMissile(EM, j);
        }
    }
}

int getNiveauMissilePosition(ensemblemissile EM, position P)
{
    int niv;
    missile M;
    M = getMissilePosition(EM, P);
    niv = M.nivMissile;
    return niv;
}
void suppEnsembleMissile(ensemblemissile *EM)
{
    int i;
    for(i=0; i<EM->taille; i++)
    {
        suppMissile(&EM->tab[i]);
    }
    EM->taille= 0;
}


missile getIemeMissile(ensemblemissile EM, int i)
{
    missile M;
    M = EM.tab[i];
    return M;
}

int MissilePosition(ensemblemissile EM, position P)
{
    int i=0, reponse=0;
    position posMissile;
    if (EM.taille > 0)
    {
        while(i<EM.taille && reponse !=1)
        {
            posMissile = getPosMissile(EM.tab[i]);
            if (comparePostion(posMissile, P) == 1)
            {
                reponse = 1;
            }
            else
            {
                reponse = 0;
            } 
            i++;
        }
    }
    else
    {
        reponse = 0;
    }
    return reponse;
}

missile getMissilePosition(ensemblemissile EM, position P)
{
    int i=0;
    missile M;
    position posMissile;
    posMissile = getPosMissile(EM.tab[0]);
    while(comparePostion(posMissile, P) != 1)
    {
        if (i < EM.taille-1)
        {
            i++;
        }
        else
        {
            printf("aucun missile à cette position\n");
        }
        posMissile = getPosMissile(EM.tab[i]);   
    }
    M = EM.tab[i];
    return M;
}

void testEnsembleMissile()
{
    int posX, posY,l, niv, resultat, nbMissile;
    position pos;
    missile mis, m1,m2,m3;
    ensemblemissile em;

    m1.idMissile= 0;
    m1.posMissile.x=0;
    m1.posMissile.y=0;
    m1.nivMissile=1;

    m2.idMissile= 1;
    m2.posMissile.x=1;
    m2.posMissile.y=1;
    m2.nivMissile=1;

    m3.idMissile= 2;
    m3.posMissile.x=2;
    m3.posMissile.y=2;
    m3.nivMissile=2;

    printf("\n\n Test de regression de ensemblemissile \n\n");
    initEnsembleMissile(&em);
    ajoutMissile(&em,m1);
    ajoutMissile(&em,m2);
    ajoutMissile(&em,m3);

    printf("\nAjout de missiles :\n");
    printf("Capacite : %d \nTaille : %d\n",em.capacite, em.taille);
    for(l=0;l<em.taille;l++)
    {
        printf("\nMissile %d\n", l+1);
        printf("id : %d \nX : %d \nY : %d \nNiveau : %d\n",em.tab[l].idMissile,em.tab[l].posMissile.x,em.tab[l].posMissile.y, em.tab[l].nivMissile);
    }

    nbMissile = getNombreMissile(em);
    printf("\nGetNombreMissile : %d\n", nbMissile);

    setPosXIemeMissile(&em, 1, 5);
    printf("SetPosXIemeMissile (i=1 et X=5)\n");

    setPosYIemeMissile(&em, 1, 5);
    printf("SetPosYIemeMissile (i=1 et Y=5)\n");

    posX = getPosXIemeMissile(em, 1);
    printf("\ngetPosXIemeMissile (i=1) : %d\n", posX);

    posY = getPosYIemeMissile(em, 1);
    printf("\ngetPosYIemeMissile (i=1) : %d\n", posY);

    pos = getPosIemeMissile(em, 0);
    printf("\ngetPosIemeMissile (i=0) : (%d;%d)\n", pos.x, pos.y);

    niv = getNiveauIemeMissile(em, 2);
    printf("\ngetNiveauIemeMissile (i=2) : %d\n", niv);

    niv = getNiveauMissilePosition(em, pos);
    printf("\ngetNiveauMissilePosition (X=%d;Y=%d) : %d\n",pos.x, pos.y, niv);

    mis = getIemeMissile(em, 1);
    printf("\ngetIemeMissile (i=1) :\n");
    printf("id : %d \nX : %d \nY : %d \nNiveau : %d\n",mis.idMissile,mis.posMissile.x,mis.posMissile.y, mis.nivMissile);

    mis = getMissilePosition(em, pos);
    printf("\ngetMissilePosition (X=%d;Y=%d) :\n", pos.x, pos.y);
    printf("id : %d \nX : %d \nY : %d \nNiveau : %d\n",mis.idMissile,mis.posMissile.x,mis.posMissile.y, mis.nivMissile);

    resultat = MissilePosition(em, pos);
    printf("\nMissilePosition (X=%d;Y=%d) : %d\n",pos.x, pos.y,resultat);

    supprimerIemeMissile(&em, 1);
    printf("\nsupprimerIemeMissile : (i=1)\nTaille : %d\n", em.taille);

    supprimerMissilePosition(&em, pos);
    printf("\nsupprimerMissilePosition : (x=%d;Y=%d)\nTaille : %d\n",pos.x,pos.y, em.taille);

    suppEnsembleMissile(&em);
    printf("\nsupprimerEnsembleMissile :\nTaille : %d\n", em.taille);

    freeEnsembleMissile(&em);
}
