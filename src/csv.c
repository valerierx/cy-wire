#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/*
 * Parseur CSV -> struct station
 */

Station* lecture_fichier(Station * fstation){
    int identifiant = -1;
    int capacite = -1;
    int consommation = -1;
    FILE* fichier=fopen("data.txt","r+");
    if(fichier==NULL){
        exit(1);
    }
}
 
int nbLigne(FILE* fichier){
    int nbr_ligne=1;
    char caractere;
    while((caractere=fgetc(fichier))!=EOF){
        if(caractere=='\n'){
            nbr_ligne++;
        }

    }
 return nbr_ligne;
}