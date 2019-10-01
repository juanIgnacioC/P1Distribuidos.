#!/bin/bash

echo ""
echo "Bienvenido al menu de Sistemas Distribuidos P1"
PS3='Ingresa tu opcion: '
options=("Erosion" "Dilatacion" "Erosion Estructurante" "Dilatacion Estructurante" "Salir")
select opt in "${options[@]}"
do
    case $opt in
        "Erosion")
            mpicc erosion.c -o erosion
            mpirun  -np 3 ./erosion
            echo ""
            echo "1) Erosion"
            echo "2) Dilatacion"
            echo "3) Erosion Estructurante"
            echo "4) Dilatacion Estructurante"
            echo "5)salir"
            ;;
        "Dilatacion")
            mpicc dilatacion.c -o dilatacion
            mpirun  -np 3 ./dilatacion
            echo ""
            echo "1) Erosion"
            echo "2) Dilatacion"
            echo "3) Erosion Estructurante"
            echo "4) Dilatacion Estructurante"
            echo "5)salir"
            ;;
        "Erosion Estructurante")
            mpicc test4.c -o test4
            mpirun  -np 4 ./test4
            echo ""
            echo "1) Erosion"
            echo "2) Dilatacion"
            echo "3) Erosion Estructurante"
            echo "4) Dilatacion Estructurante"
            echo "5)salir"
            ;;
        "Dilatacion Estructurante")
            mpicc test5.c -o test5
            mpirun  -np 4 ./test5
            echo ""
            echo "1) Erosion"
            echo "2) Dilatacion"
            echo "3) Erosion Estructurante"
            echo "4) Dilatacion Estructurante"
            echo "5)salir"
            ;;
        "Salir")
            echo "Buen dia le desea Juan Cordero y Alvaro Elgueda"
            echo ""
            break
            ;;
        *) echo "opcion invalida $REPLY" ;;
    esac
done
