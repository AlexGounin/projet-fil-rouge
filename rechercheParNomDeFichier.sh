#!/bin/sh

if [ $# -ne 2 ]
then
	echo "Erreur nombre de parametre." >&2
	exit 2
fi

if [ ! 	-d "$1/TEXTE" ]
then
	echo "Le repertoire contenant les fichiers textes n'existe pas."  >&2
	exit 3
fi

ls "$1"/TEXTE | grep "$2"*.txt
err=$?
if [ "$err" -ne 0 ]
then
	echo "Aucun nom de fichier ne correspond au critere de recherche"
fi

exit $err
