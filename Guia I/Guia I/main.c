#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char ContNY()
{
    printf("\nDesea continuar? ");
    fflush(stdin);
    char cont = getch();
    return cont;
}

void CargarString(char string[])
{
    printf("Escriba el string:");
    fflush(stdin);
    scanf("%s", string);
}

void InvertirString(char string[], char stringInv[])
{
    int j = strlen(string) - 1;
    for(int i = 0; i < strlen(string); i++)
    {
        stringInv[i] = string[j];
        j--;
    }
}

int ReturnInt(int arr[], int val)
{
    int mult = pow(10, (val-1));
    int aux;
    int suma = 0;
    for(int i = 0; i < val; i++)
    {
        aux = arr[i];
        suma = suma + aux*mult;
        mult = mult*0.1;
    }
    return suma;
}

int BuscarMayor(int arr[], int val)
{
    int may = arr[0];
    for(int i = 1; i < val; i++)
    {
        if(may < arr[i])
        {
            may = arr[i];
        }
    }
    return may;
}

int BuscarMenorArreglo(int arr[], int val)
{
    int posMen = 0;
    for(int i = 1; i < val; i++)
    {
        if(arr[posMen] > arr[i])
        {
            posMen = i;
        }
    }
    return posMen;
}

void CargarMatrizRand(int mat[][31], int filas)
{
    srand(time(NULL));
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < 31; j++)
        {
            mat[i][j] = rand() % 100;
        }
    }
}

void MostrarMatriz(int mat[][31], int filas)
{
    for(int i = 0; i < filas; i++)
    {
        printf("| ");
        for(int j = 0; j < 31; j++)
        {
            printf(" %d |", mat[i][j]);
        }
        printf("\n");
    }
}

int BuscarMayorFila(int Mat[][31], int filaBus, int columnas)
{
    int mayor = 0; //Pos mayor en columnas
    int fila = filaBus - 1;

    for(int i = 1; i < columnas; i++)
    {
        if(Mat[fila][mayor] < Mat[fila][i])
        {
            mayor = i;
        }
    }
    return mayor;
}

void PasarMayoresToArray(int matriz[][31], int columnas, int arrPos[])
{
    for(int i = 0; i < 12; i++)
    {
        arrPos[i] = BuscarMayorFila(matriz, (i+1), columnas);
    }
}

void MostrarArrInt(int arr[], int val)
{
    printf("|");
    for(int i = 0; i < val; i++)
    {
        printf(" %d |", arr[i]);
    }
}

void MostrarMatStr(char str[][100], int val)
{
    for(int i = 0; i < val; i++)
    {
        printf("| %s ", str[i]);
    }
}

int EsPalindromo(char str[])
{
    int j = strlen(str) -1;
    int flag = 1;
    puts(str);
    for(int i = 0; flag == 1 && i < (strlen(str)/2); i++)
    {
        if(str[i] != str[j])
        {
            flag = 0;
        }
        j--;
    }
    return flag;
}

void CambiarDosVar(int *a, char *b)
{
    printf("\nEscribe por que cambiar el numero: ");
    scanf("%d", &*a);

    printf("\nEscribe por que cambiar la letra: ");
    fflush(stdin);
    scanf("%c", &*b);
}

int CargarApellidoAndEdad(int edades[], char apellidos[][100])
{
    char cont = 'y';
    char aux[100];
    int i = 0;
    while(cont == 'y')
    {
        printf("\nEscriba el apellido: ");
        fflush(stdin);
        gets(aux);
        strcpy(apellidos[i], aux);

        printf("Escriba la edad: ");
        scanf("%d", &edades[i]);

        i++;

        cont = ContNY();
    }
    return i;
}

int BuscarMayorArreglo(int arr[], int val)
{
    int posMayor = 0;
    for(int i = 0; i < val; i++)
    {
        if(arr[posMayor] < arr[i])
        {
            posMayor = i;
        }
    }
    return posMayor;
}

void MostrarMayorApellido(int edades[], char apellidos[][100], int val)
{
    int posMayor = BuscarMayorArreglo(edades, val);
    printf("\nEdad: %d", edades[posMayor]);
    printf("\nApellido: %s", apellidos[posMayor]);
}

