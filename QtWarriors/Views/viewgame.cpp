#include "viewgame.hpp"
#include "ui_viewgame.h"
#include "Controllers/controller.hpp"

/**
 * @brief ViewGame::ViewGame : Instancie une vue ViewGame qui affiche la partie
 * @param controller : Objet Controller
 * @param player : Objet Player
 * @param playerEnemy : Objet Player
 * @param game : Objet Game
 * @param parent : Objet QWidget
 */
ViewGame::ViewGame(Controller * controller, std::shared_ptr<Player> player,  std::shared_ptr<Player> playerEnemy, Game game, QWidget *parent)
    : QDialog(parent),
      View (controller),
      ui(new Ui::ViewGame),
      _player(player),
      _playerEnemy(playerEnemy),
      _game(game),
      _pawnChosen(0),
      _isSelected(false),
      _allArePositioned(false),
      _x(10),
      _y(10),
      _play(false)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);

    updateDetailPawn(_pawnChosen);

    connect(_controller->getGameManagement(), &GameManagment::youPlay, this, &ViewGame::youCanPlay);
    ui->openGLWidget->chargePawns(_player->getPawns(), _playerEnemy->getPawns());

}

/**
 * @brief ViewGame::updateDetailPawn : Affiche les détails d'un monstre par rapport à un indice
 * @param index : index du monstre dans la liste des pions
 */
void ViewGame::updateDetailPawn(int index)
{
    QVBoxLayout *detailLayout = new QVBoxLayout();

    //Affiche le nom du monstre
    QHBoxLayout * hBoxName = new QHBoxLayout();
    QLabel * labelName = new QLabel(tr("Name : "));
    QLabel * labelNameVal = new QLabel(_player->getPawn(index)->getName());

    labelName->setMaximumSize(100, 30);
    hBoxName->addWidget(labelName);
    labelNameVal->setMaximumSize(100, 30);
    hBoxName->addWidget(labelNameVal);
    detailLayout->addLayout(hBoxName);

    //Affiche la vie du monstre
    QHBoxLayout * hBoxLife = new QHBoxLayout();
    QLabel * labelLife = new QLabel(tr("Life : "));
    QLabel * labelLifeVal = new QLabel(QString::number(_player->getPawn(index)->getLife()));

    labelLife->setMaximumSize(100, 30);
    hBoxLife->addWidget(labelLife);
    labelLifeVal->setMaximumSize(100, 30);
    hBoxLife->addWidget(labelLifeVal);
    detailLayout->addLayout(hBoxLife);

    //Affiche la porté des attaques du monstre
    QHBoxLayout * hBoxRange = new QHBoxLayout();
    QLabel * labelRange = new QLabel(tr("Range : "));
    QLabel * labelRangeVal = new QLabel(QString::number(_player->getPawn(index)->getMoveRadius()));

    labelRange->setMaximumSize(100, 30);
    hBoxRange->addWidget(labelRange);
    labelRangeVal->setMaximumSize(100, 30);
    hBoxRange->addWidget(labelRangeVal);
    detailLayout->addLayout(hBoxRange);

    //Affiche l'attaque du monstre
    QHBoxLayout * hBoxDomage = new QHBoxLayout();
    QLabel * labelDomage = new QLabel(tr("Damages : "));
    QLabel * labelDomageVal = new QLabel(QString::number(_player->getPawn(index)->getAttack()));

    labelDomage->setMaximumSize(100, 30);
    hBoxDomage->addWidget(labelDomage);
    labelDomageVal->setMaximumSize(100, 30);
    hBoxDomage->addWidget(labelDomageVal);
    detailLayout->addLayout(hBoxDomage);

      //Affiche la defense du monstre
    QHBoxLayout * hBoxDefence = new QHBoxLayout();
    QLabel * labelDefence = new QLabel(tr("Defence : "));
    QLabel * labelDefenceVal = new QLabel(QString::number(_player->getPawn(index)->getDefence()));

    labelDefence->setMaximumSize(100, 30);
    hBoxDefence->addWidget(labelDefence);
    labelDefenceVal->setMaximumSize(100, 30);
    hBoxDefence->addWidget(labelDefenceVal);
    detailLayout->addLayout(hBoxDefence);

    //Affiche la coordonnée X du monstre
    QHBoxLayout * hBoxX = new QHBoxLayout();
    QLabel * labelX = new QLabel(tr("X : "));
    QLabel * labelXVal;

    labelX->setMaximumSize(100, 30);
    hBoxX->addWidget(labelX);

    if(_player->getPawn(index)->getX() == 10) labelXVal = new QLabel(tr("Undefined"));
    else labelXVal = new QLabel(QString::number(_player->getPawn(index)->getX()));

    labelXVal->setMaximumSize(100, 30);
    hBoxX->addWidget(labelXVal);
    detailLayout->addLayout(hBoxX);

    //Affiche la coordonnée Y du monstre
    QHBoxLayout * hBoxY = new QHBoxLayout();
    QLabel * labelY = new QLabel(tr("Y : "));
    QLabel * labelYVal;

    labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(labelY);

    if(_player->getPawn(index)->getY() == 10) labelYVal = new QLabel(tr("Undefined"));
    else labelYVal = new QLabel(QString::number(_player->getPawn(index)->getY()));

    labelYVal->setMaximumSize(100, 30);
    hBoxY->addWidget(labelYVal);
    detailLayout->addLayout(hBoxY);

    ui->DetailsPion->insertLayout(0, detailLayout);

    (!_allArePositioned) ? choosePosition() : chooseMovementAttack();

}

