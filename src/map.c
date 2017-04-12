#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



void initMap (map * m,int x,int y)
{
    int i;
    setDimXMap( m, x);
    setDimYMap( m, y);
    m->tab=(char **) malloc((m->dimx)*sizeof(char *)); /* Declaration de la première dimension du tableau*/
    for(i = 0; i < m->dimx; i++)
    {
        m->tab[i]=(char *) malloc((m->dimy)*sizeof(char)); /* Declaration de la deuxième dimension du tableau*/
    } 
}

void freeMap(map * m)
{
    int i;
    for( i = 0; i < m->dimx; i++)
    { 
        free(m->tab[i]);
    }
    setDimXMap( m, 0);
    setDimYMap( m, 0);
    free(m->tab);
}

char getCaractMap(map m,int x, int y)
{
    assert (x >= 0 && x < m.dimx);
    assert (y >= 0 && y < m.dimy);
    return m.tab[x][y];
}

void setCaractMap(map *m, int x, int y, char c)
{
    assert (x >= 0 && x < (m->dimx));
    assert (y >= 0 && y < (m->dimy));
    m->tab[x][y]=c;
}

int getDimXMap(map m)
{
    assert(m.dimx >= 0);
    return m.dimx;
}

int getDimYMap(map m)
{
    assert(m.dimy >= 0);
    return m.dimy;
}

void setDimYMap(map * m, int y)
{
    assert( y >= 0);
    m->dimy = y;
}

void setDimXMap(map * m, int x)
{
    assert( x >= 0);
    m->dimx = x;
}

void testMap()
{
    map m;
    int i,j;

    printf ( "Test de régression pour map:\n");
    initMap(&m,30,30);
    printf("dimx et dimy de map après initmap\n");
    printf("-dimx: %i \n", m.dimx);
    printf("-dimy: %i \n", m.dimy);
    printf("On change tout les caractères de la map par # \n");
    for (i=0;i<m.dimy;i++)
    {
        for(j=0;j<m.dimx;j++)
        {
            setCaractMap(&m,j,i,'#');
        }
    }
    printf("Voici la map:\n");
    for (i=0;i<m.dimy;i++)
    {
        for(j=0;j<m.dimx;j++)
        {
           printf(" %c ",m.tab[j][i]);
        }
        printf("\n");
    }
    printf("On change le caractère # ligne 2 et colonne 4 par un & \n");
    setCaractMap(&m,3,1,'&');
    printf("Voici la map après le changement de caractère: \n");
    for (i=0;i<m.dimy;i++)
    {
        for(j=0;j<m.dimx;j++)
        {
           printf(" %c ",m.tab[j][i]);
        }
        printf("\n");

    }
    freeMap(&m);
    for (i=0;i<m.dimy;i++)
    {
        for(j=0;j<m.dimx;j++)
        {
           printf(" %c ",m.tab[j][i]);
        }
        printf("\n");
    }
    printf("Après free de map: \n -dimx: %i, \n -dimy: %i, \n", m.dimx,m.dimy);
}
