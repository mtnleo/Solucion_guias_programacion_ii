#include <stdio.h>
#include <stdlib.h>
#include "arboles.h"

nodoArbol* inicArbol()
{
    return NULL;
}

nodoArbol* CrearNodoArbol(int dato)
{
    nodoArbol* nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));

    nuevo->dato = dato;
    nuevo->der = inicArbol();
    nuevo->izq = inicArbol();
}

nodoArbol* insertarNodo(nodoArbol* arbol, int dato)
{
    if(arbol == NULL)
    {
        arbol = CrearNodoArbol(dato);
    }
    else
    {
        if(arbol->dato > dato)
        {
            arbol->izq = insertarNodo(arbol->izq, dato);
        }
        else
        {
            arbol->der = insertarNodo(arbol->der, dato);
        }
    }
    return arbol;
}

nodoArbol* buscar(nodoArbol* arbol, int dato)
{
    nodoArbol* buscado = inicArbol();
    if(arbol != NULL)
    {
        if(arbol->dato == dato)
        {
            buscado = arbol;
        }
        else if(arbol->dato > dato)
        {
            buscado = buscar(arbol->izq, dato);
        }
        else
        {
            buscado = buscar(arbol->der, dato);
        }
    }
    return buscado;
}

void preorder(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        printf("| %d | ", arbol->dato);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->izq);
        printf("| %d | ", arbol->dato);
        inorder(arbol->der);
    }
}

void posorder(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        posorder(arbol->izq);
        posorder(arbol->der);
        printf("| %d | ", arbol->dato);
    }
}

/*
nodoArbol* borrarArbol(nodoArbol* arbol, int borrar)
{
    if(arbol != NULL)
    {
        if(arbol->dato == borrar)
        {
            arbol = inicArbol();
        }
        else if()
        {

        }
        else
        {

        }
    }
    return arbol;
}
*/