/**
 * @brief ViewGame::clearDetailLayout : Supprime les détails d'un monstre (le visuel)
 */
void ViewGame::clearDetailLayout() const
{
    QLayoutItem* item = ui->DetailsPion->takeAt(0);

    while(item->layout()->count() !=0)
    {
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
void ViewGame::choosePosition()
{
    QVBoxLayout * choosePositionLayout = new QVBoxLayout();

    //Affiche la QSpinBox X du monstre
    QHBoxLayout * hBoxX = new QHBoxLayout();
    QLabel * labelX = new QLabel(tr("Position X : "));

    labelX->setMaximumSize(100, 30);
    hBoxX->addWidget(labelX);
    _spinBoxX = new QSpinBox();
    _spinBoxX->setRange(0, 9);
    _spinBoxX->setMaximumSize(100, 30);
    hBoxX->addWidget(_spinBoxX);

    choosePositionLayout->addLayout(hBoxX);

    //Affiche la QSpinBox Y du monstre
    QHBoxLayout * hBoxY = new QHBoxLayout();
    QLabel * labelY = new QLabel(tr("Position Y : "));

    labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(labelY);
    _spinBoxY = new QSpinBox();
    _spinBoxY->setRange(0, 1);
    _spinBoxY->setMaximumSize(100, 30);
    hBoxY->addWidget(_spinBoxY);

    choosePositionLayout->addLayout(hBoxY);

    //Affiche le bouton valider
    QHBoxLayout * hBoxBtn = new QHBoxLayout();
    QPushButton * buttonValidate = new QPushButton(tr("Valider"));

    buttonValidate->setMaximumSize(200, 30);
    connect(buttonValidate, &QPushButton::clicked, this, &ViewGame::updatePositionPawnSignal);
    hBoxBtn->addWidget(buttonValidate);

    choosePositionLayout->addLayout(hBoxBtn);

    ui->DetailsPion->insertLayout(1, choosePositionLayout);
}

/**
 * @brief ViewGame::clearChoosePositionLayout : Supprime le layout de position d'un monstre
 */
void ViewGame::clearChoosePositionLayout() const
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
void ViewGame::chooseMovementAttack()
{
    if(_x == 10 || !_isSelected)
        _x = _player->pawnsPossibles(_controller->getGameManagement()->getGame(), _player->getPawn(_pawnChosen))[0]._x;

    if(_y == 10 || !_isSelected)
        _y = _player->pawnsPossibles(_controller->getGameManagement()->getGame(), _player->getPawn(_pawnChosen))[0]._y;

    QVBoxLayout * chooseMovementAttackLayout = new QVBoxLayout();

    //Affiche le Qlabel X du monstre
    QHBoxLayout * hBoxX = new QHBoxLayout();
    QLabel * labelX = new QLabel("Position X : ");
    QLabel * _labelX = new QLabel(QString::number(_x));

    labelX->setMaximumSize(100, 30);
    hBoxX->addWidget(labelX);
    _labelX->setMaximumSize(100, 30);
    hBoxX->addWidget(_labelX);

    chooseMovementAttackLayout->addLayout(hBoxX);

    //Affiche la Qlabel Y du monstre
    QHBoxLayout * hBoxY = new QHBoxLayout();
    QLabel * labelY = new QLabel("Position Y : ");
    QLabel * _labelY = new QLabel(QString::number(_y));

    labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(labelY);
    _labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(_labelY);

    chooseMovementAttackLayout->addLayout(hBoxY);

    //Affiche le bouton Movement / Attack
    QHBoxLayout * hBoxBtn = new QHBoxLayout();
    _buttonValidate = new QPushButton();

    if(_controller->getGameManagement()->getGame().getBoard()[_y][_x] == nullptr)
        _buttonValidate->setText(tr("Movement"));
    else if(!_controller->getGameManagement()->getGame().getBoard()[_y][_x]->isGood())
        _buttonValidate->setText(tr("Attack"));
    else if(_controller->getGameManagement()->getGame().getBoard()[_y][_x]->isGood())
        _buttonValidate->setText(tr("Heal"));

    _buttonValidate->setMaximumSize(200, 30);

    (_play) ? _buttonValidate->setEnabled(true) : _buttonValidate->setEnabled(false);

    connect(_buttonValidate, &QPushButton::clicked, this, &ViewGame::playerPlay);

    hBoxBtn->addWidget(_buttonValidate);
    chooseMovementAttackLayout->addLayout(hBoxBtn);

    ui->DetailsPion->insertLayout(1, chooseMovementAttackLayout);
}

/**
 * @brief ViewGame::UpdatePositionPawnSignal : Mets à jour la position d'un monstre
 */
void ViewGame::updatePositionPawnSignal()
{
    bool AllOk = true;

    //vérifie que t'as position choisie n'est pas déjà prise
    for(auto pawn : _player->getPawns())
        if(pawn->getX() == _spinBoxX->value() && pawn->getY() == _spinBoxY->value())
           AllOk = AllOk && false;


    if(AllOk)
    {
        PositionPawn PP = {_spinBoxX->value(), _spinBoxY->value(), _pawnChosen};

        //émets le signal pour mettre à jour la position d'un monstre
        emit updatePositionPawn(PP);

        //Passe au monstre suivant dans la liste
        if(_pawnChosen < this->_player->getPawns().count()-1)
             _pawnChosen++;
        else
        {
             _allArePositioned = true;
             _pawnChosen = 0;
        }

        clearChoosePositionLayout();
        clearDetailLayout();
        updateDetailPawn(_pawnChosen);
    }
    else
        QMessageBox::warning(this, tr("Warning"), tr("It’s coordinated its already used"));

}

void ViewGame::youCanPlay()
{
    ui->openGLWidget->setMoveBoard();
    time = new QTimer(this);

    connect(time, &QTimer::timeout, this, &ViewGame::moveBoard);

    time->start(45000);
    _play = true;
    clearChoosePositionLayout();
    clearDetailLayout();
    updateDetailPawn(_pawnChosen);
}

void ViewGame::playerPlay()
{
    _player->setPosPawn(PositionPawn{_x, _y, _pawnChosen});
    _player->setValid(true);
    ui->openGLWidget->movePawn();
    moveBoard();
}

void ViewGame::moveBoard()
{
    _buttonValidate->setEnabled(false);
    ui->openGLWidget->setMoveBoard();

    connect(ui->openGLWidget, &OpenGLWidget::boardHasMoved, _controller, &Controller::endTurn);
}

/**
 * @brief ViewGame::keyPressEvent : Permet avec différent touche du clavier de choisir un pion, de le sélectionner
 * @param event : capture les évènements clavier
 */
void ViewGame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {

    case Qt::Key_Right :
        if(!_isSelected)
        {
            if(_pawnChosen < this->_player->getPawns().count()-1) _pawnChosen++;
            else _pawnChosen = 0;
        }
        else
        {
            for(int i = 0 ; i < 10 ; i++){
                _x++;
                if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                        break;
                else
                {
                      if(_x > _controller->getGameManagement()->maxX(_player->getPawn(_pawnChosen)))
                          _x = _controller->getGameManagement()->minX(_player->getPawn(_pawnChosen));
                      if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                          break;
                }
            }
        }

        clearChoosePositionLayout();
        clearDetailLayout();
        updateDetailPawn(_pawnChosen);
        break;

    case Qt::Key_Left :
        if(!_isSelected)
        {
            if(_pawnChosen > 0) _pawnChosen--;
            else _pawnChosen = this->_player->getPawns().count()-1;
        }
        else
        {
            for(int i = 0 ; i < 10 ; i++)
            {
                _x--;
                if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                    break;
                else
                {
                      if(_x < _controller->getGameManagement()->minX(_player->getPawn(_pawnChosen)))
                      {
                          _x = _controller->getGameManagement()->maxX(_player->getPawn(_pawnChosen));
                      }
                      if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                      {
                          break;
                      }
                }
            }
        }

        clearChoosePositionLayout();
        clearDetailLayout();
        updateDetailPawn(_pawnChosen);
        break;

    case Qt::Key_Up :
        if(_isSelected)
        {
            for(int i = 0 ; i < 10 ; i++)
            {
                _y--;
                if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                    break;
                else
                {
                    if(_y < _controller->getGameManagement()->minY(_player->getPawn(_pawnChosen)))
                        _y = _controller->getGameManagement()->maxY(_player->getPawn(_pawnChosen));
                    if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                        break;
                }
            }

            clearChoosePositionLayout();
            clearDetailLayout();
            updateDetailPawn(_pawnChosen);
        }
        break;

    case Qt::Key_Down :
        if(_isSelected)
        {
            for(int i = 0 ; i < 10 ; i++)
            {
                _y++;
                if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                    break;
                else
                {
                    if(_y > _controller->getGameManagement()->maxY(_player->getPawn(_pawnChosen)))
                        _y = _controller->getGameManagement()->minY(_player->getPawn(_pawnChosen));
                    if(_controller->getGameManagement()->containsPosition(Position{_x, _y}, _player->getPawn(_pawnChosen)))
                        break;
                }
            }

            clearChoosePositionLayout();
            clearDetailLayout();
            updateDetailPawn(_pawnChosen);
        }
        break;

    case Qt::Key_Return :
        (!_isSelected) ? this->_isSelected = true : this->_isSelected = false;
        break;

    case Qt::Key_B :
        _controller->getGameManagement()->startGame();
        ui->openGLWidget->changeGameStatus();
        break;

    case Qt::Key_Escape :
        this->close();
        break;
    }
}

void ViewGame::deleteTimer()
{
    disconnect(ui->openGLWidget, &OpenGLWidget::boardHasMoved, _controller, &Controller::endTurn);

    delete time;
    _play = false;
}

/**
 * @brief ViewGame::~ViewGame : Destructeur
 */
ViewGame::~ViewGame()
{
    delete ui;
    delete ui->openGLWidget;
}
