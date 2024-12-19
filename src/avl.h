#ifndef AVL_H_
#define AVL_H_

#include <stdio.h>
typedef struct station {
    int identifiant;
    long long capacite;
    long long consommation;
    struct  station* gauche;
    struct station* droit;
    int equilibre;
}Station;

enum {
    CENTRALE,
    HVA,
    HVB,
    LV,
    INCONNU
};
Station * creationStation(int id, long long capacite, long long consommation);  
int estVide(Station * a);
int estFeuille(Station * a);
int existeFilsGauche(Station * a);
int existeFilsDroit(Station * a);
int recherche(Station * a, int elt);
//void parcoursPrefixe(Station * a);
void parcoursInfixe(Station * a, FILE * fichier);
Station * rotationGauche(Station * a);
Station * rotationDroite(Station * a);
Station * doubleRotationGauche(Station * a);
Station * doubleRotationDroite(Station * a);
Station * equilibrerAVL(Station * a);
Station * insererStation(Station * a, int id,  long long capacite, long long consommation, int * h);
Station * rechercheNoeud(Station * racine,int id);
#endif
