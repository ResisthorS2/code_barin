#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QTimer>

#include <QJsonDocument>
#include <QJsonObject>

#include <chrono>

static constexpr std::chrono::seconds kWriteTimeout = std::chrono::seconds{5};

#define NB_CASES 10 // la map fait 10 cases de long et de haut

// Source de l'icône de la fenêtre
// https://www.flaticon.com/free-icon/map_3082383 Location icons created by Yogi Aprelliyanto - Flaticon

// variables pour la positions, l'orientation et la mission du joueur
int posY = 7;
int posX = 3;
char orientation = 'n';
int noMission = 0;

QString repertoire = ":/images_ecole/"; // comme j'ai ajouté les images à resources.qrc, je peux accéder aux images avec ce path
QString extension = ".png";

// tableau des salles dans le jeu (0=mur, 1=couloir, 2=intersection, 30xx=local)
int rooms[NB_CASES][NB_CASES] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 1, 1, 2, 0, 0, 0},
    {0, 0, 3041, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 3022, 1, 3019, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 3018, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 3016, 0, 0},
    {0, 1, 1, 2, 1, 1, 2, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void reverseOrientation(); // prototype de la fonction pour inverser l'orientation (bouton down)
bool verifyMovement(int x, int y); // prototype de la fonction qui vérifie la validité du mouvement

MainWindow::MainWindow(QWidget *parent) // constructeur de la fenêtre principale
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timer(new QTimer(this))
    , m_serial(new QSerialPort(this))
{
    ui->setupUi(this);

    //QPixmap pix(":/images_ecole/tech_desk.png");

    // Ajout de l'image de la position de départ au label dans la fenêtre (oui, on peut mettre une image dans un label)
    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image; // qDebug(), c'est comme le cout de Qt (cout marche aussi, mais il faut inclure les libs)
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));

    // connexion des signaux d'erreurs aux fonctions associées
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::handleWriteTimeout);
    m_timer->setSingleShot(true);

    // connexion des signaux du port série aux fonctions associées
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_serial, &QSerialPort::bytesWritten, this, &MainWindow::handleBytesWritten);
    //connect(m_console, &Console::getData, this, &MainWindow::writeData);

    openSerialPort(); // ouverture du port série par la fenêtre principale
}

MainWindow::~MainWindow() // destructeur de la fenêtre principale
{
    delete ui;
}

