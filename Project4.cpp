#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// Evite d'avoir à écrire std::
using namespace std;

// Dimensions de la grille (sont des entiers constants)
const int HAUTEUR = 25;
const int LARGEUR = 50;

// Fonction pour afficher la grille avec un void car on n'attend pas de valeur en retour
// On a 2 fois vector car on affiche une matrice de nombre entier (même binaire)
// La fonction prend en argument notre grille qui est une matrice 2D et on met const car on ne s'attend pas
// à ce que la fonction change la variable
void affichageGrille(const vector<vector<int>>& grille) {
    // Crée une "illusion" d'animation. (On ne sait pas comment ça marche mais... ça marche)
    cout << "\033[H";
    // On passe d'abord sur l'axe vertical
    for (int i = 0; i < HAUTEUR; ++i) {
        // Puis l'axe horizontal
        for (int j = 0; j < LARGEUR; ++j) {
            // On vérifie l'état de la cellule : 1 (vivante) ou 0 (morte)
            if (grille[i][j] == 1)
                // Astérisque pour une cellule vivante
                cout << "*"; 
            else
                // Espace pour une cellule morte
                cout << " "; 
        }
        // Ligne suivante
        cout << "\n"; 
    }
}

// Fonction pour compter les voisins vivants d'une cellule dans la grille donc renvoie un integer
// La fonction prend en entrée la grille et les coordonnées (x, y) de la cellule de départ. Prend des integers en input
int nbVoisinVivants(const vector<vector<int>>& grille, int x, int y) {

    // Initialisation du nombre de voisins vivants
    int voisinVivant = 0; 

    // On parcourt les cellules autour de la cellule de départ
    // D'abord celle sur l'axe vertical
    for (int i = -1; i <= 1; ++i) {
        // Puis sur l'axe horizontal
        for (int j = -1; j <= 1; ++j) {
            // On ne compte la i=0 et j=0 car c'est la cellule de départ
            if (i == 0 && j == 0)
                continue; // Continue passe à la prochaine itération de la boucle

            // Coordonnées des cellules voisines
            int nvX = x + i;
            int nvY = y + j;

            // Si le voisin est à l'intérieur de la grille
            if (nvX >= 0 && nvX < HAUTEUR && nvY >= 0 && nvY < LARGEUR) {
                // Incrémentation du compteur si un voisin est vivant
                voisinVivant += grille[nvX][nvY];
            }
            // Si le voisin est en dehors de la grille, il est considéré comme mort
        }
    }
    // Retourne le nombre total de voisins vivants autour de la cellule de départ
    return voisinVivant;
}


// Fonction pour mettre à jour la grille en appliquant les règles du Jeu de la Vie
// Cette fonction prend en entrée la grille actuelle et renvoie une nouvelle grille mise à jour.
vector<vector<int>> majGrille(const vector<vector<int>>& ancGrille) {
    // Création d'une nouvelle grille vide pour la prochaine génération.
    vector<vector<int>> nvGrille(HAUTEUR, vector<int>(LARGEUR, 0));

    // Parcours de chaque cellule de la grille
    for (int i = 0; i < HAUTEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            // Compte les voisins vivants de la cellule courante
            int voisinVivant = nbVoisinVivants(ancGrille, i, j);

            // Applique les règles du Jeu de la Vie :
            if (ancGrille[i][j] == 1 && (voisinVivant == 2 || voisinVivant == 3)) {
                // Règle de survie : Une cellule vivante avec deux ou trois voisins vivants reste vivante.
                nvGrille[i][j] = 1;
            }
            else if (ancGrille[i][j] == 0 && voisinVivant == 3) {
                // Règle de naissance : Une cellule morte avec exactement trois voisins vivants devient vivante.
                nvGrille[i][j] = 1;
            }
            else {
                // Règle de mort : Dans tous les autres cas, une cellule meurt ou reste morte.
                nvGrille[i][j] = 0;
            }
            // La cellule est mise à jour dans la nouvelle grille en fonction des règles ci-dessus.
        }
    }
    // Retourne la nouvelle grille avec la prochaine génération de cellules.
    return nvGrille;
}


int main() {
    // Création de notre grille
    vector<vector<int>> grille(HAUTEUR, vector<int>(LARGEUR, 0));

    // Initialisation de la grille avec un motif plus grand
    grille[15][40] = 1;
    grille[15][41] = 1;

    grille[15][44] = 1;
    grille[16][41] = 1;
    grille[16][42] = 1;

    grille[17][40] = 1;
    grille[17][41] = 1;

    grille[18][43] = 1;
    grille[18][44] = 1;
    grille[19][43] = 1;
    grille[19][44] = 1;

    grille[17][12] = 1;
    grille[17][13] = 1;
    grille[16][12] = 1;
    grille[16][11] = 1;

    // Initialisation de la grille avec un canon à planeurs de Gosper
    grille[5][1] = 1; grille[5][2] = 1; 
    grille[6][1] = 1; grille[6][2] = 1;
    grille[5][11] = 1; grille[6][11] = 1; grille[7][11] = 1;
    grille[4][12] = 1; grille[8][12] = 1;
    grille[3][13] = 1; grille[9][13] = 1;
    grille[3][14] = 1; grille[9][14] = 1;
    grille[6][15] = 1;
    grille[4][16] = 1; grille[8][16] = 1;
    grille[5][17] = 1; grille[6][17] = 1; grille[7][17] = 1;
    grille[6][18] = 1;
    grille[3][21] = 1; grille[4][21] = 1; grille[5][21] = 1;
    grille[3][22] = 1; grille[4][22] = 1; grille[5][22] = 1;
    grille[2][23] = 1; grille[6][23] = 1;
    grille[1][25] = 1; grille[2][25] = 1; grille[6][25] = 1; grille[7][25] = 1;
    grille[3][35] = 1; grille[4][35] = 1;
    grille[3][36] = 1; grille[4][36] = 1;


    // Efface l'écran et positionne le curseur en haut à gauche (pareil ça marche mais... grâce à une volonté qui nous dépasse)
    cout << "\033[2J\033[H";

    while (true) {
        affichageGrille(grille);
        grille = majGrille(grille);

        // Met en pause le code pour bien voir "l'animation"
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}

