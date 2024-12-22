#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "csv.h"

int main(int argc, char ** argv) {
    if(argc != 2) {
        printf("Erreur: nombre d'arguments incorrect. \n");
        exit(2);
    }
    Station * sta = NULL;
    sta = lecture_fichier(argv[1], sta);
    ecriture_fichier(sta);
    return 0;
}