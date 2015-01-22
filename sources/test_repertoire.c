#include "repertoire.h"

#include "lecture.h"

#include <unistd.h>

int main() {
    chdir("../ARBORESCENCE/TEXTE/");

    Repertoire r;
    if (init_repertoire(&r, "*.xml", "r") == 0)
        fprintf(stderr, "ERREUR\n");
    Fichier f;
    while (prochain_fichier(r, &f) != -1) {
        printf("Lecture de : %s\n", f.nom);
    }
    free_repertoire(&r);
    return 0;
}
