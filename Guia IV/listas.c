#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

node* inicListaL()
{
    return NULL;
}

node* AgregarNodoPrincipio(node * lista, node * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

node * AgregarNodoFinal(node * lista, node* ingresar)
{
    node* seguidora = lista;

    if(lista == NULL)
    {
        lista = ingresar;
    }
    else
    {
        while(seguidora->siguiente != NULL)
        {
            seguidora = seguidora->siguiente;
        }

        seguidora->siguiente = ingresar;
    }

    return lista;
}

node * EncontrarNodoFinal(node * lista)
{
    while(lista->siguiente != NULL)
    {
        lista = lista->siguiente;
    }
    return lista;
}
