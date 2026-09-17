// ------------------------------------------
// #INCLUDE
// ------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------------------
// STRUCT
// ------------------------------------------
typedef struct
{
    char IN[256];
    char OUT[256];
    unsigned int n, m;
} parameters;

// ------------------------------------------
// PROTOTYPES
// ------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
double ***allocMatrix(int a, int b);
void readMatrix(double ***matrix, parameters *pars);
void printMatrix(double ***matrix, int a, int b);
double ***transposeMatrix(double ***matrix, parameters *pars);
void sortColMatrix(double ***matrix, parameters *pars);
void writeMatrix(double ***matrix, char *OUT, int a, int b);
void freeMatrix(double ***matrix, int a, int b);

// ------------------------------------------
// MAIN
// ------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    double ***matrix = allocMatrix(pars->n, pars->m);

    readMatrix(matrix, pars);

    puts("");
    double ***matrixT = transposeMatrix(matrix, pars);

    sortColMatrix(matrixT, pars);
    writeMatrix(matrixT, pars->OUT, pars->m, pars->n);

    freeMatrix(matrix, pars->n, pars->m);
    freeMatrix(matrixT, pars->m, pars->n);
    free(pars);
    return 0;
}

// ------------------------------------------
// FUNCTION
// ------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 5)
    {
        error("The number of parameters must be 5 <program> <input.txt> <n> <m> <output.txt>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->IN, argv[1]);
    pars->n = atoi(argv[2]);
    pars->m = atoi(argv[3]);
    strcpy(pars->OUT, argv[4]);

    if (pars->n <= 0 || pars->m <= 0)
    {
        error("The values n and m must be > 0");
    }

    return pars;
}

double ***allocMatrix(int a, int b)
{
    double ***matrix = malloc(a * sizeof(double **));
    if (!matrix)
        error("Malloc error");

    for (int i = 0; i < a; i++)
    {
        matrix[i] = malloc(b * sizeof(double *));
        if (!matrix[i])
            error("Malloc error");

        for (int j = 0; j < b; j++)
        {
            matrix[i][j] = malloc(sizeof(double));
            if (!matrix[i][j])
                error("Malloc error");
            *matrix[i][j] = 0.0; // inizializzo a 0
        }
    }
    return matrix;
}

void readMatrix(double ***matrix, parameters *pars)
{
    FILE *fp = fopen(pars->IN, "r");
    if (!fp)
        error("Open file error");

    for (int i = 0; i < pars->n; i++)
    {
        for (int j = 0; j < pars->m; j++)
        {
            if (fscanf(fp, "%lf", matrix[i][j]) != 1)
                error("Formato riga errato");
        }
    }
    fclose(fp);

    printMatrix(matrix, pars->n, pars->m);
}

void printMatrix(double ***matrix, int a, int b)
{
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
            printf("%g\t", *matrix[i][j]);
        puts("");
    }
}

double ***transposeMatrix(double ***matrix, parameters *pars)
{
    double ***matrixT = allocMatrix(pars->m, pars->n);

    for (int i = 0; i < pars->n; i++)
    {
        for (int j = 0; j < pars->m; j++)
        {
            *matrixT[j][i] = *matrix[i][j];
        }
    }
    printMatrix(matrixT, pars->m, pars->n);
    return matrixT;
}

void sortColMatrix(double ***matrix, parameters *pars)
{
    // pars->m = numero colonne, pars->n = numero righe
    for (int col = 0; col < pars->n; col++)             // ogni colonna
    {
        for (int pass = 0; pass < pars->m - 1; pass++) // passate bubble sort
        {
            for (int row = 0; row < pars->m - 1 - pass; row++) // confronti
            {
                if (*matrix[row][col] > *matrix[row + 1][col]) // decrescente
                {
                    double tmp = *matrix[row][col];
                    *matrix[row][col] = *matrix[row + 1][col];
                    *matrix[row + 1][col] = tmp;
                }
            }
        }
    }
}

void writeMatrix(double ***matrix, char *OUT, int a, int b)
{
    FILE *fp = fopen(OUT, "w");
    if (!fp)
        error("Cannot write into file");

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
            fprintf(fp, "%g\t", *matrix[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void freeMatrix(double ***matrix, int a, int b)
{
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
            free(matrix[i][j]);
        free(matrix[i]);
    }
    free(matrix);
}
