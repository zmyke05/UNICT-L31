#include <stdio.h>
#include <string.h>

#define MAX_LEN 31

typedef struct {
    char codiceEvento[MAX_LEN];
    char nomeLuogo[MAX_LEN];
    int capienzaMax;
} record;

int main() {
    FILE *fp = fopen("input.bin", "wb");
    if (!fp) { fprintf(stderr, "Errore apertura file\n"); return 1; }

    record records[] = {
        {"EV012", "Teatro2", 1000},
        {"EV005", "OpenSpace", 645},
        {"EV033", "SalaConcerti2", 900},
        {"EV001", "Teatro1", 800},
        {"EV011", "Stadio2", 3000},
        {"EV008", "Auditorium2", 750},
        {"EV034", "OpenSpace2", 845},
        {"EV002", "Auditorium", 550},
        {"EV014", "MeetingRoom2", 600},
        {"EV006", "MeetingRoom", 400},
        {"EV009", "SalaConcerti3", 1045},
        {"EV004", "Stadio", 1000},
    };

    int n = sizeof(records) / sizeof(records[0]);
    fwrite(records, sizeof(record), n, fp);
    fclose(fp);
    printf("File input.bin creato con %d record!\n", n);
    return 0;
}