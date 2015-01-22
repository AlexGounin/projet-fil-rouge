#ifndef _IMAGE_H
#define _IMAGE_H

#include "repertoire.h"

#define ROUGE 0
#define VERT  1
#define BLEU  2

typedef struct s_image * Image;

struct s_image {
    Fichier f;
    unsigned int largeur;
    unsigned int hauteur;
    unsigned int  nbComposante;
    // pixel[ROUGE|VERT|BLEU][nièmepixel]
    unsigned int** pixel;
};

/*
* Initialisation d'une image
* retourne 1 si tout ce passe bien, 0 sinon
*/
int init_image(Image* i, Fichier f);

/*
* Affiche une image
*/
void afficher_image(Image image);

/*
* Libere la memoire d'une image
*/
void free_image(Image* image);

#endif
