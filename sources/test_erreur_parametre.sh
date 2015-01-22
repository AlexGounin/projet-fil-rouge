#!/bin/sh

exec='./indexation'

exe() {
    echo "$exec" "$@"
    $exec "$@" > /dev/null 2> /dev/null
    if [ $? -eq 0 ]
    then
        echo "ERREUR : $exec $@"
        exit 1
    fi
}

exe -qmdljkfqd tes

exe -t mqkjd mjqd
exe qmldkfj

exe -t mjqdf
exe -a mqkljdf
exe -a mlqjd -a mqld
exe -t mqjd -a mqjd

exe -t ../ARBORESCENCE -a mkqdf
exe -t ../ARBORESCENCE -t mqdf
exe -t ../ARBORESCENCE -t ../ARBORESCENCE

exit 0
