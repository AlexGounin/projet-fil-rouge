#include "indexation_texte.h"
#include "indexation_image.h"
#include "indexation_audio.h"
#include "lecture.h"
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TOUT_VA_BIEN 0
#define ERR_NB_PARAM 1
#define ERR_TIRET 2
#define ERR_REP 3
#define ERR_DOUBLE_TIRET 4
#define ERR_PWD 5
#define ERR_SCRIPT 6

void usage(char* executable) {
    printf(
        "Usage :\n"
        "%s \n"
        "\t[-t repertoire_texte_xml]\n"
        "\t[-ng repertoire_image_niveau_de_gris]\n"
        "\t[-rgb repertoire_image_rgb]\n"
        "\t[-a repertoire_audio]\n", executable);
}

int maj(char* option, int *texte, int *ng, int *rgb, int *a, int indice) {
    if (strcmp(option, "-t") == 0) {
        if (*texte != 0) {
            return ERR_DOUBLE_TIRET;
        } else {
            *texte = indice;
            return TOUT_VA_BIEN;
        }
    } else if (strcmp(option, "-ng") == 0) {
        if (*ng != 0) {
            return ERR_DOUBLE_TIRET;
        } else {
            *ng = indice;
            return TOUT_VA_BIEN;
        }
    } else if (strcmp(option, "-rgb") == 0) {
        if (*rgb != 0) {
            return ERR_DOUBLE_TIRET;
        } else {
            *rgb = indice;
            return TOUT_VA_BIEN;
        }
    } else if (strcmp(option, "-a") == 0) {
        if (*a != 0) {
            return ERR_DOUBLE_TIRET;
        } else {
            *a = indice;
            return TOUT_VA_BIEN;
        }
    } else {
        return ERR_TIRET;
    }
}

int verifierOption(int argc, char *argv[], int* texte, int* ng, int* rgb, int* a, int indice) {
    int err;
    if (argc >= indice) {
        if ((err = maj(argv[indice], texte, ng, rgb, a, indice)) != TOUT_VA_BIEN) {
            usage(argv[0]);
            return err;
        }
    }
    return TOUT_VA_BIEN;
}

int verifierDossier(char* rep) {
    if (executer_commande(2, "./dossierExistant.sh ", rep) == 0) {
        return ERR_REP;
    }
 
    return TOUT_VA_BIEN;
}

int gererErreur(int argc, char* argv[], int* texte, int* ng, int* rgb, int* a) {
    int err;
    *texte = *ng = *rgb = *a = 0;
    if (!(argc == 3 || argc == 5 || argc == 7 || argc == 9)) {
        usage(argv[0]);
        return ERR_NB_PARAM;
    }
    /* vérification des options */
    if (argc >= 3 && (err = verifierOption(argc, argv, texte, ng, rgb, a, 1)) != TOUT_VA_BIEN)
        return err;
    if (argc >= 5 && (err = verifierOption(argc, argv, texte, ng, rgb, a, 3)) != TOUT_VA_BIEN)
        return err;
    if (argc >= 7 && (err = verifierOption(argc, argv, texte, ng, rgb, a, 5)) != TOUT_VA_BIEN)
        return err;
    if (argc == 9 && (err = verifierOption(argc, argv, texte, ng, rgb, a, 7)) != TOUT_VA_BIEN)
        return err;
    
    /* vérification des dossiers */
    if (argc >= 3) {
        if (verifierDossier(argv[2]) != TOUT_VA_BIEN) return ERR_REP;
    }
    if (argc >= 5) {
        if (verifierDossier(argv[4]) != TOUT_VA_BIEN) return ERR_REP;
    }
    if (argc >= 7) {
        if (verifierDossier(argv[6]) != TOUT_VA_BIEN) return ERR_REP;
    }
    if (argc == 9) {
        if (verifierDossier(argv[8]) != TOUT_VA_BIEN) return ERR_REP;
    }
    return TOUT_VA_BIEN;
}

int changer_repertoire(char* rep) {
    if (chdir(rep) == -1) {
        perror("[indexation] changer_repertoire");
        return ERR_REP;
    }
    return TOUT_VA_BIEN;
}

char* sauvegarder_repertoire() {
    if (executer_commande(1, "pwd > chemin") == 0) {
        fprintf(stderr, "[indexation: sauvegarder_chemin] erreur pwd.\n");
        return NULL;
    }
    FILE* f = fopen("chemin", "r");
    if (f == NULL) {
        perror("[indexation.c]sauvegarde_chemin");
        return NULL;
    }
    char* chemin = malloc(1000);
    if (chemin == NULL) {
        perror("[indexation.c]sauvegarder_chemin malloc");
        return NULL;
    }
    if (lireLigne(chemin, 1000, f) == 0) {
        fprintf(stderr, "[indexation.c: sauvegarde_chemin] erreur de lecture chemin.\n");
        return NULL;
    }
    fclose(f);
    remove("chemin");
    return chemin;
}

int main(int argc, char* argv[]) {
    system("chmod u+x *.sh 2> /dev/null");
    system("export PATH=$PATH:`pwd`");
    // system()
    int texte, ng, rgb, a, err;

    char* chemin = sauvegarder_repertoire();
    if (chemin == NULL) {
        return ERR_PWD;
    }
    if ((err = gererErreur(argc, argv, &texte, &ng, &rgb, &a)) != TOUT_VA_BIEN)
        return err;

    if (executer_commande(1, "./verifierArborescence.sh") == 0) return ERR_SCRIPT;
    if (texte) {
        if (changer_repertoire(argv[texte + 1]) != TOUT_VA_BIEN) {
            printf("Indexation de texte non effectuée\n");
            return ERR_REP;
        }
        else {
            indexer_texte();
            changer_repertoire(chemin);
        }
    }
    if (ng) {
        if (changer_repertoire(argv[ng + 1]) != TOUT_VA_BIEN) {
            printf("Indexation de texte non effectuée\n");
            return ERR_REP;
        }
        else {
            indexer_image_ng();
            changer_repertoire(chemin);
        }
    }
    if (rgb) {
        if (changer_repertoire(argv[rgb + 1]) != TOUT_VA_BIEN) {
            printf("Indexation de texte non effectuée\n");
            return ERR_REP;
        }
        else {
            indexer_image_rgb();
            changer_repertoire(chemin);
        }
    }
    if (a) {
        if (changer_repertoire(argv[a + 1]) != TOUT_VA_BIEN) {
            printf("Indexation de l'audio non effectuée\n");
            return ERR_REP;
        }
        else {
            indexer_audio();
            changer_repertoire(chemin);
        }
    }

    free(chemin);
    return TOUT_VA_BIEN;
}
