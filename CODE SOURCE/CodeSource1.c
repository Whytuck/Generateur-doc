#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Programme d'un jeu sudoku
 * 
 * @author Julou 
 * 
 * @version 1.0
 * 
 * @date Novembre Décembre 2023
 * 
 * Ce programme propose toutes les fonctionnalités pour un jeu sudoku
 */

/**
 * @def TAILLE 
 * 
 * @brief Taille à 9 comme constante pour définir la taille de la grille
 * 
 */
#define TAILLE 9

/**
 * @def NOMBRE
 * 
 * @brief NOMBRE à 56 comme constante 
 * 
 */
#define NOMBRE 56

/**
 * @typedef int
 * 
 * @brief type tableau de TAILLE*TAILLE
 *
 */
typedef int t_Grille[TAILLE][TAILLE];

/*****************************************************
                * FONCTION ET PROCÉDURE *
*****************************************************/

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
 * @fn chargerGrille(t_Grille g)
 * 
 * @brief Procédure qui charge la grille appelé par le joueur
 * 
 * @param g : paramètre utilisé lors de l'utilisation du tableau 
 * 
 */
void chargerGrille(t_Grille g);

/**
 * @fn afficherGrille(t_Grille g)
 * 
 * @brief procédure affichant la grille préalablement chargé
 * 
 * @param g paramètre utilisé lors de l'utilisation du tableau 
 * 
 */
void afficherGrille(t_Grille g);

/**
 * @fn saisir( *valeursaisie)
 * 
 * @brief procédure testant les valeurs de ligne , colonne et valeur a inséré 
 *        rentré par le joueur
 * 
 * @param valeursaisie paramètre utilisé comme variable dans la procédure 
 *                     qui est renvoyé ensuite
 * 
 */
void saisir(int *valeursaisie);

/**
 * @fn bool possible(t_Grille g, int numLigne,int numColonne, int valeur)
 * 
 * @brief Fonction qui teste que aucune valeur corrspondant à la valeur voulant 
 *        être insérer ne soit compris sur la ligne , la colonne et la case
 * 
 * @param g paramètre utilisé lors de l'utilisation du tableau 
 * @param numLigne paramètre correspondant au numéro de ligne
 * @param numColonne paramètre correspondant au numéro de colonne
 * @param valeur paramètre correspondant a la valeur à insérer
 * @return true la valeur respecte les règles du sudoku 
 * @return false la valeur ne respecte pas les règles du sudoku
 * 
 */
bool possible(t_Grille g, int numLigne,int numColonne, int valeur); 

/**
 * @fn bool verifierGrille(t_Grille g)
 * 
 * @brief Fonction qui vérifie si la grille est pleine 
 * 
 * @param g paramètre utilisé lors de l'utilisation du tableau
 * @return true Il y a encore des cases vides dans la grille
 * @return false Il n'y a plus de cases vides dans la grille
 * 
 */
bool verifierGrille(t_Grille g);

/*****************************************************
                * PROGRAMME PRINCIPAL *
*****************************************************/
int main(){

    // attribuer à grille le tableau t_Grille
    t_Grille grille;
    int valeur;
    int numLigne;
    int numColonne;
    chargerGrille(grille);
    afficherGrille(grille);

    /**
     * Tant que la grille n'est pas pleine continuer 
     * 
     */
    while(verifierGrille(grille)){
        printf("Indice de la case : \n");
        saisir(&numLigne);
        saisir(&numColonne);

        /**
         * Si au coordonné rentré par le joueur il y a un chiffre entre 1 et 9 alors la case n'est pas libre
         * 
         */
        if (grille[numLigne][numColonne] != 0){
            printf("IMPOSSIBLE, La case n'est pas libre . \n");
        }
        else {
            printf("Valeur & insérer ? \n");
            saisir(&valeur);

            /**
             * valeur + 1 parce que pour les coordonnés on enlève 1 et qu'on ne veut pas enlever 1 à la valeur 
             * 
             */
            valeur = valeur + 1;

            /**
             * Si cela respecte les règles du sudoku  
             * 
             * @return true la valeur peut être insérer 
             * 
             * @return false la valeur ne peut être insérer
             * 
             */
            if (possible(grille, numLigne ,numColonne , valeur) != false){

                /**
                 * Attribuer au coordonnés numLigne numColonne , la valeur voulant être insérer
                 * 
                 */
                grille[numLigne][numColonne] = valeur;
            }
        }
        afficherGrille(grille);
    }
    printf("Grille pleine, fin de partie \n");
    return EXIT_SUCCESS;
}

/*****************************************************
* DÉFINITION DES FONCTIONS ET PROCÉDURE *
*****************************************************/

/**
 * @fn chargerGrille(t_Grille g)
 * 
 * @brief Chargé
 * 
 * Procédure qui charge la grille appelé par le joueur
 * 
 * @param g : paramètre utilisé lors de l'utilisation du tableau 
 * 
 */
void chargerGrille(t_Grille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);/**
 * @fn chargerGrille(t_Grille g)
 * 
 * @brief Procédure qui charge la grille appelé par le joueur
 * 
 * @param g : paramètre utilisé lors de l'utilisation du tableau 
 * 
 */
    f = fopen(nomFichier, "rb");
    // Ouvre le fichier puis vérifie que le fichier est bien ouvert
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } 
    else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
        fclose(f);
    }
}

/**
 * @brief Affichage
 * 
 * procédure affichant la grille préalablement chargé
 * 
 * @param g paramètre utilisé lors de l'utilisation du tableau 
 * 
 */
