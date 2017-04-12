#include "position.h"
#include <stdio.h>
#include <assert.h>


void initPosition(position *p)
{
    p->x = 0;
    p->y = 0;
}

int getPosX(position p)
{
    assert(p.x >= 0);
    return p.x;
}

int getPosY(position p)
{
    assert(p.y >= 0);
    return p.y;
}

void setPosX(position *p, int x)
{
    assert(x >= 0);
    p->x = x;
}

void setPosY(position *p, int y)
{
    assert(y >= 0);
    p->y = y;
}

int comparePostion (position p1, position p2)
{
    int i=0;
    assert(p1.x >= 0 && p2.y >= 0);
    if ((p1.x == p2.x)&&(p1.y == p2.y))
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
    return i;
}

void testPosition ()
{
    position P1;
    int c,d;
    printf("\n\nTest de regression pour position\n");

    /*Initialise de la position*/
    initPosition(&P1);
    printf("Initialisation : \n");
    printf("X : %d\nY : %d\n",P1.x,P1.y);

    /*modifie X de la position*/
    setPosX(&P1,5);
    printf("SetPosX : \n");
    printf("X : %d\nY : %d\n",P1.x,P1.y);

    /*modifie Y de la position*/
    setPosY(&P1,6);
    printf("SetPosY : \n");
    printf("X : %d\nY : %d\n",P1.x,P1.y);

    /*mets dans c le X de la postion*/
    c = getPosX(P1);
    printf("GetPosX : \n");
    printf("c : %d\n", c);

    /*mets dans d le Y de la postion*/
    d = getPosY(P1);
    printf("GetPosY : \n");
    printf("d : %d\n", d);
}