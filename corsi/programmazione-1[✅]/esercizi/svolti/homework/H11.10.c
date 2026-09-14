#include <stdio.h>
#include <math.h>

// SITEMARE IL CONTROLLO DEI NUMERI UGUALI DEI TUBI
// il programma calcola e stampa la quantit`a d’acqua raccolta in ogni vasca dopo gli M minuti specificati dall’utente

int main()
{
    // VARIABILI
    //  differenti tubi
    int numTubi[5];
    int vascaA[] = {1, 5, 6, 10};
    int portata;

    // totale minuti
    int M;

    // inserimento tubi
    printf("INSERIMENTO TUBI");
    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        int k;
        do
        {
            k = 0;
            printf("Inserisci un numero compreso tra 1 a 15: ");
            scanf("%d", &numTubi[i]);

            if (numTubi[i] < 1 || numTubi[i] > 15)
            {
                printf("\nInserimento errato (valore errato)\n");
            }

            for (int j = 0; j < i; j++)
            {
                if (numTubi[i] == numTubi[j])
                {
                    printf("\nInserimento errato (duplicato)\n");
                    k = 1;
                }
            }

        } while (numTubi[i] < 1 || numTubi[i] > 15 || k == 1);
    }

    // inserimento minuti
    printf("\n");
    printf("INSERIMENTO MINUTI");
    do
    {
        printf("\nInserisci il numero totale di minuti(M): ");
        scanf("%d", &M);

        if (M <= 0)
        {
            printf("\nInserimento errato");
        }

    } while (M <= 0);

    printf("\n");

    printf("\n");

    // CONTROLLO QUANTITÁ ACQUA RACCOLTA PER OGNI VASCA
    int A = 0;
    int B = 0;
    int C = 0;
    for (int i = 0; i < 5; i++)
    {
        // La vasca A riceve l’acqua convogliata nei tubi 1, 5, 6, 10.
        // La vasca B riceve l’acqua convogliata nei tubi da 2 a 4 e da 7 a 9.
        // La vasca C riceve l’acqua convogliata nei rimanenti tubi.

        for (int j = 0; j < 4; j++)
        {
            if (numTubi[i] == vascaA[j])
            {
                A++;
            }
        }

        if (numTubi[i] > 1 && numTubi[i] < 5 || numTubi[i] > 6 && numTubi[i] < 10)
        {
            B++;
        }

        if (numTubi[i] > 10)
        {
            C++;
        }
    }

    A = 0;
    B = 0;
    C = 0;
    for (int i = 0; i < 5; i++)
    {
        if (numTubi[i] % 2 != 0)
        {
            // Dispari
            portata = 60;
        }
        else
        {
            // Pari
            portata = 120;
        }

        if (numTubi[i] == 1 || numTubi[i] == 5 || numTubi[i] == 6 || numTubi[i] == 10)
        {
            A += portata;
        }
        else if ((numTubi[i] >= 2 && numTubi[i] <= 4) || (numTubi[i] >= 7 && numTubi[i] <= 9))
        {
            B += portata;
        }
        else
        {
            C += portata;
        }
    }

    if (A > 0)
    {
        printf("\nVasca A: %d litri d'acqua", A * M);
    }
    else
    {
        printf("\nLa vasca A é vuota");
    }
    if (B > 0)
    {
        printf("\nVasca B: %d litri d'acqua", B * M);
    }
    else
    {
        printf("\nLa vasca B é vuota");
    }
    if (C > 0)
    {
        printf("\nVasca C: %d litri d'acqua", C * M);
    }
    else
    {
        printf("\nLa vasca C é vuota");
    }
    printf("\n");
}