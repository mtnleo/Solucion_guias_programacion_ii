#include <stdio.h>
#include <stdlib.h>

int factorial(int x)
{
    int rta;

    if(x == 0)
    {
        rta = 1;
    }
    else
    {
        rta = x * factorial(x-1);
    }

    return rta;
}

int potencia(int base, int pot)
{
    int rta;

    if(pot == 0)
    {
        rta = 1;
    }
    else
    {
        rta = base * potencia(base, pot - 1);
    }

    return rta;
}

void MostrarArregloRecursivo(int arr[], int val, int i)
{
    if(i == val)
    {
        printf("\n");
    }
    else
    {
        printf("| %d |", arr[i]);
        MostrarArregloRecursivo(arr, val, i+1);
    }
}

void MostrarArregloRecursivoInverso(int arr[], int val, int i)
{
    if(i == val)
    {
        printf("\n");
    }
    else
    {
        MostrarArregloRecursivoInverso(arr, val, i+1);
        printf("| %d |", arr[i]);
    }
}

int Capicua(int arr[])
{
    int esCapicua;
}

int Sumar(int arr[], int val, int pos)
{
    int suma = 0;
    if(val == pos)
    {
        suma = 0;
    }
    else
    {
        suma = arr[pos] + Sumar(arr, val, pos+1);
    }
    return suma;
}

int BuscarMenor(int arr[], int val, int i, int posMenor)
{
    if(val == i)
    {
        posMenor = posMenor;
    }
    else
    {
        if(arr[i] < arr[posMenor])
        {
            posMenor = BuscarMenor(arr, val, i+1, i);
        }
        else
        {
            posMenor = BuscarMenor(arr, val, i+1, posMenor);
        }

    }
    return posMenor;
}

void PasarArregloToArchivo(char nombreAr[], int arr[], int val)
{
    FILE *buf = fopen(nombreAr, "ab");
    if(buf != NULL)
    {
        for(int i = 0; i < val; i++)
        {
            fwrite(&arr[i], sizeof(int), 1, buf);
        }
        fclose(buf);
    }
    else
    {
        printf("\n|X| ERROR AL ABRIR EL ARCHIVO |X|\n");
    }
}

void LeerArchivo(char nombreAr[])
{
    FILE *buf = fopen(nombreAr, "rb");
    int num;

    if(buf != NULL)
    {
        while(fread(&num, sizeof(int), 1, buf) != 0)
        {
            printf("| %d |", num);
        }
        fclose(buf);
    }
    else
    {
        printf("\n|X| ERROR AL ABRIR EL ARCHIVO |X|\n");
    }
}

int BuscarMenorArchivo(FILE * buf, int pos, int posMenor)
{
    int num, numMenor;

    fseek(buf, (pos*sizeof(int)-sizeof(int)), SEEK_SET);
    fread(&num, sizeof(int), 1, buf);

        if(!feof(buf))
        {
            fseek(buf, (posMenor*sizeof(int)-sizeof(int)), SEEK_SET);

            if(!feof(buf))
            {
                fread(&numMenor, sizeof(int), 1, buf);
            }

            if(num < numMenor)
            {
                posMenor = BuscarMenorArchivo(buf, pos+1, pos);
            }
            else
            {
                posMenor = BuscarMenorArchivo(buf, pos+1, posMenor);
            }
        }
    }


int AbrirArchivoBuscarMenor(char nombreAr[])
{
    int posMenor;
    FILE *buf = fopen(nombreAr, "rb");

    if(buf == NULL)
    {
        printf("\n|X| ERROR AL ABRIR EL ARCHIVO |X|\n");
    }
    else
    {
        posMenor = BuscarMenorArchivo(buf, 1, 1);

        fclose(buf);
    }
}

void MostrarArchivoInversa(FILE * buf, int pos)
{
    int num;

    fseek(buf, pos*sizeof(int), SEEK_SET);
    fread(&num, sizeof(int), 1, buf);


    if(!feof(buf))
    {
        MostrarArchivoInversa(buf, pos+1);

        printf("| %d | ", num);
    }
}

void AbrirArchivoMostrarInversa(char nombreAr[])
{
    int pos = 0;

    FILE *buf = fopen(nombreAr, "rb");
    if(buf != NULL)
    {
        MostrarArchivoInversa(buf, pos);

        fclose(buf);
    }
    else
    {
        puts("\n |X| ERROR AL ABRIR EL ARCHIVO |X|");
    }
}

void MostrarCharReversa()
{
    char car;

    printf("\nEscriba un caracter: ");
    fflush(stdin);
    scanf("%c", &car);

    if(car != '*')
    {
        MostrarCharReversa();

        printf("'%c'", car);
    }
}

int SaberValidosArchivo(FILE * buf)
{
    int cant;

    fseek(buf, 0, SEEK_END);
    cant = ftell(buf)/sizeof(int);

    return cant;
}

