#include "gameView.hpp"
#include "ui_viewgame.h"
#include "Controllers/controller.hpp"
#include <QTime>
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

    QPushButton *btnExit = new QPushButton("Exit");
    btnExit->setMaximumSize(250, 30);
    btnExit->setStyleSheet("font-weight: normal; background-color: red; color: black;");
    connect(btnExit, &QPushButton::clicked, this, &ViewGame::close);
    ui->DetailsPion->addWidget(btnExit);

    connect(_controller->getGameManagement(), &GameManagment::youPlay, this, &ViewGame::youCanPlay);
    ui->openGLWidget->chargePawns(_player->getPawns(), _playerEnemy->getPawns());
    ui->DetailsPion->setSpacing(10);
    ui->DetailsPion->setMargin(10);
}

/**
 * @brief ViewGame::updateDetailPawn : Affiche les détails d'un monstre par rapport à un indice
 * @param index : index du monstre dans la liste des pions
 */
void ViewGame::updateDetailPawn(int index)
{
    QVBoxLayout *detailLayout = new QVBoxLayout();

    // label Monstre
    QLabel *labelMonstre = new QLabel(tr("Monster"));
    labelMonstre->setMaximumSize(250, 30);
    labelMonstre->setAlignment(Qt::AlignCenter);
    detailLayout->addWidget(labelMonstre);

    //Affiche le nom du monstre
    QHBoxLayout * hBoxName = new QHBoxLayout();
    QLabel * labelName = new QLabel(tr("Name : "));
    QLabel * labelNameVal = new QLabel(_player->getPawn(index)->getName());

    labelName->setMaximumSize(100, 30);
    hBoxName->addWidget(labelName);
    labelNameVal->setMaximumSize(150, 30);
    labelNameVal->setStyleSheet("font-weight: normal;");
    hBoxName->addWidget(labelNameVal);
    detailLayout->addLayout(hBoxName);

    //Affiche la vie du monstre
    QHBoxLayout * hBoxLife = new QHBoxLayout();
    QLabel * labelLife = new QLabel(tr("Life : "));
    QLabel * labelLifeVal = new QLabel(QString::number(_player->getPawn(index)->getLife()));

    labelLife->setMaximumSize(100, 30);
    hBoxLife->addWidget(labelLife);
    labelLifeVal->setMaximumSize(150, 30);
    labelLifeVal->setStyleSheet("font-weight: normal;");
    hBoxLife->addWidget(labelLifeVal);
    detailLayout->addLayout(hBoxLife);

    //Affiche la porté des attaques du monstre
    QHBoxLayout * hBoxRange = new QHBoxLayout();
    QLabel * labelRange = new QLabel(tr("Range : "));
    QLabel * labelRangeVal = new QLabel(QString::number(_player->getPawn(index)->getMoveRadius()));

    labelRange->setMaximumSize(100, 30);
    hBoxRange->addWidget(labelRange);
    labelRangeVal->setMaximumSize(150, 30);
    labelRangeVal->setStyleSheet("font-weight: normal;");
    hBoxRange->addWidget(labelRangeVal);
    detailLayout->addLayout(hBoxRange);

    //Affiche l'attaque du monstre
    QHBoxLayout * hBoxDomage = new QHBoxLayout();
    QLabel * labelDomage = new QLabel(tr("Damages : "));
    QLabel * labelDomageVal = new QLabel(QString::number(_player->getPawn(index)->getAttack()));

    labelDomage->setMaximumSize(100, 30);
    hBoxDomage->addWidget(labelDomage);
    labelDomageVal->setMaximumSize(150, 30);
    labelDomageVal->setStyleSheet("font-weight: normal;");
    hBoxDomage->addWidget(labelDomageVal);
    detailLayout->addLayout(hBoxDomage);

    //Affiche la defense du monstre
    QHBoxLayout * hBoxDefence = new QHBoxLayout();
    QLabel * labelDefence = new QLabel(tr("Defence : "));
    QLabel * labelDefenceVal = new QLabel(QString::number(_player->getPawn(index)->getDefence()));

    labelDefence->setMaximumSize(100, 30);
    hBoxDefence->addWidget(labelDefence);
    labelDefenceVal->setMaximumSize(150, 30);
    labelDefenceVal->setStyleSheet("font-weight: normal;");
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

    labelXVal->setMaximumSize(150, 30);
    labelXVal->setStyleSheet("font-weight: normal;");
    hBoxX->addWidget(labelXVal);
    detailLayout->addLayout(hBoxX);

    //Affiche la coordonnée Y du monstre
    QHBoxLayout * hBoxY = new QHBoxLayout();
    QLabel * labelY = new QLabel(tr("Y : "));
    QLabel * labelYVal;

    labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(labelY);

    if(_player->getPawn(index)->getX() == 10) labelYVal = new QLabel(tr("Undefined"));
    else labelYVal = new QLabel(QString::number(_player->getPawn(index)->getY()));

    labelYVal->setMaximumSize(150, 30);
    labelYVal->setStyleSheet("font-weight: normal;");
    hBoxY->addWidget(labelYVal);
    detailLayout->addLayout(hBoxY);

    ui->DetailsPion->insertLayout(0, detailLayout);


    if(!_allArePositioned) choosePosition();
    if(_isSelected && _controller->getGameManagement()->getGame().getBoard()[_y][_x] == nullptr){
        chooseMovement();
    }
    else if(_isSelected && _controller->getGameManagement()->getGame().getBoard()[_y][_x] != nullptr){
        detailTarget();
    }
    ui->openGLWidget->updateArrow(_x, _y);

}