int IntercalarArrays(int arr1[], int val1, int arr2[], int val2, int arrInter[])
{
    int total = val1 + val2;
    int i = 0;
    int i1 = 0;
    int i2 = 0;

    while(i1 < val1 && i2 < val2)
    {
        if(arr1[i1] < arr2[i2])
        {
            arrInter[i] = arr1[i1];
            i1++;
            i++;
        }
        else
        {
            arrInter[i] = arr2[i2];
            i2++;
            i++;
        }
    }

    if(i1 >= val1)
    {
        while(i2 < val2)
        {
            arrInter[i] = arr2[i2];
            i++;
            i2++;
        }
    }
    else if(i2 >= val2)
    {
        while(i1 < val1)
        {
            arrInter[i] = arr1[i1];
            i++;
            i1++;
        }
    }

    return total;
}

float CalcPromedioArr(int arr[], int val)
{
    float promedio;
    float suma = 0;

    for(int i = 0; i < val; i++)
    {
        suma = suma + arr[i];
    }

    promedio = suma / val;
    return promedio;
}

void AnalizarArrInt(int arrInt[], int dim, int *valMax, int *valMin, float *valProm)
{
    int posMayor = BuscarMayorArreglo(arrInt, dim);
    int posMenor = BuscarMenorArreglo(arrInt, dim);

    *valMax = arrInt[posMayor];
    *valMin = arrInt[posMenor];
    *valProm = CalcPromedioArr(arrInt, dim);
}

///-------------------------------------------------------

int main()
{
    char cont = 'y';
    int numSw;

    char arr[100];
    char arrAux[100];
    int arrNum[] = {9, 6, 7, 4};

    int dayMat[12][31];

    int queFila;
    int mayorCol;

    int arrMayoresP[12];

    char arrPal[15] = "sasas";
    int esPal;

    int var1 = 10;
    char var2 = 'c';

    int valArrPar;
    int edades[100];
    char apellidos[100][100];

    int num1[] = {1, 3, 6, 8, 11};
    int num2[] = {2, 4, 5, 9, 10};
    int arrInter[15];
    int valTotal;

    int arrEnteros[] = {3, 9, 6, 4, 2, 10, 1, 6, 2};
    int valMax, valMin;
    float valProm;

    while(cont == 'y')
    {
        printf("Seleccione el ejercicio: ");
        scanf("%d", &numSw);

        switch(numSw)
        {
        case 1:
            {
                printf("1.");
                break;
            }
        case 2:
            {
                CargarString(arr);
                InvertirString(arr, arrAux);
                puts(arrAux);
                break;
            }

        case 3:
            {
                printf("El numero todo junto es: %d\n", ReturnInt(arrNum, 4));

                break;
            }

        case 4:
            {
                printf("El numero mas grande es el %d", BuscarMayor(arrNum, 4));

                break;
            }

        case 5: ///CHECK
            {
                CargarMatrizRand(dayMat, 12);
                MostrarMatriz(dayMat, 12);

                printf("\nNumeros mayores de cada fila: \n");
                PasarMayoresToArray(dayMat, 31, arrNum);
                MostrarArrInt(arrNum, 12);

                break;
            }

        case 6: //Determinar si es palindromo y devolver 1 o 0.
            {
                esPal = EsPalindromo(arrPal);
                if(esPal == 1)
                {
                    printf("Es palindromo\n");
                }
                else
                {
                    printf("No es palindromo\n");
                }
                break;
            }

        case 7: //Cambiar el contenido de dos variables
            {
                printf("Variables antes:\na: %d | b: %c", var1, var2);

                CambiarDosVar(&var1, &var2);

                printf("Variables despues:\na: %d | b: %c", var1, var2);
                break;
            }

        case 8: //2 arr ordenados, intercalar y q queden ordenados (- a +)
            {
                valTotal = IntercalarArrays(num1, 5, num2, 5, arrInter);
                MostrarArrInt(arrInter, valTotal);

                break;
            }

        case 9: //dado dos arreglos paralelos (appelidos y edades)
                //determinar el apellido de la persona con mayor edad
            {
                valArrPar = CargarApellidoAndEdad(edades, apellidos);

                MostrarMayorApellido(edades, apellidos, valArrPar);

                break;
            }

        case 10:
            {
                AnalizarArrInt(arrEnteros, 9, &valMax, &valMin, &valProm);
                printf("Val Max: %d\nVal Min: %d\nVal Promedio: %.2f", valMax, valMin, valProm);

                break;
            }

        default:
            {
                puts("Escriba un numero valido.");
                break;
            }
        }

        cont = ContNY();
    }
    return 0;
}
