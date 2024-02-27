/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

/*------------------------------ Constantes ---------------------------------*/
#define NB_CASES 10     // nombre de cases de la grille de jeu

#define RESET   "\x1b[0m"
#define BLACK   "\x1b[30m"      /* Black */     // les murs sont en noir
#define RED     "\x1b[31m"      /* Red */       // les couloirs sont en rouge
#define GREEN   "\x1b[32m"      /* Green */
#define YELLOW  "\x1b[33m"      /* Yellow */    // le bureau des techs est en jaune
#define BLUE    "\x1b[34m"      /* Blue */      // les salles sont en bleu
#define MAGENTA "\x1b[35m"      /* Magenta */   // la salle secrète est en magenta
#define CYAN    "\x1b[36m"      /* Cyan */
#define WHITE   "\x1b[37m"      /* White */     // par défaut, dans cmd en noir, les caractères sont blancs

/*------------------------- Prototypes de fonctions -------------------------*/
void showMap();
bool verifyMovement(string couleur);
bool movePlayer(char *c, char *b);
void enterRoom();
void showOne();
void showTwo();
void showThree();
void showTime(int temps);
void showDeath();
void quickTimeEvent();
void enterTech();
void enterSecret();
void findEvent();
void showLogo();
void showMission();
void clearBuffer();

/*---------------------------- Variables globales ---------------------------*/
int posX = 2;   // Position du joueur en x et en y (pour les tableaux)
int posY = 8;
int playerX = 4; // Position du joueur en x et en y dans l'affichage (chaque case fait deux de large)
int playerY = 16;

bool key = false;           // Variable pour la clé de la salle secrète
bool colereSerge = true;    // Variable pour la colère de Serge (déclenche un QTE dans le bureau des techs si true)
bool game = true;           // Variable pour qui indique que la partie est en cours (si false, le jeu se termine)

// Tableau de couleurs ()
string colors[NB_CASES][NB_CASES] = {
    {RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK},                   //LIGNE 0
    {RED, BLACK, BLACK, RED, BLACK, BLACK, RED, BLACK, RED, BLACK},         //LIGNE 1
    {RED, BLACK, BLUE, RED, BLACK, MAGENTA, RED, BLACK, RED, BLACK},        //LIGNE 2
    {RED, BLACK, BLACK, RED, BLACK, BLACK, RED, BLACK, RED, YELLOW},        //LIGNE 3
    {RED, BLACK, BLACK, RED, BLUE, BLACK, RED, BLUE, RED, BLACK},           //LIGNE 4
    {RED, BLACK, BLACK, RED, BLACK, BLACK, RED, BLACK, RED, BLACK},         //LIGNE 5
    {RED, BLACK, BLUE, RED, BLACK, BLACK, RED, BLACK, RED, BLACK},          //LIGNE 6
    {RED, BLACK, BLACK, RED, BLACK, BLACK, RED, BLUE, RED, BLACK},          //LIGNE 7
    {RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK},                   //LIGNE 8
    {BLACK, BLACK, BLUE, BLACK, BLACK, BLACK, BLUE, BLACK, BLUE, BLACK}     //LIGNE 9
};

// Tableau des numéros des salles (pour que ce soit comme à l'université)
int salles[NB_CASES][NB_CASES] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,3041,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,3024,0,0,3018,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,3035,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,3016,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,3032,0,0,0,3027,0,3014,0},
};

/*---------------------------Définition de fonctions ------------------------*/

// Fonction qui affiche la carte
void showMap() {
    system("cls");

    for (int i = 0; i < 2*NB_CASES; ++i) {
        for (int j = 0; j < 2*NB_CASES; ++j) {
            if ((i/2 == posY) && (j/2 == posX)) {   // Si on est à la position du joueur (il fait 2x2 de taille)
                cout << RESET << "00";              // on dessine le joueur (avec des 00, ça ressemble à 8 têtes, comme une équipe)
            } else {                                // Sinon, on dessine la case de couleur
                cout << colors[i/2][j/2] << "[]" << RESET;
            }
        }
        cout << endl;
    }
    cout << "Utilisez les touches WASD (ou les boutons) pour vous deplacer (Q pour quitter): ";
}

// Fonction qui vérifie si le mouvement du joueur est possible
bool verifyMovement(string couleur){
    system("cls");
    if(couleur == BLACK){
        cout << "Vous ne pouvez pas (encore) traverser les murs.";
        Sleep(500);
        showMap();
        return false;
    }
    else if(couleur == MAGENTA && key == false){
        cout << MAGENTA << "Vous n'avez pas les autorisations pour entrer ici.\n" << RESET;
        Sleep(1000);
        showMap();
        return false;
    }
    else
        return true;

}

