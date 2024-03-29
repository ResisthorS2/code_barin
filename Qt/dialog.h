#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void showMission(int number); // fonction pour afficher le no de mission

private slots:

    void on_pushButtonMain_clicked(); // fonction associée au bouton Main du Dialog (pour retourner à la main window)

private:
    Ui::Dialog *ui; // pointeur pour l'interface graphique du Dialog
};

#endif // DIALOG_H
