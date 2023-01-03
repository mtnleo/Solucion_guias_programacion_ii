#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "pilasListas.h"

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

nodoL* inicLista()
{
    return NULL;
}

nodoL* CrearNodo(Persona per)
{
    nodoL * aux = (nodoL*) malloc(sizeof(nodoL));

    aux->dato = per;
    aux->siguiente = NULL;

    return aux;
}

nodoL* CargarListaPpio(nodoL * lista, nodoL * nuevoNodo)
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

void MostrarNodo(nodoL* nodo)
{
    puts("-----------------");
    printf("Nombre: %s\n", nodo->dato.nombre);
    printf("Edad: %d\n", nodo->dato.edad);
    puts("-----------------");
}

void recorrerYmostrar(nodoL * lista)
{
    while(lista != NULL)
    {
        MostrarNodo(lista);
        lista = lista->siguiente;
    }
}

/*nodoL * EncontrarNodoFinal(nodoL * lista)
{
    while(lista->siguiente != NULL)
    {
        lista = lista->siguiente;
    }
    return lista;
}*/

nodoL * subprogramaIngresarDatosAlFinal(nodoL * lista, nodoL* ingresar)
{
    nodoL* seguidora = lista;

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

nodoL * subprogramaAgregarUnNodoEnOrden(nodoL * lista, nodoL * nodoOrdenar)
{

    if(lista == NULL)
    {
        lista = nodoOrdenar;
    }
    else if(nodoOrdenar->dato.edad < lista->dato.edad)
    {
        lista = CargarListaPpio(lista, nodoOrdenar);
    }
    else
    {
        nodoL * anterior = lista;
        nodoL * seguidora = lista->siguiente;

        while(seguidora != NULL && seguidora->dato.edad <= nodoOrdenar->dato.edad)
        {
            seguidora = seguidora->siguiente;
            anterior = anterior->siguiente;
        }

        anterior->siguiente = nodoOrdenar;
        nodoOrdenar->siguiente = seguidora;
    }

    return lista;
}

nodoL * PasarArchivoToListaOrdenado(char nombreAr[], nodoL* lista)
{
    FILE *buf = fopen(nombreAr, "rb");
    Persona per;
    nodoL* nodoAux;

    if(buf != NULL)
    {
        while(fread(&per, sizeof(Persona), 1, buf) != 0)
        {

            nodoAux = CrearNodo(per);
            lista = subprogramaAgregarUnNodoEnOrden(lista, nodoAux);
        }

        fclose(buf);
    }
    else
    {
        printf("\n|X| ERROR AL ABRIR EL ARCHIVO |X|\n");
    }

    return lista;
}

nodoL* IntercalarListas(nodoL* lista1, nodoL* lista2)
{
    nodoL* lista3 = inicLista();
    nodoL* copia = inicLista();

    while(lista1 != NULL && lista2 != NULL)
    {
        if(lista1->dato.edad <= lista2->dato.edad)
        {
            copia = lista1;
            lista1 = lista1->siguiente;
        }
        else
        {
            copia = lista2;
            lista2 = lista2->siguiente;

        }

        copia->siguiente = NULL;
        lista3 = subprogramaIngresarDatosAlFinal(lista3, copia);
    }

    if(lista1 != NULL)
    {
        lista3 = subprogramaIngresarDatosAlFinal(lista3, lista1);
    }
    else if(lista2 != NULL)
    {
        lista3 = subprogramaIngresarDatosAlFinal(lista3, lista2);
    }

    return lista3;
}

/// //////

void CargarArchivoInput(char nombreAr[])
{
    char cont = 'y';
    Persona per;

    FILE *buf = fopen(nombreAr, "ab");

    if(buf != NULL)
    {
        while(cont == 'y')
        {
            printf("Nombre: ");
            fflush(stdin);
            gets(per.nombre);

            printf("Edad: ");
            scanf("%d", &per.edad);

            fwrite(&per, sizeof(Persona), 1, buf);

            printf("Desea continuar llenando el archivo? y/n");
            fflush(stdin);
            cont = getch();
        }
        fclose(buf);
    }
    else
    {
        puts("\n|X| ERROR AL ABRIR EL ARCHIVO |X|");
    }
}

void MostrarPersona(Persona per)
{
    printf("\n-----------\n");
    printf("Nombre: %s\n", per.nombre);
    printf("Edad: %d\n", per.edad);
}

void MostrarArchivoPersonas(char nombreAr[])
{
    Persona per;

    FILE *buf = fopen(nombreAr, "rb");

    if(buf != NULL)
    {
        while(fread(&per, sizeof(Persona), 1, buf) != 0)
        {
            MostrarPersona(per);
        }

        fclose(buf);
    }
    else
    {
        puts("\n|X| ERROR AL ABRIR EL ARCHIVO |X|");
    }
}

nodoL * LeerArchivoPasarNodo(char nombreAr[], nodoL * lista)
{
    Persona per;
    nodoL * aux;

    FILE *buf = fopen(nombreAr, "rb");

    if(buf != NULL)
    {
        while(fread(&per, sizeof(Persona), 1, buf) != 0)
        {
            aux = CrearNodo(per);
            lista = subprogramaIngresarDatosAlFinal(lista, aux);
        }

        fclose(buf);
    }
    else
    {
        puts("\n|X| ERROR AL ABRIR EL ARCHIVO |X|");
    }

    return lista;
}

void MostrarLista(nodoL * lista)
{
    while(lista != NULL)
    {
        MostrarPersona(lista->dato);
        lista = lista->siguiente;
    }
}

int EncontrarLista(nodoL* lista, char nombre[])
{
    int encontrado = 0;

    while(encontrado == 0 && lista != NULL)
    {
        if(strcmpi(lista->dato.nombre, nombre) == 0)
        {
            encontrado = 1;
        }
        else
        {
            lista = lista->siguiente;
        }
    }

    return encontrado;
}

int ContarElementosLista(nodoL* lista)
{
    int cont = 0;

    while(lista != NULL)
    {
        cont++;
        lista = lista->siguiente;
    }

    return cont;
}

nodoL* InvertirLista(nodoL * lista)
{
    nodoL*seguidora=lista;

    while (seguidora->siguiente != NULL)
    {
        nodoL* seguidora2 = seguidora->siguiente;
        seguidora->siguiente = seguidora2->siguiente;
        lista = CargarListaPpio(lista, seguidora2);
    }

    return lista;
}

void ObtenerPares(nodo ** lista, Pila dada)
{
    int numero;
    while(!pilaVacia(dada))
    {
        numero = Desapilar(&dada);
        if(numero % 2 == 0)
        {
            nodo* aux = CrearNodoPila(numero);
            *lista = AgregarNodoFinal((*lista), aux);
        }
    }
}

void MostrarListaPila(nodo* lista)
{
    while(lista != NULL)
    {
        printf("   | %d |\n", lista->dato);
        lista = lista->siguiente;
    }
}

void BorrarNodosMenoresA(nodo ** lista, int dato)
{
    nodo* seguidora = (*lista)->siguiente;
    nodo* anterior = *lista;

    if(anterior->dato < dato)
    {
        nodo* borrar = anterior;
        *lista = (*lista)->siguiente;
        seguidora = seguidora->siguiente;
        anterior = anterior->siguiente;
        free(borrar);
    }

    while(seguidora != NULL)
    {
        if(seguidora->dato < dato)
        {
            nodo* borrar = seguidora;
            seguidora = seguidora->siguiente;
            anterior->siguiente = seguidora;
            free(borrar);
        }
        else
        {
            seguidora = seguidora->siguiente;
            anterior = anterior->siguiente;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char cont = 'y';
    int numSw;

    char nombreAr[] = {"ArchivoPersonas.bin"};

    char nombreAr1[] = {"ArchivoPersonas1.bin"};
    char nombreAr2[] = {"ArchivoPersonas2.bin"};

    nodoL * lista;

    //3.
    int encontrado;
    char aBuscar[40];

    //4.
    nodoL * lista1;
    nodoL * lista2;
    nodoL * lista3;

    //5.
    int elementos;

    //6.
    Pila dada;

    //7.
    nodo* listaPares = inicLista();
    Pila dada1;
    inicPila(&dada1);

    Persona per;

    while(cont == 'y')
    {
        printf("Escriba el numero de ejercicio: #");
        fflush(stdin);
        scanf("%d", &numSw);

        switch(numSw)
        {
        case 1: //Hacer un programa que lea de un archivo datos y los inserte en una lista.
        {
            lista = inicLista();
            CargarArchivoInput(nombreAr);
            lista = LeerArchivoPasarNodo(nombreAr, lista);
            MostrarLista(lista);

            break;
        }

        case 2: //Hacer un programa que lea de un archivo datos y los inserte en una lista en forma ordenada.
        {
            lista = inicLista();

            lista = PasarArchivoToListaOrdenado(nombreAr, lista);

            MostrarLista(lista);

            break;
        }

        case 3: //Hacer una función que retorne un 1 (uno) o 0 (cero) si existe un determinado elemento en una lista dada. (considerar caso ordenada y caso desordenada)
        {
            lista = inicLista();
            lista = LeerArchivoPasarNodo(nombreAr, lista);
            MostrarLista(lista);

            puts("Escriba un dato a buscar: ");
            fflush(stdin);
            gets(aBuscar);

            encontrado = EncontrarLista(lista, aBuscar);

            if(encontrado == 1)
            {
                printf("Se encontro el dato buscado!\n");
            }
            else
            {
                printf("|X| Dato buscado no encontrado |X|\n");
            }

            break;
        }

        case 4:
        {
            lista1 = inicLista();
            lista2 = inicLista();
            lista3 = inicLista();

            //CargarArchivoInput(nombreAr1);
            //CargarArchivoInput(nombreAr2);

            lista1 = LeerArchivoPasarNodo(nombreAr1, lista1);
            lista2 = LeerArchivoPasarNodo(nombreAr2, lista2);

            puts("\nLista 1:");
            MostrarLista(lista1);
            puts("\nLista 2:");
            MostrarLista(lista2);

            lista3 = IntercalarListas(lista1, lista2);
            puts("\n>>>>>> Lista Intercalada:");
            MostrarLista(lista3);


            break;
        }

        case 5: //Invertir los elementos de una lista redireccionando solamente los punteros. (No se deben crear nuevos nodos)
        {
            lista1 = inicLista();
            lista1 = LeerArchivoPasarNodo(nombreAr1, lista1);

            MostrarLista(lista1);

            lista1 = InvertirLista(lista1);
            puts("\n>>>>> LISTA INVERTIDA: ");

            MostrarLista(lista1);

            break;
        }

        case 6:
        {
            inicPila(&dada);
            Leer(&dada);
            Leer(&dada);
            Leer(&dada);

            Mostrar(dada);

            break;
        }

        case 7:
        {
            printf("A) \n");
            Leer(&dada);
            Leer(&dada);
            Leer(&dada);
            Leer(&dada);
            Leer(&dada);
            Leer(&dada);

            Mostrar(dada);

            ObtenerPares(&listaPares, dada);
            printf("Lista con pares: \n");
            MostrarListaPila(listaPares);

            printf("\nB) \n");
            BorrarNodosMenoresA(&listaPares, 10);
            MostrarListaPila(listaPares);

            break;
        }

        case 9: ///Para pruebas
        {
            lista1 = inicLista();
            lista1 = LeerArchivoPasarNodo(nombreAr1, lista1);

            MostrarLista(lista1);

            printf("\nEdad: ");
            scanf("%d", &per.edad);
            printf("\nNombre: \n");
            fflush(stdin);
            gets(per.nombre);

            nodoL* agregarFinal = CrearNodo(per);
            subprogramaIngresarDatosAlFinal(lista1, agregarFinal);

            MostrarLista(lista1);

            break;

        }



        default:
        {
            puts("\n|X| ESCRIBA UN NUMERO DE EJERCICIO VALIDO |X|");

            break;
        }


        }

        printf("\nFIN DE EJECUCION ------------------------\n");
        printf("Desea continuar? 'y/n'");
        fflush(stdin);
        cont = getch();

        system("cls");

    }


    return 0;
}