// Fonction qui déplace le joueur
bool movePlayer(char *c, char *b){
    bool moved = false;
    if (*c == 'W' || *b == 'W'){
        if (posY > 0) {
            if(verifyMovement(colors[posY-1][posX])) {
                playerY -= 2; // Déplacement de deux cases vers le haut
                posY--;
                moved = true;
            }
        }
    }
    else if (*c == 'A' || *b == 'A'){
        if (posX > 0) {
            if(verifyMovement(colors[posY][posX-1])) {
                playerX -= 2; // Déplacement de deux cases vers la gauche
                posX--;
                moved = true;
            }
        }
    }
    else if (*c == 'S' || *b == 'S'){
        if (posY < NB_CASES - 1) {
            if(verifyMovement(colors[posY+1][posX])) {
                playerY += 2; // Déplacement de deux cases vers le bas
                posY++;
                moved = true;
            }
        }
    }
    else if (*c == 'D' || *b == 'D'){
        if (posX < NB_CASES - 1) {
            if(verifyMovement(colors[posY][posX+1])) {
                playerX += 2; // Déplacement de deux cases vers la droite
                posX++;
                moved = true;
            }
        }
    }
    // Réinitialisez les valeurs des boutons à ' ' après utilisation
    *c = ' ';
    *b = ' ';
    return moved;
}

// Fonction qui affiche le numéro de la salle entrée
void enterRoom() {
    system("cls");
    cout << CYAN << "Vous etes dans la salle " << salles[posY][posX] << endl << RESET;
    Sleep(1000);
}

// Fonction qui affiche 1 en jaune de manière fancy en ASCII art
void showOne() {
    cout << YELLOW;
    cout << "  1111111   \n"
            " 1::::::1   \n"
            "1:::::::1   \n"
            "111:::::1   \n"
            "   1::::1   \n"
            "   1::::1   \n"
            "   1::::1   \n"
            "   1::::l   \n"
            "   1::::l   \n"
            "   1::::l   \n"
            "   1::::l   \n"
            "   1::::l   \n"
            "   1::::l   \n"
            "111::::::111\n"
            "1::::::::::1\n"
            "1::::::::::1\n"
            "111111111111\n";
    cout << RESET;
}

// Fonction qui affiche 2 en cyan de manière fancy en ASCII art
void showTwo() {
    cout << CYAN;
    cout << " 222222222222222    \n"
            "2:::::::::::::::22  \n"
            "2::::::222222:::::2 \n"
            "2222222     2:::::2 \n"
            "            2:::::2 \n"
            "            2:::::2 \n"
            "         2222::::2  \n"
            "    22222::::::22   \n"
            "  22::::::::222     \n"
            " 2:::::22222        \n"
            "2:::::2             \n"
            "2:::::2             \n"
            "2:::::2       222222\n"
            "2::::::2222222:::::2\n"
            "2::::::::::::::::::2\n"
            "22222222222222222222\n";
    cout << RESET;
}

// Fonction qui affiche 3 en magenta de manière fancy en ASCII art
void showThree() {
    cout << MAGENTA;
    cout << " 333333333333333   \n"
            "3:::::::::::::::33 \n"
            "3::::::33333::::::3\n"
            "3333333     3:::::3\n"
            "            3:::::3\n"
            "            3:::::3\n"
            "    33333333:::::3 \n"
            "    3:::::::::::3  \n"
            "    33333333:::::3 \n"
            "            3:::::3\n"
            "            3:::::3\n"
            "            3:::::3\n"
            "3333333     3:::::3\n"
            "3::::::33333::::::3\n"
            "3:::::::::::::::33 \n"
            " 333333333333333   \n";
    cout << RESET;
}

// Fonction qui affiche le temps de manière fancy en ASCII art (les 3 dernières secondes seulement)
void showTime(int temps){
    switch (temps)
    {
    case 1:
        showOne();
        break;
    case 2:
        showTwo();
        break;
    case 3:
        showThree();
        break;
    default:
        break;
    }
}

// Fonction qui affiche la défaite du joueur
void showDeath(){
    system("cls");
    cout << RED << "Serge vous a attrape !" << endl;
    Sleep(500);
    system("cls");
    cout << "`YMM'   `MM' .g8\"\"8q. `7MMF'   `7MF'    `7MM\"\"\"Yb. `7MMF'`7MM\"\"\"YMM  \n"
            "  VMA   ,V .dP'    `YM. MM       M        MM    `Yb. MM    MM    `7  \n"
            "   VMA ,V  dM'      `MM MM       M        MM     `Mb MM    MM   d    \n"
            "    VMMP   MM        MM MM       M        MM      MM MM    MMmmMM    \n"
            "     MM    MM.      ,MP MM       M        MM     ,MP MM    MM   Y  , \n"
            "     MM    `Mb.    ,dP' YM.     ,M        MM    ,dP' MM    MM     ,M \n"
            "   .JMML.    `\"bmmd\"'    `bmmmmd\"'      .JMMmmmdP' .JMML..JMMmmmmMMM\n";
    cout << RESET;
    Sleep(1000);
    game = false;
}

