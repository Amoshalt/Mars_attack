#include "missile.h"
#include "position.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void initMissile(missile * m)
{
    m->idMissile= 0;
    setPosX(&(m->posMissile), 0);
    setPosY(&(m->posMissile),0);
    m->nivMissile=0;
}

void setPosXMissile(missile * m, int x)
{
    assert(x >= 0);
    setPosX(&(m->posMissile), x);
}

void setPosYMissile(missile * m, int y)
{
    assert(y >= 0);
    setPosY(&(m->posMissile), y);
}

position getPosMissile(missile m)
{
    assert(m.posMissile.x >= 0 && m.posMissile.y >= 0 );
    return m.posMissile;
}

int getPosXMissile(missile m)
{
    int x;
    x = getPosX(m.posMissile);
    return x;
}

int getPosYMissile(missile m)
{
    int y;
    y = getPosY(m.posMissile);
    return y;
}

int getIdMissile(missile m)
{
    assert(m.idMissile >= 0);
    return m.idMissile;
}

void setIdMissile(missile *m , int i)
{
    assert(i >= 0);
    m->idMissile = i;
}

int getNivMissile(missile m)
{
    assert(m.nivMissile>=0);
    return m.nivMissile;
}

void setNivMissile(missile *m, int i)
{
    assert(i > 0);
    m->nivMissile = i;
}

void suppMissile(missile *m)
{
    m->idMissile= 0;
    m->posMissile.x=-1;
    m->posMissile.y=-1;
    m->nivMissile =1;
}

void testMissile()
{
    missile m;
    position posM,newPos;
    int idM,nivM,newId,newNiv, X, Y;
    newId=2;
    newNiv=1;
    newPos.x=2;
    newPos.y=3;
    printf ( "\n \n \nTest de régression pour Missile:\n");

    initMissile(&m);

    /*Modifie l'identifiant du missile avec un nouveau identifiant*/
    setIdMissile(&m,newId);
    setPosXMissile(&m,newPos.x);
    setPosYMissile(&m,newPos.y);
    setNivMissile(&m,newNiv);

    printf("\nMissile : \n");
    printf("id: %d\nposition: (%d,%d)\nniveau: %d\n",m.idMissile,m.posMissile.x,m.posMissile.y,m.nivMissile);

    /*Recupere identifiant du missile*/
    idM=getIdMissile(m);
    printf("\nid du missile : %d \n",idM);

    /*Recupere position du missile*/
    posM=getPosMissile(m);
    printf("\nposition du missile: (%d,%d)\n",posM.x,posM.y);

    X=getPosXMissile(m);
    printf("\nposition X du missile: %d\n",X);

    Y=getPosYMissile(m);
    printf("\nposition Y du missile: %d\n",Y);

    /*Recupere niveau du missile*/
    nivM=getNivMissile(m);
    printf("\nniveau du missile : %d\n",nivM);

    /*supprime missile*/
    suppMissile(&m);
}
