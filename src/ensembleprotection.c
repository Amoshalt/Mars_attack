#include "position.h"
#include "protection.h"
#include "ensembleprotection.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initEnsembleProtection(ensembleprotection *EP)
{
    EP->taille = 0;
    EP->capacite = 100;
    EP->tab = (protection*)malloc(sizeof(protection)*(EP->capacite));
}

void freeEnsembleProtection(ensembleprotection *EP)
{
    EP->capacite = 100;
    EP->taille = 0;
    free(EP->tab);
}

void ajoutProtection(ensembleprotection *EP, protection p)
{
    assert(EP->capacite >= 0);
    assert(EP->taille >= 0);
    if((EP->capacite)>(EP->taille))
    {
        EP->tab[(EP->taille)] = p;
        (EP->taille)++;
    }
    else
    {
        printf("augmenter la capacité\n");
    }
}

void suppProtectionId(ensembleprotection *EP, int ID)
{
    int i=0,j, idProtection=0;
    idProtection = getIdProtection(EP->tab[0]);
    while(idProtection != ID)
    {
        i++;
        idProtection = getIdProtection(EP->tab[i]);
    }
    for(j=i;j<EP->taille-1;j++)
    {
        (EP->tab[i])=(EP->tab[j+1]);
        i++;
    }
    initProtection(&EP->tab[j]);
    EP->taille--;
}

void suppEnsembleProtection(ensembleprotection *EP)
{
    int i;
    for(i=0; i<EP->taille; i++)
    {
        initProtection(&EP->tab[i]);
    }
    EP->taille= 0;
}

int getIdProtectionPosition(ensembleprotection EP, position P)
{
    int i=0, idProtection=0;
    position posProtection;
    posProtection = getPosProtection(EP.tab[0]);
    while(comparePostion(posProtection, P) != 1)
    {
        assert(i<EP.taille-1);
        i++;
        posProtection = getPosProtection(EP.tab[i]);
    }
    idProtection = getIdProtection(EP.tab[i]);
    return idProtection;
}

int suppVieProtectionID(ensembleprotection *EP, int id)
{
    int i=0,protectionsupprime=0, idProtection, vieProtection;
    idProtection = getIdProtection(EP->tab[0]);
    while(idProtection != id)
    {
        i++;
        idProtection = getIdProtection(EP->tab[i]);
    }
    vieProtection = getVieProtection(EP->tab[i]);
    if (vieProtection-1 == 0)
    {
        suppProtectionId(EP, id);
        protectionsupprime = 1;
    }
    else
    {
        setVieProtection(&(EP->tab[i]), vieProtection-1);
    }
    return protectionsupprime;
}

int suppVieProtectionPosition(ensembleprotection *EP, position P)
{
    int idProtection, protectionsupp=0;
    idProtection = getIdProtectionPosition(*EP, P);
    protectionsupp = suppVieProtectionID(EP, idProtection);
    return protectionsupp;
}

void testEnsembleProtection()
{
    ensembleprotection ep;
    protection P1,P2,P3;
    position pos1;
    int idP,suppression1,suppression2;
    pos1.x=2;
    pos1.y=2;
    printf("\n\nTest de regression pour ensembleprotection\n");

    /*initialise, remplit et affiche 3 protections*/
    initProtection(&P1);
    setIdProtection(&P1,4);
    setPosProtection(&P1, 1,1);
    setVieProtection(&P1, 1);

    initProtection(&P2);
    setIdProtection(&P2,2);
    setPosProtection(&P2, 2,2);
    setVieProtection(&P2, 2);

    initProtection(&P3);
    setIdProtection(&P3,1);
    setPosProtection(&P3, 3,3);
    setVieProtection(&P3, 3);

    printf("Protection1 : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",P1.idProtection,P1.posProtection.x,P1.posProtection.y,P1.vieProtection);

    printf("Protection2 : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",P2.idProtection,P2.posProtection.x,P2.posProtection.y,P2.vieProtection);

    printf("Protection3 : \n");
    printf("id : %d\nX : %d\nY : %d\nVie : %d\n",P3.idProtection,P3.posProtection.x,P3.posProtection.y,P3.vieProtection);

    /*initialise l'ensemble de protection*/
    initEnsembleProtection(&ep);
    printf("\nInitialisation : \n");
    printf("taille : %d\ncapacite : %d\n",ep.taille,ep.capacite);

    /*ajout les 3 protections dans l'ensemble*/
    ajoutProtection(&ep, P1);
    ajoutProtection(&ep, P2);
    ajoutProtection(&ep, P3);
    printf("\najoutProtection : \n");
    printf("taille : %d\ncapacite : %d\nid : %d\nX : %d\nY : %d\nVie : %d\n",ep.taille,ep.capacite,ep.tab[0].idProtection,ep.tab[0].posProtection.x, ep.tab[0].posProtection.y, ep.tab[0].vieProtection);
    printf("\nid : %d\nX : %d\nY : %d\nVie : %d\n",ep.tab[1].idProtection,ep.tab[1].posProtection.x, ep.tab[1].posProtection.y, ep.tab[1].vieProtection);
    printf("\nid : %d\nX : %d\nY : %d\nVie : %d\n",ep.tab[2].idProtection,ep.tab[2].posProtection.x, ep.tab[2].posProtection.y, ep.tab[2].vieProtection);

    /*Récupere l'identifiant de la protection à pos1*/
    idP=getIdProtectionPosition(ep,pos1);
    printf("\n Protection a la position (%d,%d)\nid: %d\n", pos1.x,pos1.y,idP);

    /*supprime une vie a la protection et dit si la protection est supprimé*/
    suppression1=suppVieProtectionID(&ep,1);
    printf("\n Supprime vie");
    printf("\nProtection avec id:1\n supprime protection? %d\n",suppression1);

    /*supprime une vie a la protection et dit si la protection est supprimé*/
    suppression2=suppVieProtectionPosition(&ep,pos1);
    printf("\n Supprime vie");
    printf("\n Protection a la position (%d,%d)\nsupprime protection? %d\n", pos1.x,pos1.y,suppression2);

    /*supprime la protection avec l'identifiant 4*/
    suppProtectionId(&ep,4);
    printf("\nsuppProtectionId : \n");
    printf("taille : %d\ncapacite : %d\nid : %d\nX : %d\nY : %d\nVie : %d\n",ep.taille,ep.capacite,ep.tab[0].idProtection,ep.tab[0].posProtection.x, ep.tab[0].posProtection.y, ep.tab[0].vieProtection);
    printf("\nid : %d\nX : %d\nY : %d\nVie : %d\n",ep.tab[1].idProtection,ep.tab[1].posProtection.x, ep.tab[1].posProtection.y, ep.tab[1].vieProtection);
    printf("\nid : %d\nX : %d\nY : %d\nVie : %d\n",ep.tab[2].idProtection,ep.tab[2].posProtection.x, ep.tab[2].posProtection.y, ep.tab[2].vieProtection);

    /*supprime l'ensemble de protection*/
    suppEnsembleProtection(&ep);

    /*libère la mémoire*/
    freeEnsembleProtection(&ep);
}
