#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

Station * creationAVL(int donne) {
    Station * arb = malloc(sizeof(AVL));
    if(arb == NULL) {
        printf("Erreur malloc\n");
        exit(2);
    }
    arb->elmt = donne;
    arb->gauche = NULL;
    arb->droit = NULL;
    arb->equilibre = 0;
    return arb;
}

int estVide(Station * a) {
    if(a == NULL) {return -1;}
    return a == NULL;
}

int estFeuille(Station * a) {
    if(a == NULL) {return -1;}
    return (a->gauche == NULL) && (a->droit == NULL);
} 

int element(Station * a) {
    if(a == NULL) {return -1;}
    return a->elmt;
}

int existeFilsGauche(Station * a) {
    if(a == NULL) {return -1;}
    return (a->gauche != NULL);
}

int existeFilsDroit(Station * a) {
    if(a == NULL) {return -1;}
    return (a->droit != NULL);
}

void traiter(Station * a) {
    printf("[%d %d] ", a->elmt, a->equilibre);
}

void parcoursPrefixe(Station * a) { // R G D
    if(estVide(a)) {
        return;
    }
    traiter(a);
    parcoursPrefixe(a->gauche);
    parcoursPrefixe(a->droit);
}

void parcoursPostfixe(Station * a) { // G D R
    if(estVide(a)) {
        return;
    }
    parcoursPostfixe(a->gauche);
    parcoursPostfixe(a->droit);
    traiter(a);
}

void parcoursInfixe(Station * a) { // G R D
    if(estVide(a)) {
        return;
    }
    parcoursInfixe(a->gauche);
    traiter(a);
    parcoursInfixe(a->droit);
}

int recherche(Station * a, int elt) {
    if(a == NULL) {
        return 0;
    }
    if(estFeuille(a) || elt == a->elmt) {
        return (elt == a->elmt);
    } else if(a->elmt > elt) {
        return recherche(a->gauche, elt);
    } else if(a->elmt <= elt) {
        return recherche(a->droit, elt);
    }
}

Station * suppMax(Station * a, int * e) {
    Station * tmp = NULL;
    if(existeFilsDroit(a)) {
        a->droit = suppMax(a->droit, e);
    } else {
        *e = a->elmt;
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
    return a->elmt > min;
}

int verifGauche(Station * a, int max) {
    if(a == NULL) {
        return 1;
    }
    return a->elmt < max;
}

int estABR(Station * a) {
    if(a == NULL) {
        return 1;
    }
    if(!verifGauche(a->gauche, a->elmt) && !verifDroit(a->droit, a->elmt)) {
        return 0;
    }

    return estABR(a->gauche) && estABR(a->droit);
}

Station * rotationGauche(Station * a) {
    if(a == NULL) {
        exit(2);
    }
    //printf("Rotation gauche\n");
    int eq_a, eq_p;
    AVL * pivot = a->droit;
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

Station * doubleRotationGauche(AVL * a) {
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

Station * insererAVL(Station * a, int elt, int * h) {
    if(estVide(a)) {
        *h = 1;
        return creationAVL(elt);
    } else if(elt < a->elmt) {
        a->gauche = insererAVL(a->gauche, elt, h);
        *h = -*h;
    } else if(elt > a->elmt) {
        a->droit = insererAVL(a->droit, elt, h);
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

Station * suppMinAVL(Station * a, int * h, int * pe) {
    Station * tmp = NULL;
    if(a->gauche == NULL) {
        *pe = a->elmt;
        *h = -1;
        tmp = a;
        a = a->droit;
        free(tmp);
        return a;
    } else {
        a->gauche = suppMinAVL(a->gauche, h, pe);
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

Station * suppressionAVL(Station * a, int element, int * pElement) {
    Station * tmp;

    if(a == NULL) {
        *pElement = 1;
        return a;
    } else if(element > a->elmt) {
        a->droit = suppressionAVL(a->droit, element, pElement);
    } else if(element < a->elmt) {
        a->gauche = suppressionAVL(a->gauche, element, pElement);
        *pElement = -*pElement;
    } else if(existeFilsDroit(a)) {
        a->droit = suppMinAVL(a->droit, pElement, &a->elmt);
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
}
