#include <stdio.h>

// Fonction pour afficher le tableau de morpion
void afficherTableau(char tableau[3][3]) {
    printf("  1 2 3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("%c ", tableau[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fonction pour vérifier si un joueur a gagné
int verifierGagnant(char tableau[3][3], char symbole) {
    // Vérification des lignes et des colonnes
    for (int i = 0; i < 3; i++) {
        if ((tableau[i][0] == symbole && tableau[i][1] == symbole && tableau[i][2] == symbole) ||
            (tableau[0][i] == symbole && tableau[1][i] == symbole && tableau[2][i] == symbole)) {
            return 1; // Le joueur a gagné
        }
    }

    // Vérification des diagonales
    if ((tableau[0][0] == symbole && tableau[1][1] == symbole && tableau[2][2] == symbole) ||
        (tableau[0][2] == symbole && tableau[1][1] == symbole && tableau[2][0] == symbole)) {
        return 1; // Le joueur a gagné
    }

    return 0; // Aucun gagnant
}

// Fonction pour vérifier si le tableau est complet (match nul)
int estMatchNul(char tableau[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tableau[i][j] == ' ') {
                return 0; // Il reste des espaces vides, le match n'est pas nul
            }
        }
    }
    return 1; // Le match est nul
}

int main() {
    char tableau[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int tour = 1; // tour = 1 pour le joueur X, tour = 2 pour le joueur O

    while (1) {
        // Affichage du tableau
        afficherTableau(tableau);

        // Saisie du mouvement
        int ligne, colonne;
        printf("Joueur %c, entrez votre mouvement (ligne colonne) : ", (tour == 1) ? 'X' : 'O');
        scanf("%d %d", &ligne, &colonne);

        // Vérification de la validité du mouvement
        if (ligne < 1 || ligne > 3 || colonne < 1 || colonne > 3 || tableau[ligne - 1][colonne - 1] != ' ') {
            printf("Mouvement invalide. Veuillez réessayer.\n");
            continue;
        }

        // Enregistrement du mouvement
        tableau[ligne - 1][colonne - 1] = (tour == 1) ? 'X' : 'O';

        // Vérification du gagnant
        if (verifierGagnant(tableau, (tour == 1) ? 'X' : 'O')) {
            afficherTableau(tableau);
            printf("Le joueur %c a gagné !\n", (tour == 1) ? 'X' : 'O');
            break;
        }

        // Vérification du match nul
        if (estMatchNul(tableau)) {
            afficherTableau(tableau);
            printf("Match nul !\n");
            break;
        }

        // Changement de joueur
        tour = (tour == 1) ? 2 : 1;
    }

    return 0;
}
