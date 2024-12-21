#!/bin/bash

for i in $@
        do
	    if [ "$i" = "-h" ]
        then
            cat README.md
            exit 0
        fi

done


#   set -e # le programme se termine si l'une des commandes retourne une erreur

if [ ! -f cy-wire ]; then
    echo "Avertissement: l'exécutable cy-wire n'a pas été trouvé, lancement de la compilation"
    make -j$(nproc)
fi


fichier=$1
station=$2
client=$3
power=$4


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


if [ "$power" = "all" ]
    then
        power="^[0-9]+"
        extension=""
    
elif [ $power -ge 6 ]
    then
        echo "Erreur : option de power plant"
        cat README.txt 
        exit 0
else
        extension="_$power"
fi



if [  -d "/tmp/cy-wire" ]
then

    echo "Le dossier /tmp/cy-wire existe, suppression de son contenu."
    rm /tmp/cy-wire/*

else

    echo "Le dossier /tmp/cy-wire existe pas, création du dossier"
    mkdir /tmp/cy-wire

fi

if [ ! -d "output" ]
then

    echo "Le dossier output n'existe pas, création du dossier"
    mkdir output
fi



chrono1=$(date +%s) #début du chronometrage du traitement


case $station in  #Identification de la station

     hvb)


        if [ "$client" = "comp" ] # Vérification option
        then

            echo "Option hvb entreprise."

            grep -E "$power;.*;.*;.*;.*;.*;.*;.*$" $fichier | cut -d';' -f2,3,5,7,8 | grep -E "^[0-9]+;-;.*;.*$" | cut -d';' -f1,4,5 | tr "-" "0" > /tmp/cy-wire/data.txt 


            ./cy-wire /tmp/cy-wire/data.txt

            mv output/renvois.csv output/hvb_comp$extension.csv


        else

            echo "Erreur Option impossible avec les hvb"
            cat README.md
            exit 2

        fi

    ;;

    hva)

        if [ "$client" = "comp" ] # Vérification option
        then

            echo "Option hva entreprise"
            grep -E "$power;.*;.*;.*;.*;.*;.*;.*$" $fichier | cut -d';' -f3,4,5,7,8 | grep -E "^[0-9]+;-;.*;.*;.*$" | cut -d';' -f1,4,5 | tr "-" "0" > /tmp/cy-wire/data.txt

            ./cy-wire /tmp/cy-wire/data.txt

            mv output/renvois.csv output/hva_comp$extension.csv

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
                grep -E "$power;.*;.*;.*;.*;.*;.*;.*$" $fichier | cut -d';' -f4,5,6,7,8 | grep -E "^[0-9]+;.*;-;.*;.*$" | cut -d';' -f1,4,5 | tr "-" "0" > /tmp/cy-wire/data.txt

                ./cy-wire /tmp/cy-wire/data.txt
     
                mv output/renvois.csv output/lv_comp$extension.csv
                
            ;;

            indiv)

                echo "lv -> indiv"
                grep -E "$power;.*;.*;.*;.*;.*;.*;.*$" $fichier | cut -d';' -f4,5,6,7,8 | grep -E "^[0-9]+;-;.*$" | cut -d';' -f1,4,5 | tr "-" "0" > /tmp/cy-wire/data.txt

                ./cy-wire /tmp/cy-wire/data.txt

                mv output/renvois.csv output/lv_indiv$extension.csv

            ;;

            all)

                echo " lv -> all"
                grep -E "$power;.*;.*;.*;.*;.*;.*;.*$" $fichier | cut -d';' -f4,5,6,7,8 | grep -E "^[0-9]+.*$" | cut -d';' -f1,4,5 | tr "-" "0"  > /tmp/cy-wire/data.txt

                ./cy-wire /tmp/cy-wire/data.txt

                sort output/renvois.csv -k2 -t';' -n > output/tmp.csv #Besoin d'un fichier temporaire pour étudier la version trié de renvois.csv

                head -n11 output/tmp.csv > output/lv_all_minmax$extension.csv
                tail output/tmp.csv  >> output/lv_all_minmax$extension.csv
                

                rm output/renvois.csv
                rm output/tmp.csv

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
chrono2=$(date +%s)

let Chrono=$(($chrono2 - $chrono1))
let m=$(($Chrono / 60))
let s=$(($Chrono % 60))

echo "Temps de traitement : $m minutes $s secondes"