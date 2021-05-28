#include "game_managment.h"


/**
 * @brief GameManagment::GameManagment : Instancie un jeu
 */
GameManagment::GameManagment()
    : _game(), _firstPlayer(rand()%2), _tours(0)
{
    GameManagment::initialisation();

    connect(this, &GameManagment::nextTurn, this, &GameManagment::game);
}

/**
 * @brief GameManagment::~GameManagment : Destructeur
 */
GameManagment::~GameManagment()
{}

/**
 * @brief GameManagment::initialisation : Initialise une partie
 */
void GameManagment::initialisation()
{
    _player = nullptr;
    _player2 = nullptr;

    _game.reset();

    if (_firstPlayer) {
        _player = std::make_shared<Player_PHYSICAL>(true);
        _player2 = std::make_shared<Player_IA>(false);
    } else {
        _player = std::make_shared<Player_IA>(true);
        _player2 = std::make_shared<Player_PHYSICAL>(false);
    }

}

/**
 * @brief GameManagment::game : Lance une partie
 * @return le résultat de la partie
 */
void GameManagment::game()
{
    std::shared_ptr<Player> player;
    _tours++;
    player = (_tours%2) ? _player2 : _player;

    if(_game.gameEnded()) emit endGame(_game.getGameState());
    else
    {
        if(player->player())
        {
            delete _time;
            emit youPlay();
        }
        else
        {
            _time = new QTimer(this);
            connect(_time, &QTimer::timeout, this, &GameManagment::IAPlay);
            _time->start(2000);

        }

        // Vérifier si des pions ont activés leurs capacités
        for (auto i : player->pawnsPlayer(_game, !player->player()))
        {
            if (i->specialAttackUsed()
                    && (i->getType() &~ 8) == 0)
            {
                std::shared_ptr<Super_Defence_Decorator> s_defence = std::make_shared<Super_Defence_Decorator>(i);
                auto temp_pawn = std::dynamic_pointer_cast<Monster_TANK_>(i);

                // Faire revenir la défense à son état d'origine.
                s_defence->super_defence(temp_pawn->isBoosted());
                temp_pawn->setBoosted();
            }
        }
    }
}

void GameManagment::IAPlay()
{
    getEnemy()->play(_game, _difficulty);

    for (auto i : getPlayer()->getPawns())
        if (i->isDead()) getPlayer()->removePawn(i);
    emit nextTurn();
}

void GameManagment::endOfTreatment()
{
    if(getPlayer()->isValid()){

        getPlayer()->play(_game, _difficulty);

        for (auto i : getEnemy()->getPawns())
            if (i->isDead()) getEnemy()->removePawn(i);

        getPlayer()->setValid(false);
    }
    emit nextTurn();
}

void GameManagment::startGame()
{
    _game.setSlot(0, 9, getEnemy()->getPawn(0));
    _game.setSlot(2, 9, getEnemy()->getPawn(1));
    _game.setSlot(4, 9, getEnemy()->getPawn(2));
    _game.setSlot(6, 9, getEnemy()->getPawn(3));

    game();

    _timeStart = QDateTime::currentDateTime().toString("hh:mm:ss AP dd/MM/yyyy");
}

/**
 * @brief GameManagment::getPlayer
 * @return le joueur physique
 */
std::shared_ptr<Player> GameManagment::getPlayer() const
{
    return (_firstPlayer) ? this->_player : this->_player2;
}

/**
 * @brief GameManagment::getEnemy
 * @return le joueur adverse
 */
std::shared_ptr<Player> GameManagment::getEnemy() const
{
    return (_firstPlayer) ? this->_player2 : this->_player;
}

int GameManagment::getTours() const
{
    return _tours;
}

QString GameManagment::getTime() const
{
    return _timeStart;
}

/**
 * @brief GameManagment::getGame
 * @return le jeu
 */
Game GameManagment::getGame() const
{
    return _game;
}

/**
 * @brief GameManagment::addPawn : Ajoute un pion à la liste des pions d'un joueur
 * @param p : Pion à ajouter
 */
void GameManagment::addPawn(std::shared_ptr<Pawn> p)
{
    (_firstPlayer) ? this->_player->addPawn(p) : this->_player2->addPawn(p);
}

/**
 * @brief GameManagment::removePawn : Supprime un pion de la liste des pions d'un joueur
 * @param p : Pion à supprimer
 */
void GameManagment::removePawn(std::shared_ptr<Pawn> p)
{
    (_firstPlayer) ? this->_player->removePawn(p) : this->_player2->removePawn(p);
}

/**
 * @brief GameManagment::viewGameRejected : Remets à zéro les listes de pions
 */
void GameManagment::viewGameRejected()
{
    this->_player->viewRejected();
    this->_player2->viewRejected();
}

/**
 * @brief GameManagment::setDifficulty
 * @param _diff
 */
void GameManagment::setDifficulty(Difficulty _diff)
{
    this->_difficulty = _diff;
}

/**
 * @brief GameManagment::maxX
 * @param p
 * @return la position maximale possible sur X
 */
int GameManagment::maxX(std::shared_ptr<Pawn> p) const
{
    int maxValue = p->getX();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(maxValue < pos._x) maxValue = pos._x;

    return maxValue;
}

/**
 * @brief GameManagment::minX
 * @param p
 * @return la position minimale possible sur X
 */
int GameManagment::minX(std::shared_ptr<Pawn> p) const
{
    int minValue = p->getX();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(minValue > pos._x) minValue = pos._x;

    return minValue;
}

/**
 * @brief GameManagment::maxY
 * @param p
 * @return la position maximale possible sur Y
 */
int GameManagment::maxY(std::shared_ptr<Pawn> p) const
{
    int maxValue = p->getY();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(maxValue < pos._y) maxValue = pos._y;

    return maxValue;
}

/**
 * @brief GameManagment::minY
 * @param p
 * @return la position minimale possible sur Y
 */
int GameManagment::minY(std::shared_ptr<Pawn> p) const
{
    int minValue = p->getY();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(minValue > pos._y) minValue = pos._y;

    return minValue;
}

/**
 * @brief GameManagment::containsPosition
 * @param p
 * @param m
 * @return vrai si la position fait parti des pions accessibles du pion m
 */
bool GameManagment::containsPosition(Position p, std::shared_ptr<Pawn> m) const
{
    for(auto pos : getPlayer()->pawnsPossibles(_game, m))
        if (pos._x == p._x && pos._y == p._y) return true;

    return false;
}

/**
 * @brief GameManagment::updateBoard
 * @param pp
 */
void GameManagment::updateBoard(PositionPawn pp)
{
    getPlayer()->getPawn(pp._pawn)->setX(pp._x);
    getPlayer()->getPawn(pp._pawn)->setY(pp._y);

    _game.setSlot(pp._x, pp._y, getPlayer()->getPawn(pp._pawn));
}

