#ifndef AVL_H_
#define AVL_H_

typedef struct station {
    int identifiant;
    int capacite;
    int consommation;
    struct  station* gauche;
    struct station* droit;
}Station;

enum {
    CENTRALE,
    HVA,
    HVB,
    LV,
    INCONNU
};
# TODO: actualiser le .h
Station * creationStation(int id, char type, int capacite, int consommation);  
int estVide(Station * a);
int estFeuille(Station * a);
int element(Station * a);
int existeFilsGauche(Station * a);
int existeFilsDroit(Station * a);
void traiter(Station * a);
void parcoursPrefixe(Station * a);
void parcoursPostfixe(Station * a);
void parcoursInfixe(Station * a);
int recherche(Station * a, int elt);
int verifDroit(Station * a, int min);
int verifGauche(Station * a, int max);
int estABR(Station * a);
Station * rotationGauche(Station * a);
Station * rotationDroite(Station * a);
Station * doubleRotationGauche(Station * a);
Station * doubleRotationDroite(Station * a);
Station * equilibrerAVL(Station * a);
Station * insererAVL(Station * a, int elt, int * h);
Station * suppMinAVL(Station * a, int * h, int * pe);
Station * suppressionAVL(Station * a, int element, int * pElement);


#endif
