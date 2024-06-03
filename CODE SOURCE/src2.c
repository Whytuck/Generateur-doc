#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Fonction pour choisir un mot au hasard dans une liste
char *choisirMot() {
    const char *listeMots[] = {"PROGRAMMATION", "INFORMATIQUE", "DEVELOPPEMENT", "LANGAGE", "OPENAI", "GPT", "PENDU"};
    int tailleListe = sizeof(listeMots) / sizeof(listeMots[0]);

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Choix d'un indice aléatoire dans la liste
    int indice = rand() % tailleListe;

    // Retourne le mot choisi
    return strdup(listeMots[indice]);
}

// Fonction pour afficher le mot partiellement révélé
void afficherMotPartiel(const char *mot, const char *lettresTrouvees) {
    for (int i = 0; i < strlen(mot); i++) {
        if (strchr(lettresTrouvees, mot[i]) != NULL) {
            printf("%c ", mot[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Fonction pour afficher le dessin du pendu
void afficherPendu(int erreurs) {
    switch (erreurs) {
        case 0:
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            break;
        case 1:
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("___\n");
            break;
        case 2:
            printf("\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("___\n");
            break;
        case 3:
            printf("_____\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("___\n");
            break;
        case 4:
            printf("_____\n");
            printf(" |   |\n");
            printf(" |\n");
            printf(" |\n");
            printf("___\n");
            break;
        case 5:
            printf("_____\n");
            printf(" |   |\n");
            printf(" |   O\n");
            printf(" |\n");
            printf("___\n");
            break;
        case 6:
            printf("_____\n");
            printf(" |   |\n");
            printf(" |   O\n");
            printf(" |  /|\\\n");
            printf("___\n");
            break;
        case 7:
            printf("_____\n");
            printf(" |   |\n");
            printf(" |   O\n");
            printf(" |  /|\\\n");
            printf(" |  /\n");
            break;
        case 8:
            printf("_____\n");
            printf(" |   |\n");
            printf(" |   O\n");
            printf(" |  /|\\\n");
            printf(" |  / \\\n");
            break;
    }
}

int main() {
    char *motSecret = choisirMot();
    int tailleMot = strlen(motSecret);
    char lettresTrouvees[tailleMot];
    memset(lettresTrouvees, ' ', tailleMot); // Initialise le tableau avec des espaces

    int erreurs = 0;
    char lettreProposee;

    printf("Bienvenue dans le jeu du Pendu!\n");

    do {
        // Affichage du mot partiellement révélé
        afficherMotPartiel(motSecret, lettresTrouvees);

        // Affichage du dessin du pendu
        afficherPendu(erreurs);

        // Saisie de la lettre proposée
        printf("Entrez une lettre : ");
        scanf(" %c", &lettreProposee);

        // Vérification de la lettre proposée
        int lettreTrouvee = 0;
        for (int i = 0; i < tailleMot; i++) {
            if (motSecret[i] == toupper(lettreProposee)) {
                lettresTrouvees[i] = toupper(lettreProposee);
                lettreTrouvee = 1;
            }
        }

        // Si la lettre n'est pas trouvée, incrémente le nombre d'erreurs
        if (!lettreTrouvee) {
            erreurs++;
        }

        // Vérification de la fin de partie
        if (erreurs == 8) {
            // Affichage du mot complet en cas de défaite
            afficherMotPartiel(motSecret, lettresTrouvees);
            printf("Désolé, vous avez perdu. Le mot était : %s\n", motSecret);
            break;
        } else if (strcmp(lettresTrouvees, motSecret) == 0) {
            // Affichage du mot complet en cas de victoire
            afficherMotPartiel(motSecret, lettresTrouvees);
            printf("Félicitations, vous avez deviné le mot : %s\n", motSecret);
            break;
        }

    } while (1);

    // Libération de la mémoire allouée pour le mot secret
    free(motSecret);

    return 0;
}
