#include "viewgame.hpp"
#include "ui_viewgame.h"
#include "Controllers/controller.hpp"
#include <iostream>

/**
 * @brief ViewGame::ViewGame : Instancie une vue ViewGame qui affiche la partie
 * @param controller : Objet Controller
 * @param player : Objet Player
 * @param playerEnemy : Objet Player
 * @param game : Objet Game
 * @param parent : Objet QWidget
 */
ViewGame::ViewGame(Controller *controller, std::shared_ptr<Player> player,  std::shared_ptr<Player> playerEnemy, Game game, QWidget *parent) :
  QDialog(parent), View (controller),
  ui(new Ui::ViewGame),
  _Player(player), _PlayerEnemy(playerEnemy), _Game(game), _PawnChoose(0), _IsSelected(false), _AllIsPositioned(false), _X(10), _Y(10),
  _play(false)
{
  ui->setupUi(this);
  setWindowState(Qt::WindowFullScreen);

  UpdateDetailPawn(_PawnChoose);

  connect(_Controller->getGameManagement(), &GameManagment::YouPlay, this, &ViewGame::YouCanPlay);

}

/**
 * @brief ViewGame::UpdateDetailPawn : Affiche les détails d'un monstre par rapport à un indice
 * @param index : index du monstre dans la liste des pions
 */
void ViewGame::UpdateDetailPawn(int index)
{
  QVBoxLayout *DetailLayout = new QVBoxLayout();

  //Affiche le nom du monstre
  QHBoxLayout *HBoxName = new QHBoxLayout();
  QLabel *LabelName = new QLabel(tr("Name : "));
  LabelName->setMaximumSize(100, 30);
  HBoxName->addWidget(LabelName);
  QLabel *LabelNameVal = new QLabel(_Player->getPion(index)->getName());
  LabelNameVal->setMaximumSize(100, 30);
  HBoxName->addWidget(LabelNameVal);
  DetailLayout->addLayout(HBoxName);

  //Affiche la vie du monstre
  QHBoxLayout *HBoxLife = new QHBoxLayout();
  QLabel *LabelLife = new QLabel(tr("Life : "));
  LabelLife->setMaximumSize(100, 30);
  HBoxLife->addWidget(LabelLife);
  QLabel *LabelLifeVal = new QLabel(QString::number(_Player->getPion(index)->getLife()));
  LabelLifeVal->setMaximumSize(100, 30);
  HBoxLife->addWidget(LabelLifeVal);
  DetailLayout->addLayout(HBoxLife);

  //Affiche la porté des attaques du monstre
  QHBoxLayout *HBoxRange = new QHBoxLayout();
  QLabel *LabelRange = new QLabel(tr("Range : "));
  LabelRange->setMaximumSize(100, 30);
  HBoxRange->addWidget(LabelRange);
  QLabel *LabelRangeVal = new QLabel(QString::number(_Player->getPion(index)->getMoveRadius()));
  LabelRangeVal->setMaximumSize(100, 30);
  HBoxRange->addWidget(LabelRangeVal);
  DetailLayout->addLayout(HBoxRange);

  //Affiche l'attaque du monstre
  QHBoxLayout *HBoxDomage = new QHBoxLayout();
  QLabel *LabelDomage = new QLabel(tr("Domage : "));
  LabelDomage->setMaximumSize(100, 30);
  HBoxDomage->addWidget(LabelDomage);
  QLabel *LabelDomageVal = new QLabel(QString::number(_Player->getPion(index)->getAttack()));
  LabelDomageVal->setMaximumSize(100, 30);
  HBoxDomage->addWidget(LabelDomageVal);
  DetailLayout->addLayout(HBoxDomage);

  //Affiche la defense du monstre
  QHBoxLayout *HBoxDefence = new QHBoxLayout();
  QLabel *LabelDefence = new QLabel(tr("Defence : "));
  LabelDefence->setMaximumSize(100, 30);
  HBoxDefence->addWidget(LabelDefence);
  QLabel *LabelDefenceVal = new QLabel(QString::number(_Player->getPion(index)->getDefence()));
  LabelDefenceVal->setMaximumSize(100, 30);
  HBoxDefence->addWidget(LabelDefenceVal);
  DetailLayout->addLayout(HBoxDefence);

  //Affiche la coordonnée X du monstre
  QHBoxLayout *HBoxX = new QHBoxLayout();
  QLabel *LabelX = new QLabel(tr("X : "));
  LabelX->setMaximumSize(100, 30);
  HBoxX->addWidget(LabelX);
  QLabel *LabelXVal;
  if(_Player->getPion(index)->getX() == 10) LabelXVal = new QLabel(tr("Undefined"));
  else LabelXVal = new QLabel(QString::number(_Player->getPion(index)->getX()));
  LabelXVal->setMaximumSize(100, 30);
  HBoxX->addWidget(LabelXVal);
  DetailLayout->addLayout(HBoxX);

  //Affiche la coordonnée Y du monstre
  QHBoxLayout *HBoxY = new QHBoxLayout();
  QLabel *LabelY = new QLabel(tr("Y : "));
  LabelY->setMaximumSize(100, 30);
  HBoxY->addWidget(LabelY);
  QLabel *LabelYVal;
  if(_Player->getPion(index)->getY() == 10) LabelYVal = new QLabel(tr("Undefined"));
  else LabelYVal = new QLabel(QString::number(_Player->getPion(index)->getY()));
  LabelYVal->setMaximumSize(100, 30);
  HBoxY->addWidget(LabelYVal);
  DetailLayout->addLayout(HBoxY);

  ui->DetailsPion->insertLayout(0, DetailLayout);

  if(!_AllIsPositioned)
    ChoosePosition();
  else
    ChooseMovementAttack();

}