/**
 * @brief ViewGame::clearDetailLayout : Supprime les détails d'un monstre (le visuel)
 */
void ViewGame::clearDetailLayout() const
{
    QLayoutItem* item = ui->DetailsPion->takeAt(0);

    QLayoutItem* item5 = item->layout()->takeAt(0);
    delete item5->widget();
    delete item5;

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
    _spinBoxX->setMaximumSize(150, 30);
    _spinBoxX->setStyleSheet("font-weight: normal; color: black;");
    hBoxX->addWidget(_spinBoxX);

    choosePositionLayout->addLayout(hBoxX);

    //Affiche la QSpinBox Y du monstre
    QHBoxLayout * hBoxY = new QHBoxLayout();
    QLabel * labelY = new QLabel(tr("Position Y : "));

    labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(labelY);
    _spinBoxY = new QSpinBox();
    _spinBoxY->setRange(0, 1);
    _spinBoxY->setMaximumSize(150, 30);
    _spinBoxY->setStyleSheet("font-weight: normal; color: black;");
    hBoxY->addWidget(_spinBoxY);

    choosePositionLayout->addLayout(hBoxY);

    //Affiche le bouton valider
    QHBoxLayout * hBoxBtn = new QHBoxLayout();
    QPushButton * buttonValidate = new QPushButton(tr("Valider"));

    buttonValidate->setMaximumSize(250, 30);
    buttonValidate->setStyleSheet("font-weight: normal; color: black;");
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

    while(item->layout()->count() != 1)
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

    QLayoutItem* item8 = item->layout()->takeAt(0);
    QLayoutItem* item9 = item8->layout()->takeAt(0);
        delete item9->widget();
        delete item9;
    delete item8;
}

/**
 * @brief ViewGame::ChooseMovementAttack : Permets de changer les valeurs de x et y d'un monstre pour le déplacer ou bien attaquer
 */
void ViewGame::chooseMovement()
{
    QVBoxLayout * chooseMovementLayout = new QVBoxLayout();

    // label target
    QLabel *labelTarget = new QLabel(tr("Target"));
    labelTarget->setMaximumSize(250, 30);
    labelTarget->setAlignment(Qt::AlignCenter);
    chooseMovementLayout->addWidget(labelTarget);

    //Affiche le Qlabel X du monstre
    QHBoxLayout * hBoxX = new QHBoxLayout();
    QLabel * labelX = new QLabel("Position X : ");
    QLabel * _labelX = new QLabel(QString::number(_x));

    labelX->setMaximumSize(100, 30);
    hBoxX->addWidget(labelX);
    _labelX->setMaximumSize(150, 30);
    _labelX->setStyleSheet("font-weight: normal;");
    hBoxX->addWidget(_labelX);

    chooseMovementLayout->addLayout(hBoxX);

    //Affiche la Qlabel Y du monstre
    QHBoxLayout * hBoxY = new QHBoxLayout();
    QLabel * labelY = new QLabel("Position Y : ");
    QLabel * _labelY = new QLabel(QString::number(_y));

    labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(labelY);
    _labelY->setMaximumSize(150, 30);
    _labelY->setStyleSheet("font-weight: normal;");
    hBoxY->addWidget(_labelY);

    chooseMovementLayout->addLayout(hBoxY);

    //Affiche le bouton Move
    _buttonValidate = new QPushButton(tr("Move"));
    _buttonValidate->setMaximumSize(250, 30);
    _buttonValidate->setStyleSheet("font-weight: normal; color: black;");
    _buttonValidate->setStyleSheet("background-color: green;");

    connect(_buttonValidate, &QPushButton::clicked, this, &ViewGame::playerPlay);

    chooseMovementLayout->addWidget(_buttonValidate);

    ui->DetailsPion->insertLayout(1, chooseMovementLayout);
}

