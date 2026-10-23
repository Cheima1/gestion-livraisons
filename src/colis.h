#ifndef COLIS_H
#define COLIS_H

typedef struct {
    int id;
    int poids;
    int valeur;
    int priorite;
    char destination[32];
} Colis;

typedef struct {
    Colis *tab;
    int nbre_colis;
    int capacite;
} Collection;

void init_collection(Collection *c);
void ajouter_colis(Collection *c, Colis nouveau);
void afficher_colis(Collection *c);
int rechercher_colis(Collection *c, int id);
void liberer_collection(Collection *c);

#endif