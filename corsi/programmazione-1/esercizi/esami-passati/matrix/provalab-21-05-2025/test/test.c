// ----------------------------------------------------------------
// #INCLUDE
// ----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ----------------------------------------------------------------
// #DEFINE
// ----------------------------------------------------------------

// ----------------------------------------------------------------
// STRUCT
// ----------------------------------------------------------------
typedef struct
{
    unsigned int a;
    unsigned int b;
    double alpha;
    double beta;
} parameters;

// ----------------------------------------------------------------
// PROTOTYPES
// ----------------------------------------------------------------
unsigned int get_random();
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
double ***allocMatrix(unsigned int a, unsigned int b);
void fillMatrix(double ***matrix, parameters *pars);
void transposeMatrix(double ***matrix, double ***matrixT, parameters *pars);
void printMatrix(double ***matrix, unsigned int a, unsigned int b);
void freeMatrix(double ***matrix, unsigned int a, unsigned int b);

// ----------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    double ***matrix = allocMatrix(pars->a, pars->b);
    double ***matrixT = allocMatrix(pars->b, pars->a);

    fillMatrix(matrix, pars);

    puts("*** Matrice m (6 x 10) ***");
    printMatrix(matrix, pars->a, pars->b);

    puts("");
    puts("*** Matrice m1 (10 x 6) ***");
    transposeMatrix(matrix, matrixT, pars);
    printMatrix(matrixT, pars->b, pars->a);

    freeMatrix(matrix, pars->a, pars->b);
    freeMatrix(matrixT, pars->b, pars->a);
    free(pars);
    puts("");
    return 0;
}

// ----------------------------------------------------------------
// FUNCTION
// ----------------------------------------------------------------
unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 5)
    {
        error("The number of parameters must be 5 <program> <a> <b> <alpha> <beta>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    pars->a = atoi(argv[1]);
    pars->b = atoi(argv[2]);
    pars->alpha = atof(argv[3]);
    pars->beta = atof(argv[4]);

    if ((pars->a < 5 || pars->a > 20) || (pars->b < 5 || pars->b > 20))
    {
        error("The values a and b must be in the range [5, 20]");
    }

    if (pars->alpha < 10 || pars->alpha > 20)
    {
        error("The value alpha must be in the range [10, 20]");
    }

    if (pars->beta < 1 || pars->beta > 5)
    {
        error("The value beta must be in the range [1, 5]");
    }

    return pars;
}

double ***allocMatrix(unsigned int a, unsigned int b)
{
    double ***matrix = malloc(a * sizeof(double **));
    if (!matrix)
    {
        error("Malloc error");
    }
    for (int i = 0; i < a; i++)
    {
        matrix[i] = malloc(b * sizeof(double *));
        if (!matrix[i])
        {
            error("Malloc error");
        }

        for (int j = 0; j < b; j++)
        {
            matrix[i][j] = malloc(sizeof(double));
        }
    }
    return matrix;
}

void fillMatrix(double ***matrix, parameters *pars)
{
    for (int i = 0; i < pars->a; i++)
    {
        for (int j = 0; j < pars->b; j++)
        {
            double p = get_random() / (UINT_MAX + 1.0);
            if (p > 0.2)
            {
                double u = get_random() / ((double)UINT_MAX + 1.0);
                double value = (pars->alpha - pars->beta) + u * (2.0 * pars->beta);
                matrix[i][j] = malloc(sizeof(double));
                (*matrix[i][j]) = value;
            }
            else
            {
                matrix[i][j] = NULL;
            }
        }
    }
}

void transposeMatrix(double ***matrix, double ***matrixT, parameters *pars)
{
    for (int i = 0; i < pars->a; i++)
    {
        for (int j = 0; j < pars->b; j++)
        {
            if (matrix[i][j] != NULL)
            {
                matrixT[j][i] = malloc(sizeof(double));
                (*matrixT[j][i]) = (*matrix[i][j]);
            }
            else
            {
                matrixT[j][i] = NULL;
            }
        }
    }
}

void printMatrix(double ***matrix, unsigned int a, unsigned int b)
{
    for (int i = 0; i < a; i++)
    { 
        for (int j = 0; j < b; j++)
        {
            if (matrix[i][j] != NULL)
            {
                printf("%.2f\t", (*matrix[i][j]));
            }
            else
            {
                printf("%c\t", 'N');
            }
        }
        puts("");
    }
}

void freeMatrix(double ***matrix, unsigned int a, unsigned int b)
{
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}