/**
 * @brief ViewGame::ClearDetailLayout : Supprime les détails d'un monstre (le visuel)
 */
void ViewGame::ClearDetailLayout() const
{
  QLayoutItem* item = ui->DetailsPion->takeAt(0);
  while(item->layout()->count() !=0){
      QLayoutItem* item2 = item->layout()->takeAt(0);
      QLayoutItem* item3 = item2->layout()->takeAt(0);
      delete item3->widget();
      delete item3;
      QLayoutItem* item4 = item2->layout()->takeAt(0);
      delete item4->widget();
      delete item4;
      delete item2;
  }
  delete item;
}

/**
 * @brief ViewGame::ChoosePosition : Affiche deux QSpinBox qui permettent de choisir la position d'un monstre
 */
void ViewGame::ChoosePosition()
{
   QVBoxLayout *ChoosePositionLayout = new QVBoxLayout();

   //Affiche la QSpinBox X du monstre
   QHBoxLayout *HBoxX = new QHBoxLayout();
   QLabel *LabelX = new QLabel(tr("Position X : "));
   LabelX->setMaximumSize(100, 30);
   HBoxX->addWidget(LabelX);
   _SpinBoxX = new QSpinBox();
   _SpinBoxX->setRange(0, 9);
   _SpinBoxX->setMaximumSize(100, 30);
   HBoxX->addWidget(_SpinBoxX);
   ChoosePositionLayout->addLayout(HBoxX);

   //Affiche la QSpinBox Y du monstre
   QHBoxLayout *HBoxY = new QHBoxLayout();
   QLabel *LabelY = new QLabel(tr("Position Y : "));
   LabelY->setMaximumSize(100, 30);
   HBoxY->addWidget(LabelY);
   _SpinBoxY = new QSpinBox();
   _SpinBoxY->setRange(0, 1);
   _SpinBoxY->setMaximumSize(100, 30);
   HBoxY->addWidget(_SpinBoxY);
   ChoosePositionLayout->addLayout(HBoxY);

   //Affiche le bouton valider
   QHBoxLayout *HBoxBtn = new QHBoxLayout();
   QPushButton *ButtonValider = new QPushButton(tr("Valider"));
   ButtonValider->setMaximumSize(200, 30);
   connect(ButtonValider, &QPushButton::clicked, this, &ViewGame::UpdatePositionPawnSignal);
   HBoxBtn->addWidget(ButtonValider);
   ChoosePositionLayout->addLayout(HBoxBtn);

   ui->DetailsPion->insertLayout(1, ChoosePositionLayout);
}

/**
 * @brief ViewGame::ClearChoosePositionLayout : Supprime le layout de position d'un monstre
 */
