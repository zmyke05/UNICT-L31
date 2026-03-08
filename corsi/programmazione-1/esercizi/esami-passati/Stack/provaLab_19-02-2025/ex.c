// -------------------------------------------------
// #INCLUDE
// -------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// -------------------------------------------------
// #DEFINE
// -------------------------------------------------

// -------------------------------------------------
// STRUCT
// -------------------------------------------------
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

// -------------------------------------------------
// PROTOTYPES
// -------------------------------------------------
unsigned int get_random();
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
double genDouble(parameters *pars);
void Push(node **top, double data);
void Pop(node **top);
void buildStack(node **top, parameters *pars);
double *buildArray(node **top, parameters *pars);
void elabValues(double *array, parameters *pars);

// -------------------------------------------------
// MAIN
// -------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *top = NULL;

    printf("** build_stack() **\n");
    buildStack(&top, pars);

    printf("\n** build_array() **\n");
    double *array = buildArray(&top, pars);
    elabValues(array, pars);

    free(pars);
    return 0;
}

// -------------------------------------------------
// FUNCTION
// -------------------------------------------------
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
    exit(EXIT_FAILURE);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        error("The number of parameters must be 4 <program> <x> <y> <n>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    pars->x = atof(argv[1]);
    pars->y = atof(argv[2]);
    pars->n = atoi(argv[3]);

    if ((pars->x < 100.0 || pars->x > 1000.0) || (pars->y < 100.0 || pars->y > 1000.0) && (pars->y < pars->x) && (pars->x - pars->y < 300.0))
    {
        error("The values x and y must be in the range [100.0, 1000.0] && [y > x] && [x - y > 300.0]");
    }

    if (pars->n < 15 || pars->n > 30)
    {
        error("The value n must be in the range [15, 30]");
    }
    return pars;
}

double genDouble(parameters *pars)
{
    double min = pars->x;
    double max = pars->y;

    if (min > max)
    {
        double tmp = min;
        min = max;
        max = tmp;
    }

    double r = (double)get_random() / (double)UINT_MAX;
    return min + r * (max - min);
}

void Push(node **top, double data)
{
    node *newNode = malloc(sizeof(node));

    newNode->data = data;
    newNode->next = (*top);
    (*top) = newNode;
}
void Pop(node **top)
{
    node *buffer = (*top);
    (*top) = (*top)->next;
    free(buffer);
}

void buildStack(node **top, parameters *pars)
{
    for (int i = 0; i < pars->n; i++)
    {
        double value = genDouble(pars);
        Push(top, value);
        printf("Dato inserito (%d): %lf\n", i, (*top)->data);
    }
    
}

double *buildArray(node **top, parameters *pars)
{
    double *array = malloc(pars->n * sizeof(double));
    for (int i = 0; i < pars->n; i++)
    {
        array[i] = (*top)->data;
        Pop(top);
        printf("Dato inserito (%d): %lf\n", i, array[i]);
    }
    return array;
}

void elabValues(double *array, parameters *pars)
{
    double media = 0;
    double somma = 0;
    int count = 0;
    for (int i = 0; i < pars->n; i++)
    {
        somma += array[i];
    }
    media = somma / pars->n;

    for (int i = 0; i < pars->n; i++)
    {
        if (array[i] > media)
        {
            count++;
        }
    }
    printf("** elabValues(), %lf, no. of values > %lf = %d", media, media, count);
}