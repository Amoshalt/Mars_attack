#include "position.h"
#include "protection.h"
#include "ensembleprotection.h"
#include "map.h"
#include "alien.h"
#include "ensemblealien.h"
#include "missile.h"
#include "ensemblemissile.h"
#include "vaisseau.h"
#include "scores.h"
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    jeu J;
    int i, k, c=0, depMV=0, depMA=0, compteur=0;

    /*Test de regression*/
    testVaisseau();
    testMap();
    testAlien();
    testEnsembleAlien();
    testProtection();
    testEnsembleProtection();
    testMissile();
    testEnsembleMissile();

    printf("\n\nEntrez un entier pour passer la version TXT du jeu\n");
    scanf("%d",&k);
   
 
    initJeu(&J);

    for (k=0;k<J.Map.dimy;k++)
    {
        for (i=0;i<J.Map.dimx;i++)
        {
            setCaractMap(&(J.Map),i,k,'#');
        }
    }

    ajoutVaisseau(&J);
    ajoutEnsembleAlien(&J);
    ajoutEnsembleprotection(&J);

    system("clear");
    afficherMap(J);
    while(c!= 8)
    {   
        
        printf("\n8: quitter 1: gauche 3:droite 5:missile 6:supermissile 0: afficher les informations\n");
        scanf("%d", &c);
        
        if(depMV == 1 && c !=0)
        {
            deplacementMissileVaisseau(&J);
        }
        if(c==3)
        {
            deplacementVaisseau(&J,0);
        }
        else if(c==1)
        {
            deplacementVaisseau(&J,1);
        }
        else if (c == 5)
        {
            depMV = 1;
            tirerMissileVaisseau(&J);
        }
        else if (c == 6)
        {
            depMV = 1;
            tirerSuperMissile(&J);
            J.supermissile--;
        }
        else if( c == 0)
        {
            afficherinformation(&J);
        }
        if( compteur%3 == 0)
        {
            depMA = 1;
            tirerMissileAlien(&J);
            deplacementAliens (&J);
        }

        if(depMA == 1 && c !=0)
        {
            deplacementMissileAlien(&J);
        }
        compteur++;
        system("clear");
        afficherMap(J);
    }

    freeJeu(&J);
    return 0; 
}
