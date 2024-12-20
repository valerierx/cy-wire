#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "avl.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

Station * creationStation(int id, long long capacite, long long consommation) {
    Station * station = malloc(sizeof(Station)); //Allocation dynamique pour Station
    if(station == NULL) {
        printf("Erreur malloc\n");
        exit(2);
    }
    //Initialisation des parametres de la structure Station
    station->identifiant = id;
    station->capacite = capacite;
    station->consommation = consommation;
    station->gauche = NULL;
    station->droit = NULL;
    station->equilibre = 0;
    return station;
}

int estVide(Station * a) {
    if(a == NULL) {return -1;}
    return a == NULL;
}


void traiter(Station * a, FILE * fichier) {
    fprintf(fichier,"%d;%lld;%lld;%lld\n",a->identifiant,a->capacite,a->consommation, a->capacite - a->consommation);
    
}

void parcoursInfixe(Station * a, FILE * fichier) { // G R D
    if(estVide(a)) {
        return;
    }
    parcoursInfixe(a->gauche, fichier);
    traiter(a, fichier);
    parcoursInfixe(a->droit, fichier);
}


Station * rotationGauche(Station * a) {
    if(a == NULL) {
        exit(2);
    }

    int eq_a, eq_p;
    Station * pivot = a->droit;
    a->droit = pivot->gauche;
    pivot->gauche = a;

    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - MAX(eq_p, 0) - 1;
    pivot->equilibre = MIN(MIN(eq_a - 2, eq_a + eq_p -2), eq_p - 1);

    return pivot;
}

Station * rotationDroite(Station * a) {
    if(a == NULL) {
        exit(2);
    }
    int eq_a, eq_p;
    Station * pivot = a->gauche;
    a->gauche = pivot->droit;
    pivot->droit = a;

    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - MIN(eq_p, 0) + 1;
    pivot->equilibre = MAX(MAX(eq_a + 2, eq_a + eq_p + 2), eq_p + 1);
    return pivot;
}

Station * doubleRotationGauche(Station * a) {
    a->droit = rotationDroite(a->droit);
    return rotationGauche(a);
}

Station * doubleRotationDroite(Station * a) {
    a->gauche = rotationGauche(a->gauche);
    return rotationDroite(a);
}

Station * equilibrerAVL(Station * a) {
    if(a->equilibre >= 2) {
        if(a->droit->equilibre >= 0) {
            return rotationGauche(a);
        } else {
            return doubleRotationGauche(a);
        }
    } else if(a->equilibre <= -2) {
        if(a->gauche->equilibre <= 0) {
            return rotationDroite(a);
        } else {
            return doubleRotationDroite(a);
        }
    } 
    return a;
}

Station * insererStation(Station * a, int id,  long long capacite, long long consommation, int * h) { 
    if(estVide(a)) {
        *h = 1;
        return creationStation(id, capacite, consommation);
    } else if(id < a->identifiant) {
        a->gauche = insererStation(a->gauche, id, capacite, consommation, h);
        *h = -*h;
    } else if(id > a->identifiant) {
        a->droit = insererStation(a->droit, id, capacite, consommation, h);
    } else {
        *h = 0;
        return a;
    }
    if(*h != 0) {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL(a);
        if(a->equilibre == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return a;
}

Station * rechercheNoeud(Station * racine,int id){
    if(racine==NULL){
        return NULL;
    }
    if(id==racine->identifiant){
        return racine;
    }
    else if(id<racine->identifiant){
        return rechercheNoeud(racine->gauche,id);
    }
    else{
    return rechercheNoeud(racine->droit,id);
    }
}

