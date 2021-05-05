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
ViewChoose::ViewChoose(Controller *controller, Start start, Choose choose, std::shared_ptr<Player> player ,QWidget *parent) :
  QDialog(parent), View(controller),
  ui(new Ui::ViewChoose), _Choose(choose), _Start(start), _Player(player),
  _ListPionAdd(new QVBoxLayout()), _MainLayout(new QHBoxLayout()),
  _RightLayout(new QVBoxLayout())
{
  ui->setupUi(this);

  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

  QLabel *lab = new QLabel(_Start.getName());
  lab->setAlignment(Qt::AlignCenter);
  _RightLayout->addWidget(lab);
  _RightLayout->addLayout(_ListPionAdd);
  _RightLayout->addWidget(ui->buttonBox);
  ui->buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(QString("background-color: #4CD80F;"));
  ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
  ui->buttonBox->button(QDialogButtonBox::Ok)->setShortcut(tr("Enter"));
  ui->buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet(QString("background-color: #D30014;"));
  ui->buttonBox->button(QDialogButtonBox::Cancel)->setShortcut(tr("CTRL+C"));

  QVector<QVBoxLayout*> _vecPions;

  for(auto pawn : choose.getListPions()){
       QVBoxLayout *BoxPawn = new QVBoxLayout();

       //Affiche le nom du monstre
       QFrame* line1 = new QFrame();
       line1->setFixedHeight(20);
       line1->setFrameShape(QFrame::VLine);
       QHBoxLayout *HBoxName = new QHBoxLayout();
       QLabel *LabelName = new QLabel(tr("Name : "));
       LabelName->setAlignment(Qt::AlignLeft);
       HBoxName->addWidget(LabelName);
       QLabel *LabelNameVal = new QLabel(pawn->getName());
       LabelNameVal->setAlignment(Qt::AlignLeft);
       HBoxName->addWidget(LabelNameVal);
       HBoxName->addWidget(line1);
       BoxPawn->addLayout(HBoxName);

       //Affiche la vie du monstre
       QFrame* line2 = new QFrame();
       line2->setFixedHeight(20);
       line2->setFrameShape(QFrame::VLine);
       QHBoxLayout *HBoxLife = new QHBoxLayout();
       QLabel *LabelLife = new QLabel(tr("Life : "));
       LabelLife->setAlignment(Qt::AlignLeft);
       HBoxLife->addWidget(LabelLife);
       QLabel *LabelLifeVal = new QLabel(QString::number(pawn->getLife()));
       LabelLifeVal->setAlignment(Qt::AlignLeft);
       HBoxLife->addWidget(LabelLifeVal);
       HBoxLife->addWidget(line2);
       BoxPawn->addLayout(HBoxLife);

       //Affiche la porté des attaques du monstre
       QFrame* line3 = new QFrame();
       line3->setFixedHeight(20);
       line3->setFrameShape(QFrame::VLine);
       QHBoxLayout *HBoxRange = new QHBoxLayout();
       QLabel *LabelRange = new QLabel(tr("Range : "));
       LabelRange->setAlignment(Qt::AlignLeft);
       HBoxRange->addWidget(LabelRange);
       QLabel *LabelRangeVal = new QLabel(QString::number(pawn->getMoveRadius()));
       LabelRangeVal->setAlignment(Qt::AlignLeft);
       HBoxRange->addWidget(LabelRangeVal);
       HBoxRange->addWidget(line3);
       BoxPawn->addLayout(HBoxRange);

       //Affiche l'attaque du monstre
       QFrame* line4 = new QFrame();
       line4->setFixedHeight(20);
       line4->setFrameShape(QFrame::VLine);
       QHBoxLayout *HBoxDomage = new QHBoxLayout();
       QLabel *LabelDomage = new QLabel(tr("Domage : "));
       LabelDomage->setAlignment(Qt::AlignLeft);
       HBoxDomage->addWidget(LabelDomage);
       QLabel *LabelDomageVal = new QLabel(QString::number(pawn->getAttack()));
       LabelDomageVal->setAlignment(Qt::AlignLeft);
       HBoxDomage->addWidget(LabelDomageVal);
       HBoxDomage->addWidget(line4);
       BoxPawn->addLayout(HBoxDomage);

       //Affiche la defense du monstre
       QFrame* line5 = new QFrame();
       line5->setFixedHeight(20);
       line5->setFrameShape(QFrame::VLine);
       QHBoxLayout *HBoxDefence = new QHBoxLayout();
       QLabel *LabelDefence = new QLabel(tr("Defence : "));
       LabelDefence->setAlignment(Qt::AlignLeft);
       HBoxDefence->addWidget(LabelDefence);
       QLabel *LabelDefenceVal = new QLabel(QString::number(pawn->getDefence()));
       LabelDefenceVal->setAlignment(Qt::AlignLeft);
       HBoxDefence->addWidget(LabelDefenceVal);
       HBoxDefence->addWidget(line5);
       BoxPawn->addLayout(HBoxDefence);

       //Affiche le bouton ajouter
       QPushButton *ButtonAdd = new QPushButton(tr("add"), this);
       ButtonAdd->setStyleSheet("background-color: #4CD80F");
       BoxPawn->addWidget(ButtonAdd);
       connect(ButtonAdd, &QPushButton::clicked, [this, pawn] {addPion(pawn->clone());});

       _vecPions.push_back(BoxPawn);
   }

  QGridLayout *PionsLayout = new QGridLayout();
  PionsLayout->setSpacing(0);

  int row = 0, col = 0;
  for(QVBoxLayout *VP: _vecPions) {
    PionsLayout->addLayout(VP, row, col);
    if(col==3){
        col = 0;
        row++;
    }
    else{
       col++;
    }
  }
  PionsLayout->setAlignment(Qt::AlignTop);
  _MainLayout->addLayout(PionsLayout);
  _MainLayout->addLayout(_RightLayout);

  setLayout(_MainLayout);

}

