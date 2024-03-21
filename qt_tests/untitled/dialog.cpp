#include "dialog.h"
#include "ui_dialog.h"

// Source de l'icône de la fenêtre
// https://www.flaticon.com/free-icon/mission_1628441 Mission icons created by deemakdaksina - Flaticon

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonMain_clicked()
{
    Dialog::close();
}

void Dialog::showMission(int number)
{
    switch (number) {
    case 0:
        ui->label_text->setText("Impossible, ce robot n'est plus fonctionnel. Vous savez combien ça coûte?\n"
                                "1000$. Vous allez me devoir 1000$ s'il ne revient pas en état dans mes mains!\n"
                                "Vous êtes chanceux, les locaux environnants peuvent vous aider à le réparer. "
                                "Retournez en cours, bande de feignants.");
        break;
    case 1:
        ui->label_text->setText("Bravo. Vous avez terminé le procédural.\n"
                                "Maintenant que vous savez comparer des pommes avec des oranges, "
                                "vous pouvez vous rendre utile.\n"
                                "Allez trouver des résistances, il me semble que les DEL ont été grillées.");
        break;
    case 2:
        ui->label_text->setText("Bravo. Vous avez trouvé les résistances.\n"
                                "Maintenant, les DEL devraient tenir le coup. Il manque le code Arduino pour "
                                "les faire fonctionner.\n"
                                "Allez au local de programmation et espérez que l'ordi ne plante pas.");
        break;
    case 3:
        ui->label_text->setText("Bravo. Vous avez codé le programme.\n"
                                "J'espère que les ordis n'ont pas causé trop de problèmes. Voici un PCB vide.\n"
                                "Allez souder les composantes. Faites attention, plusieurs reviennent, "
                                "étourdis par la fumée dégagée.");
        break;
    case 4:
        ui->label_text->setText("Bravo. Vous avez fini de souder le PCB.\n"
                                "Il ne reste qu'à aller tester tout cela au laboratoire.\n"
                                "J'espère pour vous que ça va fonctionner, car 1000$, c'est assez cher.\n"
                                "Il ne faudrait pas se priver de 5 à 8 quand même.");
        break;
    case 5:
        ui->label_text->setText("Magnifique! Qui l'aurait cru, des étudiants de S1 capables de réparer le robot.\n"
                                "Grâce à vous, les visites au 5 à 8 de votre équipe vont pouvoir continuer.\n"
                                "Malheureusement, une autre équipe a aussi eu un problème de robot. "
                                "Si seulement ils ne l'avaient pas perdu...");
        break;
    default:
        break;
    }
}