void ViewGame::ClearChoosePositionLayout() const
{
  QLayoutItem* item = ui->DetailsPion->takeAt(1);

  QLayoutItem* item2 = item->layout()->takeAt(0);
  QLayoutItem* item3 = item2->layout()->takeAt(0);
      delete item3->widget();
      delete item3;
  QLayoutItem* item4 = item2->layout()->takeAt(0);
      delete item4->widget();
      delete item4;
  delete item2;

  QLayoutItem* item5 = item->layout()->takeAt(0);
  QLayoutItem* item6 = item5->layout()->takeAt(0);
      delete item6->widget();
      delete item6;
  QLayoutItem* item7 = item5->layout()->takeAt(0);
      delete item7->widget();
      delete item7;
  delete item5;

  QLayoutItem* item8 = item->layout()->takeAt(0);
  QLayoutItem* item9 = item8->layout()->takeAt(0);
      delete item9->widget();
      delete item9;
  delete item8;

  delete item;
}

/**
 * @brief ViewGame::ChooseMovementAttack : Permets de changer les valeurs de x et y d'un monstre pour le déplacer ou bien attaquer
 */
void ViewGame::ChooseMovementAttack()
{
  if(_X == 10 || !_IsSelected)
      _X = _Player->pawnsPossibles(_Controller->getGameManagement()->getGame(), _Player->getPion(_PawnChoose))[0]._x;
  if(_Y == 10 || !_IsSelected)
      _Y = _Player->pawnsPossibles(_Controller->getGameManagement()->getGame(), _Player->getPion(_PawnChoose))[0]._y;

  QVBoxLayout *ChooseMovementAttackLayout = new QVBoxLayout();

  //Affiche le Qlabel X du monstre
  QHBoxLayout *HBoxX = new QHBoxLayout();
  QLabel *LabelX = new QLabel("Position X : ");
  LabelX->setMaximumSize(100, 30);
  HBoxX->addWidget(LabelX);
  QLabel *_LabelX = new QLabel(QString::number(_X));
  _LabelX->setMaximumSize(100, 30);
  HBoxX->addWidget(_LabelX);
  ChooseMovementAttackLayout->addLayout(HBoxX);

  //Affiche la Qlabel Y du monstre
  QHBoxLayout *HBoxY = new QHBoxLayout();
  QLabel *LabelY = new QLabel("Position Y : ");
  LabelY->setMaximumSize(100, 30);
  HBoxY->addWidget(LabelY);
  QLabel *_LabelY = new QLabel(QString::number(_Y));
  _LabelY->setMaximumSize(100, 30);
  HBoxY->addWidget(_LabelY);
  ChooseMovementAttackLayout->addLayout(HBoxY);

  //Affiche le bouton Movement / Attack
  QHBoxLayout *HBoxBtn = new QHBoxLayout();
  QPushButton *ButtonValider = new QPushButton();
  if(_Controller->getGameManagement()->getGame().getBoard()[_Y][_X] == nullptr)
      ButtonValider->setText(tr("Movement"));
  else if(!_Controller->getGameManagement()->getGame().getBoard()[_Y][_X]->isGood())
      ButtonValider->setText(tr("Attack"));
  else if(_Controller->getGameManagement()->getGame().getBoard()[_Y][_X]->isGood())
          ButtonValider->setText(tr("Heal"));
  ButtonValider->setMaximumSize(200, 30);
  if(_play == true)
      ButtonValider->setEnabled(true);
  else ButtonValider->setEnabled(false);
  connect(ButtonValider, &QPushButton::clicked, this, &ViewGame::PlayerPlay);
  HBoxBtn->addWidget(ButtonValider);
  ChooseMovementAttackLayout->addLayout(HBoxBtn);

  ui->DetailsPion->insertLayout(1, ChooseMovementAttackLayout);
}

/**
 * @brief ViewGame::UpdatePositionPawnSignal : Mets à jour la position d'un monstre
 */
void ViewGame::UpdatePositionPawnSignal()
{
     bool AllOk = true;
     //vérifie que t'as position choisie n'est pas déjà prise
     for(auto pawn : _Player->getListPionsGame()){
         if(pawn->getX() == _SpinBoxX->value() && pawn->getY() == _SpinBoxY->value()){
             AllOk = AllOk && false;
           }
     }

     if(AllOk){
         PositionPawn PP = {_SpinBoxX->value(), _SpinBoxY->value(), _PawnChoose};
         //émets le signal pour mettre à jour la position d'un monstre
         emit UpdatePositionPawn(PP);
         //Passe au monstre suivant dans la liste
         if(_PawnChoose < this->_Player->getListPionsGame().count()-1){
              _PawnChoose++;
         }else {
              _AllIsPositioned = true;
              _PawnChoose = 0;
         }
         ClearChoosePositionLayout();
         ClearDetailLayout();
         UpdateDetailPawn(_PawnChoose);
     }
     else {
         QMessageBox::warning(this, tr("Warning"), tr("It’s coordinated its already used"));
     }
}

