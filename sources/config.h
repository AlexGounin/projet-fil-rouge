#ifndef _CONFIG_H
#define _CONFIG_H

/*
* Recupere les config pour un texte
*/
void get_config_texte(int* nb_car_mot_min, int* nb_car_mot_max);

/*
* Recupere les config pour un descripteur texte
*/
void get_config_descripteur_texte(int* seuil, int* nombre_limite);

/*
* Recupere les config pour une image
*/
void get_config_image(int* pasDeQuantification);

/*
* Recupere les config pour un fichier audio
*/
void get_config_audio(int *n, int* m);

/**
 * ne pas oublier de free le char retourner
 * pour toutes les fonctions suivantes
 * Permet de recuperer le chemin des dossiers
 */
char* get_index_mot_clef();

char* get_lbd_texte();

char* get_lbd_image_ng();

char* get_lbd_image_rgb();

char* get_lbd_audio();

char* get_descripteur_texte(int id);

char* get_descripteur_image_ng(int id);

char* get_descripteur_image_rgb(int id);

char* get_descripteur_audio(int id);

#endif
