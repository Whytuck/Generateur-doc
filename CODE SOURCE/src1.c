#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Fonction pour choisir un mot au hasard dans une liste
char *choisirMot() {
    const char *listeMots[] = {"TABLE", "CHAISE", "ORDINATEUR", "PROGRAMME", "FENETRE", "VOITURE", "BANANE"};
    int tailleListe = sizeof(listeMots) / sizeof(listeMots[0]);

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Choix d'un indice aléatoire dans la liste
    int indice = rand() % tailleListe;

    // Retourne le mot choisi
    return strdup(listeMots[indice]);
}

// Fonction pour vérifier la proposition du joueur
void verifierProposition(const char *motSecret, const char *proposition) {
    int longueur = strlen(motSecret);
    int bienPlacees = 0, malPlacees = 0;

    for (int i = 0; i < longueur; i++) {
        if (proposition[i] == motSecret[i]) {
            bienPlacees++;
        } else if (strchr(motSecret, proposition[i]) != NULL) {
            malPlacees++;
        }
    }

    // Affichage du résultat
    printf("Bien placées : %d\n", bienPlacees);
    printf("Mal placées : %d\n", malPlacees);
}

int main() {
    char *motSecret = choisirMot();
    int longueurMot = strlen(motSecret);

    printf("Bienvenue dans le jeu de Motus !\n");
    printf("Devinez le mot de %d lettres.\n", longueurMot);

    do {
        char proposition[20];  // Assumons une longueur maximale pour la proposition
        printf("Entrez votre proposition : ");
        scanf("%s", proposition);

        // Vérification de la longueur de la proposition
        if (strlen(proposition) != longueurMot) {
            printf("La proposition doit avoir %d lettres. Réessayez.\n", longueurMot);
            continue;
        }

        // Vérification de la proposition
        verifierProposition(motSecret, proposition);

        // Si la proposition est correcte, le joueur a gagné
        if (strcmp(motSecret, proposition) == 0) {
            printf("Félicitations, vous avez deviné le mot : %s\n", motSecret);
            break;
        }

    } while (1);

    // Libération de la mémoire allouée pour le mot secret
    free(motSecret);

    return 0;
}
