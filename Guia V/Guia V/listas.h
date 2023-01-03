#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

typedef struct
{
    int dato;
    struct node * siguiente;
} node;

node* inicListaL();
node* AgregarNodoPrincipio(node * lista, node * nuevoNodo);
node * AgregarNodoFinal(node * lista, node* ingresar);
node * EncontrarNodoFinal(node * lista);

#endif // LISTAS_H_INCLUDED
