#ifndef TRI_H
#define TRI_H

#include "colis.h"

typedef int (*Comparateur)(const Colis *a, const Colis *b);

int comparer_poids(const Colis *a, const Colis *b);
int comparer_valeur(const Colis *a, const Colis *b);
int comparer_priorite(const Colis *a, const Colis *b);
int comparer_id(const Colis *a, const Colis *b);

void tri_fusion(Colis *tab, int n, Comparateur cmp);
void afficher_trie(Collection *c, Comparateur cmp);

#endif