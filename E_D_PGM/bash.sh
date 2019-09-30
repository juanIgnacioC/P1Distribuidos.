#!/bin/bash

echo ""
echo "Bienvenido al menu de Sistemas Distribuidos P1"
PS3='Ingresa tu opcion: '
options=("Erosion" "Dilatacion" "Opcion 3" "Salir")
select opt in "${options[@]}"
do
    case $opt in
        "Erosion")
            echo "you chose choice 1"
            mpicc erosion.c -o erosion
            mpirun  -np 3 ./erosion
            echo ""
            echo "1) Erosion"
            echo "2) Dilatacion"
            echo "4)salir"
            ;;
        "Dilatacion")
            echo "you chose choice 2"
            mpicc dilatacion.c -o dilatacion
            mpirun  -np 3 ./dilatacion
            echo ""
            echo "1) Erosion"
            echo "2) Dilatacion"
            echo "4)salir"
            ;;
        "Opcion 3")
            echo "you chose choice $REPLY which is $opt"
            ;;
        "Salir")
            echo "Buen dia le desea Juan Cordero y Alvaro Elgueda"
            break
            ;;
        *) echo "opcion invalida $REPLY" ;;
    esac
done
