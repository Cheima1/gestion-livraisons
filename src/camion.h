#ifndef CAMION_H
#define CAMION_H

#include "colis.h"

typedef int (*Score)(const Colis *c);

typedef struct {
    int *indices;
    int nb;
    int poids_total;
    int valeur_totale;
    int capacite;
} Chargement;

int score_valeur(const Colis *c);
int score_priorite(const Colis *c);

Chargement preparer_camion(Collection *c, int capacite, Score score);
void afficher_chargement(Collection *c, Chargement *ch);
void liberer_chargement(Chargement *ch);

#endif