
#ifndef FICHIER_H
#define FICHIER_H

struct Drone {
    int   id;
    float x;
    float y;
    float z;
};

float distCarre(struct Drone *a, struct Drone *b);

int trierX(const void *a, const void *b);

int trierY(const void *a, const void *b);

float plusProche(
    struct Drone  *tab,
    int            n,
    struct Drone **res1,
    struct Drone **res2
);

#endif
