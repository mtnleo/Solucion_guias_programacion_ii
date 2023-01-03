#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "arboles.h"

/*
int ContarHojas(nodoArbol* arbol)
{
    int cant = 0;

    if(arbol->izq != NULL && arbol->der != NULL)
    {
        cant = cant + ContarHojas(arbol->izq);
        cant = cant + ContarHojas(arbol->der);
    }
    else
    {
        cant++;
    }

    return cant;
}

int BuscarDato(nodoArbol* arbol, int dato)
{
    int encontrado = 0;

    if(arbol != NULL)
    {
        if(arbol->dato == dato)
        {
            encontrado = 1;
        }
        else if(arbol->dato > dato)
        {
            encontrado = BuscarDato(arbol->izq, dato);
        }
        else
        {
            encontrado = BuscarDato(arbol->der, dato);
        }
    }

    return encontrado;
}
*/
/// STRUCTS

typedef struct
{
    int legajo;
    char nombre[20];
    int edad;
} persona;

typedef struct nodoArbol
{
    persona dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
} nodoArbol;

typedef struct
{
    persona dato;
    struct nodo* sig;
} nodo;

// /////////////



nodoArbol* inicArbolPer()
{
    return NULL;
}

nodoArbol* CrearNodoPer(persona P)
{
    nodoArbol* nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));

    nuevo->dato = P;
    nuevo->der = inicArbolPer();
    nuevo->izq = inicArbolPer();

    return nuevo;
}

nodoArbol* insertarLegajo(nodoArbol* arbol, persona P)
{
    if(arbol == NULL)
    {
        nodoArbol* nuevo = CrearNodoPer(P);
        arbol = nuevo;
    }
    else if(arbol->dato.legajo > P.legajo)
    {
        arbol->izq = insertarLegajo(arbol->izq, P);
    }
    else
    {
        arbol->der = insertarLegajo(arbol->der, P);
    }

    return arbol;
}

void MostrarPersona(persona P)
{
    printf("-----------------\n");
    printf("> Nro de legajo: %d\n", P.legajo);
    printf("> Nombre: %s\n", P.nombre);
    printf("> Edad: %d\n", P.edad);
    printf("-----------------\n");
}

void inorderP(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        inorderP(arbol->izq);
        MostrarPersona(arbol->dato);
        inorderP(arbol->der);
    }
}

persona CargarPersona()
{
    persona P;

    printf("Escriba el nombre: ");
    fflush(stdin);
    gets(P.nombre);
    printf("Escriba la edad: ");
    scanf("%d", &P.edad);
    printf("Escriba el legajo: ");
    scanf("%d", &P.legajo);

    return P;
}

nodoArbol* cargarPersonasArbol(nodoArbol* arbol)
{
    char cont = 's';
    persona P;

    while(cont == 's')
    {
        P = CargarPersona();
        arbol = insertarLegajo(arbol, P);

        printf("\nDesea continuar? ");
        fflush(stdin);
        cont = getch();
    }

    return arbol;
}

nodo* inicLista()
{
    return NULL;
}

nodo* CrearNodoLista(persona P)
{
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));

    nuevo->dato = P;
    nuevo->sig = inicLista();

    return nuevo;
}

void agregarPpio(nodo ** lista, nodo* add)
{
    if(*lista == NULL)
    {
        *lista = add;
    }
    else
    {
        add->sig = *lista;
        *lista = add;
    }
}

nodoArbol* pasarArbolToListaSimple(nodoArbol* arbol, nodo** lista)
{
    if(arbol != NULL)
    {
        arbol->izq = pasarArbolToListaSimple(arbol->izq, lista);
        nodo * nuevo = CrearNodoLista(arbol->dato);
        agregarPpio(lista, nuevo);
        arbol->der = pasarArbolToListaSimple(arbol->der, lista);
    }
    return arbol;
}

void MostrarLista(nodo* lista)
{
    while(lista != NULL)
    {
        MostrarPersona(lista->dato);
        lista = lista->sig;
    }
}

