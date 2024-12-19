#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "avl.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

Station * creationStation(int id, long long capacite, long long consommation) {
    Station * station = malloc(sizeof(Station));
    if(station == NULL) {
        printf("Erreur malloc\n");
        exit(2);
    }
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

int estFeuille(Station * a) {
    if(a == NULL) {return -1;}
    return (a->gauche == NULL) && (a->droit == NULL);
}

int existeFilsGauche(Station * a) {
    if(a == NULL) {return -1;}
    return (a->gauche != NULL);
}

int existeFilsDroit(Station * a) {
    if(a == NULL) {return -1;}
    return (a->droit != NULL);
}

void traiter(Station * a, FILE * fichier) {
    fprintf(fichier,"%d;%lld;%lld\n",a->identifiant,a->capacite,a->consommation);
    //printf("[id = %d, cap = %lld, conso = %lld, equi = %d]\n", a->identifiant, a->capacite, a->consommation, a->equilibre);
}

/*void parcoursPrefixe(Station * a) { // R G D
    if(estVide(a)) {
        return;
    }
    traiter(a);
    parcoursPrefixe(a->gauche);
    parcoursPrefixe(a->droit);
}*/

/*
void parcoursPostfixe(Station * a) { // G D R
    if(estVide(a)) {
        return;
    }
    parcoursPostfixe(a->gauche);
    parcoursPostfixe(a->droit);
    traiter(a);
}
*/
void parcoursInfixe(Station * a, FILE * fichier) { // G R D
    if(estVide(a)) {
        return;
    }
    parcoursInfixe(a->gauche, fichier);
    traiter(a, fichier);
    parcoursInfixe(a->droit, fichier);
}

/*int recherche(Station * a, int id) {
    if(a == NULL) {
        return 0;
    }
    if(estFeuille(a) || id == a->identifiant) {
        return (id == a->identifiant);
    } else if(a->identifiant > id) {
        return recherche(a->gauche, id);
    } else if(a->identifiant <= id) {
        return recherche(a->droit, id);
    }
}*/

/*Station * suppMax(Station * a, int * e) {
    Station * tmp = NULL;
    if(existeFilsDroit(a)) {
        a->droit = suppMax(a->droit, e);
    } else {
        *e = a->identifiant;
        tmp = a;
        a = a->gauche;
        free(tmp);
    }
    return a;
}


int verifDroit(Station * a, int min) {
    if(a == NULL) {
        return 1;
    }
    return a->identifiant > min;
}

int verifGauche(Station * a, int max) {
    if(a == NULL) {
        return 1;
    }
    return a->identifiant < max;
}

int estABR(Station * a) {
    if(a == NULL) {
        return 1;
    }
    if(!verifGauche(a->gauche, a->identifiant) && !verifDroit(a->droit, a->identifiant)) {
        return 0;
    }

    return estABR(a->gauche) && estABR(a->droit);
}*/

Station * rotationGauche(Station * a) {
    if(a == NULL) {
        exit(2);
    }
    //printf("Rotation gauche\n");
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
    //printf("Rotation droite\n");
    int eq_a, eq_p;
    Station * pivot = a->gauche;
    a->gauche = pivot->droit;
    pivot->droit = a;

    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - MIN(eq_p, 0) + 1;
    pivot->equilibre = MAX(MAX(eq_a + 2, eq_a + eq_p + 2), eq_p + 1);
    /*printf("Pivot: %d, ", pivot->elmt);    
    printf("%d fils gauche %d fils droit", pivot->gauche->elmt, pivot->droit->elmt);
    printf("\n");*/
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
        //printf("avant: %d\n", a->elmt);
        a = equilibrerAVL(a);
        //printf("après: %d\n", a->elmt);
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

/*Station * suppMinStation(Station * a, int * h, int * pe) {
    Station * tmp = NULL;
    if(a->gauche == NULL) {
        *pe = a->identifiant;
        *h = -1;
        tmp = a;
        a = a->droit;
        free(tmp);
        return a;
    } else {
        a->gauche = suppMinStation(a->gauche, h, pe);
        *h = -*h;
    }
    if(*h != 0) {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL(a);
        if(a->equilibre == 0) {
            *h = -1;
        } else {
            *h = 0;
        }
    }
    return a;
}

Station * suppressionStation(Station * a, int id, int * pElement) {
    Station * tmp;

    if(a == NULL) {
        *pElement = 1;
        return a;
    } else if(id > a->identifiant) {
        a->droit = suppressionStation(a->droit, id, pElement);
    } else if(id < a->identifiant) {
        a->gauche = suppressionStation(a->gauche, id, pElement);
        *pElement = -*pElement;
    } else if(existeFilsDroit(a)) {
        a->droit = suppMinStation(a->droit, pElement, &a->identifiant);
    } else {
        tmp = a;
        a = a->gauche;
        free(tmp);
        *pElement = -1;
        return a;
    }
    if(*pElement != 0) {
        a->equilibre = a->equilibre + *pElement;
        a = equilibrerAVL(a);
        if(a->equilibre == 0) {
            *pElement = -1;
        } else {
            *pElement = 0;
        }
    }
    return a;
}*/