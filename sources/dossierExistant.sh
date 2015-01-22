#!/bin/sh

if [ $# -ne 1 ]
then
	echo "Erreur nombre de parametre."
	exit 1
fi

if [ -d "$1" ]
then
	exit 0
fi

exit 1
