#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
    char materia[40];
    int idMateria;
} registroArchivo;

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
} notaAlumno;

typedef struct _nodo
{
    notaAlumno dato;
    struct _nodo *siguiente;
} nodo;

typedef struct
{
    int idMateria;
    char materia[40];
    nodo * listaDeNotas;
} celda;

/// // // // // // // // // // // //

int BuscarPos(celda C[], int validos, char materia[])
{
    int j = -1;
    for(int i = 0; i < validos && j == -1; i++)
    {
        if(strcmpi(C[i].materia, materia) == 0)
        {
            j = i;
        }
    }
    return j;
}

nodo* inicLista()
{
    return NULL;
}

nodo* CrearNodo(registroArchivo dato)
{
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));

    nuevo->dato.legajo = dato.legajo;
    nuevo->dato.nota = dato.nota;
    strcpy(nuevo->dato.nombreApe, dato.nombreApe);

    nuevo->siguiente = inicLista();

    return nuevo;
}

nodo* agregarPrincipio(nodo* lista, registroArchivo dato)
{
    nodo* nuevo = CrearNodo(dato);

    nuevo->siguiente = lista;
    lista = nuevo;

    return lista;
}

int AgregarMateriaArr(celda C[], int validos, registroArchivo materia)
{
    C[validos].idMateria = materia.idMateria;
    strcpy(C[validos].materia, materia.materia);

    return validos + 1;
}

int alta(celda C[], int validos, registroArchivo CargarArchivo)
{
    int pos = BuscarPos(C, validos, CargarArchivo.materia);


    if(pos == -1) //si no existe la materia
    {
        validos = AgregarMateriaArr(C, validos, CargarArchivo);
        pos = validos - 1;
    }

    C[pos].listaDeNotas = agregarPrincipio(C[pos].listaDeNotas, CargarArchivo);

    return validos;
}

registroArchivo CargarUnDato()
{
    registroArchivo carga;

    printf("-----\n");
    printf("> Ingrese la materia: ");
    fflush(stdin);
    gets(carga.materia);
    printf("> Ingrese la ID de la Materia: #");
    scanf("%d", &carga.idMateria);
    printf("> Ingrese el nombre y apellido: ");
    fflush(stdin);
    gets(carga.nombreApe);
    printf("> Ingrese el legajo: #");
    scanf("%d", &carga.legajo);
    printf("> Ingrese la nota: ");
    scanf("%d", &carga.nota);

    return carga;
}

void CargarDatos(celda C[], int validos)
{
    registroArchivo carga = CargarUnDato();

    alta(C, validos, carga);
}

void CargarArchivo(char nombreAr[])
{
    FILE * buf = fopen(nombreAr, "ab");
    registroArchivo reg;
    char cont = 's';

    if(buf != NULL)
    {
        while(cont == 's')
        {
            reg = CargarUnDato();
            fwrite(&reg, sizeof(registroArchivo), 1, buf);

            printf("-------- Desea continuar agregando datos? ");
            fflush(stdin);
            cont = getch();
        }
        fclose(buf);
    }
    else
    {
        printf("|X| ERROR AL ABRIR EL ARCHIVO |X|\n");
    }
}

int LeerArchivoCargarDatos(char nombreAr[], celda C[], int validos)
{
    FILE * buf = fopen(nombreAr, "rb");
    registroArchivo reg;

    if(buf != NULL)
    {
        while(fread(&reg, sizeof(registroArchivo), 1, buf) > 0)
        {
            validos = alta(C, validos, reg);
        }
        fclose(buf);
    }
    else
    {
        printf("|X| ERROR AL ABRIR EL ARCHIVO |X|\n");
    }

    return validos;
}

void MostrarNotaAlumnx(notaAlumno nota)
{
    printf("-----------------------------------\n");
    printf("===== Nombre: %s\n", nota.nombreApe);
    printf("----- Legajo: #%d\n", nota.legajo);
    printf("===== Nota: %d\n", nota.nota);
    printf("-----------------------------------\n");
}

void MostrarMateria(registroArchivo materia)
{
    printf(">>>>> Materia: %s\n", materia.materia);
    printf(">>>>> Legajo: #%d\n", materia.legajo);
}

void MostrarRegistroArchivo(registroArchivo nota)
{
    printf("-----------------------------------\n");
    printf(">>>>> Materia: %s\n", nota.materia);
    printf(">>>>> Legajo: #%d\n", nota.legajo);
    printf("===== Nombre: %s\n", nota.nombreApe);
    printf("----- Legajo: #%d\n", nota.legajo);
    printf("===== Nota: %d\n", nota.nota);
    printf("-----------------------------------\n");
}

void MostrarArreglo(celda C[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        printf("-----------------------------------\n");
        printf(">>>>> Materia: %s\n", C[i].materia);
        printf(">>>>> ID: #%d\n", C[i].idMateria);
        printf("-----------------------------------\n");
    }
}

void MostrarLista(nodo * lista)
{
    while(lista != NULL)
    {
        MostrarNotaAlumnx(lista->dato);
        lista = lista->siguiente;
    }
}

void MostrarListaMateria(celda C[], int validos, char materia[])
{
    int pos = BuscarPos(C, validos, materia);
    MostrarLista(C[pos].listaDeNotas);
}

/// ####################################################################
int main()
{
    char nombreAr[] = {"materias.bin"};
    int validos = 0;
    celda C[100];
    char materiaBuscar[100];

    //CargarArchivo(nombreAr);
    validos = LeerArchivoCargarDatos(nombreAr, C, validos);
    printf("############## ARREGLO: ##############\n");
    MostrarArreglo(C, validos);
    printf("Escribe la materia a mostrar: ");
    fflush(stdin);
    gets(materiaBuscar);
    printf("\n############## LISTA DE MATERIA: ##############\n");
    MostrarListaMateria(C, validos, materiaBuscar);


    return 0;
}
