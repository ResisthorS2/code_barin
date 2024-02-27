#include <iostream>
#include <conio.h>
#include <windows.h>

#define NB_CASES 10
#define GRIDSIZE 20

using namespace std;

#define RESET   "\x1b[0m"
#define BLACK   "\x1b[30m"      /* Black */
#define RED     "\x1b[31m"      /* Red */
#define GREEN   "\x1b[32m"      /* Green */
#define YELLOW  "\x1b[33m"      /* Yellow */
#define BLUE    "\x1b[34m"      /* Blue */
#define MAGENTA "\x1b[35m"      /* Magenta */
#define CYAN    "\x1b[36m"      /* Cyan */
#define WHITE   "\x1b[37m"      /* White */

int posX = 2;
int posY = 8;
int playerX = 4;
int playerY = 16;

bool key = false;

// Utiliser les constantes pour définir le tableau de couleurs
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

// Fonction pour afficher la carte
void showMap() {
    system("cls");

    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            if ((i/2 == posY) && (j/2 == posX)) {
                cout << RESET << "00"; // Case vide au milieu
            } else {
                cout << colors[i/2][j/2] << "[]" << RESET; // Case
            }
        }
        cout << endl;
    }
}

bool verifyMovement(string couleur){
    system("cls");
    if(couleur == BLACK){
        cout << "Vous ne pouvez pas (encore) traverser les murs.";
        Sleep(500);
        return false;
    }
    else if(couleur == MAGENTA && key == false){
        cout << MAGENTA << "Vous n'avez pas les autorisations pour entrer ici.\n" << RESET;
        Sleep(1000);
        return false;
    }
    else
        return true;

}

void movePlayer(char c){
    switch (c) {
        case 'W':
            if (posY > 0) {
                if(verifyMovement(colors[posY-1][posX])) {
                    playerY -= 2; // Déplacement de deux cases vers le haut
                    posY--;
                }
            }
            break;
        case 'A':
            if (posX > 0) {
                if(verifyMovement(colors[posY][posX-1])) {
                    playerX -= 2; // Déplacement de deux cases vers la gauche
                    posX--;
                }
            }
            break;
        case 'S':
            if (posY < NB_CASES - 1) {
                if(verifyMovement(colors[posY+1][posX])) {
                    playerY += 2; // Déplacement de deux cases vers le bas
                    posY++;
                }
            }
            break;
        case 'D':
            if (posX < NB_CASES - 1) {
                if(verifyMovement(colors[posY][posX+1])) {
                    playerX += 2; // Déplacement de deux cases vers la droite
                    posX++;
                }
            }
            break;
        default:
            break;
    }
}

void enterRoom() {
    system("cls");
    cout << CYAN << "Vous etes dans la salle " << salles[posY][posX] << endl << RESET;
    Sleep(1000);
}

void enterTech() {
    system("cls");
    cout << YELLOW << "Vous etes dans le bureau des techniciens.\n" << RESET;
    Sleep(1000);
}

void enterSecret(){
    system("cls");
    cout << MAGENTA << "Bienvenue dans la salle secrete.\n" << RESET;
    Sleep(1000);
}

void findEvent() {
    string couleur = colors[posY][posX];
    if(couleur == BLUE)
        enterRoom();
    else if(couleur == YELLOW)
        enterTech();
    else if(couleur == MAGENTA)
        enterSecret();
}

void showLogo() {
    cout << GREEN;
    cout << "                     /$$       /$$                    \n";
    cout << "                    | $$      |__/                    \n";
    cout << "  /$$$$$$   /$$$$$$ | $$   /$$ /$$ /$$$$$$$  /$$$$$$$$\n";
    cout << " /$$__  $$ /$$__  $$| $$  /$$/| $$| $$__  $$|____ /$$/\n";
    cout << "| $$  \\ $$| $$$$$$$$| $$$$$$/ | $$| $$  \\ $$   /$$$$/ \n";
    cout << "| $$  | $$| $$_____/| $$_  $$ | $$| $$  | $$  /$$__/  \n";
    cout << "| $$$$$$$/|  $$$$$$$| $$ \\  $$| $$| $$  | $$ /$$$$$$$$\n";
    cout << "| $$____/  \\_______/|__/  \\__/|__/|__/  |__/|________/\n";
    cout << "| $$                                                  \n";
    cout << "| $$                                                  \n";
    cout << "|__/                                                  \n";

    cout << "                                                            \n";
    cout << "                                                            \n";
    cout << " /$$   /$$  /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$$  /$$$$$$$\n";
    cout << "|  $$ /$$/ /$$__  $$ /$$__  $$ /$$__  $$ /$$_____/ /$$_____/\n";
    cout << " \\  $$$$/ | $$  \\ $$| $$  \\__/| $$$$$$$$|  $$$$$$ |  $$$$$$ \n";
    cout << "  >$$  $$ | $$  | $$| $$      | $$_____/ \\____  $$ \\____  $$\n";
    cout << " /$$/\\  $$| $$$$$$$/| $$      |  $$$$$$$ /$$$$$$$/ /$$$$$$$/\n";
    cout << "|__/  \\__/| $$____/ |__/       \\_______/|_______/ |_______/ \n";
    cout << "          | $$                                               \n";
    cout << "          | $$                                               \n";
    cout << "          |__/                                               \n" << RESET;
    Sleep(2500);
}

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

int main() {
    showLogo();
    showMission();

    char move;

    while(true){
        showMap();

        cout << "Utilisez les touches WASD pour vous deplacer (Q pour quitter): ";
        move = toupper(_getch());

        if(move == 'Q')
            break;
        else{
            movePlayer(move);
            findEvent();
        }
        
    }

    system("cls");
    cout << "Merci d'avoir joue !" << endl;
    Sleep(1000);

    return 0;
}
