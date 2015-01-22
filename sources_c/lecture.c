#include "lecture.h"

#include <stdlib.h>
#include <string.h>


void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

/**
 * lecture sécurisé d'une ligne d'un fichier
 */
int lireLigne(char* chaine, int longueur, FILE* f) {
    char* positionEntree = NULL;
    if (fgets(chaine, longueur, f) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            *positionEntree = '\0';
        } else {
            viderBuffer();
            fprintf(stderr, "[lecture.c: lireLigne] dépassement de chaine pour fgets\n");
            return 0;
        }
        return 1;
    } else {
        // viderBuffer();
        return 0;
    }
}

int longueur_chaine(int n, char* c, va_list params) {
    int somme = strlen(c);
    for (int i = 1; i < n; i++)
        somme += strlen(va_arg(params, char*));
    return somme + 1;
}

char* concat(int n, char* c, ...) {
    va_list params;
    va_start(params, c);
    int longueur = longueur_chaine(n, c, params);
    va_end(params);

    char* commande = malloc(longueur);
    commande[0] = '\0';
    va_start(params, c);
    strcat(commande, c);
    for (int i = 1; i < n; i++)
        strcat(commande, va_arg(params, char*));

    return commande;
}

char* lireClavier() {
    char tmp;
    char* c = NULL;
    int i = 0;
    do
    {
        c = realloc(c, i + 1);
        tmp = getchar();
        if (tmp == '\n')
            c[i] = '\0';
        else
            c[i] = tmp;
        ++i;
    } while (tmp != '\n' && tmp != EOF);
    return c;
}
