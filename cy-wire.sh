#!/bin/bash

set -e # le programme se termine si l'une des commandes retourne une erreur

if [ ! -f cy-wire ]; then
    echo "Avertissement: l'exécutable cy-wire n'a pas été trouvé, lancement de la compilation"
    make -j$(nproc)
fi

for i in $@
        do
	    if [ "$i" = "-h" ]
        then
            cat README.md
            exit 0
        fi

done


fichier=$1
station=$2
client=$3


if [ ! -f $fichier ] #assertion
then

    echo "Erreur : Le premier argument n'est pas un fichier ou il n'existe pas"
    cat README.md
    exit 0

elif [[ ! $fichier = *.csv && ! $fichier = *.dat ]] #Double crochet nécessaire pour comparer avec le metacraractere *
then

    echo "Erreur fichier au mauvais format"
    cat README.md
    exit 0

fi


if [  -d "tmp" ]
then

    echo "Le dossier tmp existe, suppression de son contenu."
    rm tmp/*

else

    echo "Le dossier tmp existe pas, création du dossier"
    mkdir tmp

fi





case $station in  #Identification de la station

     hvb)


        if [ "$client" = "comp" ] # Vérification option
        then
            echo "Option hvb entreprise -> suite en c."

        else

            echo "Erreur Option impossible avec les hvb"
            cat README.md
            exit 2

        fi

    ;;

    hva)

        if [ "$client" = "comp" ] # Vérification option
        then
            echo "Option hva entreprise -> suite en c."

        else

            echo "Erreur Option impossible avec les hva"
            cat README.md
            exit 2

        fi


    ;;

    lv)

        case $client in # Vérification option

            comp)

                echo "lv -> comp"

            ;;

            indiv)

                echo "lv -> indiv"

            ;;

            all)

                 echo " lv -> all"

            ;;

            *)

                echo "Erreur Option lv"
                cat README.md
                exit 4

            ;;

            esac

    ;;

    *)

        echo "Erreur : l'option de station est incorrecte"
        cat README.md
        exit 1

    ;;

esac


