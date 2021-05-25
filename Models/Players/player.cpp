#include "player.h"

/**
 * @brief Player::Player : Instancie un joueur
 * @param player : true (premier), false (deuxième)
 */
Player::Player(const bool &player)
    : _player(player), _listPionsGame(), _posPawn(), _isValid(false)
{}

/**
 * @brief Player::play : Block le mutex et permet au joueur de choisir son coup
 * @param game : Jeu courant
 * @param pawn : Pion qui joue
 * @param pawn_mutex : Mutex courant
 * @param position : Position de la case choisie
 */
void Player::play(Game game, Position &pawn, std::mutex &pawn_mutex, Position &position, Difficulty _difficulty)
{
    pawn_mutex.lock();
    position = search_next_shot(game, pawn, _difficulty);
    pawn_mutex.unlock();
}

/**
 * @brief Player::player
 * @return le joueur jouant (true : utilisateur, false : IA)
 */
bool Player::player() const {
    return _player;
}

/**
 * @brief Player::setPlayer
 * @param player : Nouvelle valeur de _player
 */
void Player::setPlayer(const bool &player) {
    _player = player;
}

/**
 * @brief Player::pawnsPlayer : Pions du joueur
 * @param game : Jeu courant
 * @return un vecteur contenant les pions du joueur
 */
QVector<std::shared_ptr<Pawn>> Player::pawnsPlayer(Game game, const bool &b)
{
    QVector<std::shared_ptr<Pawn>> pions;

    for (int i(0); i < WIDTH_BOARD; i++)
    {
        auto ligne = game.getBoard()[i];
        for (auto bloc : ligne) {
            if (bloc && b && bloc->isGood()) pions.push_back(bloc);
            else if (bloc && !b && !bloc->isGood()) pions.push_back(bloc);
        }
    }

    return pions;
}

/**
 * @brief Player::pawnsPossibles : Coups possible pour le joueur
 * @param game : Jeu courant
 * @param p : Pion du joueur choisi
 * @return un vecteur contenant les coups possibles (nullptr : case libre, Pion : adversaire ou coéquipier)
 */
QVector<Position> Player::pawnsPossibles(Game game, std::shared_ptr<Pawn> p)
{
    QVector<Position> pawns;
    std::shared_ptr<Pawn> pion;
    Position pos;

    int deb_X = (p->getX() - p->getMoveRadius() <= 0) ? 0 : p->getX() - p->getMoveRadius();
    int fin_X = (p->getX() + p->getMoveRadius() >= WIDTH_BOARD - 1) ? WIDTH_BOARD - 1 : p->getX() + p->getMoveRadius();

    int radius = (p->getX() - p->getMoveRadius() >= 0) ? 0 : abs(p->getX() - p->getMoveRadius());
    bool left = true;

    for (int x(deb_X); x <= fin_X; x++)
    {
        int deb_Y = (p->getY() - radius <= 0) ? 0 : p->getY() - radius;
        int fin_Y = (p->getY() + radius >= HEIGHT_BOARD - 1) ? HEIGHT_BOARD - 1 : p->getY() + radius;

        for(int y(deb_Y); y <= fin_Y; y++)
        {

            pos = {x, y};
            if (game.getBoard()[y][x] == p) pawns.push_back(pos);
            pion = game.getBoard()[y][x];

            if (!pion) pawns.push_back(pos); // Case vide

            else if ((p->isGood() && pion->isGood() && p->getType() == 2) ||
                     (!p->isGood() && !pion->isGood() && p->getType() == 2)) // Coéquipier
                pawns.push_back(pos);

            else if ((p->isGood() && !pion->isGood()) || (!p->isGood() && pion->isGood())) // Adversaire
                pawns.push_back(pos);
        }

        if (x == p->getX()) left = false;
        (left) ? radius++ : radius--;
    }

    return pawns;
}

QVector<std::shared_ptr<Pawn> > Player::getTargets(Game game, std::shared_ptr<Pawn> p)
{
    QVector<std::shared_ptr<Pawn>> pawns;
    std::shared_ptr<Pawn> pion;

    int deb_X = (p->getX() - p->getMoveRadius() <= 0) ? 0 : p->getX() - p->getMoveRadius();
    int fin_X = (p->getX() + p->getMoveRadius() >= WIDTH_BOARD - 1) ? WIDTH_BOARD - 1 : p->getX() + p->getMoveRadius();

    int radius = (p->getX() - p->getMoveRadius() >= 0) ? 0 : abs(p->getX() - p->getMoveRadius());
    bool left = true;

    for (int x(deb_X); x <= fin_X; x++)
    {
        int deb_Y = (p->getY() - radius <= 0) ? 0 : p->getY() - radius;
        int fin_Y = (p->getY() + radius >= HEIGHT_BOARD - 1) ? HEIGHT_BOARD - 1 : p->getY() + radius;

        for(int y(deb_Y); y <= fin_Y; y++)
        {
            pion = game.getBoard()[y][x];

            if (!pion || pion == p) continue;

            if ((p->isGood() && pion->isGood() && p->getType() == 2) ||
                     (!p->isGood() && !pion->isGood() && p->getType() == 2)) // Coéquipier
                pawns.push_back(pion);

            else if ((p->isGood() && !pion->isGood()) || (!p->isGood() && pion->isGood())) // Adversaire
                pawns.push_back(pion);
        }

        if (x == p->getX()) left = false;
        (left) ? radius++ : radius--;
    }

    return pawns;
}

/**
 * @brief Player::addListPionGame : Ajoute un pion à la liste des pions du jeu
 * @param p : Pion à ajouter
 */
void Player::addListPionGame(std::shared_ptr<Pawn> p)
{
    this->_listPionsGame.push_back(std::move(p));
}

/**
 * @brief Player::removeListPionGame :
 * @param p : Pion à effacer
 */
void Player::removeListPionGame(std::shared_ptr<Pawn> p)
{
    for(auto i = _listPionsGame.begin() ; i != _listPionsGame.end() ; ++i){
        if((*i) == p){
            _listPionsGame.erase(i);
            return;
        }
    }
}

/**
 * @brief Player::ViewRejected : Vide la liste des pions du jeu
 */
void Player::viewRejected()
{
    this->_listPionsGame.clear();
}

/**
 * @brief Player::getListPionsGame
 * @return la liste des pions du joueur
 */
QVector<std::shared_ptr<Pawn>> Player::getListPionsGame() const
{
    return this->_listPionsGame;
}

/**
 * @brief Player::getPion : Récupère un pion à un certain index
 * @param index
 * @return le pion à l'index index
 */
std::shared_ptr<Pawn> Player::getPion(int index) const
{
    return this->_listPionsGame.at(index);
}

bool Player::getValid() const
{
    return this->_isValid;
}

void Player::setValid(bool valid)
{
    this->_isValid = valid;
}

void Player::setPosPawn(PositionPawn p)
{
    _posPawn = p;
}