nodoArbol* BuscarPorLegajo(nodoArbol* arbol, int legBuscado)
{
    nodoArbol* buscado = inicArbolPer();

    if(arbol != NULL && arbol->dato.legajo > legBuscado)
    {
        arbol->izq = BuscarPorLegajo(arbol->izq, legBuscado);
    }
    else if(arbol != NULL && arbol->dato.legajo < legBuscado)
    {
        arbol->der = BuscarPorLegajo(arbol->der, legBuscado);
    }
    else
    {
        buscado = arbol;
    }

    return buscado;
}

nodoArbol* BuscarPorNombre(nodoArbol* arbol, char nombre[])
{
    nodoArbol* buscado = inicArbol();

    if(arbol != NULL && strcmpi(arbol->dato.nombre, nombre) == 0)
    {
        buscado = arbol;
    }
    else if(arbol != NULL)
    {
        if(arbol->izq != NULL)
        {
            buscado = BuscarPorNombre(arbol->izq, nombre);
        }
        else if(arbol->der != NULL)
        {
            buscado = BuscarPorNombre(arbol->der, nombre);
        }
    }
    return buscado;
}

int ObtenerAltura(nodoArbol* arbol)
{
    int contadorIzq = 0;
    int contadorDer = 0;
    int contFinal = 0;
    if(arbol != NULL)
    {
        contadorIzq = 1 + ObtenerAltura(arbol->izq);
        contadorIzq = 1 + ObtenerAltura(arbol->der);

        contadorDer = 1 + ObtenerAltura(arbol->der);
        contadorDer = 1 + ObtenerAltura(arbol->izq);

        if(contadorDer > contadorIzq)
        {
            contFinal = contadorDer;
        }
        else
        {
            contFinal = contadorIzq;
        }
    }

    return contFinal;
}

int ContarNodosArbol(nodoArbol* arbol)
{
    int cont = 0;
    if(arbol != NULL)
    {
        cont = 1 + ContarNodosArbol(arbol->izq);
        cont = 1 + ContarNodosArbol(arbol->der);
    }
    return cont;
}

nodoArbol* hardcodeDatos()
{
    nodoArbol* arbol = inicArbolPer();
    persona personita;

    personita.legajo = 2;
    strcpy(personita.nombre, "Tincho");
    personita.edad = 18;
    arbol = insertarLegajo(arbol, personita);

    personita.legajo = -2;
    strcpy(personita.nombre, "LongTin");
    personita.edad = 20;
    arbol = insertarLegajo(arbol, personita);

    personita.legajo = 1;
    strcpy(personita.nombre, "Malena");
    personita.edad = 23;
    arbol = insertarLegajo(arbol, personita);

    personita.legajo = 4;
    strcpy(personita.nombre, "hDog");
    personita.edad = 20;
    arbol = insertarLegajo(arbol, personita);

    personita.legajo = 3;
    strcpy(personita.nombre, "Toto");
    personita.edad = 20;
    arbol = insertarLegajo(arbol, personita);

    personita.legajo = 5;
    strcpy(personita.nombre, "Felpa");
    personita.edad = 20;
    arbol = insertarLegajo(arbol, personita);

    personita.legajo = -1;
    strcpy(personita.nombre, "Juancito");
    personita.edad = 20;
    arbol = insertarLegajo(arbol, personita);

    return arbol;
}

