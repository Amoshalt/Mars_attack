#include "position.h"
#include "protection.h"
#include <stdio.h>
#include <assert.h>

void initProtection(protection *p)
{
    p->idProtection = 0;
    initPosition(&(p->posProtection));
    p->vieProtection = 0;
}

void setIdProtection(protection *p, int i)
{
    assert(i >= 0);
    p->idProtection = i;
}

int getIdProtection(protection p)
{
    assert(p.idProtection >= 0);
    return p.idProtection;
}

position getPosProtection(protection p)
{
    assert(p.posProtection.x >= 0);
    assert(p.posProtection.y >= 0);
    return p.posProtection;
}

void setPosProtection(protection *p, int x, int y)
{
    assert(x >= 0);
    assert(y >= 0);
    setPosX(&(p->posProtection), x);
    setPosY(&(p->posProtection), y);
}

int getVieProtection(protection p)
{
    assert(p.vieProtection >= 0);
    return p.vieProtection;
}

void setVieProtection(protection *p, int i)
{
    assert(i >= 0);
    p->vieProtection = i;
}

protection creationProtection(int id, int vie, int x, int y)
{
    protection P;
    
    assert(id >= 0);
    setIdProtection(&P, id);

    assert(vie >= 0);
    setVieProtection(&P, vie);

    assert(x >= 0 && y >= 0);
    setPosProtection(&P, x, y);

    return P;
}

void testProtection ()
{
    protection pro1,pro2;
    position P1;
    int b,a;
    printf("\n\nTest de regression pour protection\n");

    /*Initialise la protection*/
    initProtection(&pro1);
    printf("\nInitialisation : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",pro1.idProtection,pro1.posProtection.x,pro1.posProtection.y,pro1.vieProtection);

    /*modifie l'id de la protection*/
    setIdProtection(&pro1,4);
    printf("\nsetIdProtection : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",pro1.idProtection,pro1.posProtection.x,pro1.posProtection.y,pro1.vieProtection);

    /*mets dans b l'id de la protection*/
    b = getIdProtection(pro1);
    printf("\ngetIdProtection : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",b,pro1.posProtection.x,pro1.posProtection.y,pro1.vieProtection);

    /*modifie la position de la protection*/
    setPosProtection(&pro1, 2,3);
    printf("\nsetPosProtection : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",pro1.idProtection,pro1.posProtection.x,pro1.posProtection.y,pro1.vieProtection);

    /*mets dans P1 la position de la protection*/
    P1 = getPosProtection(pro1);
    printf("\ngetPosProtection : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",pro1.idProtection,P1.x,P1.y,pro1.vieProtection);

    /*modifie la vie de la protection*/
    setVieProtection(&pro1, 5);
    printf("\nsetVieProtection : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",pro1.idProtection,pro1.posProtection.x,pro1.posProtection.y,pro1.vieProtection);

    /*mets dans a la vie de la protection*/
    a = getVieProtection(pro1);
    printf("\ngetVieProtection : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",pro1.idProtection,P1.x,P1.y,a);

    /*crée une nouvelle protection*/
    pro2=creationProtection(2,3,2,2);
    printf("\nNouvelle Protection: \nid : %d\nX : %d\nY : %d\nVie : %d\n",pro2.idProtection,pro2.posProtection.x,pro2.posProtection.y,pro2.vieProtection);
    
}