void InvertirArchivoRecursiva(FILE *buf, int i, int j, int cant)
{
    int aux1, aux2;

    if(i < cant/2)
    {
        fseek(buf, sizeof(int)*i, SEEK_SET);
        fread(&aux1, sizeof(int), 1, buf);

        fseek(buf, sizeof(int)*(j-1), SEEK_END);
        fread(&aux2, sizeof(int), 1, buf);

        fseek(buf, sizeof(int)*i, SEEK_SET);
        fwrite(&aux2, sizeof(int), 1, buf);

        fseek(buf, sizeof(int)*(j-1), SEEK_END);
        fwrite(&aux1, sizeof(int), 1, buf);

        InvertirArchivoRecursiva(buf, i+1, j-1, cant);
    }
}

void AbrirArchivoInvertir(char nombreAr[])
{
    FILE *buf = fopen(nombreAr, "r+b");
    if(buf != NULL)
    {
        int val = SaberValidosArchivo(buf);

        InvertirArchivoRecursiva(buf, 0, 0, val);

        fclose(buf);
    }
    else
    {
        printf("\n|X| ERROR AL ABRIR EL ARCHIVO |X|\n");
    }
}

///-----------------------------------

int main()
{
    char cont = 'y';
    int numSw;

    while(cont == 'y')
    {
        printf("\nEscriba el numero del ejercicio a realizar: ");
        scanf("%d", &numSw);

        //1.
        int sacarFactorial, rtaFactorial;

        //2.
        int basePotencia, potPotencia, rtaPotencia;

        //3. y 4.
        int arr[] = {4, 2, 0, 2, 5, 3, 5};
        int val;

        //5.

        //6.
        int sumaArr[] = {4, 2, 7, 3, 5};
        int valSuma = 5;
        int suma;

        //7.
        int arrBuscarMenor[] = {3, 5, 9, 8, -3, 6};
        int valMenor = 6;
        int posMenor = 0;

        //9.
        int valArchi;

        //8. y 10.
        int arrArchivo[] = {2, 6, 1, 3, 7, 9};
        int valAr = 6;
        char nombreAr[] = {"archivoArrInt.bin"};
        int posMenorAr;

        switch(numSw)
        {
        case 1: //Calcular el factorial de un número en forma recursiva.
        {
            printf("Escriba el numero del que quiere saber su factorial: ");
            scanf("%d", &sacarFactorial);

            rtaFactorial = factorial(sacarFactorial);
            printf("| %d! | = | %d |", sacarFactorial, rtaFactorial);
            break;
        }

        case 2: //Calcular la potencia de un número en forma recursiva.
        {
            printf("Escriba el numero del que quiere saber su potencia: ");
            scanf("%d", &basePotencia);
            printf("\nA que potencia lo quieres elevar?\n");
            scanf("%d", &potPotencia);

            rtaPotencia = potencia(basePotencia, potPotencia);

            printf("| %d^%d | = | %d |", basePotencia, potPotencia, rtaPotencia);

            break;
        }

        case 3: //Recorrer un arreglo y mostrar sus elementos en forma recursiva.
        {
            MostrarArregloRecursivo(arr, 7, 0);

            break;
        }

        case 4:
        {
            MostrarArregloRecursivoInverso(arr, 7, 0);

            break;
        }

        case 5:
        {


            break;
        }

        case 6: //Sumar recursivo
        {
            suma = Sumar(sumaArr, valSuma, 0);
            printf("El resultado de la suma es: %d", suma);

            break;
        }

        case 7: //Buscar menor recursivo
        {
            posMenor = BuscarMenor(arrBuscarMenor, valMenor, posMenor, posMenor);
            printf("\nEl menor se encuentra en la posicion %d, y es el numero %d", posMenor, arrBuscarMenor[posMenor]);

            break;
        }

        case 8: //Buscar menor en archivo recursivo
        {
            PasarArregloToArchivo(nombreAr, arrArchivo, valAr);
            LeerArchivo(nombreAr);
            posMenorAr = BuscarMenorArchivo(nombreAr, 1, 1);
            printf("\nEl numero menor del archivo se encuentra en la posicion %d", posMenorAr);

            break;
        }

        case 9: //Invertir archivo recursivo
        {
            LeerArchivo(nombreAr);
            printf("\n");
            AbrirArchivoInvertir(nombreAr);
            LeerArchivo(nombreAr);

            break;
        }

        case 10: //Mostrar archivo al reves recursivo
        {
            LeerArchivo(nombreAr);
            puts("\n");
            AbrirArchivoMostrarInversa(nombreAr);

            break;
        }

        case 11: //Mostrar char inversa hasta *
        {
            MostrarCharReversa();

            break;
        }

        case 12: //Encontrar numero recursiva
        {


            break;
        }

        default:
        {
            puts("\nEscriba un ejercicio valido.");
        }
        }

        printf("\nDesea continuar? 'y/n'");
        cont = getch();
    }

    return 0;
}
