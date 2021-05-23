#include "viewchoose.hpp"
#include "ui_viewchoose.h"

/**
 * @brief ViewChoose::ViewChoose : Instancie la vue ViewChoose en affichant tous les monstres qui existent avec leurs caractéristiques
 * @param controller : Objet controller
 * @param start : Objet start
 * @param choose : Objet choose
 * @param player : Objet player
 * @param parent : Objet QWidget
 */
ViewChoose::ViewChoose(Controller * controller, Start start, Choose choose, std::shared_ptr<Player> player, QWidget *parent)
    : QDialog(parent), View(controller),
      ui(new Ui::ViewChoose),
      _choose(choose),
      _start(start),
      _player(player),
      _listPionAdd(new QVBoxLayout()),
      _mainLayout(new QHBoxLayout()),
      _rightLayout(new QVBoxLayout())
{

    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QLabel * lab = new QLabel(_start.getName());

    lab->setAlignment(Qt::AlignCenter);

    _rightLayout->addWidget(lab);
    _rightLayout->addLayout(_listPionAdd);
    _rightLayout->addWidget(ui->buttonBox);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(QString("background-color: #4CD80F;"));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setShortcut(tr("Enter"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet(QString("background-color: #D30014;"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setShortcut(tr("CTRL+C"));

    QVector<QVBoxLayout *> _vecPions;

    for(auto pawn : choose.getListPions()){

        QVBoxLayout * boxPawn = new QVBoxLayout();

        //Affiche le nom du monstre
        QFrame * line1 = new QFrame();
        QHBoxLayout * hBoxName = new QHBoxLayout();
        QLabel * labelName = new QLabel(tr("Name : "));
        QLabel * labelNameVal = new QLabel(pawn->getName());

        line1->setFixedHeight(20);
        line1->setFrameShape(QFrame::VLine);
        labelName->setAlignment(Qt::AlignLeft);
        hBoxName->addWidget(labelName);
        labelNameVal->setAlignment(Qt::AlignLeft);
        hBoxName->addWidget(labelNameVal);
        hBoxName->addWidget(line1);
        boxPawn->addLayout(hBoxName);

        //Affiche la vie du monstre
        QFrame * line2 = new QFrame();
        QHBoxLayout * hBoxLife = new QHBoxLayout();
        QLabel * labelLife = new QLabel(tr("Life : "));
        QLabel * labelLifeVal = new QLabel(QString::number(pawn->getLife()));

        line2->setFixedHeight(20);
        line2->setFrameShape(QFrame::VLine);
        labelLife->setAlignment(Qt::AlignLeft);
        hBoxLife->addWidget(labelLife);
        labelLifeVal->setAlignment(Qt::AlignLeft);
        hBoxLife->addWidget(labelLifeVal);
        hBoxLife->addWidget(line2);
        boxPawn->addLayout(hBoxLife);

        //Affiche la porté des attaques du monstre
        QFrame * line3 = new QFrame();
        QHBoxLayout * hBoxRange = new QHBoxLayout();
        QLabel * labelRange = new QLabel(tr("Range : "));
        QLabel * labelRangeVal = new QLabel(QString::number(pawn->getMoveRadius()));

        line3->setFixedHeight(20);
        line3->setFrameShape(QFrame::VLine);
        labelRange->setAlignment(Qt::AlignLeft);
        hBoxRange->addWidget(labelRange);
        labelRangeVal->setAlignment(Qt::AlignLeft);
        hBoxRange->addWidget(labelRangeVal);
        hBoxRange->addWidget(line3);
        boxPawn->addLayout(hBoxRange);

        //Affiche l'attaque du monstre
        QFrame * line4 = new QFrame();
        QHBoxLayout * hBoxDomage = new QHBoxLayout();
        QLabel * labelDomage = new QLabel(tr("Damages : "));
        QLabel * labelDomageVal = new QLabel(QString::number(pawn->getAttack()));

        line4->setFixedHeight(20);
        line4->setFrameShape(QFrame::VLine);
        labelDomage->setAlignment(Qt::AlignLeft);
        hBoxDomage->addWidget(labelDomage);
        labelDomageVal->setAlignment(Qt::AlignLeft);
        hBoxDomage->addWidget(labelDomageVal);
        hBoxDomage->addWidget(line4);
        boxPawn->addLayout(hBoxDomage);

        //Affiche la defense du monstre
        QFrame * line5 = new QFrame();
        QHBoxLayout *hBoxDefence = new QHBoxLayout();
        QLabel *labelDefence = new QLabel(tr("Defence : "));
        QLabel *labelDefenceVal = new QLabel(QString::number(pawn->getDefence()));

        line5->setFixedHeight(20);
        line5->setFrameShape(QFrame::VLine);
        labelDefence->setAlignment(Qt::AlignLeft);
        hBoxDefence->addWidget(labelDefence);
        labelDefenceVal->setAlignment(Qt::AlignLeft);
        hBoxDefence->addWidget(labelDefenceVal);
        hBoxDefence->addWidget(line5);
        boxPawn->addLayout(hBoxDefence);

        //Affiche le bouton ajouter
        QPushButton * buttonAdd = new QPushButton(tr("add"), this);

        buttonAdd->setStyleSheet("background-color: #4CD80F");
        boxPawn->addWidget(buttonAdd);
        connect(buttonAdd, &QPushButton::clicked, [this, pawn] {addPion(pawn->clone());});

        _vecPions.push_back(boxPawn);
    }

    QGridLayout * pionsLayout = new QGridLayout();
    pionsLayout->setSpacing(0);

    int row = 0, col = 0;
    for(QVBoxLayout * vp : _vecPions) {
        pionsLayout->addLayout(vp, row, col);
        if(col==3){
            col = 0;
            row++;
        }
        else
            col++;
    }

    pionsLayout->setAlignment(Qt::AlignTop);
    _mainLayout->addLayout(pionsLayout);
    _mainLayout->addLayout(_rightLayout);

    setLayout(_mainLayout);

}

/**
 * @brief ViewChoose::addPion : Ajoute un monstre à ma liste et à mon visuel avec un bouton pour le supprimer de ma liste
 * @param p : Pointeur intelligent sur un Pawn
 */
void ViewChoose::addPion(std::shared_ptr<Pawn> p){

    if(_player->getListPionsGame().count() < 4){
        //émets le signal pour ajouter le monstre de la liste
        emit updateListPionsGame(p);

        QHBoxLayout * hLayout = new QHBoxLayout();
        hLayout->addWidget(new QLabel(p->getName()));

        QPushButton * btn = new QPushButton("X", this);
        btn->setStyleSheet("background-color: #D30014");
        btn->setMaximumSize(30.0, 30.0);

        hLayout->addWidget(btn);

        connect(btn, &QPushButton::clicked, [this, p] {delPionSignal(p);});
        connect(btn, &QPushButton::clicked, [this, hLayout] {delPion(hLayout);});

        this->_listPionAdd->addLayout(hLayout);

        if(_player->getListPionsGame().count() == 4)
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

}

/**
 * @brief ViewChoose::delPionSignal : Supprime un Pawn de ma liste de pions
 * @param p : Pointeur intelligent sur un Pawn
 */
void ViewChoose::delPionSignal(std::shared_ptr<Pawn> p)
{
    //émets le signal pour supprimer le monstre de la liste
    emit updateListPionsGameDel(p);
}

/**
 * @brief ViewChoose::delPion : Supprime le visuel du monstre choisi
 * @param _layout
 */
void ViewChoose::delPion(QHBoxLayout * _layout){

    while(_layout->count() != 0){
        QLayoutItem * item = _layout->takeAt(0);
        delete item->widget();
        delete item;
    }
    delete _layout;

    //Mets le bouton Ok en désactiver
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

}

/**
 * @brief ViewChoose::setPlayer : Mets à jour l'attribue _player
 * @param player : Objet player
 */
void ViewChoose::setPlayer(std::shared_ptr<Player> player)
{
    this->_player = std::move(player);
}

/**
 * @brief ViewChoose::~ViewChoose : Destructeur
 */
ViewChoose::~ViewChoose()
{
    delete ui;
}
