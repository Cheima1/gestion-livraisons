#include <stdio.h>
#include <stdlib.h>
#include "camion.h"

int score_valeur(const Colis *c) {
    return c->valeur;
}

int score_priorite(const Colis *c) {
    return c->valeur * c->priorite;
}

Chargement preparer_camion(Collection *c, int capacite, Score score) {
    int n = c->nbre_colis;
    int W = capacite;
    Chargement ch = {NULL, 0, 0, 0, capacite};

    long long *dp = calloc(W + 1, sizeof(long long));
    unsigned char *pris = calloc((size_t)n * (W + 1), sizeof(unsigned char));
    ch.indices = malloc((n > 0 ? n : 1) * sizeof(int));
    if (dp == NULL || pris == NULL || ch.indices == NULL) {
        printf("Erreur d'allocation (capacite ou nombre de colis trop grand)\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        int p = c->tab[i].poids;
        long long s = score(&c->tab[i]);
        for (int w = W; w >= p; w--) {
            if (dp[w - p] + s > dp[w]) {
                dp[w] = dp[w - p] + s;
                pris[(size_t)i * (W + 1) + w] = 1;
            }
        }
    }

    int w = W;
    for (int i = n - 1; i >= 0; i--) {
        if (pris[(size_t)i * (W + 1) + w]) {
            ch.indices[ch.nb++] = i;
            ch.poids_total += c->tab[i].poids;
            ch.valeur_totale += c->tab[i].valeur;
            w -= c->tab[i].poids;
        }
    }

    free(dp);
    free(pris);
    return ch;
}

void afficher_chargement(Collection *c, Chargement *ch) {
    if (ch->indices == NULL) {
        printf("Aucun chargement prepare.\n");
        return;
    }
    printf("Capacite : %d kg\n", ch->capacite);
    for (int k = 0; k < ch->nb; k++) {
        Colis *p = &c->tab[ch->indices[k]];
        printf("  ID %d : %d kg, valeur %d, priorite %d\n",
               p->id, p->poids, p->valeur, p->priorite);
    }
    printf("Total : %d colis, %d kg, valeur %d\n",
           ch->nb, ch->poids_total, ch->valeur_totale);
}

void liberer_chargement(Chargement *ch) {
    free(ch->indices);
    ch->indices = NULL;
    ch->nb = 0;
}