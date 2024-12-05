#ifndef AVL_H_
#define AVL_H_

typedef struct avl {
    int elmt;
    struct avl * gauche;
    struct avl * droit;
    int equilibre;
}AVL;

AVL * creationAVL(int donne);
int estVide(AVL * a);
int estFeuille(AVL * a);
int element(AVL * a);
int existeFilsGauche(AVL * a);
int existeFilsDroit(AVL * a);
void traiter(AVL * a);
void parcoursPrefixe(AVL * a);
void parcoursPostfixe(AVL * a);
void parcoursInfixe(AVL * a);
int recherche(AVL * a, int elt);
int verifDroit(AVL * a, int min);
int verifGauche(AVL * a, int max);
int estABR(AVL * a);
AVL * rotationGauche(AVL * a);
AVL * rotationDroite(AVL * a);
AVL * doubleRotationGauche(AVL * a);
AVL * doubleRotationDroite(AVL * a);
AVL * equilibrerAVL(AVL * a);
AVL * insererAVL(AVL * a, int elt, int * h);
AVL * suppMinAVL(AVL * a, int * h, int * pe);
AVL * suppressionAVL(AVL * a, int element, int * pElement);


#endif
