/**
 * @file morpion.c
 * @brief Un programme simple de jeu de morpion avec des structures.
 * @author Delouya
 * @date 05 Décembre 2023
 * @version 1.0
 */

#include <stdio.h>

/**
 * @brief Structure représentant un joueur.
 */
struct Joueur {
  char symbole; /**< Le symbole du joueur ('X' ou 'O'). */
  int tour;     /**< Le numéro du tour du joueur (1 ou 2). */
};

/**
 * @brief Structure représentant une case du tableau de morpion.
 */
struct Case {
  char contenu; /**< Le contenu de la case ('X', 'O' ou ' '). */
};

/**
 * @brief Affiche le tableau de morpion.
 * @param tableau Le tableau de morpion à afficher.
 */
void afficherTableau(struct Case tableau[3][3]) {
  printf("  1 2 3\n");
  for (int i = 0; i < 3; i++) {
    printf("%d ", i + 1);
    for (int j = 0; j < 3; j++) {
      printf("%c ", tableau[i][j].contenu);
    }
    printf("\n");
  }
  printf("\n");
}

/**
 * @brief Vérifie si un joueur a gagné.
 * @param tableau Le tableau de morpion.
 * @param joueur Le joueur à vérifier.
 * @return 1 si le joueur a gagné, 0 sinon.
 */
int verifierGagnant(struct Case tableau[3][3], struct Joueur joueur) {
  // Vérification des lignes et des colonnes
  for (int i = 0; i < 3; i++) {
    if ((tableau[i][0].contenu == joueur.symbole &&
         tableau[i][1].contenu == joueur.symbole &&
         tableau[i][2].contenu == joueur.symbole) ||
        (tableau[0][i].contenu == joueur.symbole &&
         tableau[1][i].contenu == joueur.symbole &&
         tableau[2][i].contenu == joueur.symbole)) {
      return 1; // Le joueur a gagné
    }
  }

  // Vérification des diagonales
  if ((tableau[0][0].contenu == joueur.symbole &&
       tableau[1][1].contenu == joueur.symbole &&
       tableau[2][2].contenu == joueur.symbole) ||
      (tableau[0][2].contenu == joueur.symbole &&
       tableau[1][1].contenu == joueur.symbole &&
       tableau[2][0].contenu == joueur.symbole)) {
    return 1; // Le joueur a gagné
  }

  return 0; // Aucun gagnant
}

/**
 * @brief Vérifie si le tableau est complet (match nul).
 * @param tableau Le tableau de morpion.
 * @return 1 si le match est nul, 0 sinon.
 */
int estMatchNul(struct Case tableau[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (tableau[i][j].contenu == ' ') {
        return 0; // Il reste des espaces vides, le match n'est pas nul
      }
    }
  }
  return 1; // Le match est nul
}

/**
 * @brief Fonction principale du jeu de morpion.
 * @return 0 si le programme s'est exécuté avec succès.
 */
int main() {
  struct Case tableau[3][3] = {
      {{' '}, {' '}, {' '}}, {{' '}, {' '}, {' '}}, {{' '}, {' '}, {' '}}};
  struct Joueur joueurX = {'X', 1};
  struct Joueur joueurO = {'O', 2};

  while (1) {
    // Affichage du tableau
    afficherTableau(tableau);

    // Saisie du mouvement
    int ligne, colonne;
    printf("Joueur %c, entrez votre mouvement (ligne colonne) : ",
           (joueurX.tour == 1) ? 'X' : 'O');
    scanf("%d %d", &ligne, &colonne);

    // Vérification de la validité du mouvement
    if (ligne < 1 || ligne > 3 || colonne < 1 || colonne > 3 ||
        tableau[ligne - 1][colonne - 1].contenu != ' ') {
      printf("Mouvement invalide. Veuillez réessayer.\n");
      continue;
    }

    // Enregistrement du mouvement
    tableau[ligne - 1][colonne - 1].contenu = (joueurX.tour == 1) ? 'X' : 'O';

    // Vérification du gagnant
    if (verifierGagnant(tableau, joueurX) ||
        verifierGagnant(tableau, joueurO)) {
      afficherTableau(tableau);
      printf("Le joueur %c a gagné !\n", (joueurX.tour == 1) ? 'X' : 'O');
      break;
    }

    // Vérification du match nul
    if (estMatchNul(tableau)) {
      afficherTableau(tableau);
      printf("Match nul !\n");
      break;
    }

    // Changement de joueur
    joueurX.tour = (joueurX.tour == 1) ? 2 : 1;
    joueurO.tour = (joueurO.tour == 1) ? 2 : 1;
  }

  return 0;
}
