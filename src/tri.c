#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tri.h"

int comparer_poids(const Colis *a, const Colis *b) {
    return a->poids - b->poids;
}

int comparer_valeur(const Colis *a, const Colis *b) {
    return b->valeur - a->valeur;
}

int comparer_priorite(const Colis *a, const Colis *b) {
    return b->priorite - a->priorite;
}

int comparer_id(const Colis *a, const Colis *b) {
    return a->id - b->id;
}

static void fusionner(Colis *tab, Colis *tmp, int debut, int milieu, int fin, Comparateur cmp) {
    int i = debut;
    int j = milieu;
    int k = debut;

    while (i < milieu && j < fin) {
        if (cmp(&tab[i], &tab[j]) <= 0)
            tmp[k++] = tab[i++];
        else
            tmp[k++] = tab[j++];
    }
    while (i < milieu) tmp[k++] = tab[i++];
    while (j < fin)    tmp[k++] = tab[j++];

    for (k = debut; k < fin; k++)
        tab[k] = tmp[k];
}

static void tri_rec(Colis *tab, Colis *tmp, int debut, int fin, Comparateur cmp) {
    if (fin - debut <= 1) return;
    int milieu = debut + (fin - debut) / 2;
    tri_rec(tab, tmp, debut, milieu, cmp);
    tri_rec(tab, tmp, milieu, fin, cmp);
    fusionner(tab, tmp, debut, milieu, fin, cmp);
}

void tri_fusion(Colis *tab, int n, Comparateur cmp) {
    if (n < 2) return;
    Colis *tmp = malloc(n * sizeof(Colis));
    if (tmp == NULL) {
        printf("Erreur d'allocation\n");
        exit(1);
    }
    tri_rec(tab, tmp, 0, n, cmp);
    free(tmp);
}

void afficher_trie(Collection *c, Comparateur cmp) {
    if (c->nbre_colis == 0) {
        printf("Aucun colis.\n");
        return;
    }
    Collection copie;
    copie.nbre_colis = c->nbre_colis;
    copie.capacite = c->nbre_colis;
    copie.tab = malloc(c->nbre_colis * sizeof(Colis));
    if (copie.tab == NULL) {
        printf("Erreur d'allocation\n");
        exit(1);
    }
    memcpy(copie.tab, c->tab, c->nbre_colis * sizeof(Colis));
    tri_fusion(copie.tab, copie.nbre_colis, cmp);
    afficher_colis(&copie);
    free(copie.tab);
}