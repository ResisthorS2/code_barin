#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // instanciation de l'app
    MainWindow w; // instanciation de la fenêtre principale
    w.show(); // affichage de la fenêtre principale
    Dialog d; // instanciation du Dialog de Serge
    d.setModal(true); // je mets le Dialog en modal (on ne peut donc plus cliquer sur les autres fenêtres tant qu'on ne ferme pas celle-ci)
    d.show(); // affichage du Dialog de Serge (je ne sais pas si vous voulez l'afficher dès le début du jeu comme ça)
    return a.exec(); // exécution de l'app
}
