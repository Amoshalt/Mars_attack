#include "position.h"
#include "alien.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



void initAlien(alien * a)
{
    a->idAlien=0;
    a->vieAlien=0;
    setPosX(&(a->posAlien), 0);
    setPosY(&(a->posAlien), 0);
}

int getVieAlien(alien a)
{
    assert(a.vieAlien >= 0);
    return a.vieAlien;
}

void setVieAlien(alien *a, int i)
{
    assert(i>=0);
    a->vieAlien=i;
}

position getPosAlien(alien a)
{
    assert(a.posAlien.x >= 0);
    assert(a.posAlien.y >= 0);
    return a.posAlien;
}

int getPosXAlien(alien a)
{
    int x;
    x = getPosX(a.posAlien);
    return x;
}

int getPosYAlien(alien a)
{
    int y;
    y = getPosY(a.posAlien);
    return y;
}
void setPosXAlien(alien * a, int x)
{
    assert(x >= 0);
    setPosX(&(a->posAlien), x);
}

void setPosYAlien(alien * a, int y)
{
    assert(y >= 0);
    setPosY(&(a->posAlien), y);
}

int getIdAlien(alien a)
{
    assert(a.idAlien >= 0);
    return a.idAlien;
}

void setIdAlien(alien * a, int i)
{
    assert(i >= 0);
    a->idAlien=i;
}

alien creationAlien(int id, int vie, int x, int y)
{
    alien A;

    assert(id >= 0);
    setIdAlien(&A, id);

    assert(vie >= 0);
    setVieAlien(&A, vie);

    assert(x >= 0);
    setPosXAlien(&A, x);

    assert(y >= 0);
    setPosYAlien(&A, y);
    return A;
}

void testAlien()
{
    alien a,a2;
    position p1,p2;
    int id,vie, X, Y;
    p1.x=5;
    p1.y=10;

    printf( "\n \n \n Test de régression pour Alien:\n");

    initAlien(&a);
    printf("Initialisation : \n");
    printf("id : %d \nX : %d \nY : %d \nVie : %d \n ",a.idAlien,a.posAlien.x,a.posAlien.y,a.vieAlien);

    setVieAlien(&a,3);
    printf("Modification Nombre de vie : \n");
    printf("id : %d \nVie: %d \n ",a.idAlien,a.vieAlien);

    vie=getVieAlien(a);
    printf("Recuperation Nombre de vie : \n");
    printf("id: %d \nVie : %d \n",a.idAlien,vie);

    p2=getPosAlien(a);
    printf("Recuperation Position: \n");
    printf("X : %d \nY : %d \n ",p2.x,p2.y);

    setPosXAlien(&a,p1.x);
    printf("Modification Position X: \n");
    printf("id : %d \nX : %d \nY : %d \n ",a.idAlien,a.posAlien.x,a.posAlien.y);

    setPosYAlien(&a,p1.y);
    printf("Modification Position Y: \n");
    printf("id : %d \nX : %d \nY : %d \n ",a.idAlien,a.posAlien.x,a.posAlien.y);

    X=getPosXAlien(a);
    Y=getPosYAlien(a);
    printf("Recuperation Position: \n");
    printf("X : %d \nY : %d \n ",X,Y);

    setIdAlien(&a,1);
    printf("Modification Identifiant : \n");
    printf("id : %d \nX : %d \nY : %d \nVie : %d \n ",a.idAlien,a.posAlien.x,a.posAlien.y,a.vieAlien);

    id=getIdAlien(a);
    printf("Recuperation Identifiant: \n");
    printf("id : %d \n",id);

    a2=creationAlien(1,2,3,4);
    printf("Creation d'un alien :\n");
    printf("id : %d \nX : %d \nY : %d \nVie : %d \n ",a2.idAlien,a2.posAlien.x,a2.posAlien.y,a2.vieAlien);
} 