// Fonction pour le QTE (Quick Time Event) contre Serge
void quickTimeEvent() {
    char touche;
    string input;
    string sequence = "SERGE";

    // Afficher le message d'instructions
    cout << RED << "Serge est en colere. Appuyez sur les bonnes touches pour lui echapper." << RESET << endl;
    Sleep(2000);

    for(int i = 0; i < sequence.length(); i++) {
        system("cls");
        // Afficher la séquence à l'utilisateur
        cout << RED << "Appuyez sur la touche: " << sequence[i] << RESET << endl;

        // Chronométrer le délai de 4 secondes
        auto start = high_resolution_clock::now();
        auto end = start + seconds(4);
        auto old_remaining_int = 4;

        // Lire les touches de l'utilisateur pendant le délai
        while (high_resolution_clock::now() < end) {
            auto remaining_time = duration_cast<seconds>(end - high_resolution_clock::now()).count();
            if ((int)(remaining_time) != old_remaining_int) {
                system("cls");
                cout << RED << "Appuyez sur la touche: " << sequence[i] << RESET << endl;
                showTime(remaining_time);
                old_remaining_int = (int)(remaining_time);  // Mettre à jour la partie entière du temps restant
            }

            if (_kbhit()) {
                touche = toupper(_getch());
                input += touche;
                break;
            }
        }

        // Comparer la touche d'entrée avec la touche attendue
        if (touche != sequence[i]) {
            showDeath();
            break;
        }
    }

    if (input == sequence) {
        system("cls");
        cout << GREEN << "Bravo, vous avez echappe a Serge !" << RESET << endl;
    }
    Sleep(1000);
    colereSerge = false;
}

// Fonction qui affiche que vous êtes dans le bureau des techs et qui déclenche le QTE si Serge est en colère
void enterTech() {
    system("cls");
    cout << YELLOW << "Vous etes dans le bureau des techniciens.\n" << RESET;
    Sleep(1000);
    if(colereSerge)
        quickTimeEvent();
}

// Fonction qui affiche que vous êtes dans la salle secrète
void enterSecret(){
    system("cls");
    cout << MAGENTA << "Bienvenue dans la salle secrete.\n" << RESET;
    Sleep(1000);
}

// Fonction qui vérifie si le joueur est sur une case spéciale où il faut afficher quelque chose
void findEvent() {
    string couleur = colors[posY][posX];
    if(couleur == BLUE)
        enterRoom();
    else if(couleur == YELLOW)
        enterTech();
    else if(couleur == MAGENTA)
        enterSecret();
}

// Fonction qui affiche le logo du jeu au début
void showLogo() {
    cout << GREEN;
    cout << "                     /$$       /$$                    \n";
            "                    | $$      |__/                    \n";
            "  /$$$$$$   /$$$$$$ | $$   /$$ /$$ /$$$$$$$  /$$$$$$$$\n";
            " /$$__  $$ /$$__  $$| $$  /$$/| $$| $$__  $$|____ /$$/\n";
            "| $$  \\ $$| $$$$$$$$| $$$$$$/ | $$| $$  \\ $$   /$$$$/ \n";
            "| $$  | $$| $$_____/| $$_  $$ | $$| $$  | $$  /$$__/  \n";
            "| $$$$$$$/|  $$$$$$$| $$ \\  $$| $$| $$  | $$ /$$$$$$$$\n";
            "| $$____/  \\_______/|__/  \\__/|__/|__/  |__/|________/\n";
            "| $$                                                  \n";
            "| $$                                                  \n";
            "|__/                                                  \n";

            "                                                            \n";
            "                                                            \n";
            " /$$   /$$  /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$$  /$$$$$$$\n";
            "|  $$ /$$/ /$$__  $$ /$$__  $$ /$$__  $$ /$$_____/ /$$_____/\n";
            " \\  $$$$/ | $$  \\ $$| $$  \\__/| $$$$$$$$|  $$$$$$ |  $$$$$$ \n";
            "  >$$  $$ | $$  | $$| $$      | $$_____/ \\____  $$ \\____  $$\n";
            " /$$/\\  $$| $$$$$$$/| $$      |  $$$$$$$ /$$$$$$$/ /$$$$$$$/\n";
            "|__/  \\__/| $$____/ |__/       \\_______/|_______/ |_______/ \n";
            "          | $$                                               \n";
            "          | $$                                               \n";
            "          |__/                                               \n";
    cout << RESET;
    Sleep(2500);
}

// Fonction qui affiche la mission du joueur
void showMission() {
    system("cls");
    cout << RED << "Bienvenue dans le jeu 'Pekinz xpress' !\n";
    cout << "L'equipe P-15 a perdu son robot, et c'est a vous de le retrouver.\n";
    cout << "Votre mission : explorer l'etage 3 de la faculte de genie pour localiser le robot\n";
    cout << "et le ramener a Serge, le technicien, avant qu'il ne soit trop tard.\n";
    cout << "Si le robot n'est pas retrouve, une facture de 650$ sera emise!\n";
    cout << "Bonne chance et que la mission commence !\n" << RESET;
    cout << endl << "Appuyer sur entree pour commencer: ";
    char c;

    do {
        c = _getch();
    } while (c != '\r');
}

// Fonction pour effacer la mémoire tampon de _getch(), car sinon les caractères s'accumulent
void clearBuffer() {
    while (_kbhit()) {
        _getch(); // Lire et ignorer les caractères dans le tampon
    }
}
