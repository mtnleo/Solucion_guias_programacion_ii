#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED

typedef struct
{
    int dato;
    struct nodoArbol *izq;
    struct nodoArbol *der;
} nodoArbol;

nodoArbol* inicArbol();
nodoArbol* CrearNodoArbol(int dato);
nodoArbol* insertarNodo(nodoArbol* arbol, int dato);
nodoArbol* buscar(nodoArbol* arbol, int dato);
void preorder(nodoArbol* arbol);
void posorder(nodoArbol* arbol);
void inorder(nodoArbol* arbol);
//nodoArbol* borrarArbol(nodoArbol* arbol, int borrar);

#endif // ARBOLES_H_INCLUDED
