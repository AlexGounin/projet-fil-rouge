#ifndef _DESCRIPTEUR_IMAGE_H
#define _DESCRIPTEUR_IMAGE_H

#include <stdio.h>

#include "image.h"
#include "repertoire.h"

/*
* Création d'un descripteur image à partir de l'Id, d'une image
* et du chemin ou l'on souhaite sauvegarder le descripteur
* retourne 1 si tout ce passe bien, 0 sinon
*/
int creation_descripteur_image(int id, Image *image, char *chemin, int pasDeQuantification);

/*
* Permet de quantifier une Image donner avec un pas de quantifiaction passé en parametre.
* L'image quantifié est retourné par pointeur
*/
void quantification_image(Image *image, int pasQuantification);

/*
* Retourne dans un tableau le nombre d'occurence de chaque valeur possible
*/
void histogramme_image(Image image, int *tab, int pasQuantification);

/*
* Modifie l'image passer en parametre afin de regrouper les 3 composantes sur un seul nombre
*/
void modif_image_histogramme(Image *image, int pasQuantification);

/*
* Calcule la puissance de a par b et retourne le resultat
*/
int puissance(int a, int b);

#endif
