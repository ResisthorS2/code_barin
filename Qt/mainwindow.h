#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include "dialog.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTimer;
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // fonctions associées aux boutons dans la fenêtre principale
    void on_pushButtonLeft_clicked();

    void on_pushButtonRight_clicked();

    void on_pushButtonUp_clicked();

    void on_pushButtonDown_clicked();

    void on_pushButtonQuit_clicked();

    void on_pushButtonDialog_clicked();

    // fonctions du port série
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);
    void handleBytesWritten(qint64 bytes);
    void handleWriteTimeout();

private:
    Ui::MainWindow *ui; // pointeur pour l'interface de la fenêtre principale
    Dialog *dialog; // pointeur pour le Dialog de Serge

    void showWriteError(const QString &message);

    qint64 m_bytesToWrite = 0;
    QTimer *m_timer = nullptr;
    QSerialPort *m_serial = nullptr; // objet pour le port série (initialisé dans le constructeur)

};
#endif // MAINWINDOW_H