/**
 * @brief ViewGame::detailTarget
 */
void ViewGame::detailTarget()
{
    QVBoxLayout * detailTargetLayout = new QVBoxLayout();

    // label target
    QLabel *labelTarget = new QLabel(tr("Target"));
    labelTarget->setMaximumSize(250, 30);
    labelTarget->setAlignment(Qt::AlignCenter);
    detailTargetLayout->addWidget(labelTarget);

    // label type
    QHBoxLayout * hBoxType = new QHBoxLayout();
    QLabel *labelType = new QLabel(tr("Type"));
    QLabel *labelTypeVal = new QLabel(_controller->getGameManagement()->getGame().getBoard()[_y][_x]->getName());
    labelTypeVal->setStyleSheet("font-weight: normal;");
    labelType->setMaximumSize(100, 30);
    labelTypeVal->setMaximumSize(150, 30);
    hBoxType->addWidget(labelType);
    hBoxType->addWidget(labelTypeVal);
    detailTargetLayout->addLayout(hBoxType);

    // label life
    QHBoxLayout * hBoxLife = new QHBoxLayout();
    QLabel *labelLife = new QLabel(tr("Life"));
    QLabel *labelLifeVal = new QLabel(QString::number(_controller->getGameManagement()->getGame().getBoard()[_y][_x]->getLife()));
    labelLifeVal->setStyleSheet("font-weight: normal;");
    labelLife->setMaximumSize(100, 30);
    labelLifeVal->setMaximumSize(150, 30);
    hBoxLife->addWidget(labelLife);
    hBoxLife->addWidget(labelLifeVal);
    detailTargetLayout->addLayout(hBoxLife);

    //Affiche la coordonnée X du monstre
    QHBoxLayout * hBoxX = new QHBoxLayout();
    QLabel * labelX = new QLabel(tr("X : "));
    QLabel * labelXVal =  new QLabel(QString::number(_x));
    labelX->setMaximumSize(100, 30);
    hBoxX->addWidget(labelX);
    labelXVal->setMaximumSize(150, 30);
    labelXVal->setStyleSheet("font-weight: normal;");
    hBoxX->addWidget(labelXVal);
    detailTargetLayout->addLayout(hBoxX);

    //Affiche la coordonnée Y du monstre
    QHBoxLayout * hBoxY = new QHBoxLayout();
    QLabel * labelY = new QLabel(tr("Y : "));
    QLabel * labelYVal = new QLabel(QString::number(_y));
    labelY->setMaximumSize(100, 30);
    hBoxY->addWidget(labelY);
    labelYVal->setMaximumSize(150, 30);
    labelYVal->setStyleSheet("font-weight: normal;");
    hBoxY->addWidget(labelYVal);
    detailTargetLayout->addLayout(hBoxY);

    //Affiche le bouton Attack
     bool specialUse = false;
    _buttonValidate = new QPushButton();
    if(!_controller->getGameManagement()->getGame().getBoard()[_y][_x]->isGood()){
        _buttonValidate->setText(tr("Attack"));
        connect(_buttonValidate, &QPushButton::clicked, [this, specialUse] {playerPlay(specialUse);});
        _buttonValidate->setMaximumSize(250, 30);
        _buttonValidate->setStyleSheet("font-weight: normal; color: black;");
        _buttonValidate->setStyleSheet("background-color: green;");
        detailTargetLayout->addWidget(_buttonValidate);
    }
    else if(_controller->getGameManagement()->getGame().getBoard()[_y][_x]->isGood()){
        if(!_player->getPawn(_pawnChosen)->specialAttackUsed()){
            _buttonValidate->setText(tr("Special skill"));
            specialUse = true;
            connect(_buttonValidate, &QPushButton::clicked, [this, specialUse] {playerPlay(specialUse);});
            _buttonValidate->setMaximumSize(250, 30);
            _buttonValidate->setStyleSheet("font-weight: normal; color: black;");
            _buttonValidate->setStyleSheet("background-color: green;");
            detailTargetLayout->addWidget(_buttonValidate);
        }
    }

    if((_player->getPawn(_pawnChosen)->getType() &~ 1) == 0 && !_player->getPawn(_pawnChosen)->specialAttackUsed()){
        QPushButton *btn = new QPushButton("Special skill");
        specialUse = true;
        connect(btn, &QPushButton::clicked, [this, specialUse] {playerPlay(specialUse);});
        btn->setMaximumSize(250, 30);
        btn->setStyleSheet("font-weight: normal; color: black;");
        btn->setStyleSheet("background-color: green;");
        detailTargetLayout->addWidget(btn);
    }

    ui->DetailsPion->insertLayout(1, detailTargetLayout);
}

