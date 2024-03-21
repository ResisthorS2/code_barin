#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QTimer>

#include <QJsonDocument>
#include <QJsonObject>

#include <chrono>

static constexpr std::chrono::seconds kWriteTimeout = std::chrono::seconds{5};

#define NB_CASES 10

// Source de l'icône de la fenêtre
// https://www.flaticon.com/free-icon/map_3082383 Location icons created by Yogi Aprelliyanto - Flaticon

int posY = 7;
int posX = 3;
char orientation = 'n';
int noMission = 0;

QString repertoire = ":/images_ecole/";
QString extension = ".png";

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

void reverseOrientation();
bool verifyMovement(int x, int y);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timer(new QTimer(this))
    , m_serial(new QSerialPort(this))
{
    ui->setupUi(this);

    //QPixmap pix(":/images_ecole/tech_desk.png");

    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::handleWriteTimeout);
    m_timer->setSingleShot(true);

    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_serial, &QSerialPort::bytesWritten, this, &MainWindow::handleBytesWritten);
    //connect(m_console, &Console::getData, this, &MainWindow::writeData);

    openSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLeft_clicked()
{
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
    if(verifyMovement(newPosX, newPosY))
    {
        posX = newPosX;
        posY = newPosY;
        orientation = newOrientation;
    }

    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButtonRight_clicked()
{
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
    if(verifyMovement(newPosX, newPosY))
    {
        posX = newPosX;
        posY = newPosY;
        orientation = newOrientation;
    }

    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButtonUp_clicked()
{
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

    int salle = rooms[newPosY][newPosX];
    if(salle == 2)
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
        if(verifyMovement(newPosX, newPosY))
        {
            posX = newPosX;
            posY = newPosY;
        }
    }
    else if(salle != 0 && salle < 3000)
    {
        posX = newPosX;
        posY = newPosY;
    }


    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButtonDown_clicked()
{
    reverseOrientation();

    QString image = QString::number(posY) + QString::number(posX) + orientation;
    QPixmap pix(repertoire+image+extension);
    qDebug() << image;
    ui->label->setPixmap(pix.scaled(800, 400, Qt::KeepAspectRatio));
}

void reverseOrientation()
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

bool verifyMovement(int x, int y)
{
    int salle = rooms[y][x];
    if(salle == 0)
    {
        return false;
    }
    else if(salle == 2)
    {
        return false;
    }
    else if(salle > 3000)
    {
        return false;
    }
    else
        return true;
}

void MainWindow::on_pushButtonQuit_clicked()
{
    qApp->quit();
}

void MainWindow::on_pushButtonDialog_clicked()
{
    dialog = new Dialog(this);
    dialog->setModal(true);
    dialog->show();
    dialog->showMission(noMission);
    noMission++;
}

void MainWindow::openSerialPort()
{
    m_serial->setPortName("COM3");
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite))
        qDebug() << "merci";
    else
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
}

void MainWindow::writeData(const QByteArray &data)
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

void MainWindow::readData()
{
    if(m_serial->canReadLine())
    {
        const QByteArray data = m_serial->readAll();

        qDebug() << data;

        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &error);

        // Vérification s'il y a une erreur d'analyse JSON
        if (error.error == QJsonParseError::NoError) {
            // Extraction du bouton appuyé s'il est présent dans l'objet JSON
            QJsonObject jsonObject = jsonDocument.object();
            if (jsonObject.contains("bouton")) {
                QJsonValue boutonValue = jsonObject.value("bouton");

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

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::handleBytesWritten(qint64 bytes)
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

void MainWindow::showWriteError(const QString &message)
{
    QMessageBox::warning(this, tr("Warning"), message);
}
