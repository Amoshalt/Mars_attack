#include "position.h"
#include "vaisseau.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initVaisseau(vaisseau * v)
{
    v->idVaisseau = 0;
    v->vieVaisseau = 0;
    v->posVaisseau.x = 0;
    v->posVaisseau.y = 0;
}

int getVieVaisseau(vaisseau v)
{
    assert(v.vieVaisseau >= 0);
    return v.vieVaisseau;
}

void setVieVaisseau(vaisseau *v, int i)
{
    assert(i >= 0);
    v->vieVaisseau=i;
}

position getPosVaisseau(vaisseau v)
{
    position pos;

    pos = v.posVaisseau;
    assert(pos.x >= 0);
    assert(pos.y >= 0);

    return v.posVaisseau;
}

int getPosXVaisseau(vaisseau v)
{
    int x;
    x = getPosX(v.posVaisseau);
    return x;
}

int getPosYVaisseau(vaisseau v)
{
    int y;
    y = getPosY(v.posVaisseau);
    return y;
}

void setPosXVaisseau(vaisseau * v, int x)
{
    assert(x >= 0);
    setPosX(&(v->posVaisseau), x);
}

void setPosYVaisseau(vaisseau * v, int y)
{
    assert(y >= 0);
    setPosY(&(v->posVaisseau), y);
}

int getIdVaisseau(vaisseau v)
{
    assert(v.idVaisseau >= 0);
    return v.idVaisseau;
}

void setIdVaisseau(vaisseau * v, int i)
{
    assert(i >= 0);
    v->idVaisseau = i;
}

vaisseau creationVaisseau(int id, int vie, int x, int y)
{
    vaisseau V;

    assert(id >= 0);
    setIdVaisseau(&V, id);

    assert(vie >= 0);
    setVieVaisseau(&V, vie);

    assert(x >= 0);
    setPosXVaisseau(&V, x);

    assert(y >= 0);
    setPosYVaisseau(&V, y);
    return V;
}

int suppVieVaisseau(vaisseau *v)
{
    int def = 0;
    setVieVaisseau(v, v->vieVaisseau - 1);
    if(v->vieVaisseau == 0)
    {
        def = 1;
    }
    return def;
}

void testVaisseau()
{
    vaisseau v1,v2;
    position p1,p2;
    int id,vie, suppression;
    setPosX(&p1,1);
    setPosY(&p1,1);
    
    printf ( "\n \n \n Test de régression pour Vaisseau:\n");

    initVaisseau(&v1);
    printf("\nInitialisation : \n");
    printf("id : %d \nX : %d \nY : %d \nVie : %d \n ",getIdVaisseau(v1),getPosXVaisseau(v1),getPosYVaisseau(v1),getVieVaisseau(v1));

    setPosXVaisseau(&v1,getPosX(p1));
    printf("\nModification Position: \n");
    printf("id : %d \nX : %d \nY : %d \n ",getIdVaisseau(v1),getPosXVaisseau(v1),getPosYVaisseau(v1));

    setPosYVaisseau(&v1,getPosY(p1));
    printf("\nModification Position: \n");
    printf("id : %d \nX : %d \nY : %d \n ",getIdVaisseau(v1),getPosXVaisseau(v1),getPosYVaisseau(v1));

    p2=getPosVaisseau(v1);
    printf("\nRecuperation Position: \n");
    printf("X : %d \nY : %d \n ",getPosX(p2),getPosY(p2));

    setIdVaisseau(&v1,1);
    printf("\nModification Identifiant : \n");
    printf("id : %d \nX : %d \nY : %d \nVie : %d \n ",getIdVaisseau(v1),getPosXVaisseau(v1),getPosYVaisseau(v1),getVieVaisseau(v1));

    id=getIdVaisseau(v1);
    printf("\nRecuperation Identifiant: \n");
    printf("id : %d \n",id);

    setVieVaisseau(&v1,3);
    printf("\nModification Nombre de vie : \n");
    printf("id : %d \nVie: %d \n ",getIdVaisseau(v1),getVieVaisseau(v1));

    vie=getVieVaisseau(v1);
    printf("\nRecuperation Nombre de vie : \n");
    printf("id: %d \nVie : %d \n",getIdVaisseau(v1),vie);

    v2=creationVaisseau(5,2,2,2);
    printf("\nNouveau vaisseau \n id : %d\nX :%d\nY: %d\nVie : %d\n",getIdVaisseau(v2),getPosXVaisseau(v2),getPosYVaisseau(v2),getVieVaisseau(v2));

    suppression=suppVieVaisseau(&v1);
    printf("\nSuppression vie \nid : %d \nX : %d \nY : %d \nVie : %d \nvaisseau supprime? %d\n ",getIdVaisseau(v1),getPosXVaisseau(v1),getPosYVaisseau(v1),getVieVaisseau(v1),suppression);

    

}