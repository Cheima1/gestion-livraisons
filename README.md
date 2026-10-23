# Gestion des livraisons

Programme de gestion de colis et de préparation du chargement d'un camion.

## Langage : C

J'ai choisi le C parce qu'il oblige à gérer soi-même la mémoire et les structures de données. Chaque choix (tableau dynamique, tri, programmation dynamique) est donc écrit à la main et peut être justifié précisément, sans dépendre de fonctions toutes faites dont on ne maîtrise pas le fonctionnement. Le C permet aussi de mesurer des temps d'exécution représentatifs de l'algorithme lui-même.

## Organisation du code

```
src/
├── colis.h / colis.c     structures, ajout, affichage, recherche
├── tri.h / tri.c         tri fusion et fonctions de comparaison
├── camion.h / camion.c   préparation du camion (sac à dos)
├── tests.h / tests.c     génération aléatoire et mesures de temps
└── main.c                menu
```

## Compilation et exécution

Depuis le dossier `src/` :

```
gcc -Wall -O2 -o livraison main.c colis.c tri.c camion.c tests.c
./livraison
```

Sous Windows : `.\livraison.exe`

## Utilisation

```
1. Afficher les colis
2. Ajouter un colis
3. Rechercher un colis
4. Organiser les colis       (par poids, valeur ou priorité)
5. Preparer un camion        (valeur seule, ou valeur + priorité)
6. Afficher le chargement
7. Afficher les statistiques
8. Charger les colis d'exemple
9. Tests de performance
0. Quitter
```

Pour tester rapidement : option 8 pour charger les colis de l'énoncé, puis option 5 avec une capacité de 9 kg.

## Conventions

- **Priorité** : de 1 (faible) à 5 (forte). Ce choix correspond à l'énoncé ("priorité importante") et permet d'utiliser directement la priorité comme coefficient dans le score.
- **Poids** : entiers en kg, nécessaires pour la programmation dynamique du camion.
- **ID** : unique, un ajout avec un ID existant est refusé.

## Choix algorithmiques

| Opération | Stratégie | Temps | Espace |
|---|---|---|---|
| Stockage | Tableau dynamique, capacité doublée si plein | Ajout O(1) amorti | O(n) |
| Recherche par ID | Parcours séquentiel | O(n) | O(1) |
| Affichage trié | Tri fusion sur une copie, critère passé en paramètre | O(n log n) | O(n) |
| Camion | Sac à dos 0/1 par programmation dynamique | O(n × W) | O(W) + O(n × W) octets |
| Priorité | Même algorithme, score = valeur × priorité | O(n × W) | idem |

n = nombre de colis, W = capacité du camion en kg.

Le détail des justifications et des alternatives est dans `rapport.pdf`.

## Exemple de résultat (capacité 9 kg)

| Mode | Colis chargés | Poids | Valeur |
|---|---|---|---|
| Valeur seule | 104, 105 | 7 kg | 40 |
| Avec priorité | 104, 102 | 8 kg | 35 |

Avec la priorité, le programme accepte une valeur un peu plus faible pour embarquer le colis 102, qui a la priorité maximale.

## Performances mesurées

Capacité du camion : 50 kg. Temps en millisecondes.

| n | Ajout | 1000 recherches | Tri | Camion |
|---|---|---|---|---|
| 100 | 0 | 0 | 0 | 0 |
| 1 000 | 0 | 1 | 0 | 0 |
| 10 000 | 1 | 4 | 1 | 0 |
| 100 000 | 9 | 238 | 11 | 5 |

La précision de `clock()` sous Windows est d'environ 1 ms, les valeurs à 0 sont donc inférieures à 1 ms.

La recherche par ID est l'opération qui se dégrade le plus. Amélioration possible : tableau trié par ID et recherche dichotomique en O(log n), ou table de hachage en O(1) en moyenne.