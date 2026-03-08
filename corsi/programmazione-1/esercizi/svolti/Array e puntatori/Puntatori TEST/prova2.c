#include <stdio.h>

int main() {
    int a = 42;
    int *p = &a;

    printf("a: %d\n", a);
    printf("indirizzo di a: %p\n", (void*)&a);
    printf("p (contiene indirizzo): %p\n", (void*)p);
    printf("*p (valore a cui punta): %d\n", *p);

    *p = 100;
    printf("a dopo modifica tramite p: %d\n", a);
    return 0;
}
