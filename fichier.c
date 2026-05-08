#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdio.h>

#include "fichier.h"

/* ============================================
 * fichier.c
 * Implementation des fonctions algorithmiques
 * Systeme de detection de collision UAV
 * ============================================ */

/* Carre de la distance euclidienne 3D */
float distCarre(struct Drone *a, struct Drone *b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;

    return dx*dx + dy*dy + dz*dz;
}

/* Comparateur tri par X pour qsort */
int trierX(const void *a, const void *b)
{
    struct Drone *d1 = (struct Drone *)a;
    struct Drone *d2 = (struct Drone *)b;

    if (d1->x < d2->x) return -1;
    if (d1->x > d2->x) return  1;

    return 0;
}

/* Comparateur tri par Y pour qsort */
/* Travaille sur un tableau de pointeurs vers Drone */
int trierY(const void *a, const void *b)
{
    struct Drone *d1 = *(struct Drone **)a;
    struct Drone *d2 = *(struct Drone **)b;

    if (d1->y < d2->y) return -1;
    if (d1->y > d2->y) return  1;

    return 0;
}

/* Algorithme diviser pour regner : plus proche paire */
float plusProche(
    struct Drone  *tab,
    int            n,
    struct Drone **res1,
    struct Drone **res2)
{
    /* Cas de base : comparaison directe (n <= 3) */
    if (n <= 3) {

        float dmin = FLT_MAX;

        for (int i = 0; i < n - 1; i++) {

            for (int j = i + 1; j < n; j++) {

                float d = distCarre(tab + i, tab + j);

                if (d < dmin) {
                    dmin  = d;
                    *res1 = tab + i;
                    *res2 = tab + j;
                }
            }
        }

        return dmin;
    }

    /* Division : on coupe le tableau en deux */
    int   mid  = n / 2;
    float xMid = (tab + mid)->x;

    /* Recursion gauche */
    struct Drone *g1 = NULL;
    struct Drone *g2 = NULL;
    float dGauche = plusProche(tab, mid, &g1, &g2);

    /* Recursion droite */
    struct Drone *d1 = NULL;
    struct Drone *d2 = NULL;
    float dDroite = plusProche(tab + mid, n - mid, &d1, &d2);

    /* On conserve le minimum des deux sous-problemes */
    float dmin;

    if (dGauche <= dDroite) {
        dmin  = dGauche;
        *res1 = g1;
        *res2 = g2;
    } else {
        dmin  = dDroite;
        *res1 = d1;
        *res2 = d2;
    }

    /* -----------------------------------------------
     * BANDE CENTRALE : etape cle pour O(n log n)
     */
    float delta = sqrtf(dmin);

    struct Drone **bande =
        (struct Drone **)malloc(n * sizeof(struct Drone *));

    if (bande == NULL) {
        printf("Erreur allocation bande\n");
        exit(1);
    }

    /* Remplissage de la bande par arithmetique de pointeurs */
    int nb = 0;

    for (int i = 0; i < n; i++) {

        if (fabsf((tab + i)->x - xMid) < delta) {
            *(bande + nb) = tab + i;
            nb++;
        }
    }

    /* Tri de la bande par Y : O(nb log nb) */
    /* Necesaire pour que la limite a 7 soit valide */
    qsort(bande, nb, sizeof(struct Drone *), trierY);

    for (int i = 0; i < nb - 1; i++) {

        for (int j = i + 1; j < nb && j <= i + 7; j++) {

            /* Coupure anticipee : si dy seul depasse dmin, inutile */
            float dy = (*(bande + j))->y - (*(bande + i))->y;

            if (dy * dy >= dmin) {
                break;
            }

            float d = distCarre(*(bande + i), *(bande + j));

            if (d < dmin) {
                dmin  = d;
                *res1 = *(bande + i);
                *res2 = *(bande + j);
            }
        }
    }

    /* Liberation de la bande centrale */
    free(bande);

    return dmin;
}
