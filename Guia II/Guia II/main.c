#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>

typedef struct
{
    char nombre[30];
    char genero;
    int edad;
} stPersona;

typedef struct
{
    int matricula;
    char nombre[30];
} stAlumno;

typedef struct
{
    int codigo;
    char nombreMat[30];
} stMateria;

typedef struct
{
    int matricula;
    int codigo;
    int nota;
} stNota;

int CargarArregloPersonas(stPersona arr[], int dim)
{
    char cont = 'y';
    int val = 0;

    while(cont == 'y' && val < dim)
    {
        printf("Escriba el nombre: \n");
        fflush(stdin);
        gets(arr[val].nombre);
        printf("\nEscriba el genero (m/f/o)\n");
        fflush(stdin);
        scanf("%c", &arr[val].genero);
        printf("\nEscriba la edad: \n");
        scanf("%d", &arr[val].edad);

        val++;

        printf("\nDesea seguir ingresando datos? 'y/n'\n");
        fflush(stdin);
        scanf("%c", &cont);
    }
    return val;
}

void MostrarArregloPersonas(stPersona arr[], int val)
{
    for(int i = 0; i < val; i++)
    {
        puts("--------------");
        printf("Nombre: %s\n", arr[i].nombre);
        printf("Genero: %c\n", arr[i].genero);
        printf("Edad: %d\n", arr[i].edad);
        puts("--------------\n\n");
    }
}

int ContarGeneroArregloPersonas(stPersona arr[], int val, char generoBuscado)
{
    int suma = 0;
    for(int i = 0; i < val; i++)
    {
        if(arr[i].genero == generoBuscado)
        {
            suma++;
        }
    }
    return suma;
}

int EncontrarPosMenor(stPersona arr[], int val, int currPos)
{
    int posMenor = currPos;
    for(int i = currPos + 1; i < val; i++)
    {
        if(arr[i].edad < arr[posMenor].edad)
        {
            posMenor = i;
        }
    }
    return posMenor;
}

void OrdenamientoSeleccion(stPersona arr[], int val)
{
    int posMenor;
    stPersona aux;
    for(int i = 0; i < val; i++)
    {
        posMenor = EncontrarPosMenor(arr, val, i);

        aux = arr[i];
        arr[i] = arr[posMenor];
        arr[posMenor] = arr[i];
    }
}

void CargarPila(Pila *pila)
{
    char cont = 'y';
    int dato;
    while(cont == 'y')
    {
        printf("Escriba un numero: ");
        scanf("%d", &dato);
        apilar(pila, dato);

        printf("\nDeseas continuar? 'y/n'\n");
        cont = getch();
    }
}

void PasarUnaPilaAOtra(Pila pilaQuePasa, Pila *aPasar)
{
    while(!pilavacia(&pilaQuePasa))
    {
        apilar(aPasar, desapilar(&pilaQuePasa));
    }
}

void PasarPilasIntercalado(Pila pila1, Pila pila2, Pila *pilaInterc)
{
    Pila aux1, aux2;
    inicpila(&aux2);
    inicpila(&aux1);

    PasarUnaPilaAOtra(pila1, &aux1);
    PasarUnaPilaAOtra(pila2, &aux2);

    while(!pilavacia(&aux1) && !pilavacia(&aux2))
    {
        if(tope(&aux1) < tope(&aux2))
        {
            apilar(&pilaInterc, desapilar(&aux1));
        }
        else
        {
            apilar(&pilaInterc, desapilar(&aux2));
        }
    }

    if(!pilavacia(&aux1))///VERIFICAR POR QUE CUANDO VUELVE DE ACA
    {                      /// FUNCA MAL
        PasarUnaPilaAOtra(aux1, &pilaInterc);
    }
    else if(!pilavacia(&aux2))
    {
        PasarUnaPilaAOtra(aux2, &pilaInterc);
    }
}

void MostrarArregloEnteros(int arr[], int val)
{
    printf("|");
    for(int i = 0; i < val; i++)
    {
        printf(" %d |", arr[i]);
    }
}

void InsertarEnArreglo(int arr[], int ult, int dato)
{
    int i = ult;
    while(i >= 0 && dato < arr[i])
    {
        arr[i+1] = arr[i];
        i--;
    }
    arr[i+1] = dato;
}

void OrdenamientoInsercion(int arrDesord[], int val) ///Revisar
{
    int i = 0;
    while(i < val - 2)
    {
        InsertarEnArreglo(arrDesord, (val-1), arrDesord[i+1]);
        i++;
    }
}

