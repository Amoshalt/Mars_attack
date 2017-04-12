#include "position.h"
#include "alien.h"
#include "ensemblealien.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void initEnsembleAlien(ensemblealien *EA)
{
    EA->taille = 0;
    EA->capacite = 100;
    EA->tab = (alien*)malloc(sizeof(alien)*(EA->capacite));
    EA->descendu = 1;
    srand(time(NULL));
    EA->direction = rand()%2;
}

void freeEnsembleAlien(ensemblealien *EA)
{
    EA->capacite = 100;
    EA->taille = 0;
    free(EA->tab);
}

void ajoutAlien(ensemblealien *EA, alien a)
{
    assert(EA->capacite >= 0);
    assert(EA->taille >= 0);
    if((EA->capacite)>(EA->taille))
    {
        EA->tab[(EA->taille)] = a;
        (EA->taille)++;
    }
    else
    {
        printf("augmenter la capacité\n");
    }
}

int getNombreAlien(ensemblealien EA)
{
    assert(EA.taille >= 0);
    return EA.taille;
}

void suppAlienId(ensemblealien *EA, int ID)
{
    int i=0,j, idAlien=0;
    idAlien = getIdAlien(EA->tab[0]);
    while(idAlien != ID)
    {
        i++;
        idAlien = getIdAlien(EA->tab[i]);
    }
    for(j=i;j<EA->taille-1;j++)
    {
        (EA->tab[i])=(EA->tab[j+1]);
        i++;
    }
    initAlien(&EA->tab[j]);
    EA->taille--;
}

void suppEnsembleAlien(ensemblealien *EA)
{
    int i;
    for(i=0; i<EA->taille; i++)
    {
        initAlien(&EA->tab[i]);
    }
    EA->taille= 0;
}

void setPosXIemeAlien(ensemblealien *EA, int i, int x)
{
    setPosXAlien(&(EA->tab[i]), x);
}

void setPosYIemeAlien(ensemblealien *EA, int i, int y)
{
    setPosYAlien(&(EA->tab[i]), y);
}

position getPosIemeAlien(ensemblealien EA, int i)
{
    position pos;
    pos = getPosAlien(EA.tab[i]);
    return pos;
}

int getPosXIemeAlien(ensemblealien EA, int i)
{
    int x;
    x = getPosXAlien(EA.tab[i]);
    return x;
}

int getPosYIemeAlien(ensemblealien EA, int i)
{
    int y;
    y = getPosYAlien(EA.tab[i]);
    return y;
}


int getVieAlienPosition(ensemblealien EA, int x, int y)
{
    int vie=0,i;
    position P, posAlien;
    P.x = x;
    P.y = y;
    for (i = 0; i<EA.taille; i++)
    {
        posAlien = getPosAlien(EA.tab[i]);
        if (comparePostion(posAlien, P) == 1)
        {
            vie = getVieAlien(EA.tab[i]);
        }
    }
    return vie;
}


int getIdAlienPosition(ensemblealien EA, position P)
{
    int i=0, idAlien=0;
    position posAlien;
    posAlien = getPosAlien(EA.tab[0]);
    while(idAlien != -1 && (comparePostion(posAlien, P) != 1))
    {
        assert(i<EA.taille-1);
        i++;
        posAlien = getPosAlien(EA.tab[i]);
    }
    idAlien = getIdAlien(EA.tab[i]);
    return idAlien;
}

int getVieIemeAlien(ensemblealien EA, int i)
{
    int vie;
    vie = getVieAlien(EA.tab[i]);
    return vie;
}

int suppVieAlienID(ensemblealien *EA, int id)
{
    int i=0,aliensupprime=0, idAlien, vieAlien;
    idAlien = getIdAlien(EA->tab[0]);

    while(idAlien != id)
    {
        i++;
        idAlien = getIdAlien(EA->tab[i]);
    }
    vieAlien = getVieAlien(EA->tab[i]);
    if (vieAlien-1 == 0)
    {
        suppAlienId(EA, id);
        aliensupprime = 1;
    }
    else
    {
        setVieAlien(&(EA->tab[i]),vieAlien-1 );
    }
    return aliensupprime;
}

int suppVieAlienPosition(ensemblealien *EA, position P)
{
    int idAlien, aliensupp=0;
    idAlien = getIdAlienPosition(*EA, P);
    aliensupp = suppVieAlienID(EA, idAlien);
    return aliensupp;
}

int getDirectionAlien(ensemblealien EA)
{
    int i; 
    i = EA.direction;
    return i;
}

int getDescenduAlien(ensemblealien EA)
{
    int i; 
    i = EA.descendu;
    return i;
}

void setDirectionAlien(ensemblealien *EA, int i)
{
    assert(i>=0); 
    EA->direction = i;
}

void setDescenduAlien(ensemblealien *EA, int i)
{
    assert(i>=0); 
    EA->descendu = i;
}