/**
 * @brief ViewGame::clearDetailTarget
 */
void ViewGame::clearDetailTarget() const
{
    int i = 1;
    QLayoutItem* item = ui->DetailsPion->takeAt(1);

    if((_player->getPawn(_pawnChosen)->getType() &~ 1) == 0 && item->layout()->count() == 7){
        i = 2;
    }

    if(_player->getPawn(_pawnChosen)->specialAttackUsed() && item->layout()->count() == 5){
        i = 0;
    }

    QLayoutItem* item5 = item->layout()->takeAt(0);
    delete item5->widget();
    delete item5;

    while(item->layout()->count() != i)
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

    while(item->layout()->count() != 0){
        QLayoutItem* item8 = item->layout()->takeAt(0);
        delete item8->widget();
        delete item8;
    }

    delete item;
}

/**
 * @brief ViewGame::clearChrono
 */
void ViewGame::clearChrono() const
{
    //supprime le layout et son contenu
    QLayoutItem* item = ui->DetailsPion->takeAt(ui->DetailsPion->count()-2);

    QLayoutItem* item2 = item->layout()->takeAt(0);
    delete item2->widget();
    delete item2;

    QLayoutItem* item3 = item->layout()->takeAt(0);
    delete item3->widget();
    delete item3;

    delete item;
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
        if(_pawnChosen < this->_player->getPawns().count()-1){
             _pawnChosen++;
        }
        else
        {
             _allArePositioned = true;
             _pawnChosen = 0;
             _x = _player->getPawn(_pawnChosen)->getX();
             _y = _player->getPawn(_pawnChosen)->getY();
             _controller->getGameManagement()->startGame();
        }

        clearChoosePositionLayout();
        clearDetailLayout();
        updateDetailPawn(_pawnChosen);
    }
    else{
            QScreen *screen = QGuiApplication::primaryScreen();
            QMessageBox *msg = new QMessageBox(this);
            msg->setWindowTitle(tr("Warning"));
            msg->setText(tr("It’s coordinates are already used"));
            msg->setFont(QFont("Bradley Hand ITC", 13));
            msg->setStyleSheet("background-color: #2c91c8;");
            msg->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
            msg->adjustSize();
            msg->move(screen->geometry().center() - msg->rect().center());
            msg->open();
        }
}

/**
 * @brief ViewGame::youCanPlay
 */
void ViewGame::youCanPlay()
{
    ui->openGLWidget->updateTitle(tr("It's your turn"));
    _x = _player->getPawn(_pawnChosen)->getX();
    _y = _player->getPawn(_pawnChosen)->getY();
    ui->openGLWidget->setPrintArrow();

    clearDetailLayout();
    updateDetailPawn(_pawnChosen);

    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &ViewGame::NoPlay);
    time->start(45000);
    _play = true;

    setFocusPolicy(Qt::StrongFocus);

    _ti = new QTimer(this);
    connect(_ti, &QTimer::timeout, this, &ViewGame::updateTimer);
    _ti->start(1000);

    _chrono = 45;

    QHBoxLayout * hBox = new QHBoxLayout();
    QLabel *labelChrono = new QLabel(tr("Timer"));
    QLabel *labelChronoVal = new QLabel(QString::number(_chrono) + " seconds");
    labelChronoVal->setStyleSheet("font-weight: normal;");
    labelChrono->setMaximumSize(100, 30);
    labelChronoVal->setMaximumSize(150, 30);
    hBox->addWidget(labelChrono);
    hBox->addWidget(labelChronoVal);
    ui->DetailsPion->insertLayout(ui->DetailsPion->count()-1, hBox);

}

/**
 * @brief ViewGame::playerPlay
 * @param specialUse
 */
