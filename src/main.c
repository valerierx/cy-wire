#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "csv.h"

int main(int argc, char ** argv) {
    Station * sta = NULL;
    sta = lecture_fichier(sta);
    parcoursInfixe(sta);
    return 0;
}