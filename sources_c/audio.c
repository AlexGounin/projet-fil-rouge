#include "audio.h"

#include <stdio.h>
#include <stdlib.h>

FILE* creation_descripteur(char* chemin, int id) {
    FILE* f = fopen(chemin, "w+");
    if (f == NULL) {
        perror("creation_descripteur audio");
        fprintf(stderr, "Erreur lors de l'ouverture de %s\n", chemin);
        return NULL;
    }
    fprintf(f, "%d\n", id);
    return f;
}

void ecrireFenetre(FILE* f, int* histogramme, int nbIntervalle) {
    for (int i = 0; i < nbIntervalle - 1; ++i) {
        fprintf(f, "%d\t", histogramme[i]);
    }
    fprintf(f, "%d\n", histogramme[nbIntervalle - 1]);
}

double swap(double d) {
    double a;
    unsigned char *dst = (unsigned char *)&a;
    unsigned char *src = (unsigned char *)&d;

    dst[0] = src[7];
    dst[1] = src[6];
    dst[2] = src[5];
    dst[3] = src[4];
    dst[4] = src[3];
    dst[5] = src[2];
    dst[6] = src[1];
    dst[7] = src[0];

    return a;
}

int indexer_fichier_audio(Fichier f, int nbEchantillon, int nbIntervalle, int id, char* chemin) {
    double valeur;
    int nbValeurLue;
    
    /* création du fichier et écriture de l'id */
    FILE* ficDescripteur = creation_descripteur(chemin, id);

    int nb = 0, indice;
    int* histogramme = (int*) malloc(sizeof(int) * nbIntervalle);
    double tailleIntervalle = 2.0 / (double) nbIntervalle;
    /**
     * parcours complet du fichier
     */
    for (int i = 0; i < nbIntervalle; ++i) {
        histogramme[i] = 0;
    }
    while ((nbValeurLue = fread(&valeur, sizeof(double), 1, f.fichier)) == 1) {
        // printf("  %e\n", swap(valeur));
        valeur = swap(valeur);
        if (valeur + 1 < 0.0 || valeur + 1 > 2.0)
            printf("valeur = %e.\n", valeur);
        indice = (int) ((valeur + 1.0) / tailleIntervalle);
        if (indice < 0 || indice > nbIntervalle)
            printf("indice = %d\n", indice);
        
        histogramme[indice]++;
        if (nb + 1 == nbEchantillon) {
            ecrireFenetre(ficDescripteur, histogramme, nbIntervalle);
            for (int i = 0; i < nbIntervalle; ++i) {
                histogramme[i] = 0;
            }
            nb = 0;
        }
        nb++;
    }
    /* écriture de la dernière fenêtre si incomplète */
    if (nb - 1 != nbEchantillon) {
        ecrireFenetre(ficDescripteur, histogramme, nbIntervalle);
    }
    fclose(ficDescripteur);
    return 1;
}
