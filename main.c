#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "fichier.h"

int main()
{
    int n = 10000;

    srand((unsigned int)time(NULL));

    /* allocation dynamique */
    struct Drone *essaim =
        (struct Drone *)malloc(
            n * sizeof(struct Drone)
        );

    if (essaim == NULL) {

        printf("Erreur allocation memoire\n");
        return 1;
    }

    /* generation des drones */
    for (int i = 0; i < n; i++) {

        (essaim + i)->id = i + 1;

        (essaim + i)->x =
            ((float)rand() / RAND_MAX)
            * 1000.0f;

        (essaim + i)->y =
            ((float)rand() / RAND_MAX)
            * 1000.0f;

        (essaim + i)->z =
            ((float)rand() / RAND_MAX)
            * 1000.0f;
    }

    /* debut chrono */
    clock_t debut = clock();

    /* tri selon X */
    qsort(
        essaim,
        n,
        sizeof(struct Drone),
        trierX
    );

    struct Drone *meilleur1 = NULL;
    struct Drone *meilleur2 = NULL;

    /* recherche principale */
    float dCarreMin =
        plusProche(
            essaim,
            n,
            &meilleur1,
            &meilleur2
        );

    /* fin chrono */
    clock_t fin = clock();

    if (meilleur1 == NULL ||
        meilleur2 == NULL) {

        printf("Aucune paire trouvee\n");

        free(essaim);

        return 1;
    }

    /* distance finale */
    float distMin =
        sqrtf(dCarreMin);

    /* temps execution */
    double tempsExecution =
        ((double)(fin - debut)
        / CLOCKS_PER_SEC)
        * 1000.0;

    /* affichage */
    printf("\n");
    printf("===== SYSTEME UAV =====\n\n");

    printf(
        "Drone 1 : ID=%d | "
        "x=%.2f | y=%.2f | z=%.2f\n",

        meilleur1->id,
        meilleur1->x,
        meilleur1->y,
        meilleur1->z
    );

    printf(
        "Drone 2 : ID=%d | "
        "x=%.2f | y=%.2f | z=%.2f\n",

        meilleur2->id,
        meilleur2->x,
        meilleur2->y,
        meilleur2->z
    );

    printf(
        "\nDistance minimale : %.6f\n",
        distMin
    );

    printf(
        "Temps execution   : %.6f ms\n",
        tempsExecution
    );

    /* liberation memoire */
    free(essaim);

    return 0;
}
