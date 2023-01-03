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

node* CrearNodo(int dato)
{
    node* lista = (node*)malloc(sizeof(node));

    lista->siguiente = NULL;
    lista->dato = dato;

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

void MostrarLista(node* lista)
{
    while(lista != NULL)
    {
        printf("| %d |\n", lista->dato);
        lista = lista->siguiente;
    }
}

int ContarElementosLista(node* lista)
{
    int i = 0;
    while(lista != NULL)
    {
        i++;
    }
    return i;
}
