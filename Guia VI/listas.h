#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

typedef struct node
{
    int dato;
    struct node * siguiente;
} node;

node* inicListaL();
node* CrearNodo(int dato);
node* AgregarNodoPrincipio(node * lista, node * nuevoNodo);
node * AgregarNodoFinal(node * lista, node* ingresar);
node * EncontrarNodoFinal(node * lista);
void MostrarLista(node* lista);
int ContarElementosLista(node* lista);

#endif // LISTAS_H_INCLUDED
