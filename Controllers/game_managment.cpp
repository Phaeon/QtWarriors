#include "game_managment.h"

bool GameManagment::_firstPlayer(rand()%2);
int GameManagment::_tours(0);

/**
 * @brief GameManagment::GameManagment : Instancie un jeu
 */
GameManagment::GameManagment()
    : _game(), _pawn(), _pos(), _mutex()
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
    _mutex.unlock();

    if(_game.gameEnded()) emit endGame(_game.getGameState());
    else
    {
        if(player->player())
        {
            emit youPlay();
        }
        else
        {
            player->play(_game, std::ref(_pTemp), std::ref(_mutex), std::ref(_pos), _difficulty);

            _pawn = _game.getBoard()[_pTemp._y][_pTemp._x];

            _game.play(player->player(), _pawn, _pos);

            for (auto i : getPlayer()->getListPionsGame())
                if (i->isDead()) getPlayer()->removeListPionGame(i);
            emit nextTurn();

        }
    }
}

void GameManagment::endOfTreatment()
{
    if(getPlayer()->getValid()){
        Position pos;

        pos = getPlayer()->search_next_shot(_game, _pTemp, _difficulty);
        _pawn = _game.getBoard()[_pTemp._y][_pTemp._x];
        _game.play(getPlayer()->player(), _pawn, pos);

        for (auto i : getPlayerEnemy()->getListPionsGame())
            if (i->isDead()) getPlayerEnemy()->removeListPionGame(i);

        getPlayer()->setValid(false);
    }
    emit boardCanMove();
}

void GameManagment::startGame()
{
    _game.setSlot(0, 9, getPlayerEnemy()->getPion(0));
    _game.setSlot(2, 9, getPlayerEnemy()->getPion(1));
    _game.setSlot(4, 9, getPlayerEnemy()->getPion(2));
    _game.setSlot(6, 9, getPlayerEnemy()->getPion(3));

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
 * @brief GameManagment::getPlayerEnemy
 * @return le joueur adverse
 */
std::shared_ptr<Player> GameManagment::getPlayerEnemy() const
{
    return (_firstPlayer) ? this->_player2 : this->_player;
}

int GameManagment::getTour() const
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
 * @brief GameManagment::addListPionGame : Ajoute un pion à la liste des pions d'un joueur
 * @param p : Pion à ajouter
 */
void GameManagment::addListPionGame(std::shared_ptr<Pawn> p)
{
    (_firstPlayer) ? this->_player->addListPionGame(p) : this->_player2->addListPionGame(p);
}

/**
 * @brief GameManagment::removeListPionGame : Supprime un pion de la liste des pions d'un joueur
 * @param p : Pion à supprimer
 */
void GameManagment::removeListPionGame(std::shared_ptr<Pawn> p)
{
    (_firstPlayer) ? this->_player->removeListPionGame(p) : this->_player2->removeListPionGame(p);
}


void GameManagment::viewGameRejected()
{
    this->_player->viewRejected();
    this->_player2->viewRejected();
}

void GameManagment::setDifficulte(Difficulty _diff)
{
    this->_difficulty = _diff;
}


int GameManagment::maxX(std::shared_ptr<Pawn> p) const
{
    int maxValue = p->getX();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(maxValue < pos._x) maxValue = pos._x;

    return maxValue;
}

int GameManagment::minX(std::shared_ptr<Pawn> p) const
{
    int minValue = p->getX();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(minValue > pos._x) minValue = pos._x;

    return minValue;
}

int GameManagment::maxY(std::shared_ptr<Pawn> p) const
{
    int maxValue = p->getY();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(maxValue < pos._y) maxValue = pos._y;

    return maxValue;
}

int GameManagment::minY(std::shared_ptr<Pawn> p) const
{
    int minValue = p->getY();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p))
        if(minValue > pos._y) minValue = pos._y;

    return minValue;
}

bool GameManagment::isInPawnPossible(Position p, std::shared_ptr<Pawn> m) const
{
    for(auto pos : getPlayer()->pawnsPossibles(_game, m))
        if (pos._x == p._x && pos._y == p._y) return true;

    return false;
}

void GameManagment::updateBoard(PositionPawn pp)
{
    getPlayer()->getPion(pp._pawn)->setX(pp._x);
    getPlayer()->getPion(pp._pawn)->setY(pp._y);
    _game.setSlot(pp._x, pp._y, getPlayer()->getPion(pp._pawn));
}