int BuscarDatoArreglo(int arr[], int val, int dato)
{
    int posDato = -1;

    for(int i = 0; posDato == -1 && i < val; i++)
    {
        if(arr[i] == dato)
        {
            posDato = i;
        }
    }

    return posDato;
}

void PasarPosAUltimo(int arr[], int val, int posDesde)
{
    int aux = arr[posDesde];
    for(int i = posDesde; i < val; i++)
    {
        arr[i] = arr[i+1];
    }
    arr[val-1] = aux;
}

int EliminarIntArreglo(int arr[], int val, int dato)
{
    int pos = BuscarDatoArreglo(arr, val, dato);
    if(pos != -1)
    {
        PasarPosAUltimo(arr, val, pos);
    }
    else
    {
        puts("Dato no encontrado");
    }
    return val - 1;
}

//8.
int CargarMaterias(stMateria arr[], int dim)
{
    char cont = 'y';
    int i;

    for(i = 0; i < dim && cont == 'y'; i++)
    {
        printf("\nEscriba el codigo de la materia: ");
        scanf("%d", &arr[i].codigo);
        printf("\nEscriba el nombre de la materia: ");
        fflush(stdin);
        gets(arr[i].nombreMat);

        printf("\nDesea seguir agregando datos? 'y/n'\n");
        cont = getch();
    }

    return i;
}

void MostrarMaterias(stMateria arr[], int val)
{
    for(int i = 0; i < val; i++)
    {
        printf("Nombre de materia: ");
        puts(arr[i].nombreMat);
        printf("Codigo: %d\n", arr[i].codigo);
    }
}

stAlumno CargarAl()
{
    stAlumno al;
    printf("Escriba la matricula: ");
    scanf("%d", &al.matricula);
    printf("Escriba el nombre: ");
    fflush(stdin);
    gets(al.nombre);
    return al;
}

int CargarAlumnos(stAlumno arr[], int dim)
{
    int i = 0;
    char cont = 'y';
    for(i; i < dim && cont == 'y'; i++)
    {
        arr[i] = CargarAl();

        puts("Quiere seguir agregando datos? 'y/n'");
        fflush(stdin);
        scanf("%c", &cont);
    }
    return i;
}

void MostrarAlumnos(stAlumno arr[], int val)
{
    for(int i = 0; i < val; i++)
    {
        printf("Matricula: %d\n", arr[i].matricula);
        printf("Nombre del alumno: ");
        puts(arr[i].nombre);
    }
}

int ValidarNotaCodigo(stMateria mat[], int valMat, stNota nota)
{
    int valid = 0;
    for(int i = 0; valid == 0 && i < valMat; i++)
    {
        if(mat[i].codigo == nota.codigo)
        {
            valid = 1;
        }
    }
    return valid;
}

int ValidarNotaMatricula(stAlumno al[], int valAl, stNota nota)
{
    int valid = 0;
    for(int i = 0; valid == 0 && i < valAl; i++)
    {
        if(al[i].matricula == nota.matricula)
        {
            valid = 1;
        }
    }
    return valid;
}

stNota CargarNota(stAlumno al[], int valAl, stMateria mat[], int valMat)
{
    stNota nota;

    printf("Escriba el codigo: ");
    scanf("%d", &nota.codigo);
    while(ValidarNotaCodigo(mat, valMat, nota) == 0)
    {
        puts("\nEl codigo no coincide, ingreselo nuevamente: ");
        scanf("%d", &nota.codigo);
    }

    printf("\nEscriba la matricula: ");
    scanf("%d", &nota.matricula);
    while(ValidarNotaMatricula(al, valAl, nota) == 0)
    {
        puts("\nLa matricula no coincide, ingresela nuevamente: ");
        scanf("%d", &nota.matricula);
    }

    printf("\nEscriba la nota: ");
    scanf("%d", &nota.nota);

    return nota;
}

int CargarNotas(stNota arr[], int dim, stAlumno al[], int valAl, stMateria mat[], int valMat)
{
    int i = 0;
    char cont = 'y';

    for(i; i < dim && cont == 'y'; i++)
    {
        arr[i] = CargarNota(al, valAl, mat, valMat);

        puts("Quieres continuar? 'y/n'");
        fflush(stdin);
        cont = getch();
    }

    return i;
}

void MostrarNotas(stNota nota)
{
    printf("Matricula: %d\n", nota.matricula);
    printf("Codigo: %d\n", nota.codigo);
    printf("Nota: %d\n", nota.nota);
}

