#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int initialiser_structure_image(Image* i, Fichier f) {
    *i = malloc(sizeof(struct s_image));
    if (*i == NULL) {
        fprintf(stderr, "[image.c: initialiser_structure_image] erreur malloc sur *i\n");
        return 0;
    }
    (*i)->f = f;
    fscanf(f.fichier, "%d", &((*i)->largeur));
    fscanf(f.fichier, "%d", &((*i)->hauteur));
    fscanf(f.fichier, "%d", &((*i)->nbComposante));

    (*i)->pixel = malloc((*i)->nbComposante * sizeof(int*));
    if ((*i)->pixel == NULL) {
        perror("[image.c] initialiser_structure_image");
        return 0;
    }

    int nbValeur = (*i)->largeur * (*i)->hauteur;
    for (int composante = 0; composante < (*i)->nbComposante; ++composante)
    {
        (*i)->pixel[composante] = malloc(sizeof(int) * nbValeur);
        if ((*i)->pixel[composante] == NULL) {
            perror("[image.c] initialiser_structure_image");
            return 0;
        }
    }
    return 1;
}

int init_image(Image* image, Fichier f) {
    if (initialiser_structure_image(image, f) == 0) return 0;
    int nbValeur = (*image)->largeur * (*image)->hauteur;
    for (int i = 0; i < (*image)->nbComposante; i++) {
        for (int j = 0; j < nbValeur; ++j) {
            fscanf(f.fichier, "%d", &((*image)->pixel[i][j]));
            if ((*image)->pixel[i][j] < 0 || (*image)->pixel[i][j] > 255)
                fprintf(stderr, "\ncomposante pixel invalide %d\n", (*image)->pixel[i][j]);
        }
    }
    return 1;
}

void afficher_image(Image image) {
    assert(image);
    printf("%d %d %d\n", image->largeur, image->hauteur, image->nbComposante);
    int indice = 0;
    for (int composante = 0; composante < image->nbComposante; ++composante) {
        indice = 0;
        for (int ligne = 0; ligne < image->hauteur; ++ligne) {
            for (int colonne = 0; colonne < image->largeur - 1; ++colonne) {
                printf("%d ", image->pixel[composante][indice++]);
            }
            printf("%d\n", image->pixel[composante][indice++]);
        }
    }
}

void free_image(Image* image) {
    for (int composante = 0; composante < (*image)->nbComposante; ++composante) {
        free((*image)->pixel[composante]);
    }
    free((*image)->pixel);
    free(*image);
    *image = NULL;
}
