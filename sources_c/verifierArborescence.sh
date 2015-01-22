#!/bin/sh

listeRepertoire=\
"$HOME/.indexation \
$HOME/.indexation/IMG_NG \
    $HOME/.indexation/IMG_NG/DESCRIPTEURS \
    $HOME/.indexation/IMG_NG/LISTE_DESCRIPTEUR \
$HOME/.indexation/IMG_RGB \
    $HOME/.indexation/IMG_RGB/DESCRIPTEURS \
    $HOME/.indexation/IMG_RGB/LISTE_DESCRIPTEUR \
$HOME/.indexation/SON \
    $HOME/.indexation/SON/DESCRIPTEURS \
    $HOME/.indexation/SON/LISTE_DESCRIPTEUR \
$HOME/.indexation/TEXTE \
    $HOME/.indexation/TEXTE/DESCRIPTEURS \
    $HOME/.indexation/TEXTE/LISTE_DESCRIPTEUR \
    $HOME/.indexation/TEXTE/INDEX_MOT_CLEF"

for rep in $listeRepertoire
do
    if [ ! -d "$rep" ]
    then
        mkdir "$rep"
    fi
done

listeFichier=\
"$HOME/.indexation/config_texte.txt \
$HOME/.indexation/config_descripteur_texte.txt \
$HOME/.indexation/config_image.txt \
$HOME/.indexation/config_audio.txt \
$HOME/.indexation/IMG_NG/LISTE_DESCRIPTEUR/liste_descripteur.txt \
$HOME/.indexation/IMG_RGB/LISTE_DESCRIPTEUR/liste_descripteur.txt \
$HOME/.indexation/SON/LISTE_DESCRIPTEUR/liste_descripteur.txt \
$HOME/.indexation/TEXTE/LISTE_DESCRIPTEUR/liste_descripteur.txt \
$HOME/.indexation/TEXTE/INDEX_MOT_CLEF/index_mot_clef.txt" \

for fichier in $listeFichier
do
    if [ ! -f "$fichier" ]
    then
        touch "$fichier"
    fi
done


exit 0