void MostrarNombreMateriaPorCodigo(stMateria arr[], int val, int codigo)
{
    for(int i = 0; i < val; i++)
    {
        if(arr[i].codigo == codigo)
        {
            printf("%s", arr[i].nombreMat);
        }
    }
}

void MostrarNotaAlumno(stNota nota, stMateria arrMaterias[], int valMats)
{
    printf("Materia: ");
    MostrarNombreMateriaPorCodigo(arrMaterias, valMat, nota.codigo);
    printf("Nota: ", nota.nota);
}



void MostrarDatosAlumno(stAlumno alus[], int valAl, char nombreAl[])
{
    int encontrado = 0;
    for(int i = 0; encontrado == 0 && i < valAl; i++)
    {
        if(strcmpi(alus[i].nombre, nombreAl) == 0)
        {

        }
    }
}

///-----------------------------------------------------\\\
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |||
///-----------------------------------------------------///

int main()
{
    //1.
    stPersona arrPersonas[30];
    int validosPers;
    char generoBusc;
    int cantGeneroBusc;

    //4.
    Pila pila1, pila2, pilaInterc;
    inicpila(&pila1);
    inicpila(&pila2);
    inicpila(&pilaInterc);

    //5.
    int arrOrdenadoInsertar[] = {1, 3, 5, 6, 7, 10};
    int dato = 2;
    int newVal;

    //6.
    int arrDesordInsertar[] = {4, 2, 9, 1, 8, 3, 10, 5};

    //7.
    int arrEliminar[] = {2, 6, 3, 9, 5};
    int valEliminar = 5;
    int encontrado;

    //8.
    stAlumno alus[20]; // para almacenar los datos de los 20 alumnos.
    stMateria mats[5]; // para almacenar los códigos y nombres de las 5 materias.
    stNota notas[100]; // para almacenar todas las notas de los alumnos.
    int valAlus, valMats, valNotas;

    int numSw;
    char cont = 'y';

    while(cont == 'y')
    {
        printf("Escriba el numero del ejercicio: ");
        scanf("%d", &numSw);

        switch(numSw)
        {
        case 1:
        {
            validosPers = CargarArregloPersonas(arrPersonas, 30);
            MostrarArregloPersonas(arrPersonas, validosPers);

            printf("Escribe el genero a buscar: ");
            fflush(stdin);
            scanf("%c", &generoBusc);
            cantGeneroBusc = ContarGeneroArregloPersonas(arrPersonas, validosPers, generoBusc);

            printf("Hay %d del genero '%c'", cantGeneroBusc, generoBusc);

            break;
        }

        case 2: //Ord seleccion por edad
        {
            OrdenamientoSeleccion(arrPersonas, validosPers);
            MostrarArregloPersonas(arrPersonas, validosPers);

            break;
        }

        case 3:
            {

                break;
            }

        case 4: //Intercalar ordenadamente dos pilas
            {
                CargarPila(&pila1);
                CargarPila(&pila2);
                mostrar(&pila1);
                mostrar(&pila2);

                PasarPilasIntercalado(pila1, pila2, &pilaInterc);
                printf("\nPila luego de ser intercalada: ");
                mostrar(&pilaInterc);

                break;
            }

        case 5: //Insertar en un arreglo ordenado
            {
                InsertarEnArreglo(arrOrdenadoInsertar, 6, dato);
                MostrarArregloEnteros(arrOrdenadoInsertar, 7);

                break;
            }

        case 6: //Ordenamiento insercion
            {
                OrdenamientoInsercion(arrDesordInsertar, 8);
                MostrarArregloEnteros(arrDesordInsertar, 8);

                break;
            }

        case 7: //Función eliminar un elemento de un arreglo. (ver por desplazamiento si es ordenado)
            {
                puts("Arreglo antes de eliminar el 6");
                MostrarArregloEnteros(arrEliminar, valEliminar);

                valEliminar = EliminarIntArreglo(arrEliminar, valEliminar, 6);
                puts("Arreglo despues de eliminar");

                MostrarArregloEnteros(arrEliminar, valEliminar);

                break;
            }

        case 8:
            {
                //Cargar el arreglo de las materias
                valMats = CargarMaterias(mats, 5);
                MostrarMaterias(mats, valMats);

                //Cargar alumnos
                valAlus = CargarAlumnos(alus, 20);
                MostrarAlumnos(alus, valAlus);

                //Cargar notas
                valNotas = CargarNotas(notas, 100, alus, valAlus, mats, valMats);

                //Mostrar todo


                break;
            }

        default:
        {

            break;
        }
        }
        puts("Desea continuar? y/n\n");
        fflush(stdin);
        cont = getch();
    }

    return 0;
}
