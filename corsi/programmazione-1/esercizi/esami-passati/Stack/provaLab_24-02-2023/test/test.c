// ---------------------------------------------------------------
// #INCLUDE <.h>
// ---------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------
// #DEFINE
// ---------------------------------------------------------------

// ---------------------------------------------------------------
// STRUCT
// ---------------------------------------------------------------
typedef struct
{
    unsigned N;
    char a;
    char b;
} parameters;

typedef struct node
{
    char c;
    struct node *next;
} node;

// ---------------------------------------------------------------
// PROTOTYPES
// ---------------------------------------------------------------
unsigned int get_random();
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
char getVowel();
char getConsonant();
void push(node **top, char c);
void fillStack(node **top, parameters *pars);
void printStack(node *top);

// ---------------------------------------------------------------
// FUNCTION
// ---------------------------------------------------------------
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
    fprintf(stderr, "[ERRROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        error("The number of parameters must be 4 <program> <value> <character> <character>");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    pars->N = atoi(argv[1]);
    pars->a = argv[2][0];
    pars->b = argv[3][0];

    if (pars->N < 5 || pars->N > 10)
    {
        error("The value N must be in the range [5, 10]");
    }

    if (pars->a < 'a' || pars->a > 'z' || pars->b < 'a' || pars->b > 'z')
    {
        error("The character a and b must be in the range [a, z]");
    }
    return pars;
}

char getVowel()
{

    char vowels[] = {'a', 'e', 'i', 'o', 'u'};

    return vowels[get_random() % 5];
}

// --------------
// genConsonant()
// -------------
char getConsonant()
{

    char consonant[] = "bcdfghjklmnpqrstvwxyz";

    return consonant[get_random() % 21];
}

void push(node **top, char c)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    newNode->c = c;
    newNode->next = *top;
    *top = newNode;
}

void fillStack(node **top, parameters *pars)
{
    for (int i = 0; i < pars->N; i++)
    {
        char r = (get_random() % 9) + 1;
        char x = '0' + r;

        for (int j = 0; j < r; j++)
        {
            char c;
            if (r >= 1 && r <= 4)
            {
                c = getVowel();
            }
            else
            {
                c = getConsonant();
            }

            if (c == pars->a)
                c = '*';
            else if (c == pars->b)
                c = '?';

            push(top, c);
        }

        push(top, x);
    }
}

void printStack(node *top)
{

    node *cur = top;
    printf("**TOP-> ");

    while (cur)
    {
        printf("%c ", cur->c);
        cur = cur->next;
    }

    printf("<- BOTTOM **\n");
}

void freeStack(node *top)
{
    node *cur;
    while (top)
    {
        cur = top;
        top = top->next;
        free(cur);
    }
}
// ---------------------------------------------------------------
// MAIN
// ---------------------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *top = NULL;

    fillStack(&top, pars);

    printStack(top);

    free(pars);
    freeStack(top);
    return 0;
}