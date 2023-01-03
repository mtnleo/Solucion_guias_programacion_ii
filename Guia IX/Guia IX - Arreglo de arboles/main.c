#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char nombreAr[] = {"animales.dat"};

typedef struct
{
    char animal[30];
    int cant;
    int habitat;
    int idEspecie;
    char especie[20];
} registroArchivo;

typedef struct
{
    char nombreAnimal [30];
    int cantidad;
    int habitat;
    // 1 - selva, 2- sabana, 3-bosque, 4-mar
} animal;

typedef struct
{
    animal dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct
{
    int idEspecie;
    char especie [20];
    // "Mamiferos", "Aves"
    // "Reptiles", "Peces",”Anfibios”
    nodoArbol * arbolDeAnimales;
} celdaEspecie;

int LeerArchivo(celdaEspecie C[], int validos);
int alta(celdaEspecie C[], int validos, registroArchivo reg);
int AgregarCelda(celdaEspecie C[], int validos, registroArchivo reg);
int BuscarPos(celdaEspecie C[], int validos, char buscado[]);
void inorder(nodoArbol* arbol);
void MostrarArbol(celdaEspecie C[], int validos, char especie[]);
void MostrarArreglo(celdaEspecie C[], int validos);
void MostrarCelda(celdaEspecie C);
void MostrarAnimal(animal A);
nodoArbol* insertarArbol(nodoArbol* arbol, registroArchivo reg);
nodoArbol* CrearNodoArbol(registroArchivo reg);
nodoArbol* inicArbol();
void pasarDeADAToArchivosAnimales(celdaEspecie C[], int validos);
void AbrirArchivoEspecie(celdaEspecie C);
void PasarArbolToArchivo(FILE * buf, nodoArbol* arbol);
nodoArbol* PasarArchivoArbol(char nombre[]);

/// ###############################

nodoArbol* inicArbol()
{
    return NULL;
}

nodoArbol* CrearNodoArbol(registroArchivo reg)
{
    nodoArbol * nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevo->dato.cantidad = reg.cant;
    nuevo->dato.habitat = reg.habitat;
    strcpy(nuevo->dato.nombreAnimal, reg.animal);

    nuevo->der = inicArbol();
    nuevo->izq = inicArbol();

    return nuevo;
}

nodoArbol* CrearNodoArbolAnimal(animal A)
{
    nodoArbol * nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));

    nuevo->dato = A;

    nuevo->der = inicArbol();
    nuevo->izq = inicArbol();

    return nuevo;
}


nodoArbol* insertarArbol(nodoArbol* arbol, registroArchivo reg)
{
    if(arbol == NULL)
    {
        arbol = CrearNodoArbol(reg);
    }
    else if(arbol->dato.cantidad > reg.cant)
    {
        arbol->izq = insertarArbol(arbol->izq, reg);
    }
    else
    {
        arbol->der = insertarArbol(arbol->der, reg);
    }

    return arbol;
}

nodoArbol* insertarArbolAnimal(nodoArbol* arbol, animal A)
{
    if(arbol == NULL)
    {
        arbol = CrearNodoArbolAnimal(A);
    }
    else if(arbol->dato.cantidad > A.cantidad)
    {
        arbol->izq = insertarArbolAnimal(arbol->izq, A);
    }
    else
    {
        arbol->der = insertarArbolAnimal(arbol->der, A);
    }

    return arbol;
}

/// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void MostrarAnimal(animal A)
{
    printf("-------------\n");
    printf("Nombre: %s\n", A.nombreAnimal);
    printf("Cantidad: %d\n", A.cantidad);
    printf("Habitat: %d\n", A.habitat);
    printf("-------------\n");
}

void MostrarCelda(celdaEspecie C)
{
    printf("###############\n");
    printf("ESPECIE: %s\n", C.especie);
    printf("ID: #%d\n", C.idEspecie);
    printf("###############\n");
}

void MostrarRegistro(registroArchivo R)
{
    printf("-------------\n");
    printf("Nombre: %s\n", R.animal);
    printf("Cantidad: %d\n", R.cant);
    printf("Habitat: %d\n", R.habitat);
    printf("-------------\n");
}

