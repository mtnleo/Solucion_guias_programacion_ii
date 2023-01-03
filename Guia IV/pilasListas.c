#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "pilasListas.h"

nodo* CrearNodoPila(int dato)
{
    nodo * nuevo = (nodo*) malloc(sizeof(nodo));

    nuevo->dato = dato;
    nuevo->siguiente = NULL;

    return nuevo;
}

void inicPila(Pila *dada)
{
    dada->lista = inicListaL();
}

void Apilar(Pila *dada, int dato)
{
    nodo* lista = CrearNodoPila(dato);
    dada->lista = AgregarNodoPrincipio(dada->lista, lista);
}

int Desapilar(Pila *dada)
{
    int dato = dada->lista->dato;
    dada->lista = dada->lista->siguiente;
    return dato;
}

int pilaVacia(Pila dada)
{
    int vacia;

    if(dada.lista == NULL)
    {
        vacia = 1;
    }
    else
    {
        vacia = 0;
    }

    return vacia;
}

void Mostrar(Pila dada)
{
    printf("/-- TOPE --\ \n");
    while(!pilaVacia(dada))
    {
        printf("   | %d |\n", Desapilar(&dada));

    }
    printf("\-- BASE --/ \n");
}

void Leer(Pila *dada)
{
    int dato;

    printf(">Escriba un numero a agregar a la Pila: ");
    scanf("%d", &dato);

    Apilar(dada, dato);
}

int Tope(Pila dada)
{
    int dato = dada.lista->dato;
    return dato;
}
