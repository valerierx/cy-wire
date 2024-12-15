#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/*
 * Parseur CSV -> struct station
 */

Station* lecture_fichier(Station * fstation){
    FILE* fichier=fopen("data.txt","r+");
    if(fichier==NULL){
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

char ligne[256];
int h=0; //Equilibrage AVL;
while(fgets(ligne,sizeof(ligne),fichier)){
    int id;
    long long capacite=0;
    long long consommation=0;

    sscanf(ligne,"%d;%lld;%lld",&id,&capacite,&consommation);
    Station* noeud=rechercheNoeud(fstation,id); // creer la fonction rechercheNoeud dans avl.c
    if(noeud!=NULL){
        noeud->capacite=noeud->capacite+consommation;
        noeud->consommation=noeud->consommation+consommation;
    }
    else{
        fstation=insererStation(fstation,id,capacite,consommation,&h);
    }
}
fclose(fichier);
return fstation;
}
 
/*int nbLigne(FILE* fichier){
    int nbr_ligne=1;
    char caractere;
    while((caractere=fgetc(fichier))!=EOF){
        if(caractere=='\n'){
            nbr_ligne++;
        }

    }
 return nbr_ligne;
}*/