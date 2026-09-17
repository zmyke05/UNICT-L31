#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
    int numPersone;
    char presDiabetici[2];
    // Base
    float farinaBase = 0.3;
    float uovaBase = 4;
    float zuccheroBase = 0.1;

    // Medio
    float farinaMedio = 2.5 * farinaBase;
    float uovaMedio = 2.5 * uovaBase;
    float zuccheroMedio = 1.5 * zuccheroBase;

    // Grande
    float farinaGrande = farinaBase + farinaMedio;
    float uovaGrande = uovaBase + uovaMedio;
    float zuccheroGrande = zuccheroBase + zuccheroMedio;

    // Finali
    float farinaFinale;
    float uovaFinale;
    float zuccheroFinale;
    float dolcificante;

    // Numero persone comprese da 2 a 16
    do
    {
        printf("\nInserisci un numero di persone compreso tra 2 e 16: ");
        scanf("%d", &numPersone);

        if (numPersone < 2 && numPersone > 16)
        {
            printf("\nInseramento errato.");
        }

    } while (numPersone < 2 && numPersone > 16);

    printf("\nInserimento corretto");

    // Controllo Diabetici
    do
    {
        printf("\nCi sono diabetici? si/no: ");
        scanf("%s", presDiabetici);

        if (strcasecmp(presDiabetici, "si") != 0 && strcasecmp(presDiabetici, "no") != 0)
        {
            printf("\nInseramento errato.");
        }

    } while (strcasecmp(presDiabetici, "si") != 0 && strcasecmp(presDiabetici, "no") != 0);

    printf("\nInserimento corretto");
    printf("\n");

    if (numPersone >= 2 && numPersone <= 4)
    {
        farinaFinale = farinaBase;
        uovaFinale = uovaBase;
        zuccheroFinale = zuccheroBase;
    }
    else if (numPersone >= 5 && numPersone <= 8)
    {
        farinaFinale = farinaMedio;
        uovaFinale = uovaMedio;
        zuccheroFinale = zuccheroMedio;
    }
    else
    {
        farinaFinale = farinaGrande;
        uovaFinale = uovaGrande;
        zuccheroFinale = zuccheroGrande;
    }

    if(strcmp(presDiabetici, "si") == 0)
    dolcificante = 2.0/3.0 * zuccheroFinale;
    else
    dolcificante = zuccheroFinale;

    uovaFinale = ceil(uovaFinale);
    printf("\n%.2fkg farina, %.0f uova, %.2fkg zucchero", farinaFinale, uovaFinale, dolcificante);

    printf("\n");
}