//int DibujarArbolLinea(struct nodoArbol * arbol, int esIzq, int inicia, int nivel, char s[20][255])
//{
//    char b[10];
//    int ancho = 4; //es el ancho del nodo que dibujo
//    int i;
//
//    if (!arbol) return 0;
//
//    sprintf(b, "(%d)", arbol->dato.legajo); // agrego valor de nodo a la matriz
//
//    int izq  = DibujarArbolLinea(arbol->izq,  1, inicia,                nivel + 1, s);
//    int der = DibujarArbolLinea(arbol->der, 0, inicia + izq + ancho, nivel + 1, s);
//
//    //dibujo nodo
//    for (i = 0; i < ancho; i++)
//        s[2 * nivel][inicia + izq + i] = b[i];
//
//    //dibujo lineas .----+----.
//    if (nivel && esIzq) {
//
//        for (i = 0; i < ancho + der; i++)
//            s[2 * nivel - 1][inicia + izq + ancho/2 + i] = '-';
//
//        s[2 * nivel - 1][inicia + izq + ancho/2] = '.';
//        s[2 * nivel - 1][inicia + izq + ancho + der + ancho/2] = '+';
//
//    } else if (nivel && !esIzq) {
//
//        for (i = 0; i < izq + ancho; i++)
//            s[2 * nivel - 1][inicia - ancho/2 + i] = '-';
//
//        s[2 * nivel - 1][inicia + izq + ancho/2] = '.';
//        s[2 * nivel - 1][inicia - ancho/2 - 1] = '+';
//    }
//
//    //Cerebros quemados everywere!!
//    return izq + ancho + der;
//}
//
//int DibujarArbol(struct nodoArbol * arbol)
//{
//    char s[10][255];
//    int i;
//    //creo una matriz de char para hacer mi "dibujo"
//    for (i = 0; i < 10; i++)
//        sprintf(s[i], "%80s", " ");
//
//    //Hago magia
//    DibujarArbolLinea(arbol, 0, 0, 0, s);
//
//    //Imprimo matriz
//    for (i = 0; i < 10; i++)
//        printf("%s\n", s[i]);
//}

nodoArbol* eliminarNodoUnHijo(nodoArbol* arbol)
{
    nodoArbol* borrar = arbol;
    if(arbol->der != NULL)
    {
        arbol = arbol->der;
    }
    else
    {
        arbol = arbol->izq;
    }
    free(borrar);
    return arbol;
}

nodoArbol* eliminarNodoDosHijos(nodoArbol* arbol, nodoArbol* seg)
{
    if(seg != NULL)
    {
        if(arbol == seg)
        {
            seg->izq = eliminarNodoDosHijos(arbol, seg->izq);
        }
        else if(arbol != seg && seg->der != NULL)
        {
            seg->der = eliminarNodoDosHijos(arbol, seg->der);
        }
        else
        {
            nodoArbol* aux = seg;
            if(seg->der != NULL || seg->izq != NULL)
            {
                printf("el1");
                seg = eliminarNodoUnHijo(seg);
            }
            else
            {
                printf("empty");
                seg = NULL;
                free(seg);
            }

            //seg = eliminarNodoUnHijo(seg);
            aux->der = arbol->der;
            aux->izq = arbol->izq;
            arbol = aux;
        }
    }

    return arbol;
}

//nodoArbol* BorrarNodo(nodoArbol** arbol, int borrar)
//{
//    nodoArbol* borrado = NULL;
//
//    printf("#");
//    if((*arbol)->dato.legajo == borrar)
//    {
//        printf("*");
//        borrado = *arbol;
//
//
//        if((*arbol)->izq != NULL && (*arbol)->der != NULL)
//        {
//            (*arbol) = eliminarNodoDosHijos(*arbol, *arbol);
//        }
//        else if((*arbol)->izq == NULL && (*arbol)->der == NULL)
//        {
//            (*arbol) = NULL;
//            free((*arbol));
//        }
//        else
//        {
//            (*arbol) = eliminarNodoUnHijo((*arbol));
//        }
//    }
//    else if((*arbol) != NULL)
//    {
//        borrado = BorrarNodo((*arbol)->izq, borrar);
//        borrado = BorrarNodo((*arbol)->der, borrar);
//    }
//
//    printf("NULL\n");
//    return borrado;
//}

