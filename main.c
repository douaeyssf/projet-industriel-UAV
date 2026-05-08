#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

/* Structure drone */
struct Drone {
    int id;
    float x;
    float y;
    float z;
};

/* Distance au carré */
float distanceCarree(struct Drone *a, struct Drone *b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;

    return dx * dx + dy * dy + dz * dz;
}

/* Comparaison pour tri */
int comparerDrones(const void *a, const void *b)
{
    struct Drone *d1 = (struct Drone *)a;
    struct Drone *d2 = (struct Drone *)b;

    if (d1->x > d2->x)
        return 1;

    if (d1->x < d2->x)
        return -1;

    return 0;
}

/* Recherche minimum */
void trouverPaireLaPlusProche(
    struct Drone *essaim,
    int n,
    int *id1,
    int *id2,
    float *distanceMinCarree)
{
    /* Vérification minimale */
    if (n < 2) {

        *id1 = -1;
        *id2 = -1;

        *distanceMinCarree = 0.0f;

        return;
    }

    /* Initialisation distance */
    *distanceMinCarree =
        distanceCarree(essaim, essaim + 1);

    *id1 = essaim->id;
    *id2 = (essaim + 1)->id;

    /* Parcours des drones */
    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            /* Différence sur x */
            float dx =
                (essaim + j)->x -
                (essaim + i)->x;

            /* Condition d'arrêt */
            if ((dx * dx) >= *distanceMinCarree) {
                break;
            }

            /* Distance actuelle */
            float d =
                distanceCarree(
                    essaim + i,
                    essaim + j
                );

            /* Nouveau minimum */
            if (d < *distanceMinCarree) {

                *distanceMinCarree = d;

                *id1 = (essaim + i)->id;
                *id2 = (essaim + j)->id;
            }
        }
    }
}

int main()
{
    /* Nombre drones */
    int n = 10000;

    /* Initialisation random */
    srand(time(NULL));

    /* Allocation mémoire */
    struct Drone *essaim =
        (struct Drone *)malloc(
            n * sizeof(struct Drone)
        );

    /* Vérification malloc */
    if (essaim == NULL) {

        printf("Erreur allocation\n");

        return 1;
    }

    /* Génération drones */
    for (int i = 0; i < n; i++) {

        (essaim + i)->id = i;

        (essaim + i)->x =
            ((float)rand() /
            (float)RAND_MAX) * 1000.0f;

        (essaim + i)->y =
            ((float)rand() /
            (float)RAND_MAX) * 1000.0f;

        (essaim + i)->z =
            ((float)rand() /
            (float)RAND_MAX) * 1000.0f;
    }

    /* Tri des drones */
    qsort(
        essaim,
        n,
        sizeof(struct Drone),
        comparerDrones
    );

    int id1;
    int id2;

    float distanceMinCarree;

    /* Début chrono */
    clock_t debut = clock();

    /* Recherche paire */
    trouverPaireLaPlusProche(
        essaim,
        n,
        &id1,
        &id2,
        &distanceMinCarree
    );

    /* Fin chrono */
    clock_t fin = clock();

    /* Distance finale */
    float distanceMin =
        sqrt(distanceMinCarree);

    /* Temps total */
    double tempsExecution =
        ((double)(fin - debut)
        / CLOCKS_PER_SEC) * 1000.0;

    /* Affichage résultat */
    printf("\n");
    printf("========== RESULTAT ==========\n");

    printf(
        "Drones proches : ID=%d et ID=%d\n",
        id1,
        id2
    );

    printf(
        "Distance minimale : %.6f\n",
        distanceMin
    );

    printf(
        "Temps execution : %.6f ms\n",
        tempsExecution
    );

    /* Libération mémoire */
    free(essaim);

    return 0;
}