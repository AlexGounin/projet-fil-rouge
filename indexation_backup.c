#include "indexation_image.h"
#include "indexation_texte.h"
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>

#define TOUT_VA_BIEN       0
#define ERR_NB_PARAM       1
#define ERR_NON_REP        2
#define ERR_ARBORESCENCE   3
#define ERR_INDEXAGE_TEXTE 4

void usage(char* exec) {
    printf("Usage: %s repertoire_source.\n", exec);
}

int gererErreur(int argc, char* argv[]) {
    /* verification du nombre de parametre */
    if (argc != 2) {
        fprintf(stderr, "Le nombre de parametre doit etre de 1.\n");
        usage(argv[0]);
        return ERR_NB_PARAM;
    }

    /* verification que le parametre est bien un repertoire */
    if (executer_commande(2, "verifDossier.sh ", argv[1]) == 0) {
        fprintf(stderr, "Le parametre \"%s\" passe n'est pas un repertoire.\n", argv[1]);
        return ERR_NON_REP;
    }

    return TOUT_VA_BIEN;
}

int main(int argc, char *argv[])
{
    int exitStatut;
    if (gererErreur(argc, argv) > TOUT_VA_BIEN) return 0;

    chdir(argv[1]);

    if (executer_commande(1, "verifierArborescence.sh") == 0) {
        fprintf(stderr, "verifierArborescence.sh a retournée %d.\n", WEXITSTATUS(exitStatut));
        return ERR_ARBORESCENCE;
    }

    indexer_texte();

    indexer_image();

    printf("Fin du programme\n");
    return 0;
}
