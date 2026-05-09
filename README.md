# Système de Collision pour Essaim Autonome (UAV)

**Auteur :** Douae Youssef  
**Groupe :** A — Filière ICSD — Numéro : 39  
**Module :** Programmation Avancée en C — Pr. Tarik HOUICHIME  
**École :** ESI (École des Sciences de l'Information), Rabat

---

## Description

Ce projet implémente un algorithme de détection de collision pour un essaim de
10 000 micro-drones autonomes. Il identifie en temps réel les deux drones les
plus proches l'un de l'autre dans l'espace 3D, afin de déclencher une manœuvre
d'évitement avant un crash en chaîne.

---

## Structure des fichiers

```
.
├── fichier.h     # Définition de struct Drone et déclarations des fonctions
├── fichier.c     # Algorithme Divide & Conquer, tri, distance
├── main.c        # Programme principal : allocation, initialisation, affichage
├── Makefile      # Compilation automatisée
└── README.md     # Ce fichier
```

---

## Contraintes respectées

- Zéro utilisation des crochets `[]` — arithmétique pure des pointeurs (`*(p+i)`)
- Allocation dynamique obligatoire avec `malloc` et vérification `NULL`
- Libération mémoire avec `free` en fin de programme
- Algorithme en O(n log² n) — Divide & Conquer complet

---

## Compilation

### Avec le Makefile (recommandé)

```bash
make
```

### Manuellement

```bash
gcc -Wall -Wextra -std=c99 -o uav main.c fichier.c -lm
```

---

## Exécution

```bash
./uav
```

ou via le Makefile :

```bash
make run
```

---

## Exemple de sortie

```
===== SYSTEME UAV =====

Drone 1 : ID=4821 | x=12.34 | y=567.89 | z=234.56
Drone 2 : ID=7103 | x=12.41 | y=568.02 | z=234.71

Distance minimale : 0.214631
Temps execution   : 2.341000 ms
```

---

## Algorithme

L'algorithme implémenté est le **Closest Pair of Points** en 3D,
basé sur le paradigme **Divide & Conquer** :

1. **Tri** du tableau par coordonnée X — O(n log n)
2. **Division** récursive en deux moitiés égales
3. **Résolution** récursive sur chaque moitié
4. **Analyse** d'une tranche centrale (slab 3D) de largeur 2*delta
5. **Fusion** : conservation du minimum global

**Complexité temporelle :** O(n log² n)  
**Complexité spatiale :** O(n)

---

## Nettoyage

```bash
make clean
```

---

## Environnement de développement

- Système : Ubuntu Linux (VirtualBox)
- Compilateur : GCC avec flags `-Wall -Wextra -std=c99`
- Bibliothèques : `<math.h>` (lier avec `-lm`)
