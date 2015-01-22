#include "shell.h"
#include "lecture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/**
 * n : nombre de paramètre envoyé après n
 * les autres paramètres doivent être de type char*, ou bien directement des "mqjdmfdqj"
 * exemple d'utilisation :
 * executer_commande(3, "ls -l", nomFichier, " > fichier.tmp")
 * 3 pour 3 chaines de caractère
 * nomFichier doit être de type char*
 */
int executer_commande(int n, char* c, ...) {
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

    // printf("%s\n", commande);
    int exitStatus = system(commande);
    free(commande);
    if (WEXITSTATUS(exitStatus) > 0) {
        return 0;
    }
    return 1;
}

int nb_ligne_fichier(char* fichier) {
    FILE* f = fopen(fichier, "rt");
    if (f == NULL) {
        perror("shell.c: nb_ligne_fichier");
        fprintf(stderr, "[shell.c: nb_ligne_fichier] erreur lors de l'ouverture de %s.\n", fichier);
        return 0;
    }
    int nbLigne = 0;
    char chaine[1000];
    while (lireLigne(chaine, 1000, f) != 0) 
        nbLigne++;
    fclose(f);
    return nbLigne;
}

int recupererIemeLigne(char* nomFic, int ligne, char* contenu) {
    return 1;
    // FILE* f = fopen(nomFic, "r");
    // for (int i = 0; i < ligne; ++i)
    // {
        
    // }
    // contenu = NULL;
    // char ligne[100];
    // snprintf(ligne, 100, " %d ", i);
    // char* commande = malloc(
    //     strlen("head -n ") +
    //     strlen(ligne) + 
    //     strlen(nomFic) +
    //     strlen(" | tail -n ") +
    //     strlen(ligne) + 
    //     strlen("> ligne.tmp")
    //     );
    // if (commande == NULL) {
    //     fprintf(stderr, "[shell.c: recupererIemeLigne] disfonctionnement malloc\n");
    //     return 0;
    // }
    // sprintf(commande, "head -n %d %s | tail -n %d > ligne.tmp", i, nomFic, i);
    // int exitStatus = system(commande);
    // if (WEXITSTATUS(exitStatus) > 0) {
    //     fprintf("[shell.c: recupererIemeLigne] commande head ne fonctionne pas");
    //     return 0;
    // }

}
