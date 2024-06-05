#include "landmarkADT.h"
#include <stdlib.h>


typedef struct landmarkType { 
    int dim;            // cantidad de sitios
    char * names[20];   // hasta 20 sitios de interés
} landmarkType;


typedef struct landmarkCDT
{
   landmarkType * v;
   char * ocup; //donde 1 es ocupado y 0 vacio
   size_t dim; //espacio reservado
   size_t count; //cantidad de sitios
   int (*compare) (landmarkType , landmarkType);

}landmarkCDT;




landmarkADT newLandmark(int (*cmp) (landmarkType , landmarkType) )
{
    landmarkADT new = calloc(1 , sizeof(*new));
    new->compare = cmp;
    return new;
}


/**
 * Agrega un punto de interés #site a #meters metros del origen. Si ya había
 * un sitio, sólo queda #site (ver programa de testeo)
 */
void addLandmark(landmarkADT landmark, size_t meters, landmarkType site)
{
    int aux = meters/100;
    int flag = 0;
    if(landmark->dim <= aux)
    {
        landmark->v = realloc(landmark->v, (aux+1) * sizeof(landmarkType));
        landmark->ocup = realloc(landmark->ocup, (aux+1 )* sizeof(char));
        for(int i = landmark->dim ; i < aux+1 ; i++)
        {
            landmark->ocup[i] = 0;
        }
        landmark->dim = aux+1;
    }
    landmark->v[aux] = site;
    if(!landmark->ocup[aux])
    {
        landmark->count++;
        landmark->ocup[aux] = 1;
    }

}

/*
 * Retorna 1 si a esa distancia aproximada hay un sitio de interés. Ejemplo: si
 * meters es 135 retorna 1 si se registró algún sitio de interés entre los 100 y 199   
 * metros), 0 sinó
 */
int hasLandmark(const landmarkADT landmark, size_t meters);

/*
 * Retorna la distancia aproximada en la cual se encuentra el sitio de interés 
 * o -1 si no existe. Ejemplo: si el sitio de interés se indicó que está a 135
 * metros retorna 100, si se indicó a 1240 metros retorna 1200
 */
int distance(const landmarkADT landmark, landmarkType site);

/*
 * Retorna cuántos sitios de interés se registraron
 */
size_t landmarkCount(const landmarkADT landmark)
{
    return landmark->count;
}

/*
 * Retorna un vector con los sitios de interés, en orden ascendente por distancia
 * al origen. Si no hubiera sitios de interés retorna NULL
 */
landmarkType * landmarks(const landmarkADT landmark)
{
    return landmark->v;
}

/*
 * Retorna un vector con los sitios de interés entre dos distancias, 
 * en orden ascendente por distancia al origen, dejando en *dim la cantidad
 * Si from es mayor que to o no hay sitios de interés en ese rango retorna NULL y
 * deja *dim en cero
 */
landmarkType * landmarksBetween(const landmarkADT landmark, size_t from, size_t to, size_t *dim);