/**
 * @brief ViewChoose::addPion : Ajoute un monstre à ma liste et à mon visuel avec un bouton pour le supprimer de ma liste
 * @param p : Pointeur intelligent sur un Pawn
 */
void ViewChoose::addPion(std::shared_ptr<Pawn> p){

  if(_Player->getListPionsGame().count() < 4){
    //émets le signal pour ajouter le monstre de la liste
    emit UpdateListPionsGame(p);

    QHBoxLayout *Hlayout = new QHBoxLayout();
    Hlayout->addWidget(new QLabel(p->getName()));

    QPushButton *btn = new QPushButton("X", this);
    btn->setStyleSheet("background-color: #D30014");
    btn->setMaximumSize(30.0, 30.0);

    Hlayout->addWidget(btn);

    connect(btn, &QPushButton::clicked, [this, p] {delPionSignal(p);});
    connect(btn, &QPushButton::clicked, [this, Hlayout] {delPion(Hlayout);});

    this->_ListPionAdd->addLayout(Hlayout);

    if(_Player->getListPionsGame().count() == 4)
      ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
  }
  else {
     ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
  }

}

/**
 * @brief ViewChoose::delPionSignal : Supprime un Pawn de ma liste de pions
 * @param p : Pointeur intelligent sur un Pawn
 */
void ViewChoose::delPionSignal(std::shared_ptr<Pawn> p)
{
  //émets le signal pour supprimer le monstre de la liste
  emit UpdateListPionsGameDel(p);
}

/**
 * @brief ViewChoose::delPion : Supprime le visuel du monstre choisi
 * @param _layout
 */
void ViewChoose::delPion(QHBoxLayout *_layout){

  while(_layout->count() != 0){
      QLayoutItem* item = _layout->takeAt(0);
      delete item->widget();
      delete item;
  }
  delete _layout;

  //Mets le bouton Ok en désactiver
  ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

}

/**
 * @brief ViewChoose::setPlayer : Mets à jour l'attribue _Player
 * @param player : Objet player
 */
void ViewChoose::setPlayer(std::shared_ptr<Player> player)
{
  this->_Player = std::move(player);
}

/**
 * @brief ViewChoose::~ViewChoose : Destructeur
 */
ViewChoose::~ViewChoose()
{
  delete ui;
}