nodoArbol* BorrarNodo(nodoArbol* arbol, int borrar)
{
    if(arbol != NULL)
    {
        if(arbol->dato.legajo > borrar)
        {
            arbol->izq = BorrarNodo(arbol->izq, borrar);
        }
        else if(arbol->dato.legajo < borrar)
        {
            arbol->der = BorrarNodo(arbol->der, borrar);
        }
        else
        {
            if(arbol->der != NULL && arbol->izq != NULL)
            {
                printf("el2");
                arbol = eliminarNodoDosHijos(arbol, arbol);
            }
            else if(arbol->der != NULL || arbol->izq != NULL)
            {
                printf("el1");
                arbol = eliminarNodoUnHijo(arbol);
            }
            else
            {
                printf("empty");
                arbol = NULL;
                free(arbol);
            }
        }
    }
    return arbol;
}

/// /////////////////////////////////////////////////////////////////
int main()
{
    char cont = 's';
    int numSw;

    /*int cantHojas;
    int nodoBuscado;
    int datoEncontrado;*/

    nodoArbol* arbol = inicArbolPer();
    nodoArbol* buscado = inicArbolPer();
    nodoArbol* borrado = inicArbolPer();
    persona P;

    int longitudArbol;
    int cantNodos;

    int legBuscado;

    nodo* lista = inicLista();

    while(cont == 's')
    {
        printf("Escriba el numero del ejercicio: ");
        scanf("%d", &numSw);

        switch(numSw)
        {
        case 0: // Funciones anteriores
        {
            /*
               arbol = insertarNodo(arbol, 10);
               arbol = insertarNodo(arbol, 6);
               arbol = insertarNodo(arbol, 3);
               arbol = insertarNodo(arbol, 13);
               arbol = insertarNodo(arbol, 9);
               arbol = insertarNodo(arbol, 7);
               arbol = insertarNodo(arbol, 2);

               cantHojas = ContarHojas(arbol);
               printf("Hay %d hojas\n", cantHojas);

               printf("Escriba el nodo a buscar: ");
               scanf("%d", &nodoBuscado);

               datoEncontrado = BuscarDato(arbol, nodoBuscado);
               if(datoEncontrado == 1)
               {
                   printf("\nSe encontro el nodo buscado.");
               }
               else
               {
                   printf("\nNo se encontro el nodo buscado.");
               }

               */
            break;
        }
        case 1:
        {
            arbol = cargarPersonasArbol(arbol);
            inorderP(arbol);

            break;
        }
        case 2:
        {
            arbol = cargarPersonasArbol(arbol);
            inorderP(arbol);

            break;
        }
        case 3:
        {
            arbol = cargarPersonasArbol(arbol);

            pasarArbolToListaSimple(arbol, &lista);
            MostrarLista(lista);

            break;
        }
        case 4:
        {
            printf("Escriba el numero de legajo a buscar: #");
            scanf("%d", &legBuscado);
            buscado = BuscarPorLegajo(arbol, legBuscado);
            MostrarPersona(buscado->dato);

            break;
        }
        case 5:
        {
            arbol = hardcodeDatos();
            inorderP(arbol);
            buscado = BuscarPorNombre(arbol, "toto");
            printf("\nDATO RETORNADO: \n");
            MostrarPersona(buscado->dato);

            break;
        }
        case 6:
        {
            arbol = hardcodeDatos();
            longitudArbol = ObtenerAltura(arbol);
            printf("\nLa altura del arbol es de %d\n ", longitudArbol);

            break;
        }
        case 7:
        {
            arbol = hardcodeDatos();
            cantNodos = ContarNodosArbol(arbol);
            printf("\nEl arbol tiene %d nodos\n", cantNodos);

            break;
        }
        case 8:
        {
            arbol = hardcodeDatos();
            printf("\nARBOL ANTES DE BORRAR: \n");
            inorderP(arbol);

            borrado = BorrarNodo(arbol, 2);

            printf("\nARBOL DESPUES DE BORRAR: \n");
            inorderP(arbol);

            break;
        }

        default:
        {
            printf("|X| ESCRIBA UN EJERCICIO VALIDO |X|\n");
        }
        }

        printf("\n> Desea continuar? ");
        fflush(stdin);
        cont = getch();
    }


    return 0;
}


