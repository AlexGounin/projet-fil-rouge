#include "texte.h"

#include "repertoire.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    chdir("../ARBORESCENCE/TEXTE");

    Texte t;
    Fichier f;
    f.fichier = fopen("03-Mimer_un_signal_nerveux_pour_utf8.xml", "r");
    strcpy(f.nom, "03-Mimer_un_signal_nerveux_pour_utf8.xml");
    if (init_texte(&t, f, 4, 10) == 0) {
        fprintf(stderr, "ERREUR.\n");
        return 1;
    }
    afficher_texte(t);

    free_texte(&t);
    return 0;
}
