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

    connect(&_game, &Game::endOfTurn, this, &GameManagment::game);
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

    //std::cout << _game << std::endl;

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

   // _game.setSlot(0, 9, getPlayerEnemy()->getPion(0));
    //_game.setSlot(2, 9, getPlayerEnemy()->getPion(1));
    //_game.setSlot(4, 9, getPlayerEnemy()->getPion(2));
    //_game.setSlot(6, 9, getPlayerEnemy()->getPion(3));

    //std::cout << "Début de la game !" << std::endl;
    //int tour(0);

    std::shared_ptr<Player> player;
    //std::shared_ptr<Pawn> pawnAdv = nullptr;
    //while (!_game.gameEnded()) {
        _tours++;
        player = (_tours%2) ? _player2 : _player;
        _mutex.unlock();

       // std::cout << player->player() << std::endl;

       //QVector<std::shared_ptr<Pawn>> pawns = player->getListPionsGame();

        //if (player->player()) {

           //std::cout << "Un tour qui se joue !" << std::endl << "Voici vos joueurs disponibles :" << std::endl;
            //for (int i(0); i < pawns.size(); i++)
            //{
              //  std::cout << i+1 << " - " << pawns[i] << std::endl;
            //}

            //int c(1);

            //do {
                //std::cout << "Quel est votre choix ?" << std::endl;
              //  std::cin >> c;
            //} while (c <= 0 || c > pawns.size());

           // _pawn = pawns[c-1];

            //emit YouPlay();
            //std::cout << "player play";

        //} else {
            //std::cout << "L'adversaire joue..." << std::endl;
          //  _pawn = pawns[rand()%pawns.size()];
        //}

        //pawnAdv = _pawn;
        if(player->player()) emit YouPlay();

        Position pTemp;

        std::thread thread_game(&Player::play,
                               player,
                               _game,
                               std::ref(pTemp),
                               std::ref(_mutex),
                               std::ref(_pos));

        if (player->player()) {
            for (auto temps = std::chrono::system_clock::now() + std::chrono::seconds(TIME_ROUND_PLAYER); std::chrono::system_clock::now() < temps;)
                if (!player->hasPlayed()) break;
        } else std::this_thread::sleep_for(std::chrono::seconds(TIME_ROUND_ADV));

        _pawn = _game.getBoard()[pTemp._y][pTemp._x];

        bool erreur = false;

        if (!_mutex.try_lock()) {
            std::cerr << "Mutex non rendu !" << std::endl;
            erreur = 1;
        } else if (player->hasPlayed()) {
            std::cerr << "Vous n'avez pas joué votre tour à temps. C'est à l'adversaire de play." << std::endl;
            erreur = 1;
        }

        thread_game.detach();

        player->setPlayed();

        if (!erreur) _game.play(player->player(), _pawn, _pos); // A REVOIR

        //std::cout << _game << std::endl;
    //}


    // if (_game.getGameState() != STATE_GAME::DRAW) emit endOfTurn();
     //else if (_game.getGameState() != STATE_GAME::END_1) emit endOfTurn();
     //else if (_game.getGameState() != STATE_GAME::END_2) emit endOfTurn();
     //else std::cout << "YOU WIN"; // Code erreur


    // Fin de game en cas de victoire simple d'un Player
    //if (_game.getGameState() == STATE_GAME::DRAW) return 0;
    //else if (_game.getGameState() == STATE_GAME::END_1) return 1;
    //else if (_game.getGameState() == STATE_GAME::END_2) return -1;
    //else return -2; // Code erreur

}

void GameManagment::startGame()
{
    _game.setSlot(0, 9, getPlayerEnemy()->getPion(0));
    _game.setSlot(2, 9, getPlayerEnemy()->getPion(1));
    _game.setSlot(4, 9, getPlayerEnemy()->getPion(2));
    _game.setSlot(6, 9, getPlayerEnemy()->getPion(3));

    std::cout << "Début de la game !" << std::endl;

    game();
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


void GameManagment::ViewGameRejected()
{
    this->_player->ViewRejected();
    this->_player2->ViewRejected();
}


int GameManagment::MaxX(std::shared_ptr<Pawn> p) const
{
    int maxValue = p->getX();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p)){
        if(maxValue < pos._x) maxValue = pos._x;
    }

    return maxValue;
}

int GameManagment::MinX(std::shared_ptr<Pawn> p) const
{
    int minValue = p->getX();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p)){
        if(minValue > pos._x) minValue = pos._x;
    }

    return minValue;
}

int GameManagment::MaxY(std::shared_ptr<Pawn> p) const
{
    int maxValue = p->getY();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p)){
        if(maxValue < pos._y) maxValue = pos._y;
    }

    return maxValue;
}

int GameManagment::MinY(std::shared_ptr<Pawn> p) const
{
    int minValue = p->getY();
    for(auto pos : getPlayer()->pawnsPossibles(_game, p)){
        if(minValue > pos._y) minValue = pos._y;
    }

    return minValue;
}

bool GameManagment::IsInPawnPossible(Position p, std::shared_ptr<Pawn> m) const
{
    for(auto pos : getPlayer()->pawnsPossibles(_game, m)){
        if(pos._x == p._x && pos._y == p._y) return true;
    }
    return false;
}

void GameManagment::UpdateBoard(PositionPawn PP)
{
    getPlayer()->getPion(PP._Pawn)->setX(PP._x);
    getPlayer()->getPion(PP._Pawn)->setY(PP._y);
    _game.setSlot(PP._x, PP._y, getPlayer()->getPion(PP._Pawn));
}

