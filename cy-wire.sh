#!/bin/bash





getopts "h" opt


case $opt in 

    h)

    cat README.txt   

    ;;

    ?)



    fichier=$1
    station=$2
    client=$3


    if [ ! -f $fichier ] #assertion
    then

        echo "Erreur : Le premier argument n'est pas un fichier ou il n'existe pas"
        exit 0

    elif [[ ! $fichier = *.csv ]] #Double crochet nécessaire pour comparer avec le metacraractere *
    then

        echo "Erreur fichier au mauvais format"
        exit 0

    fi


    if [  -d "tmp" ]
    then

        echo "Le dosser tmp existe, suppression de son contenu."
        #rm tmp/*

    fi


    





    case $station in  #Identification de la station

        hvb)

            echo "ça marche, étudion les hvb"

            if [ "$client" = "comp" ] # Vérification option
            then
                echo "Option hvb entreprise -> suite en c."

            else

                echo "Erreur Option impossible avec les hvb, seul les entreprise peuvent être raccorder au hvb."
                exit 2

            fi

        ;;

        hva)

            echo "ça marche, étudion les hva"

            if [ "$client" = "comp" ] # Vérification option
            then
                echo "Option hva entreprise -> suite en c."

            else

                echo "Erreur Option impossible avec les hva, seul les entreprise peuvent être raccorder au hva."
                exit 2

            fi


        ;;

        lv)

            echo "ça marche, étudions les lv"

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

                    echo "Erreur Option lv, option voulu : comp, indiv, all."
                    exit 4

                ;;

                esac

        ;;

        *)

            echo "Erreur : l'option de station est incorrecte"
            exit 1

        ;;

    esac


??

esac