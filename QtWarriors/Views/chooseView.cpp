#include "chooseView.hpp"
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
      _addedPawns(new QVBoxLayout()),
      _mainLayout(new QHBoxLayout()),
      _rightLayout(new QVBoxLayout())
{

    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QLabel * lab = new QLabel(_start.getName());

    lab->setAlignment(Qt::AlignCenter);

    _rightLayout->addWidget(lab);
    _rightLayout->addLayout(_addedPawns);
    _rightLayout->addWidget(ui->buttonBox);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(QString("background-color: #4CD80F;"));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setShortcut(tr("Enter"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet(QString("background-color: #D30014;"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setShortcut(tr("CTRL+C"));

    QVector<QVBoxLayout *> _vecPions;

    for(auto pawn : choose.getListPawns()){

        QVBoxLayout * boxPawn = new QVBoxLayout();

        //Affiche le nom du monstre
        QHBoxLayout * hBoxName = new QHBoxLayout();
        QLabel * labelName = new QLabel(tr("Name : "));   
        QLabel * labelNameVal = new QLabel(pawn->getName());

        labelNameVal->setStyleSheet("font-weight: normal;");
        labelName->setAlignment(Qt::AlignLeft);
        hBoxName->addWidget(labelName);
        labelNameVal->setAlignment(Qt::AlignLeft);
        hBoxName->addWidget(labelNameVal);
        boxPawn->addLayout(hBoxName);


        //Affiche la vie du monstre
        QHBoxLayout * hBoxLife = new QHBoxLayout();
        QLabel * labelLife = new QLabel(tr("Life : "));
        QLabel * labelLifeVal = new QLabel(QString::number(pawn->getLife()));

        labelLifeVal->setStyleSheet("font-weight: normal;");
        labelLife->setAlignment(Qt::AlignLeft);
        hBoxLife->addWidget(labelLife);
        labelLifeVal->setAlignment(Qt::AlignLeft);
        hBoxLife->addWidget(labelLifeVal);
        boxPawn->addLayout(hBoxLife);

        //Affiche la porté des attaques du monstre
        QHBoxLayout * hBoxRange = new QHBoxLayout();
        QLabel * labelRange = new QLabel(tr("Range : "));
        QLabel * labelRangeVal = new QLabel(QString::number(pawn->getMoveRadius()));

        labelRangeVal->setStyleSheet("font-weight: normal;");
        labelRange->setAlignment(Qt::AlignLeft);
        hBoxRange->addWidget(labelRange);
        labelRangeVal->setAlignment(Qt::AlignLeft);
        hBoxRange->addWidget(labelRangeVal);
        boxPawn->addLayout(hBoxRange);

        //Affiche l'attaque du monstre
        QHBoxLayout * hBoxDomage = new QHBoxLayout();
        QLabel * labelDomage = new QLabel(tr("Damages : "));
        QLabel * labelDomageVal = new QLabel(QString::number(pawn->getAttack()));

        labelDomageVal->setStyleSheet("font-weight: normal;");
        labelDomage->setAlignment(Qt::AlignLeft);
        hBoxDomage->addWidget(labelDomage);
        labelDomageVal->setAlignment(Qt::AlignLeft);
        hBoxDomage->addWidget(labelDomageVal);
        boxPawn->addLayout(hBoxDomage);

        //Affiche la defense du monstre
        QHBoxLayout *hBoxDefence = new QHBoxLayout();
        QLabel *labelDefence = new QLabel(tr("Defence : "));
        QLabel *labelDefenceVal = new QLabel(QString::number(pawn->getDefence()));

        labelDefenceVal->setStyleSheet("font-weight: normal;");
        labelDefence->setAlignment(Qt::AlignLeft);
        hBoxDefence->addWidget(labelDefence);
        labelDefenceVal->setAlignment(Qt::AlignLeft);
        hBoxDefence->addWidget(labelDefenceVal);
        boxPawn->addLayout(hBoxDefence);

        //Fenêtre OpenGL
        QHBoxLayout *layoutGL = new QHBoxLayout();
        _gl = new ChooseGL(pawn->get3DPawn(), this);
        _gl->setMinimumSize(200, 200);
        layoutGL->addWidget(_gl);
        boxPawn->addLayout(layoutGL);

        //Affiche le bouton ajouter
        QHBoxLayout *HboxBtn = new QHBoxLayout();
        QPushButton * buttonAdd = new QPushButton(tr("Add"), this);

        buttonAdd->setStyleSheet("background-color: #4CD80F; color : black; font-weight: normal;");
        HboxBtn->addWidget(buttonAdd);
        boxPawn->addLayout(HboxBtn);
        connect(buttonAdd, &QPushButton::clicked, [this, pawn] {addPawn(pawn->clone());});

        _vecPions.push_back(boxPawn);

        QVBoxLayout * box = new QVBoxLayout();
        QFrame * line7 = new QFrame();

        line7->setFixedHeight(325);
        line7->setFrameShape(QFrame::VLine);
        line7->setStyleSheet("color : black;");
        box->setMargin(5);
        box->addWidget(line7);
        _vecPions.push_back(box);
    }

    QGridLayout * pionsLayout = new QGridLayout();
    pionsLayout->setSpacing(0);

    int row = 0, col = 0;
    for(QVBoxLayout * vp : _vecPions) {
        pionsLayout->addLayout(vp, row, col);
        if(col==7){
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
 * @brief ViewChoose::addPawn : Ajoute un monstre à ma liste et à mon visuel avec un bouton pour le supprimer de ma liste
 * @param p : Pointeur intelligent sur un Pawn
 */
void ViewChoose::addPawn(std::shared_ptr<Pawn> p){

    if(_player->getPawns().count() < 4){
        //émets le signal pour ajouter le monstre de la liste
        emit updatePawns(p);

        QHBoxLayout * hLayout = new QHBoxLayout();
        QLabel *labelName = new QLabel(p->getName());
        labelName->setStyleSheet("font-weight: normal;");
        hLayout->addWidget(labelName);

        QPushButton * btn = new QPushButton("X", this);
        btn->setStyleSheet("background-color: #D30014; color: black; font-weight: normal;");
        btn->setMaximumSize(30.0, 30.0);

        hLayout->addWidget(btn);

        connect(btn, &QPushButton::clicked, [this, p] {delPawnSignal(p);});
        connect(btn, &QPushButton::clicked, [this, hLayout] {delPawn(hLayout);});

        this->_addedPawns->addLayout(hLayout);

        if(_player->getPawns().count() == 4)
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

}

/**
 * @brief ViewChoose::delPawnSignal : Supprime un Pawn de ma liste de pions
 * @param p : Pointeur intelligent sur un Pawn
 */
void ViewChoose::delPawnSignal(std::shared_ptr<Pawn> p)
{
    //émets le signal pour supprimer le monstre de la liste
    emit updateDeletedPawns(p);
}

/**
 * @brief ViewChoose::delPawn : Supprime le visuel du monstre choisi
 * @param _layout
 */
void ViewChoose::delPawn(QHBoxLayout * _layout){

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
    delete _gl;
}
