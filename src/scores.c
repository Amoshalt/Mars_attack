#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "scores.h"



void initMeilleurScore(scores * s)
{
    FILE * f=NULL;
    int nMS;
    f= fopen("./data/sauvegardeMS.txt","r");
    if(f!=NULL)
    {
        fscanf(f,"MS=%d;",&nMS);
        assert (nMS>=0);
        s->MeilleurScore=nMS;
    }
    else
    {
        printf("Erreur de chargement du meilleur score, le meilleur score sera remis à 0");
        s->MeilleurScore=0;
    }
    fclose(f);
}

void initScore(scores * s)
{
    s->Score=0;
}

void initScores(scores * s)
{
    initMeilleurScore(s);
    initScore(s);
}

void setMeilleurScore(scores * s)
{
    FILE * f=NULL;
    int MS=0;
    f= fopen("./data/sauvegardeMS.txt","r+");
    if (f != NULL)
    {
        fscanf(f, "MS= %i;", &MS);
        rewind(f);
        if (MS<s->Score)
        {
            fprintf(f,"MS=%d;",s->Score);
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegardeMS.txt \n");
    }
    fclose(f);
}

void ajoutScore(scores * s, int i)
{
    assert(i>=0);
    s->Score = s->Score + i;
}

void setScore(scores * s, int i)
{
    assert (i>=0);
    s->Score=i;
}

int getMeilleurScore(scores  s)
{
    assert(s.MeilleurScore >= 0);
    return s.MeilleurScore;
}

int getScore(scores s)
{
    assert(s.Score >= 0);
    return s.Score;
}

void initSauvegarde()
{
    FILE * f=NULL;
    f= fopen("./data/sauvegardeMS.txt","w+");
    if (f != NULL)
    {

        fprintf(f,"MS=%d;",0);
        
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegardeMS.txt \n");

    }
    fclose(f);
}