void ViewGame::YouCanPlay()
{
    std::cout << "test";
   _play = true;
   ClearChoosePositionLayout();
   ClearDetailLayout();
   UpdateDetailPawn(_PawnChoose);
}

void ViewGame::PlayerPlay()
{
    _Player->setPosPawn(PositionPawn{_X, _Y, _PawnChoose});
    _Player->setValid(true);
    _play= false;
    ClearChoosePositionLayout();
    ClearDetailLayout();
    UpdateDetailPawn(_PawnChoose);
}

/**
 * @brief ViewGame::keyPressEvent : Permet avec différent touche du clavier de choisir un pion, de le sélectionner
 * @param event : capture les évènements clavier
 */
void ViewGame::keyPressEvent(QKeyEvent *event)
{
  switch(event->key()) {

    case Qt::Key_Right :
        if(!_IsSelected){
          if(_PawnChoose < this->_Player->getListPionsGame().count()-1) _PawnChoose++;
          else _PawnChoose = 0;
        }else {
            for(int i = 0 ; i < 10 ; i++){
                _X++;
                if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose)))
                        break;
                else{
                      if(_X > _Controller->getGameManagement()->MaxX(_Player->getPion(_PawnChoose)))
                          _X = _Controller->getGameManagement()->MinX(_Player->getPion(_PawnChoose));
                      if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose)))
                          break;
                }
            }
        }

        ClearChoosePositionLayout();
        ClearDetailLayout();
        UpdateDetailPawn(_PawnChoose);
        break;

    case Qt::Key_Left :
        if(!_IsSelected){
          if(_PawnChoose > 0) _PawnChoose--;
          else _PawnChoose = this->_Player->getListPionsGame().count()-1;
        }else {
            for(int i = 0 ; i < 10 ; i++){
                _X--;
                if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose)))
                        break;
                else{
                      if(_X < _Controller->getGameManagement()->MinX(_Player->getPion(_PawnChoose))){
                          _X = _Controller->getGameManagement()->MaxX(_Player->getPion(_PawnChoose));
                      }
                      if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose))){
                          break;
                      }
                }
            }
        }

        ClearChoosePositionLayout();
        ClearDetailLayout();
        UpdateDetailPawn(_PawnChoose);
        break;

    case Qt::Key_Up :
        if(_IsSelected){
            for(int i = 0 ; i < 10 ; i++){
                _Y--;
                if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose)))
                        break;
                else{
                      if(_Y < _Controller->getGameManagement()->MinY(_Player->getPion(_PawnChoose)))
                          _Y = _Controller->getGameManagement()->MaxY(_Player->getPion(_PawnChoose));
                      if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose)))
                          break;
                }
            }

            ClearChoosePositionLayout();
            ClearDetailLayout();
            UpdateDetailPawn(_PawnChoose);
        }
        break;

    case Qt::Key_Down :
      if(_IsSelected){
          for(int i = 0 ; i < 10 ; i++){
              _Y++;
              if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose)))
                      break;
              else{
                    if(_Y > _Controller->getGameManagement()->MaxY(_Player->getPion(_PawnChoose)))
                        _Y = _Controller->getGameManagement()->MinY(_Player->getPion(_PawnChoose));
                    if(_Controller->getGameManagement()->IsInPawnPossible(Position{_X, _Y}, _Player->getPion(_PawnChoose)))
                        break;
              }
          }

          ClearChoosePositionLayout();
          ClearDetailLayout();
          UpdateDetailPawn(_PawnChoose);
      }
        break;

    case Qt::Key_Return :
        if(!_IsSelected) this->_IsSelected = true;
        else this->_IsSelected = false;
        break;
  case Qt::Key_B :
        _Controller->getGameManagement()->startGame();
      break;

    case Qt::Key_Escape :
        this->close();
        break;
    }
}

/**
 * @brief ViewGame::~ViewGame : Destructeur
 */
ViewGame::~ViewGame()
{
  delete ui;
}
