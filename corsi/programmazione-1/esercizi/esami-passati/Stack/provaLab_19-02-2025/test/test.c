// ---------------------------------------------------
// #INCLUDE <.h>
// ---------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ---------------------------------------------------
// #DEFINE
// ---------------------------------------------------

// ---------------------------------------------------
// STRUCT
// ---------------------------------------------------
typedef struct
{
    double x;
    double y;
    int n;
} parameters;

typedef struct node
{
    double data;
    struct node *next;
} node;

// ---------------------------------------------------
// PROTOTYPES
// ---------------------------------------------------
unsigned int get_random();
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
double genDouble(double min, double max);
void push(node **top, double data);
void pop(node **top);
void buildStack(node **top, parameters *pars);
double **buildArray(parameters *pars, node **top);
void elabValues(double **array, parameters *pars);
void freeArray(double **array, parameters *pars);

// ---------------------------------------------------
// MAIN
// ---------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *top = NULL;

    buildStack(&top, pars);
    double **array = buildArray(pars, &top);

    puts("");
    elabValues(array, pars);

    free(pars);
    freeArray(array, pars);
    puts("");
    return 0;
}

// ---------------------------------------------------
// FUNCTION
// ---------------------------------------------------
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
    if (argc != 4)
    {
        error("The number of parameters must be 4 <program> <x> <y> <n>");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    pars->x = atof(argv[1]);
    pars->y = atof(argv[2]);
    pars->n = atoi(argv[3]);

    if (pars->x < 100.0 || pars->y < 100.0 || pars->x > 1000.0 || pars->y > 1000.0 || pars->y < pars->x || pars->y - pars->x < 300.0)
    {
        error("The values x and y must be this propriety: [100.0, 1000.0], y > x, y - x > 300");
    }

    if (pars->n < 15 || pars->n > 30)
    {
        error("The value n must be in the range [15, 30]");
    }

    return pars;
}

double genDouble(double min, double max)
{
    // assicurarsi che min < max
    if (min > max)
    {
        double tmp = min;
        min = max;
        max = tmp;
    }

    // genera numero double nell'intervallo [min, max]
    double r = (double)get_random() / (double)UINT_MAX;
    return min + r * (max - min);
}

void push(node **top, double data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    newNode->data = data;
    newNode->next = (*top);
    (*top) = newNode;
}

void pop(node **top)
{
    if (!(*top))
    {
        error("The stack is empty");
    }
    node *buffer = (*top);
    (*top) = (*top)->next;
    free(buffer);
}

void buildStack(node **top, parameters *pars)
{
    for (int i = 0; i < pars->n; i++)
    {
        double value = genDouble(pars->x, pars->y);
        push(top, value);
        printf("Dato inserito (%d): %g\n", i, (*top)->data);
    }
}

double **buildArray(parameters *pars, node **top)
{
    double **array = malloc(sizeof(double *) * pars->n);
    if (array == NULL)
        return NULL;

    for (int i = 0; i < pars->n; i++)
    {
        array[i] = malloc(sizeof(double));
        if (array[i] == NULL)
        {
            // in caso di errore, libera la memoria già allocata
            for (int j = 0; j < i; j++)
                free(array[j]);
            free(array);
            return NULL;
        }
    }

    for (int i = 0; i < pars->n; i++)
    {
        if ((*top) == NULL)
            break;

        *array[i] = (*top)->data;
        pop(top);
    }

    return array;
}

void elabValues(double **array, parameters *pars)
{
    double media = 0;
    double somma = 0;
    int count = 0;
    for (int i = 0; i < pars->n; i++)
    {
        somma+=(*array[i]);
    }
    media = somma / pars->n;

    for (int i = 0; i < pars->n; i++)
    {
        if ((*array[i]) > media)
        {
            count++;
        }
    }

    printf("** elabValues(), avg=%g, no. of values > %g = %d ", media, media, count);
}

void freeArray(double **array, parameters *pars)
{
    for (int i = 0; i < pars->n; i++)
    {
        free(array[i]);
    }
    free(array);
}