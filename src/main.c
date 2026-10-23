#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "colis.h"
#include "tri.h"
#include "camion.h"
#include "tests.h"

static int lire_entier(const char *message) {
    int x;
    printf("%s", message);
    while (scanf("%d", &x) != 1) {
        while (getchar() != '\n');
        printf("Entree invalide. %s", message);
    }
    return x;
}

static void charger_exemples(Collection *col) {
    Colis ex[] = {
        {101, 8, 20, 2, "Paris"},
        {102, 3, 10, 5, "Lille"},
        {103, 12, 40, 1, "Lyon"},
        {104, 5, 25, 4, "Paris"},
        {105, 2, 15, 3, "Lille"}
    };
    for (int i = 0; i < 5; i++) {
        if (rechercher_colis(col, ex[i].id) == -1)
            ajouter_colis(col, ex[i]);
    }
    printf("Exemples charges.\n");
}

static void saisir_colis(Collection *col) {
    Colis nouveau;
    nouveau.id = lire_entier("ID : ");
    if (rechercher_colis(col, nouveau.id) != -1) {
        printf("Un colis avec cet ID existe deja.\n");
        return;
    }
    do {
        nouveau.poids = lire_entier("Poids (kg, > 0) : ");
    } while (nouveau.poids <= 0);
    nouveau.valeur = lire_entier("Valeur : ");
    do {
        nouveau.priorite = lire_entier("Priorite (1 a 5) : ");
    } while (nouveau.priorite < 1 || nouveau.priorite > 5);
    printf("Destination : ");
    scanf("%31s", nouveau.destination);

    ajouter_colis(col, nouveau);
    printf("Colis ajoute.\n");
}

static void rechercher(Collection *col) {
    int id = lire_entier("ID recherche : ");
    int pos = rechercher_colis(col, id);
    if (pos == -1) {
        printf("Colis introuvable.\n");
        return;
    }
    Colis *p = &col->tab[pos];
    printf("ID %d : %d kg, valeur %d, priorite %d, %s\n",
           p->id, p->poids, p->valeur, p->priorite, p->destination);
}

static void organiser(Collection *col) {
    printf("1. Par poids (croissant)\n2. Par valeur (decroissante)\n3. Par priorite (decroissante)\n");
    int choix = lire_entier("Choix : ");
    if (choix == 1)      afficher_trie(col, comparer_poids);
    else if (choix == 2) afficher_trie(col, comparer_valeur);
    else if (choix == 3) afficher_trie(col, comparer_priorite);
    else printf("Choix invalide.\n");
}

static void preparer(Collection *col, Chargement *ch) {
    int capacite;
    do {
        capacite = lire_entier("Capacite du camion (kg, > 0) : ");
    } while (capacite <= 0);

    printf("1. Maximiser la valeur\n2. Maximiser la valeur en favorisant la priorite\n");
    int choix = lire_entier("Choix : ");

    liberer_chargement(ch);
    if (choix == 2) *ch = preparer_camion(col, capacite, score_priorite);
    else            *ch = preparer_camion(col, capacite, score_valeur);
    afficher_chargement(col, ch);
}

static void statistiques(Collection *col) {
    if (col->nbre_colis == 0) {
        printf("Aucun colis.\n");
        return;
    }
    long long poids = 0, valeur = 0;
    for (int i = 0; i < col->nbre_colis; i++) {
        poids += col->tab[i].poids;
        valeur += col->tab[i].valeur;
    }
    printf("Nombre de colis : %d\n", col->nbre_colis);
    printf("Poids total : %lld kg (moyenne %.2f)\n", poids, (double)poids / col->nbre_colis);
    printf("Valeur totale : %lld (moyenne %.2f)\n", valeur, (double)valeur / col->nbre_colis);
}

int main(void) {
    srand(time(NULL));
    Collection col;
    init_collection(&col);
    Chargement ch = {NULL, 0, 0, 0, 0};
    int choix;

    do {
        printf("\n===== GESTION DES LIVRAISONS =====\n");
        printf("1. Afficher les colis\n");
        printf("2. Ajouter un colis\n");
        printf("3. Rechercher un colis\n");
        printf("4. Organiser les colis\n");
        printf("5. Preparer un camion\n");
        printf("6. Afficher le chargement\n");
        printf("7. Afficher les statistiques\n");
        printf("8. Charger les colis d'exemple\n");
        printf("9. Tests de performance\n");
        printf("0. Quitter\n");
        choix = lire_entier("Choix : ");

        switch (choix) {
            case 1: afficher_colis(&col); break;
            case 2: saisir_colis(&col); break;
            case 3: rechercher(&col); break;
            case 4: organiser(&col); break;
            case 5: preparer(&col, &ch); break;
            case 6: afficher_chargement(&col, &ch); break;
            case 7: statistiques(&col); break;
            case 8: charger_exemples(&col); break;
            case 9: lancer_tests(); break;
            case 0: printf("Au revoir.\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);

    liberer_chargement(&ch);
    liberer_collection(&col);
    return 0;
}