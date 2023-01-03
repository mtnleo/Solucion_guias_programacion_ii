#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

void ContNY(char *cont)
{
    printf("\n> CONTINUAR? (y/n)\n");
    fflush(stdin);
    *cont = getch();
}

node* MostrarListaInvertidaRecursiva(node* lista)
{
    if(lista != NULL)
    {
        lista->siguiente = MostrarListaInvertidaRecursiva(lista->siguiente);
        printf("| %d |\n", lista->dato);

    }
    return lista;
}

int SumarElementosListaRecursiva(node* lista)
{
    int suma = 0;

    if(lista != NULL)
    {
        suma = lista->dato + SumarElementosListaRecursiva(lista->siguiente);
    }

    return suma;
}

void MostrarElementosPar(node* lista)
{
    if(lista != NULL)
    {
        printf("| %d |", lista->dato);
        MostrarElementosPar(lista->siguiente->siguiente);
    }
}

node* BorrarDatoRecursiva(node* lista, int dato)
{
    if(lista != NULL)
    {
        if(dato == lista->siguiente->dato)
        {
            node* aux = lista->siguiente;
            lista->siguiente = lista->siguiente->siguiente;
            free(aux);
        }
        else
        {
            BorrarDatoRecursiva(lista->siguiente, dato);
        }
    }
    return lista;
}

node* InsertarNodoOrdenadoRecursiva(node* lista, node* aInsertar)
{
    if(lista != NULL)
    {
        if(lista->siguiente->dato >= aInsertar->dato)
        {
            aInsertar->siguiente = lista->siguiente;
            lista->siguiente = aInsertar;
        }
        else
        {
            InsertarNodoOrdenadoRecursiva(lista->siguiente, aInsertar);
        }
    }
    return lista;
}

node* InvertirListaRecursiva(node* ante, node* seg)
{
    node* aux;
    if(seg != NULL)
    {
        aux = seg->siguiente;
        seg->siguiente = ante;

        seg = InvertirListaRecursiva(seg, aux);
    }
    else
    {
        seg = ante;
    }
    return seg;
}

/// *****************************

int main()
{
    char cont = 'y';
    while(cont == 'y')
    {
        int numSw;
        printf("Escriba el numero del ejercicio: #");
        scanf("%d", &numSw);
        node* lista = inicListaL();
        node* aux;
        int suma;

        node* aInsertar;


        switch(numSw)
        {
        case 1:
            {
                aux = CrearNodo(1);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(2);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(3);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(4);
                lista = AgregarNodoPrincipio(lista, aux);

                MostrarListaInvertidaRecursiva(lista);

                break;
            }

        case 2:
            {
                aux = CrearNodo(5);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(2);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(10);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(4);
                lista = AgregarNodoPrincipio(lista, aux);

                suma = SumarElementosListaRecursiva(lista);
                printf("Los elementos de la lista suman %d", suma);

                break;
            }

        case 3:
            {
                aux = CrearNodo(5);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(2);///
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(10);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(4);///
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(8);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(23);///
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(1);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(9);///
                lista = AgregarNodoPrincipio(lista, aux);

                MostrarElementosPar(lista);

                break;
            }

        case 4:
            {
                aux = CrearNodo(5);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(2);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(10);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(4);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(8);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(23);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(1);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(9);
                lista = AgregarNodoPrincipio(lista, aux);

                lista = BorrarDatoRecursiva(lista, 8);
                MostrarListaInvertidaRecursiva(lista);

                break;
            }

        case 5:
            {
                aux = CrearNodo(6);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(5);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(3);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(2);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(1);
                lista = AgregarNodoPrincipio(lista, aux);
                aInsertar = CrearNodo(4);

                lista = InsertarNodoOrdenadoRecursiva(lista, aInsertar);
                MostrarLista(lista);

                break;
            }

        case 6:
            {
                aux = CrearNodo(6);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(5);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(4);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(3);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(2);
                lista = AgregarNodoPrincipio(lista, aux);
                aux = CrearNodo(1);
                lista = AgregarNodoPrincipio(lista, aux);
                printf("--- ANTES DE INVERTIR ---\n");
                MostrarLista(lista);

                printf("--- DESPUES DE INVERTIR ---\n");
                lista = InvertirListaRecursiva(NULL, lista);
                MostrarLista(lista);

                break;
            }

        default:
            {
                printf("\n|X| ERROR, ESCRIBA UN NUMERO DE EJERCICIO VALIDO |X|\n");
                break;
            }
        }

        ContNY(&cont);
    }

    return 0;
}
