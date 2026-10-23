#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colis.h"

void init_collection(Collection *c) {
    c->capacite = 16;
    c->nbre_colis = 0;
    c->tab = malloc(c->capacite * sizeof(Colis));
    if (c->tab == NULL) {
        printf("Erreur d'allocation\n");
        exit(1);
    }
}

void ajouter_colis(Collection *c, Colis nouveau) {
    if (c->nbre_colis == c->capacite) {
        c->capacite *= 2;
        Colis *tmp = realloc(c->tab, c->capacite * sizeof(Colis));
        if (tmp == NULL) {
            printf("Erreur d'allocation\n");
            exit(1);
        }
        c->tab = tmp;
    }
    c->tab[c->nbre_colis] = nouveau;
    c->nbre_colis++;
}

void afficher_colis(Collection *c) {
    printf("%-6s %-6s %-6s %-9s %s\n", "ID", "Poids", "Valeur", "Priorite", "Destination");
    for (int i = 0; i < c->nbre_colis; i++) {
        Colis *p = &c->tab[i];
        printf("%-6d %-6d %-6d %-9d %s\n",
               p->id, p->poids, p->valeur, p->priorite, p->destination);
    }
}

int rechercher_colis(Collection *c, int id) {
    for (int i = 0; i < c->nbre_colis; i++) {
        if (c->tab[i].id == id) {
            return i;
        }
    }
    return -1;
}

void liberer_collection(Collection *c) {
    free(c->tab);
    c->tab = NULL;
    c->nbre_colis = 0;
    c->capacite = 0;
}