void MostrarArreglo(celdaEspecie C[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        MostrarCelda(C[i]);
        inorder(C[i].arbolDeAnimales);
    }
}

void MostrarArbol(celdaEspecie C[], int validos, char especie[])
{
    int pos = BuscarPos(C, validos, especie);

    if(pos >= 0)
    {
        inorder(C[pos].arbolDeAnimales);
    }
    else
    {
        printf("|X| NO EXISTE ESA ESPECIE |X|\n");
    }
}

void inorder(nodoArbol* arbol)
{
    if(arbol!= NULL)
    {
        inorder(arbol->izq);
        MostrarAnimal(arbol->dato);
        inorder(arbol->der);
    }

}

int BuscarPos(celdaEspecie C[], int validos, char buscado[])
{
    int encontrado = -1;
    for(int i = 0; encontrado == -1 && i < validos; i++)
    {
        if(strcmpi(buscado, C[i].especie) == 0)
        {
            encontrado = i;
        }
    }
    return encontrado;
}

int AgregarCelda(celdaEspecie C[], int validos, registroArchivo reg)
{
    strcpy(C[validos].especie, reg.especie);
    C[validos].idEspecie = reg.idEspecie;

    C[validos].arbolDeAnimales = inicArbol();

    return validos + 1;
}

int alta(celdaEspecie C[], int validos, registroArchivo reg)
{
    int pos = BuscarPos(C, validos, reg.especie);

    if(pos == -1)
    {
        validos = AgregarCelda(C, validos, reg);
        pos = validos-1;
    }

    C[pos].arbolDeAnimales = insertarArbol(C[pos].arbolDeAnimales, reg);

    return validos;
}

int LeerArchivo(celdaEspecie C[], int validos)
{
    FILE * buf = fopen(nombreAr, "rb");
    registroArchivo reg;
    int i = 0;

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
        printf("|X| ERROR AL ABRIR ARCHIVO |X|\n");
    }
    return validos;
}

void PasarArbolToArchivo(FILE * buf, nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        fwrite(&(arbol->dato), sizeof(arbol->dato), 1, buf);
        PasarArbolToArchivo(buf, arbol->izq);
        PasarArbolToArchivo(buf, arbol->der);
    }
}

void AbrirArchivoEspecie(celdaEspecie C)
{
    FILE * buf = fopen(C.especie, "ab");

    if(buf != NULL)
    {
        PasarArbolToArchivo(buf, C.arbolDeAnimales);
        fclose(buf);
    }
    else
    {
        printf("|X| ERROR AL ABRIR EL ARCHIVO '%s'|X|\n", C.especie);
    }
}

void pasarDeADAToArchivosAnimales(celdaEspecie C[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        AbrirArchivoEspecie(C[i]);
    }
}

nodoArbol* PasarArchivoArbol(char nombre[])
{
    FILE * buf = fopen(nombre, "rb");
    animal A;
    nodoArbol* arbol = inicArbol();

    if(buf != NULL)
    {
        while(fread(&A, sizeof(animal), 1, buf) > 0)
        {
            arbol = insertarArbolAnimal(arbol, A);
        }
        fclose(buf);
    }
    else
    {
        printf("|X| ERROR AL ABRIR EL ARCHIVO '%s'|X|\n", nombre);
    }

    return arbol;
}


/// /////////////////////
int main()
{
    celdaEspecie C[100];
    int validos = 0;
    nodoArbol * arbolUwu;

    validos = LeerArchivo(C, validos);


//    printf("ARREGLO: \n");
//    MostrarArreglo(C, validos);
//
//
//    printf("ARBOL: \n");
//    MostrarArbol(C, validos, "mamiferos");


    pasarDeADAToArchivosAnimales(C, validos);

    for(int i = 0; i < validos; i++)
    {
        arbolUwu = PasarArchivoArbol(C[i].especie);
        printf("\n---- ARBOL %s ------\n", C[i].especie);
        inorder(arbolUwu);
    }


    return 0;
}
