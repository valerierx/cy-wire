#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "avl.h"

/*
 * Parseur CSV -> struct station
 */

Station* lecture_fichier(char * chemin, Station * fstation){
    FILE* fichier=fopen(chemin,"r+");
    Station * noeud = NULL;
    int id;
    long long capacite=0;
    long long consommation=0;
    char ligne[256];
    int h=0; //Equilibrage AVL;
    int surconsommation;

    if(fichier==NULL){
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    while(fgets(ligne,sizeof(ligne),fichier)){
        sscanf(ligne,"%d;%lld;%lld",&id,&capacite,&consommation);
        noeud = rechercheNoeud(fstation,id); // creer la fonction rechercheNoeud dans avl.c
        if(noeud!=NULL){
            noeud->capacite=noeud->capacite+capacite;
            noeud->consommation=noeud->consommation+consommation;
            /*if((noeud->capacite - noeud->consommation)<0){
                surconsommation=-(noeud->capacite - noeud->consommation);
                printf("La station %d est en surconsommation de %d ",id,surconsommation);
            }*/
        } else {
            fstation=insererStation(fstation,id,capacite,consommation,&h);
        }
    }
    
    fclose(fichier);
    return fstation;
}

void ecriture_fichier(Station * fstation) {
    FILE * sortie = NULL;
    sortie = fopen("output/renvois.csv", "a+");
    if(sortie == NULL) {
        printf("Erreur création fichier sortie");
        exit(1);
    }
    parcoursInfixe(fstation, sortie);
    fclose(sortie);

}