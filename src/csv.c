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
    while(fscanf(fichier,"%d;%d;%d;%d",&identifiant,&capacite,&consommation)!=EOF){
        int id_tmp=fstation->identifiant;
        if(fstation->identifiant!=identifiant){
            insererStation(fstation, identifiant, capacite, consommation);
        }
    }
    return 
}