#ifndef AVL_H_
#define AVL_H_

typedef struct station {
    int identifiant;
    int capacite;
    int consommation;
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
Station * creationStation(int id, int capacite, int consommation);  
int estVide(Station * a);
int estFeuille(Station * a);
int existeFilsGauche(Station * a);
int existeFilsDroit(Station * a);
int recherche(Station * a, int elt);
Station * rotationGauche(Station * a);
Station * rotationDroite(Station * a);
Station * doubleRotationGauche(Station * a);
Station * doubleRotationDroite(Station * a);
Station * equilibrerAVL(Station * a);
Station * insererStation(Station * a, int id,  int capacite, int consommation, int * h);
Station * rechercheNoeud(Station * racine,int id);

#endif
