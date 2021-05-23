#include "endgameview.hpp"
#include "ui_endgameview.h"

EndGameView::EndGameView(int nbMonster, int nbTour, const QString &time, const STATE_GAME &val, const QString &name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndGameView)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->labelNumberMonsters->setText(QString::number(nbMonster));
    ui->labelNumberTurns->setText(QString::number(nbTour));
    int minutes = qFloor(time.toInt()/60);
    int secondes = time.toInt() - minutes * 60;
    ui->labelTime->setText(QString::number(minutes) + " minutes and " + QString::number(secondes )+ " seconds");


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &EndGameView::buttonhasClicked);

    layout()->addWidget(buttonBox);


    switch (val) {
        case STATE_GAME::END_1:
            ui->labelWhoWin->setText(name + " you win");
            break;
        case STATE_GAME::END_2:
            ui->labelWhoWin->setText(name + " you lose");
            break;
        default:
            break;
    }
}

EndGameView::~EndGameView()
{
    delete ui;
}

void EndGameView::buttonhasClicked()
{
   emit accepted();
   accept();
}
