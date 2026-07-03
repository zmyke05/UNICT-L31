#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 255

/* Prototipi */
void readParameters(int argc, char *argv[], char *in, char *out);
double ***createMatrix(const char *filename, int *n, int *m);
void sparsify(double ***A, int n, int m);
double *collect(double ***A, int n, int m, int *size);
void writeToFile(const char *filename, double *array, int size);
void freeMatrix(double ***A, int n, int m);

int main(int argc, char *argv[]) {
    char input[MAX_NAME + 1], output[MAX_NAME + 1];
    int n, m, size;
    double ***A;
    double *array;

    readParameters(argc, argv, input, output);

    A = createMatrix(input, &n, &m);
    sparsify(A, n, m);
    array = collect(A, n, m, &size);
    writeToFile(output, array, size);

    free(array);
    freeMatrix(A, n, m);

    return 0;
}

/* ------------------------------------------------ */

void readParameters(int argc, char *argv[], char *in, char *out) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <input.txt> <output.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strlen(argv[1]) > MAX_NAME || strlen(argv[2]) > MAX_NAME) {
        fprintf(stderr, "Errore: nome file troppo lungo\n");
        exit(EXIT_FAILURE);
    }

    strcpy(in, argv[1]);
    strcpy(out, argv[2]);
}

/* ------------------------------------------------ */

double ***createMatrix(const char *filename, int *n, int *m) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Errore apertura file input");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    *n = 0;
    *m = 0;

    /* Conta righe e colonne */
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (*n == 0) {
            char *tmp = strtok(buffer, " ");
            while (tmp) {
                (*m)++;
                tmp = strtok(NULL, " ");
            }
        }
        (*n)++;
    }

    rewind(fp);

    /* Allocazione matrice */
    double ***A = malloc(*n * sizeof(double **));
    for (int i = 0; i < *n; i++) {
        A[i] = malloc(*m * sizeof(double *));
        for (int j = 0; j < *m; j++) {
            A[i][j] = malloc(sizeof(double));
            fscanf(fp, "%lf", A[i][j]);
        }
    }

    fclose(fp);
    return A;
}

/* ------------------------------------------------ */

void sparsify(double ***A, int n, int m) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;

        for (int j = 0; j < m; j++)
            sum += *(A[i][j]);

        double avg = sum / m;

        for (int j = 0; j < m; j++) {
            if (*(A[i][j]) < avg) {
                free(A[i][j]);
                A[i][j] = NULL;
            }
        }
    }
}

/* ------------------------------------------------ */

double *collect(double ***A, int n, int m, int *size) {
    *size = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (A[i][j] != NULL)
                (*size)++;

    double *array = malloc(*size * sizeof(double));
    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] != NULL) {
                array[k++] = *(A[i][j]);
            }
        }
    }

    return array;
}

/* ------------------------------------------------ */

void writeToFile(const char *filename, double *array, int size) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Errore apertura file output");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
        fprintf(fp, "%.6f ", array[i]);

    fclose(fp);
}

/* ------------------------------------------------ */

void freeMatrix(double ***A, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] != NULL)
                free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);
}
