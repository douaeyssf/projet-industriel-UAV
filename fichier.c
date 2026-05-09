#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdio.h>

#include "fichier.h"

/* distance 3D au carre */
float distCarre(struct Drone *a, struct Drone *b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;

    return dx * dx + dy * dy + dz * dz;
}

/* tri selon X */
int trierX(const void *a, const void *b)
{
    struct Drone *d1 = (struct Drone *)a;
    struct Drone *d2 = (struct Drone *)b;

    if (d1->x < d2->x)
        return -1;

    if (d1->x > d2->x)
        return 1;

    return 0;
}

/* tri selon Y */
int trierY(const void *a, const void *b)
{
    struct Drone *d1 = *(struct Drone **)a;
    struct Drone *d2 = *(struct Drone **)b;

    if (d1->y < d2->y)
        return -1;

    if (d1->y > d2->y)
        return 1;

    return 0;
}

/* algorithme divide and conquer */
float plusProche(
    struct Drone  *tab,
    int            n,
    struct Drone **res1,
    struct Drone **res2)
{
    /* cas simple */
    if (n <= 3) {

        float dmin = FLT_MAX;

        for (int i = 0; i < n - 1; i++) {

            for (int j = i + 1; j < n; j++) {

                float d =
                    distCarre(tab + i, tab + j);

                if (d < dmin) {

                    dmin = d;

                    *res1 = tab + i;
                    *res2 = tab + j;
                }
            }
        }

        return dmin;
    }

    /* division */
    int mid = n / 2;

    float xMid = (tab + mid)->x;

    /* partie gauche */
    struct Drone *g1 = NULL;
    struct Drone *g2 = NULL;

    float dGauche =
        plusProche(tab, mid, &g1, &g2);

    /* partie droite */
    struct Drone *d1 = NULL;
    struct Drone *d2 = NULL;

    float dDroite =
        plusProche(tab + mid, n - mid, &d1, &d2);

    /* minimum courant */
    float dmin;

    if (dGauche <= dDroite) {

        dmin = dGauche;

        *res1 = g1;
        *res2 = g2;
    }
    else {

        dmin = dDroite;

        *res1 = d1;
        *res2 = d2;
    }

    /* bande centrale */
    float delta = sqrtf(dmin);

    struct Drone **bande =
        (struct Drone **)malloc(
            n * sizeof(struct Drone *)
        );

    if (bande == NULL) {

        printf("Erreur allocation bande\n");
        exit(1);
    }

    /* remplissage */
    int nb = 0;

    for (int i = 0; i < n; i++) {

        if (fabsf((tab + i)->x - xMid) < delta) {

            *(bande + nb) = tab + i;
            nb++;
        }
    }

    /* tri selon Y */
    qsort(
        bande,
        nb,
        sizeof(struct Drone *),
        trierY
    );

    /*
       En 3D la borne theorique
       est plus grande qu'en 2D.

       On limite les comparaisons
       a 27 voisins pour garder
       une complexite O(n log n).
    */

    for (int i = 0; i < nb - 1; i++) {

        for (int j = i + 1;
             j < nb && j <= i + 27;
             j++) {

            float dy =
                (*(bande + j))->y -
                (*(bande + i))->y;

            if (dy * dy >= dmin) {
                break;
            }

            float d =
                distCarre(
                    *(bande + i),
                    *(bande + j)
                );

            if (d < dmin) {

                dmin = d;

                *res1 = *(bande + i);
                *res2 = *(bande + j);
            }
        }
    }

    free(bande);

    return dmin;
}
