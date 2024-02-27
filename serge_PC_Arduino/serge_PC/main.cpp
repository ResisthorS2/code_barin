/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Février 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
 * Modif : Février 2024, Mohammad Barin Wahidi
*/

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

/*-------------------------- Librairies externes ----------------------------*/
#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
#include "include/serge.hpp"
using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 9600           // Fréquence de transmission sérielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message

/*------------------------- Prototypes de fonctions -------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg);
bool RcvFromSerial(SerialPort *arduino, string &msg);


/*---------------------------- Variables globales ---------------------------*/
SerialPort * arduino; //doit être un objet global!

/*----------------------------- Fonction "Main" -----------------------------*/
int main(){
    // Demandez à l'utilisateur s'il veut utiliser l'Arduino
    char choix;
    cout << "Voulez-vous utiliser l'Arduino ? Appuyez sur O pour oui, N pour non : ";
    choix = toupper(_getch());

    string raw_msg;
    json j_msg_send, j_msg_rcv; // Structure de données JSON pour envoi et réception

    if(choix == 'O')
    {
        // Initialisation du port de communication
        string com = "COM3";
        arduino = new SerialPort(com.c_str(), BAUD);
        
        if(!arduino->isConnected()){
            cerr << "Impossible de se connecter au port "<< string(com) <<". Fermeture du programme!" <<endl;
            exit(1);
        }
    }

    // Affichage en début de partie
    /*showLogo();
    showMission();*/

    char move = ' ';    // caractère pour le mouvement au clavier (PC)
    char bouton = ' ';  // caractère pour le mouvement par la manette (Arduino)
    bool moved = true;  // booléen pour vérifier si le joueur a bougé

    while(game){
        
        if(moved){  // si le joueur a bougé, on affiche la carte
            showMap();
        }
        
        // Utilisez _kbhit() pour vérifier si une touche a été enfoncée
        if (_kbhit()) {
            clearBuffer();
            move = toupper(_getch());
        }

        if(choix == 'O')
        {
            if(!RcvFromSerial(arduino, raw_msg)){
                cerr << "Erreur lors de la reception du message. " << endl;
            }
            
            // Impression du message de l'Arduino si valide
            if(raw_msg.size()>0){
                try
                {
                    j_msg_rcv = json::parse(raw_msg);
                    bouton  = j_msg_rcv["bouton"].get<char>(); // on va chercher le bouton appuyé sous forme de char
                }
                catch(const exception& e){}
            }
        }

        if(move == 'Q' || bouton == 'Q') // si le bouton Q a été appuyé, ça quitte le jeu
            break;
        else{   // sinon, on essaie de déplacer le joueur
            moved = movePlayer(&move, &bouton);
            if(moved)   // si le joueur a bougé, on affiche l'évènement selon la case où il se trouve
                findEvent();
        }
        Sleep(100); // délai pour que la communication sérielle marche (vous pouvez changer la durée)
    }

    system("cls");  // effacer l'écran
    cout << "Merci d'avoir joue !" << endl;
    Sleep(1000);    // afficher le message de fin pendant 1 seconde

    return 0;
}


/*---------------------------Definition de fonctions ------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg){
    // Return 0 if error
    string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


bool RcvFromSerial(SerialPort *arduino, string &msg){
    // Return 0 if error
    // Message output in msg
    string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)

    // Version fonctionnel dans VScode, mais non fonctionnel avec Visual Studio
/*  
    while(msg.back()!='\n'){
        if(msg.size()>MSG_MAX_SIZE){
            return false;
        }

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);
    }
*/

    // Version fonctionnelle dans VScode et Visual Studio
    buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    str_buffer.assign(char_buffer, buffer_size);
    msg.append(str_buffer);

    //msg.pop_back(); //remove '/n' from string

    return true;
}