void MainWindow::on_pushButtonLeft_clicked() // fonction appelée lorsqu'on appuie sur le bouton gauche
{
    // variables new pour vérifier si le mouvement de l'usager est valide sans changer sa position
    int newPosX = posX;
    int newPosY = posY;
    char newOrientation = orientation;
    switch (orientation) {
    case 'n':
        newPosY--;
        newPosX--;
        newOrientation = 'w';
        break;
    case 's':
        newPosY++;
        newPosX++;
        newOrientation = 'e';
        break;
    case 'e':
        newPosX++;
        newPosY--;
        newOrientation = 'n';
        break;
    case 'w':
        newPosX--;
        newPosY++;
        newOrientation = 's';
        break;
    default:
        break;
    }
    if(verifyMovement(newPosX, newPosY)) // si le mouvement est valide, on met les nouvelles valeurs
    {
        posX = newPosX;
        posY = newPosY;
        orientation = newOrientation;
    }

    // on change l'image du label selon la position du joueur (les images sont nommées xyorientation.png, ie. 73s)
    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButtonRight_clicked() // fonction appelée lorsqu'on appuie sur le bouton droit
{
    // variables new pour vérifier si le mouvement de l'usager est valide sans changer sa position
    int newPosX = posX;
    int newPosY = posY;
    char newOrientation = orientation;
    switch (orientation) {
    case 'n':
        newPosY--;
        newPosX++;
        newOrientation = 'e';
        break;
    case 's':
        newPosY++;
        newPosX--;
        newOrientation = 'w';
        break;
    case 'e':
        newPosX++;
        newPosY++;
        newOrientation = 's';
        break;
    case 'w':
        newPosX--;
        newPosY--;
        newOrientation = 'n';
        break;
    default:
        break;
    }
    if(verifyMovement(newPosX, newPosY)) // si le mouvement est valide, on met les nouvelles valeurs
    {
        posX = newPosX;
        posY = newPosY;
        orientation = newOrientation;
    }

    // on change l'image du label selon la position du joueur
    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButtonUp_clicked() // fonction appelée lorsqu'on appuie sur le bouton haut
{
    // variables new pour vérifier si le mouvement de l'usager est valide sans changer sa position
    int newPosX = posX;
    int newPosY = posY;
    switch (orientation) {
    case 'n':
        newPosY--;
        break;
    case 's':
        newPosY++;
        break;
    case 'e':
        newPosX++;
        break;
    case 'w':
        newPosX--;
        break;
    default:
        break;
    }

    int salle = rooms[newPosY][newPosX]; // variable pour vérifier la case désirée par le joueur
    if(salle == 2) // s'il y a une intersection devant le joueur, il peut sauter par dessus
    {
        switch (orientation) {
        case 'n':
            newPosY--;
            break;
        case 's':
            newPosY++;
            break;
        case 'e':
            newPosX++;
            break;
        case 'w':
            newPosX--;
            break;
        default:
            break;
        }
        if(verifyMovement(newPosX, newPosY)) // si le mouvement est valide, on met les nouvelles valeurs
        {
            posX = newPosX;
            posY = newPosY;
        }
    }
    else if(salle != 0 && salle < 3000) // si ce n'est pas une intersection devant et pas un local (donc couloir), on met les nouvelles valeurs
    {
        posX = newPosX;
        posY = newPosY;
    }

    // on change l'image du label selon la position du joueur
    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButtonDown_clicked() // fonction appelée lorsqu'on appuie sur le bouton haut
{
    reverseOrientation(); // inverse l'orientation du joueur

    // on change l'image du label selon la position du joueur
    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void reverseOrientation() // fonction pour inverser l'orientation du joueur
{
    switch (orientation) {
    case 'n':
        orientation = 's';
        break;
    case 's':
        orientation = 'n';
        break;
    case 'e':
        orientation = 'w';
        break;
    case 'w':
        orientation = 'e';
        break;
    default:
        break;
    }
}

bool verifyMovement(int x, int y) // fonction pour vérifier la validité du mouvement du joueur
{
    int salle = rooms[y][x]; // on va chercher la case où le joueur va se trouver dans le tableau rooms
    if(salle == 0) // si le joueur essaie de rentrer dans un mur, on retourne false
    {
        return false;
    }
    else if(salle == 2) // si le joueur essaie de rentrer dans une intersection, on retourne false
    {
        return false;
    }
    else if(salle > 3000) // à changer, si le joueur entre dans un local (je n'ai pas ajouté les mini-jeux)
    {
        return false;
    }
    else // sinon, (couloir), on retourne true
        return true;
}

void MainWindow::on_pushButtonQuit_clicked() // si le joueur apppuie sur le bouton Quit, ça ferme l'app
{
    qApp->quit();
}

void MainWindow::on_pushButtonDialog_clicked() // si le joueur appuie sur le bouton Dialog, ça ouvre les dialogues de Serge (C'est pour du debug)
{
    dialog = new Dialog(this); // on crée un nouveau Dialog
    dialog->setModal(true); // on la met en mode tu ne peux pas cliquer sur les autres fenêtres (genre la map)
    dialog->show(); // on affiche le Dialog
    dialog->showMission(noMission); // on appelle la fonction pour afficher le texte de Serge selon la mission du joueur
    noMission++; // pour le debug, j'incrémente le numéro de mission à chaque appui du bouton Dialog (normalement, ce serait après un mini-jeu)
}

void MainWindow::openSerialPort() // fonction pour ouvrir le port série (inspiré des exemples de Qt 6.6.2 dans Qt Creator)
{
    m_serial->setPortName("COM3"); // le numéro du port est COM3 dans mon cas
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) // ouvre le port série
        qDebug() << "merci";
    else
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
}

void MainWindow::closeSerialPort() // fonction pour fermer le port série
{
    if (m_serial->isOpen())
        m_serial->close();
}

void MainWindow::writeData(const QByteArray &data) // fonction pour écrire des données sur le port série (j'ai pas testé)
{
    const qint64 written = m_serial->write(data);
    if (written == data.size()) {
        m_bytesToWrite += written;
        m_timer->start(kWriteTimeout);
    } else {
        const QString error = tr("Failed to write all data to port %1.\n"
                                 "Error: %2").arg(m_serial->portName(),
                                       m_serial->errorString());
        showWriteError(error);
    }
}

void MainWindow::readData() // fonction pour lire le port série
{
    if(m_serial->canReadLine()) // si le message reçu possède un "\n"
    {
        const QByteArray data = m_serial->readAll(); // on lit le port série

        qDebug() << data; // on l'affiche pour vérifier

        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &error); // on crée un doc json

        // Vérification s'il y a une erreur d'analyse JSON
        if (error.error == QJsonParseError::NoError) {
            QJsonObject jsonObject = jsonDocument.object();
            // Extraction du bouton appuyé s'il est présent dans l'objet JSON
            if (jsonObject.contains("bouton"))
            {
                QJsonValue boutonValue = jsonObject.value("bouton");

                // selon le bouton appuyé, j'appelle une fonction du main (oui, on peut appeler des fonctions associées à des objets)
                if(boutonValue == "Q")
                    on_pushButtonQuit_clicked();
                else if(boutonValue == "W")
                    on_pushButtonUp_clicked();
                else if(boutonValue == "A")
                    on_pushButtonLeft_clicked();
                else if(boutonValue == "S")
                    on_pushButtonDown_clicked();
                else if(boutonValue == "D")
                    on_pushButtonRight_clicked();
            }
        }
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error) // fonction s'il y a une erreur sérielle
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::handleBytesWritten(qint64 bytes) // fonction qui s'occupe des messages à écrire sur le port série
{
    m_bytesToWrite -= bytes;
    if (m_bytesToWrite == 0)
        m_timer->stop();
}

void MainWindow::handleWriteTimeout()
{
    const QString error = tr("Write operation timed out for port %1.\n"
                             "Error: %2").arg(m_serial->portName(),
                                   m_serial->errorString());
    showWriteError(error);
}

void MainWindow::showWriteError(const QString &message) // fonction qui montre les messages d'erreur d'écriture sérielle
{
    QMessageBox::warning(this, tr("Warning"), message);
}