void afficherGrille(t_Grille g){
    int lig, col ; 
    // Affiche les numéros de colonnes 
    printf("    1   2   3    4   5   6    7   8   9 \n");
    // Teste tant que l'on est toujours dans la colonne
    for (lig = 0 ; lig < TAILLE ; lig++){
        // Calcul lig divisé par 3 pour afficher une ligne de pointillés tout les trois cases à la vertical
        if (lig % 3 == 0) {
           printf(" +------------+------------+------------+ \n");

        }
        // Affiche les numéros de lignes
        printf("%d", lig + 1);
        // Teste tant que l'on est toujours sur la ligne
        for (col = 0 ; col < TAILLE ; col++){
            // calcul col divisé par 3 pour ajouter un pipe toutes les 3 cases  l'horizontal
            if (col % 3 == 0) {
                printf("|");
            }
            // Teste le caractère contenu dans la case
            // Si un point on affiche un point dans la case
            if (g[lig][col] == 0){
                printf("  %s ", ".");
            //Sinon la valeur attribué à la case
            } else {
                printf("  %d ", g[lig][col]);
            }
        }
        //Affiche un pipe à chaque fin de ligne
        printf("|\n");
    }
    //Affiche une ligne de pointillés à la fin de la grille
    printf(" +------------+------------+------------+ \n");

  
}    if()

/**
 * @fn saisir( *valeursaisie)
 * 
 * @brief Test valeurs
 * 
 * procédure testant les valeurs de ligne , colonne et valeur a inséré 
 * rentré par le joueur
 * 
 * @param valeursaisie paramètre utilisé comme variable dans la procédure 
 *                     qui est renvoyé ensuite
 * 
 */
void saisir(int *valeursaisie){
    char ch[30];
    int x ; 
    //scan la valeur voulant être insérer
    scanf("%s", ch);
    if (sscanf(ch, "%d", &x) !=0){
        // la conversion a réussi, x contient la
        // valeur entière lue au clavier
        // Teste si la valeur est comprise entre 1 et 9
            if((x <= 9) && (x > 0)){
                //Fais -1 à la valeur car les coordonnés sont décalés de -1 
                *valeursaisie = x - 1;
            } 
            else{
                //Redemande de saisir une valeur
                printf("Ecrire une valeur entre 1 et 9 : \n");
                //Rappele la procédure pour recommencer
                saisir(valeursaisie);
            }
        } 
        else {
            //la conversion en entier a échoué
            //Redemande de saisir une valeur
            printf("La valeur rentré n'est pas un entier compris entre 1 et 9 \n");
            printf("Ecrire une valeur entre 1 et 9 : \n");
            //Rappele la procédure pour recommencer
            saisir(valeursaisie);
        }    
}

/**
 * 
 * @brief Fonction qui vérifie les règles du sudoku
 * 
 * Fonction qui teste que aucune valeur corrspondant à la valeur voulant 
 * être insérer ne soit compris sur la ligne , la colonne et la case
 * 
 * @param g paramètre utilisé lors de l'utilisation du tableau 
 * @param numLigne paramètre correspondant au numéro de ligne
 * @param numColonne paramètre correspondant au numéro de colonne
 * @param valeur paramètre correspondant a la valeur à insérer
 * @return true la valeur respecte les règles du sudoku 
 * @return false la valeur ne respecte pas les règles du sudoku
 * 
 */
bool possible(t_Grille g, int numLigne, int numColonne, int valeur){
    int lig, col , ligcase , colcase , N ;
    bool isAllow;
    lig = 0; col = 0;
    isAllow = true;

    N = 3 ;

    // Vérifier la colonne
    //Vérifie lig ne soit pas supérieur à TAILLE et ne soit pas vrai
    while (lig < TAILLE && isAllow){
        // Teste si la valeur est au coordonné
        if (valeur != g[lig][numColonne]) {  
            lig++;
        //Si elle est au coordonné cela retourne faux
        } else {
            printf("La valeur est déjà sur la colonne \n ");
            isAllow = false ;
        }
    }

    //Vérifier la ligne
    //Vérifie col ne soit pas supérieur à TAILLE et ne soit pas vrai
    while (col < TAILLE && isAllow){
        // Teste si la valeur est au coordonné
            if(valeur != g[numLigne][col]) {
                col++;
            //Si elle est au coordonné cela retourne faux
            } else {
                printf("La valeur est déjà sur la ligne \n");
                isAllow = false ;
            }
        }
    //Vérifier la case
    ligcase= ((lig -1 ) /N )*N;

    colcase= ((col -1 ) /N )*N;
    // Vérifie que col ne dépasse pas N
    while(col < N) {
    //Vérifie que lig ne dépasse pas N
        while (lig < N) {
            // Teste si la valeur est dans la case
            if(g[ligcase+lig][colcase+col] == valeur){
                isAllow = false ;
                printf("La valeur est déjà dans la case \n");
            }
            lig++;
        }
        col++;
    }
    return isAllow ;
}

/**
 * 
 * @brief Vérifier grille
 * 
 * Fonction qui vérifie si la grille est pleine en comparant les valeurs de chaque case
 * 
 * @param g paramètre utilisé lors de l'utilisation du tableau
 * @return true Il y a encore des cases vides dans la grille
 * @return false Il n'y a plus de cases vides dans la grille
 * 
 */
bool verifierGrille(t_Grille g){
    int lig=0;
    int col=0;
    bool trouve ;
    trouve = false;
    // Vérifie que col ne dépasse pas TAILLE
    while(col != TAILLE) {
        // Vérifie que lig ne dépasse pas TAILLE
        while (lig != TAILLE) {
            //Vérifie que il n'y a plus de 0 dans la grille 
            if (g[lig][col] == 0) {
                trouve = true ;
            }
            lig++;
        }
        lig=0;
        col++;
    }
    return trouve ;
}

