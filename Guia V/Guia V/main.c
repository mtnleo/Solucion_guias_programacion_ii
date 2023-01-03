#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

typedef struct
{
    char nombre[30];
    int edad;
} Persona;

typedef struct
{
    Persona dato;
    struct nodoL * siguiente;
} nodoL;

typedef struct
{
    Persona dato;
    struct nodoLD* anterior;
    struct nodoLD* siguiente;
} nodoLD;

Persona CargarPersona()
{
    Persona per;

    printf("Escriba el nombre: ");
    fflush(stdin);
    gets(per.nombre);
    printf("Escriba la edad: ");
    scanf("%d", &per.edad);

    return per;
}

nodoLD* inicListaLD()
{
    return NULL;
}

nodoLD* crearNodoLD(Persona per)
{
    nodoLD* lista = (nodoLD*)malloc(sizeof(nodoLD));

    lista->anterior = inicListaLD();
    lista->siguiente = inicListaLD();
    lista->dato = per;

    return lista;
}

nodoLD* agregarAlPpioLD(nodoLD* lista, nodoLD* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        lista->anterior = nuevoNodo;
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoLD* BuscarUltimoLD(nodoLD* lista)
{
    nodoLD* seg = lista;
    while(seg->siguiente != NULL)
    {
        seg = seg->siguiente;
    }
    return seg;
}

nodoLD* agregarAlFinalLD(nodoLD* lista, nodoLD* nuevoNodo)
{
    if(lista->siguiente == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoLD* ultimo = BuscarUltimoLD(lista);

        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }

    return lista;
}

nodoLD* borrarPrimerNodoLD(nodoLD* lista)
{
    nodoLD* borrar;

    borrar = lista;
    lista = lista->siguiente;
    lista->anterior = NULL;

    free(borrar);

    return borrar;
}

nodoLD* borrarNodo(nodoLD* lista, Persona per)
{
    if(lista != NULL)
    {
        if(strcmpi(lista->dato.nombre, per.nombre) == 0)
        {
            lista = borrarPrimerNodoLD(lista);
        }
        else
        {
            nodoLD* ante = lista;
            nodoLD* seg = lista->siguiente;
            while((seg!=NULL) && (strcmp(per.nombre, seg->dato.nombre) != 0))
            {
                ante = seg;
                seg = seg->siguiente;
            }
            if(seg!=NULL)
            {
                ante->siguiente = seg->siguiente;
                if(seg->siguiente!= NULL)
                {
                    nodoLD* aux = seg->siguiente;
                    aux->anterior = ante;
                }

                free(seg);
            }
        }
    }
    return lista;
}

void MostrarNodoLD(nodoLD* nod)
{
    printf("\n----------\n");
    printf("Nombre: %s\n", nod->dato.nombre);
    printf("Edad: %d\n", nod->dato.edad);
}

void MostrarLDPersonas(nodoLD* lista)
{
    while(lista != NULL)
    {
        MostrarNodoLD(lista);
        lista = lista->siguiente;
    }
}

nodoLD* insertarNodoOrdenadoLD(nodoLD* lista, nodoLD* aInsertar)
{
    if(lista == NULL)
    {
        lista = aInsertar;
    }
    else if(lista->dato.edad >= aInsertar->dato.edad)
    {
        lista = agregarAlPpioLD(lista, aInsertar);
    }
    else
    {
        nodoLD* seg = lista->siguiente;
        nodoLD* ante = lista;

        while((seg != NULL) && (aInsertar->dato.edad > seg->dato.edad))
        {
            ante = seg;
            seg = seg->siguiente;
        }
        ante->siguiente = aInsertar;
        aInsertar->anterior = ante;
        aInsertar->siguiente = seg;
        if(seg != NULL)
        {
            seg->anterior = aInsertar;
        }
    }

    return lista;
}

nodoLD* CargarLDOrdenado(nodoLD* lista)
{
    char cont = 'y';
    while(cont == 'y')
    {
        Persona per = CargarPersona();
        nodoLD* nodoAdd = crearNodoLD(per);
        lista = insertarNodoOrdenadoLD(lista, nodoAdd);

        printf("\nDesea continuar (y/n): ");
        fflush(stdin);
        cont = getch();
    }
    return lista;
}

int ContarLista(nodoLD * lista)
{
    int validos = 0;

    while(lista != NULL)
    {
        lista = lista->siguiente;
        validos++;
    }

    return validos;
}

void EliminarNodoMedioLista(nodoLD **lista)
{
    if((*lista)->siguiente == NULL)
    {
        nodoLD* aux = *lista;
        *lista = NULL;
        free(aux);
    }
    else if(*lista != NULL)
    {
        nodoLD* seg = (*lista);
        nodoLD* ante = (*lista)->anterior;
        int i;
        int validos = ContarLista(*lista);
        for(i = 0; i < (validos/2); i++)
        {
            ante = seg;
            seg = seg->siguiente;
        }

        printf("%d", i);

        nodoLD* aux = seg->siguiente;
        ante->siguiente = seg->siguiente;
        aux->anterior = ante;

        free(seg);
    }
}


///***************** MAIN ***********************************

int main()
{
    nodoLD* lista;
    lista = inicListaLD();
    MostrarLDPersonas(lista);
    lista = CargarLDOrdenado(lista);
    MostrarLDPersonas(lista);

    EliminarNodoMedioLista(&lista);
    MostrarLDPersonas(lista);

    return 0;
}
