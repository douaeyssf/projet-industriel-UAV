#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "drone.h"

/* ============================================
 * main.c
 * Point d'entree du systeme de collision UAV
 * Generation, tri, recherche et affichage
 * ============================================ */

int main()
{
    /* Nombre de drones dans l'essaim */
    int n = 10000;

    /* Initialisation du generateur aleatoire */
    srand((unsigned int)time(NULL));

    /* Allocation dynamique de l'essaim sur le tas */
    struct Drone *essaim =
        (struct Drone *)malloc(n * sizeof(struct Drone));

    if (essaim == NULL) {
        printf("Erreur allocation memoire\n");
        return 1;
    }

    /* Generation des coordonnees 3D aleatoires */
    /* Navigation par arithmetique de pointeurs - crochets interdits */
    for (int i = 0; i < n; i++) {

        (essaim + i)->id = i + 1;

        (essaim + i)->x =
            ((float)rand() / (float)RAND_MAX) * 1000.0f;

        (essaim + i)->y =
            ((float)rand() / (float)RAND_MAX) * 1000.0f;

        (essaim + i)->z =
            ((float)rand() / (float)RAND_MAX) * 1000.0f;
    }

    /* Tri par coordonnee X : requis par l'algorithme D&C */
    qsort(essaim, n, sizeof(struct Drone), trierX);

    /* Declarations locales pour la paire resultat */
    struct Drone *meilleur1 = NULL;
    struct Drone *meilleur2 = NULL;

    /* Debut du chronometrage */
    clock_t debut = clock();

    /* Lancement de l'algorithme diviser pour regner */
    float dCarreMin =
        plusProche(essaim, n, &meilleur1, &meilleur2);

    /* Fin du chronometrage */
    clock_t fin = clock();

    /* Verification de securite avant affichage */
    if (meilleur1 == NULL || meilleur2 == NULL) {
        printf("Aucune paire trouvee\n");
        free(essaim);
        return 1;
    }

    /* Calcul de la distance reelle (un seul sqrt final) */
    float distMin = sqrtf(dCarreMin);

    /* Conversion du temps en millisecondes */
    double tempsExecution =
        ((double)(fin - debut) / CLOCKS_PER_SEC) * 1000.0;

    /* Affichage des resultats */
    printf("\n");
    printf("===== SYSTEME DE COLLISION UAV =====\n\n");

    printf(
        "Drone 1 : ID=%d | x=%.2f | y=%.2f | z=%.2f\n",
        meilleur1->id,
        meilleur1->x,
        meilleur1->y,
        meilleur1->z
    );

    printf(
        "Drone 2 : ID=%d | x=%.2f | y=%.2f | z=%.2f\n",
        meilleur2->id,
        meilleur2->x,
        meilleur2->y,
        meilleur2->z
    );

    printf("\nDistance minimale : %.6f\n", distMin);
    printf("Temps execution   : %.6f ms\n", tempsExecution);

    /* Liberation de la memoire allouee */
    free(essaim);

    return 0;
}
