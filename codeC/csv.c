#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "avl.h"

/*
 * Parseur CSV -> struct station
 */

Station* lecture_fichier(char * chemin, Station * fstation){
    FILE* fichier=fopen(chemin,"r+"); //ouverture du fichier en mode lecture et écriture
    Station * noeud = NULL;
    //Initialisation des variables pour la somme
    int id;   
    long long capacite=0;
    long long consommation=0;
    char ligne[256];
    int h=0; //Equilibrage AVL;

    if(fichier==NULL){
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    while(fgets(ligne,sizeof(ligne),fichier)){
        sscanf(ligne,"%d;%lld;%lld",&id,&capacite,&consommation);//Enregistrements des paramètres dans un ligne formatée
        noeud = rechercheNoeud(fstation,id); //rechercher si cette station avec cette ID existe déjà
        if(noeud!=NULL){ //si la station existe on met à jour les valeurs
            noeud->capacite=noeud->capacite+capacite;
            noeud->consommation=noeud->consommation+consommation;
        } else {//sinon on insère l'insère dans l'avl
            fstation=insererStation(fstation,id,capacite,consommation,&h);
        }
    }
    
    fclose(fichier);
    return fstation;
}

void ecriture_fichier(Station * fstation) {
    FILE * sortie = NULL;
    sortie = fopen("tests/renvois.csv", "a+"); //ouverture du fichier en mode ajout dans le dossier output
    if(sortie == NULL) {
        printf("Erreur création fichier sortie");
        exit(1);
    }
    fprintf(sortie, "Station;Capacite;Consommation;Difference\n");//ecriture dans l'en-tête du CSV
    parcoursInfixe(fstation, sortie); //Parcours dans l'ordre croissant les données du fichier
    fclose(sortie);
}