void ViewGame::playerPlay(const bool & specialUse)
{
    delete _ti;
    clearChrono();
    ui->openGLWidget->setPrintArrow();
    ui->openGLWidget->setSelected();
    _player->setPosPawn(PositionPawn{_x, _y, _pawnChosen, specialUse});
    _player->setValid(true);
    _isSelected = false;

    clearDetailTarget();
    clearDetailLayout();
    updateDetailPawn(_pawnChosen);
    _pawnChosen = 0;

    emit playerHasPlayed();
    ui->openGLWidget->updateTitle(tr("The computer is playing"));
}

/**
 * @brief ViewGame::NoPlay
 */
void ViewGame::NoPlay() {
    clearChrono();
    delete _ti;
    ui->openGLWidget->setPrintArrow();
    if(_isSelected){
        ui->openGLWidget->setSelected();
        clearDetailTarget();
    }
    _isSelected = false;
    clearDetailLayout();
    updateDetailPawn(_pawnChosen);
    _pawnChosen = 0;

    emit playerHasPlayed();
    ui->openGLWidget->updateTitle(tr("The computer is playing"));
}

/**
 * @brief ViewGame::updateTimer
 */
void ViewGame::updateTimer()
{
    clearChrono();

    _chrono--;
    QHBoxLayout * hBox = new QHBoxLayout();
    QLabel *labelChrono = new QLabel(tr("Timer"));
    QLabel *labelChronoVal = new QLabel(QString::number(_chrono) + " seconds");
    labelChronoVal->setStyleSheet("font-weight: normal;");
    labelChrono->setMaximumSize(100, 30);
    labelChronoVal->setMaximumSize(150, 30);
    hBox->addWidget(labelChrono);
    hBox->addWidget(labelChronoVal);
    ui->DetailsPion->insertLayout(ui->DetailsPion->count()-1, hBox);

}

/**
 * @brief ViewGame::keyPressEvent : Permet avec différent touche du clavier de choisir un pion, de le sélectionner
 * @param event : capture les évènements clavier
 */
void ViewGame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {

    case Qt::Key_Left :
        if(!_isSelected)
        {
            if(_pawnChosen < this->_player->getPawns().count()-1) _pawnChosen++;
            else _pawnChosen = 0;
            _x = _player->getPawn(_pawnChosen)->getX();
            _y = _player->getPawn(_pawnChosen)->getY();
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
            clearDetailTarget();
        }

        clearDetailLayout();
        updateDetailPawn(_pawnChosen);
        break;

    case Qt::Key_Right :
        if(!_isSelected)
        {
            if(_pawnChosen > 0) _pawnChosen--;
            else _pawnChosen = this->_player->getPawns().count()-1;
            _x = _player->getPawn(_pawnChosen)->getX();
            _y = _player->getPawn(_pawnChosen)->getY();
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
            clearDetailTarget();
        }

        clearDetailLayout();
        updateDetailPawn(_pawnChosen);
        break;

    case Qt::Key_Down :
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
            clearDetailTarget();
            clearDetailLayout();
            updateDetailPawn(_pawnChosen);
        }
        break;

    case Qt::Key_Up :
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
            clearDetailTarget();
            clearDetailLayout();
            updateDetailPawn(_pawnChosen);
        }

        break;

    case Qt::Key_Return :
        if(_play){
            if(!_isSelected){
                this->_isSelected = true;
                //le warrior ne peut pas se selectionner lui-même
                if((_player->getPawn(_pawnChosen)->getType() &~ 1) == 0){
                    Position pos = _player->pawnsPossibles(_controller->getGameManagement()->getGame(), _player->getPawn(_pawnChosen))[0];
                    _x = pos._x;
                    _y = pos._y;
                }
                else{
                    _x = _player->getPawn(_pawnChosen)->getX();
                    _y = _player->getPawn(_pawnChosen)->getY();
                }
                ui->openGLWidget->setSelected();
                clearDetailLayout();
                updateDetailPawn(_pawnChosen);
            }
            else{
                this->_isSelected = false;
                _x = _player->getPawn(_pawnChosen)->getX();
                _y = _player->getPawn(_pawnChosen)->getY();
                ui->openGLWidget->setSelected();
                clearDetailTarget();
                clearDetailLayout();
                updateDetailPawn(_pawnChosen);
            }
        }
        break;
    }
}

/**
 * @brief ViewGame::deleteTimer
 */
void ViewGame::deleteTimer()
{
    delete time;
    _play = false;
}

/**
 * @brief ViewGame::~ViewGame : Destructeur
 */
ViewGame::~ViewGame()
{
    delete ui->openGLWidget;
    delete ui;

}
