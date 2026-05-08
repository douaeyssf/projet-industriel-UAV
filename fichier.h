#ifndef DRONE_H
#define DRONE_H

/* ============================================
 * fichier.h
 * Declarations de la structure et des fonctions
 * Systeme de detection de collision UAV
 * ============================================ */

/* Structure imposee par le cahier des charges */
struct Drone {
    int   id;
    float x;
    float y;
    float z;
};

/* Calcul du carre de la distance entre deux drones */
/* On evite sqrt tant que possible pour les performances */
float distCarre(struct Drone *a, struct Drone *b);

/* Comparateur pour qsort : tri par coordonnee X */
int trierX(const void *a, const void *b);

/* Comparateur pour qsort : tri de pointeurs par coordonnee Y */
/* Utilise pour ordonner la bande centrale */
int trierY(const void *a, const void *b);

/* Algorithme diviser pour regner */
/* Retourne le carre de la distance minimale */
/* res1 et res2 sont mis a jour avec les deux drones les plus proches */
float plusProche(
    struct Drone  *tab,
    int            n,
    struct Drone **res1,
    struct Drone **res2
);

#endif /* DRONE_H */
