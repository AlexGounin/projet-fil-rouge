#include "audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void afficherBitsPerSample(Fichier f, char* message, int nbOctet, int* bitsPerSample) {
    *bitsPerSample = 0;
    fread(bitsPerSample, nbOctet, 1, f.fichier);
    printf("%s %d\n", message, *bitsPerSample);
}

void afficherNbOctet(Fichier f, char* message, int nb, unsigned int* nbOctet) {
    *nbOctet = 0;
    fread(nbOctet, nb, 1, f.fichier);
    printf("%s %d\n", message, *nbOctet);
}

void afficherEnteteWav(Fichier f, int* bitsPerSample, unsigned int* nbOctet) {
    printf("\n[Bloc de déclaration d'un fichier au format wave]\n");
    afficherConfigHexa(f, "\tFileTypeBlocID :", 4);
    afficherConfig(f, "\tFileSize :", 4);
    afficherConfigHexa(f, "\tFileFormatID :", 4);

    printf("\n[Bloc décrivant le format audio]\n");
    afficherConfigHexa(f, "\tFormatBlocID :", 4);
    afficherConfig(f, "\tBlocSize :", 4);

    printf("\n");
    afficherConfig(f, "\tAudioFormat :", 2);
    afficherConfig(f, "\tNbrCanaux :", 2);
    afficherConfig(f, "\tFréquence :", 4);
    afficherConfig(f, "\tBytePerSecond :", 4);
    afficherConfig(f, "\tBytePerBloc :", 2);
    afficherBitsPerSample(f, "\tBitsPerSample :", 2, bitsPerSample);

    printf("\n[Bloc de donnée]\n");
    afficherConfigHexa(f, "\tDataBlocID :", 4);
    afficherNbOctet(f, "\tDataSize :", 4, nbOctet);
}

int indexer_fichier_audio(Fichier f, int nbEchantillon, int nbIntervalle, int id, char* chemin) {
    /* création du fichier et écriture de l'id */
    FILE* ficDescripteur = creation_descripteur(chemin, id);

    int* histogramme = (int*) malloc(sizeof(int) * nbIntervalle);
    for (int i = 0; i < nbIntervalle; ++i) {
        histogramme[i] = 0;
    }
    int bytesPerSample;
    unsigned int nbOctet;
    afficherEnteteWav(f, &bytesPerSample, &nbOctet);
    bytesPerSample /= 8;

    /**
     * parcours de tout les échantillons
     */
    char* fenetre = malloc(bytesPerSample * nbEchantillon);
    long valeur = 0;
    while (fread(fenetre, bytesPerSample, nbEchantillon, f.fichier)) {
        for (int i = 0; i < nbEchantillon; i += bytesPerSample) {
            memcpy(&valeur, &fenetre[i], bytesPerSample);
            printf("  %ld\n", valeur);
        }
    }
    fclose(ficDescripteur);
    return 1;
}
