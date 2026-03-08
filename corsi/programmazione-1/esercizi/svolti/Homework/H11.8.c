#include <stdio.h>
#include <math.h>

int main()

{
    float raggio;

    printf("\nInsersci il raggio del cerchio: ");
    scanf("%f", &raggio);

    float area = M_PI * pow(raggio, 2);
    float circonferenza = 2 * M_PI * raggio;

    printf("\nArea: %.4f", area);
    printf("\nCirconferenza: %.4f", circonferenza);

    printf("\n");
}