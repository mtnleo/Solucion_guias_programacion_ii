#ifndef PILASLISTAS_H_INCLUDED
#define PILASLISTAS_H_INCLUDED
#include "listas.h"

typedef struct
{
    int dato;
    struct nodo * siguiente;
} nodo;

typedef struct
{
    nodo * lista;
} Pila;
nodo* CrearNodoPila(int dato);
void inicPila(Pila *dada);
int Desapilar(Pila *dada);
int pilaVacia(Pila dada);
void Mostrar(Pila dada);
void Leer(Pila *dada);
int Tope(Pila dada);

#endif // PILASLISTAS_H_INCLUDED
