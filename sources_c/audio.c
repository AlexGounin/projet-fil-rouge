#include "audio.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct s_block {
    unsigned int id;
    unsigned int nbOctet;
    char* octets;
} Block;

int init_block(Block* b, Fichier f) {
    if (fread(&(b->id), 4, 1, f.fichier) == 0) return 0;
    if (fread(&(b->nbOctet), 4, 1, f.fichier) == 0) return 0;
    b->octets = malloc(b->nbOctet);
    if (fread(b->octets, b->nbOctet, 1, f.fichier) == 0) return 0;
    return 1;
}

void free_block(Block *b) {
    free(b->octets);
}

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

void afficherConfigHexa(Fichier f, char* message, int nbOctet) {
    unsigned int config;
    fread(&config, nbOctet, 1, f.fichier);
    printf("%s 0x%x\n", message, config);
}

void afficherConfig(Fichier f, char* message, int nbOctet) {
    unsigned int config;
    fread(&config, nbOctet, 1, f.fichier);
    printf("%s %d\n", message, config);
}

void afficherEnteteWav(Fichier f) {
    afficherConfigHexa(f, "FileTypeBlocID :", 4);
    
    afficherConfig(f, "FileSize :", 4);
    
    afficherConfigHexa(f, "FileFormatID :", 4);

    afficherConfigHexa(f, "FormatBlocID :", 4);

    afficherConfig(f, "BlocSize :", 4);

    afficherConfig(f, "AudioFormat :", 2);

    afficherConfig(f, "NbrCanaux :", 2);

    afficherConfig(f, "Fréquence :", 4);

    afficherConfig(f, "BytePerSecond :", 4);

    afficherConfig(f, "BytePerBloc :", 2);

    afficherConfig(f, "BytePerSample :", 2);
}

void lireBloc(Fichier f) {

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
    afficherEnteteWav(f);
    Block b;
    while (init_block(&b, f) != 0) {
        /* problème de parcours de tableau ! nbOctet != bytePerSample*/
        for (int i = 0; i < b.nbOctet; i++) {

        }
        free_block(&b);
    }
    fclose(ficDescripteur);
    return 1;
}
