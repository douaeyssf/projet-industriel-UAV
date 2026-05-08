# UAV Collision System

Projet réalisé en C dans le cadre du module de **Programmation Avancée en C**.  
École des Sciences de l'Information — Pr. Tarik HOUICHIME

---

## Objectif du projet

Le système simule un essaim de **10 000 drones autonomes** et recherche les deux drones
les plus proches afin de prévenir les collisions aériennes.

L'objectif principal est d'optimiser les performances tout en respectant des contraintes strictes :

- allocation dynamique avec `malloc`
- interdiction des crochets `[]`
- utilisation de l'arithmétique des pointeurs
- optimisation des comparaisons grâce au tri

---

## Structure utilisée

```c
struct Drone {
    int   id;
    float x;
    float y;
    float z;
};
```

Chaque drone possède :
- un identifiant unique
- une position 3D dans l'espace

---

## Fonctionnement du programme

Le programme effectue les étapes suivantes :

1. Allocation dynamique de 10 000 drones
2. Génération aléatoire des coordonnées flottantes
3. Tri des drones selon la coordonnée `x` avec `qsort`
4. Recherche optimisée de la paire la plus proche (Divide & Conquer)
5. Affichage de la distance minimale et du temps d'exécution

---

## Optimisation utilisée

L'algorithme appliqué est le **Closest Pair of Points** par la méthode **Diviser pour Régner**.

Après le tri par `x`, le tableau est découpé récursivement en deux moitiés.
Chaque moitié est traitée indépendamment, puis on vérifie uniquement les drones
situés dans une bande centrale de largeur `2 * delta` autour de la frontière.

Dans cette bande, les drones sont triés par `y`. La preuve géométrique garantit
qu'on ne compare jamais plus de **7 voisins** par drone — ce qui rend la bande
linéaire en `O(n)` au lieu de `O(n²)`.

Résultat : la complexité totale est **O(n log n)** au lieu de **O(n²)** pour l'approche naïve.

---

## Compilation

```bash
# Avec le Makefile
make

# Manuellement
gcc -Wall -Wextra -O2 -o uav main.c drone.c -lm
```

---

## Exécution

```bash
./uav
```

Exemple de sortie :

```
===== SYSTEME DE COLLISION UAV =====

Drone 1 : ID=4854 | x=861.35 | y=201.11 | z=898.48
Drone 2 : ID=44   | x=860.58 | y=201.93 | z=897.15

Distance minimale : 1.739998
Temps execution   : 4.429000 ms
```

---

## Technologies utilisées

- Langage C (C99)
- `malloc` / `free`
- `qsort`
- Arithmétique des pointeurs
- Bibliothèque mathématique (`math.h`)

---

## Contraintes respectées

- Aucun accès avec `[]`
- Navigation uniquement par pointeurs
- Allocation dynamique sécurisée avec vérification `NULL`
- Libération complète de la mémoire
- Séparation `fichier.h` / `fichier.c` / `main.c`
- Complexité O(n log n) garantie

---

## Auteur

Projet réalisé par **Douae Youssef**  
Étudiante en première année cycle ingénieur ICSD — ESI Rabat
