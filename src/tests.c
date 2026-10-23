#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tests.h"
#include "tri.h"
#include "camion.h"

void generer_colis(Collection *c, int n) {
    const char *villes[] = {"Paris", "Lille", "Lyon", "Marseille", "Nantes"};
    for (int i = 0; i < n; i++) {
        Colis x;
        x.id = i + 1;
        x.poids = 1 + rand() % 20;
        x.valeur = 1 + rand() % 100;
        x.priorite = 1 + rand() % 5;
        strcpy(x.destination, villes[rand() % 5]);
        ajouter_colis(c, x);
    }
}

static double ms(clock_t debut, clock_t fin) {
    return 1000.0 * (fin - debut) / CLOCKS_PER_SEC;
}

void lancer_tests(void) {
    int tailles[] = {100, 1000, 10000, 100000};
    int capacite = 50;

    printf("%-8s %-12s %-18s %-12s %-12s\n",
           "n", "Ajout (ms)", "1000 rech. (ms)", "Tri (ms)", "Camion (ms)");

    for (int t = 0; t < 4; t++) {
        int n = tailles[t];
        Collection c;
        init_collection(&c);

        clock_t t0 = clock();
        generer_colis(&c, n);
        clock_t t1 = clock();

        clock_t t2 = clock();
        for (int k = 0; k < 1000; k++)
            rechercher_colis(&c, -1);
        clock_t t3 = clock();

        Colis *copie = malloc(n * sizeof(Colis));
        memcpy(copie, c.tab, n * sizeof(Colis));
        clock_t t4 = clock();
        tri_fusion(copie, n, comparer_poids);
        clock_t t5 = clock();
        free(copie);

        clock_t t6 = clock();
        Chargement ch = preparer_camion(&c, capacite, score_valeur);
        clock_t t7 = clock();
        liberer_chargement(&ch);

        printf("%-8d %-12.2f %-18.2f %-12.2f %-12.2f\n",
               n, ms(t0, t1), ms(t2, t3), ms(t4, t5), ms(t6, t7));

        liberer_collection(&c);
    }
}