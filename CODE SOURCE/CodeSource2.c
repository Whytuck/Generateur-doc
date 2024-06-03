#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief Programme d'un jeu sudoku
 * 
 * @author Julou 
 * 
 * @version 1.0
 * 
 * @date 05 Décembre 2023
 * 
 * Ce programme propose toutes les fonctionnalités pour le jeu du pendu 
 */

/**
 * @def TAILLE 
 * 
 * @brief Taille à 10 comme constante pour définir la taille du tableau
 * 
 */
#define TAILLE 10

/**
 * @def NOMBRE
 * 
 * @brief NOMBRE à 56 comme constante 
 * 
 */
#define NOMBRE 56

/**
 * @brief structure donnant les caractéristique de monique
 * 
 * @param nb1 Un entier positif
 * @param nb2 Un nombre décimal
 * @param loin Renvoie l'endroit ou est situé monique
 * 
 */
typedef struct 
{
    int nb1 ;
    float nb2 ;
    char loin ;
} monique;

/**
 * @brief structure contenant les caractéristique de la chasse d'Alan
 * 
 * @param trouve renvoie 1 ou 0 si Alan est trouvé
 * @param cherche renvoie un message pourchercher Alan
 * @param perdu renvoie vrai si Alan est retrouver et faux dans le cas contraire
 * 
 */
typedef struct 
{
  int trouve ;
  char cherche ;
  bool perdu ;
} Alan;


/**
 * @brief Choisi aléatoirement un mot parmi une liste prédéfinie.
 *
 * Cette fonction sélectionne aléatoirement un mot parmi une liste prédéfinie
 * et renvoie une copie allouée dynamiquement du mot choisi.
 *
 * @return Un pointeur vers une nouvelle chaîne de caractères (mot choisi).
 *
 */
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

/**
 * @brief Affiche une version partiellement découverte du mot.
 *
 * Cette fonction affiche une version partiellement découverte du mot en fonction
 * des lettres déjà trouvées. Les lettres trouvées sont affichées, tandis que les
 * lettres non découvertes sont représentées par des underscores.
 *
 * @param mot Le mot à afficher partiellement.
 * @param lettresTrouvees Les lettres déjà trouvées dans le mot.
 */
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

/**
 * @brief Affiche le dessin du pendu en fonction du nombre d'erreurs.
 *
 * Cette fonction affiche une représentation graphique du pendu en fonction du
 * nombre d'erreurs commises dans le jeu. Chaque niveau d'erreur correspond à
 * une étape différente du dessin.
 *
 * @param erreurs Le nombre d'erreurs commises.
 *   - 0 : Aucune erreur.
 *   - 1 : Premier niveau d'erreur.
 *   - 2 : Deuxième niveau d'erreur.
 *   - 3 : Troisième niveau d'erreur.
 *   - 4 : Quatrième niveau d'erreur.
 *   - 5 : Cinquième niveau d'erreur.
 *   - 6 : Sixième niveau d'erreur.
 *   - 7 : Septième niveau d'erreur.
 *   - 8 : Huitième niveau d'erreur (partie perdue).
 */
void afficherPendu(int erreurs) {
    switch (erreurs) {
    afficherPendu(erreurs){
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
/**
 * @brief défini un tableau 
 * 
 * @param TAILLE défini la taille du tableau à TAILLE
 * 
 */
typedef float t_vecteur[TAILLE];

/**
 * @brief défini un tableau de TAILLE*TAILLE
 * 
 * @param TAILLE défini la taille du tableau à TAILLE
 * 
 */
typedef float t_matrice[TAILLE][TAILLE];



/**
 * @brief Fonction principale du jeu du Pendu.
 *
 * Cette fonction initialise le jeu du Pendu, génère un mot secret,
 * puis permet à l'utilisateur de deviner les lettres du mot.
 *
 * @return 0 si le programme s'exécute correctement.
 */
int main() {

    t_vecteur vInitial ={35,25,20,20}; // rentre les valeurs dans le tableau de t_vecteur et lui attribue le nom vInitial
    t_matrice mEvolution =  {{0.9,0.06,0.08,0.05},
                             {0.03,0.8,0.02,0.03},
                             {0.02,0.03,0.75,0.04},
                             {0.05,0.11,0.15,0.88}
                            };// rentre les valeurs dans le tableau de t_matrice et lui attribue le nom mEvolution

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

    return EXIT_SUCCESS ;
}