void testEnsembleAlien()
{
    ensemblealien ea;
    alien A1,A2,A3;
    int idA, suppression1,suppression2, nbAlien, vie, X, Y, direction, descendu;
    position P1, P2,P3;
    P1.x = 1;
    P1.y = 1;
    P2.x = 2;
    P2.y = 2;
    P3.x = 3;
    P3.y = 3;
    printf("Test de regression sur EnsembleAlien");

    initAlien(&A1);
    setIdAlien(&A1,4);
    setPosXAlien(&A1,P1.x);
    setPosYAlien(&A1,P1.y);
    setVieAlien(&A1, 1);
    initAlien(&A2);
    setIdAlien(&A2,2);
    setPosXAlien(&A2,P2.x);
    setPosYAlien(&A2,P2.y);
    setVieAlien(&A2, 3);
    initAlien(&A3);
    setIdAlien(&A3,8);
    setPosXAlien(&A3,P3.x);
    setPosYAlien(&A3,P3.y);
    setVieAlien(&A3, 2);
    
    printf("Alien1 : \n");
    printf("id : %d\nVie : %d\nX : %d\nY : %d\n",A1.idAlien, A1.vieAlien, A1.posAlien.x, A1.posAlien.y);
    printf("\nAlien2 : \n");
    printf("id : %d\nVie : %d\nX : %d\nY : %d\n",A2.idAlien, A2.vieAlien, A2.posAlien.x, A2.posAlien.y);
    printf("\nAlien3 : \n");
    printf("id : %d\nVie : %d\nX : %d\nY : %d\n",A3.idAlien, A3.vieAlien, A3.posAlien.x, A3.posAlien.y);

    initEnsembleAlien(&ea);
    printf("\nInitialisation : \n");
    printf("taille : %d\ncapacite : %d\n",ea.taille,ea.capacite);

    ajoutAlien(&ea, A1);
    ajoutAlien(&ea, A2);
    ajoutAlien(&ea, A3);
    printf("\najoutAlien : \n");
    printf("id : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[0].idAlien, ea.tab[0].vieAlien, ea.tab[0].posAlien.x, ea.tab[0].posAlien.y);
    printf("\nid : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[1].idAlien, ea.tab[1].vieAlien, ea.tab[1].posAlien.x, ea.tab[1].posAlien.y);
    printf("\nid : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[2].idAlien, ea.tab[2].vieAlien, ea.tab[2].posAlien.x, ea.tab[2].posAlien.y);

    nbAlien = getNombreAlien(ea);
    printf("\nNombre d'alien : %d\n",nbAlien);

    suppAlienId(&ea,2);
    printf("\nsuppAlienId : \n");
    printf("id : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[0].idAlien, ea.tab[0].vieAlien, ea.tab[0].posAlien.x, ea.tab[0].posAlien.y);
    printf("\nid : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[1].idAlien, ea.tab[1].vieAlien, ea.tab[1].posAlien.x, ea.tab[1].posAlien.y);
    printf("\nid : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[2].idAlien, ea.tab[2].vieAlien, ea.tab[2].posAlien.x, ea.tab[2].posAlien.y);

    nbAlien = getNombreAlien(ea);
    printf("\nNouveau nombre d'alien : %d\n",nbAlien);

    setPosXIemeAlien(&ea, 0, 4);
    setPosYIemeAlien(&ea, 0, 4);
    X=getPosYIemeAlien(ea,0);
    Y=getPosXIemeAlien(ea,0);
    printf("\nModification de la position de l'alien 0 avec la position (4,4): \n");
    printf("X : %d\nY : %d\n",X,Y);
    printf("\nid : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[0].idAlien, ea.tab[0].vieAlien, ea.tab[0].posAlien.x, ea.tab[0].posAlien.y);
    printf("\nid : %d\nVie : %d\nX : %d\nY : %d\n",ea.tab[1].idAlien, ea.tab[1].vieAlien, ea.tab[1].posAlien.x, ea.tab[1].posAlien.y);

    idA=getIdAlienPosition(ea,P3);
    printf("\nAlien a la position : (%d,%d)\nId : %d\n", P3.x,P3.y,idA);

    vie = getVieAlienPosition(ea, 4, 4);
    printf("\nVie de l'alien (4,4) : %d\n", vie);

    vie = getVieIemeAlien(ea, 0);
    printf("\nVie de l'alien 0 : %d\n", vie);

    suppression1=suppVieAlienID(&ea,4);
    printf("\nSuppression vie alien id : 4 \nalien supprime? %d\n",suppression1);
    
    suppression2=suppVieAlienPosition(&ea,P3);
    printf("\nSuppression vie alien a la position : (%d,%d)\nalien supprime? %d\n",P3.x,P3.y,suppression2);

    setDirectionAlien(&ea, 1);
    setDescenduAlien(&ea, 1);
    direction=getDirectionAlien(ea);
    descendu=getDescenduAlien(ea);
    printf("\ndirection  : %d\ndescendu :  %d\n",direction, descendu);
    
    suppEnsembleAlien(&ea);
    freeEnsembleAlien(&ea);
}
