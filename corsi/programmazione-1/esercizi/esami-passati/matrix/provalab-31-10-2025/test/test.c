// ----------------------------------------------------------------------------------
// #INCLUDE <.h>
// ----------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------------------------------------------
// #DEFINE
// ----------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------
// STRUCT
// ----------------------------------------------------------------------------------
typedef struct
{
    char filename[256];
    int N;
    int M;
} parameters;

// ----------------------------------------------------------------------------------
// PROTOTYPES
// ----------------------------------------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
double ***allocateMatrix(parameters *pars);
void fillMatrix(double ***matrix, parameters *pars);
void printMatrix(double ***matrix, parameters *pars);
void normalize(double ***matrixA, double ***matrixB, parameters *pars);
void sortMatrixCols(double ***matrix, parameters *pars);
void freeMatrix(double ***matrix, parameters *pars);

// ----------------------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    double ***matrixA = allocateMatrix(pars);
    double ***matrixB = allocateMatrix(pars);

    fillMatrix(matrixA, pars);
    printMatrix(matrixA, pars);

    puts("");

    normalize(matrixA, matrixB, pars);
    printMatrix(matrixB, pars);

    puts("");

    sortMatrixCols(matrixB, pars);
    printMatrix(matrixB, pars);

    freeMatrix(matrixA, pars);
    freeMatrix(matrixB, pars);
    free(pars);
    puts("");
    return 0;
}

// ----------------------------------------------------------------------------------
// FUNCTION
// ----------------------------------------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        error("The number of parameters must be 4 <program> <file.txt> <N> <M>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->filename, argv[1]);
    pars->N = atoi(argv[2]);
    pars->M = atoi(argv[3]);

    if ((pars->N < 5 || pars->N > 15) || (pars->M < 5 || pars->M > 15))
    {
        error("The values N and M must be in the range [5, 15]");
    }

    return pars;
}

double ***allocateMatrix(parameters *pars)
{
    double ***matrix = malloc(pars->N * sizeof(double **));
    if (!matrix)
    {
        error("Malloc error");
    }

    for (int i = 0; i < pars->N; i++)
    {
        matrix[i] = malloc(pars->M * sizeof(double *));
        if (!matrix[i])
        {
            error("Malloc error");
        }

        for (int j = 0; j < pars->M; j++)
        {
            matrix[i][j] = malloc(sizeof(double));
            if (!matrix[i][j])
            {
                error("Malloc error");
            }
        }
    }

    return matrix;
}

void fillMatrix(double ***matrix, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
    {
        error("File open error");
    }

    for (int i = 0; i < pars->N; i++)
    {
        for (int j = 0; j < pars->M; j++)
        {
            if (fscanf(fp, "%lf", matrix[i][j]) != 1)
            {
                fprintf(stderr, "Errore formato riga a [%d][%d]\n", i, j);
                error("Errore formato riga");
            }
        }
    }
    fclose(fp);
}

void printMatrix(double ***matrix, parameters *pars)
{
    for (int i = 0; i < pars->N; i++)
    {
        for (int j = 0; j < pars->M; j++)
        {
            printf("\t%lf", (*matrix[i][j]));
        }
        puts("");
    }
}

void normalize(double ***matrixA, double ***matrixB, parameters *pars)
{
    for (int j = 0; j < pars->M; j++)
    {
        double max = (*matrixA[0][j]);
        for (int i = 1; i < pars->N; i++)
        {
            if ((*matrixA[i][j]) > max)
            {
                max = (*matrixA[i][j]);
            }
        }

        for (int i = 0; i < pars->N; i++)
        {
            if (max != 0)
            {
                (*matrixB[i][j]) = (*matrixA[i][j]) / max;
            }
            else
            {
                (*matrixB[i][j]) = 0;
            }
        }
    }
}

void sortMatrixCols(double ***matrix, parameters *pars)
{
    for (int j = 0; j < pars->M; j++)          // per ogni colonna
    {
        for (int i = 0; i < pars->N - 1; i++)
        {
            for (int k = 0; k < pars->N - 1 - i; k++)
            {
                if (*matrix[k][j] > *matrix[k + 1][j])
                {
                    double tmp = *matrix[k][j];
                    *matrix[k][j] = *matrix[k + 1][j];
                    *matrix[k + 1][j] = tmp;
                }
            }
        }
    }
}



void freeMatrix(double ***matrix, parameters *pars)
{
    for (int i = 0; i < pars->N; i++)
    {
        for (int j = 0; j < pars->M; j++)
        {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}