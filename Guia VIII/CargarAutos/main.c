#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char marca[20]; ///Ford,Fiat,Volkswagen,Chevrolet.
    char modelo[20];
    int precio;  ///5000 < X < 60.000
    char categoria[20]; /// Sedan, Suv, PickUp, Van, Coupe.
    int anio;
} Autos;
/// ////
Autos CargarAuto()
{
    Autos aut;
    printf("\nMARCA: ");
    fflush(stdin);
    gets(aut.marca);
    printf("\nMODELO: ");
    fflush(stdin);
    gets(aut.modelo);
    printf("\nCATEGORIA: ");
    fflush(stdin);
    gets(aut.categoria);
    printf("\nANIO: ");
    scanf("%d", &aut.anio);
    printf("\nPRECIO: $");
    scanf("%d", &aut.precio);

    return aut;
}

MostrarAuto(Autos A)
{
    printf("\nMARCA: %s", A.marca);
    printf("\nMODELO: %s", A.modelo);
    printf("\nCATEGORIA: %s", A.categoria);
    printf("\nANIO: %d", A.anio);
    printf("\nPRECIO: $%d", A.precio);
}

void CargarArchivo(char nombreAr[])
{
    FILE *buf = fopen(nombreAr, "ab");
    Autos A;
    char cont = 's';
    char ver;

    if(buf != NULL)
    {
        while(cont == 's')
        {
            A = CargarAuto();
            printf("\n-------- # --------\n");
            MostrarAuto(A);
            printf("\n>>>> DESEA CARGAR ESTE AUTO? <<<<\n");
            fflush(stdin);
            ver = getch();
            if(ver == 's')
            {
                printf("!!! AUTO CARGADO EXITOSAMENTE !!!\n");
                fwrite(&A, sizeof(Autos), 1, buf);

            }
            else
            {
                printf("|X| NO SE CARGO EL AUTO |X|\n");
            }

            printf("\nDesea continuar? ('s'/'n')");
            fflush(stdin);
            cont = getch();
        }
        fclose(buf);
    }
    else
    {
        puts("|X| ERROR AL ABRIR EL ARCHIVO |X|");
    }
}




int main()
{
    char nombreAr[] = {"Autos.bin"};

    CargarArchivo(nombreAr);

    return 0;
}
