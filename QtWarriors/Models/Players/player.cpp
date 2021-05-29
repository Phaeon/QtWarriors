#include "player.h"

/**
 * @brief Player::Player : Instancie un joueur
 * @param player : true (premier), false (deuxième)
 */
Player::Player(const bool &player)
    : _player(player), _listPawns(), _posPawn(), _isValid(false)
{}

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
            if (game.getBoard()[y][x] == p && (p->getType() &~ 1) != 0) pawns.push_back(pos);
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

/**
 * @brief Player::getTargets
 * @param game
 * @param p
 * @return l'ensemble des
 */
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
 * @brief Player::getTargetsNull
 * @param game
 * @param pp : Position de départ
 * @param rad : Rayon
 * @return l'ensemble des pions adverses accessibles à partir d'une case nulle
 */
QVector<std::shared_ptr<Pawn> > Player::getTargetsNull(Game game, Position pp, int rad)
{
    QVector<std::shared_ptr<Pawn>> pawns;
    std::shared_ptr<Pawn> pion;

    int deb_X = (pp._x - rad <= 0) ? 0 : pp._x - rad;
    int fin_X = (pp._x + rad >= WIDTH_BOARD - 1) ? WIDTH_BOARD - 1 : pp._x + rad;

    int radius = (pp._x - rad >= 0) ? 0 : abs(pp._x - rad);
    bool left = true;

    for (int x(deb_X); x <= fin_X; x++)
    {
        int deb_Y = (pp._y - radius <= 0) ? 0 : pp._y - radius;
        int fin_Y = (pp._y + radius >= HEIGHT_BOARD - 1) ? HEIGHT_BOARD - 1 :pp._y + radius;

        for(int y(deb_Y); y <= fin_Y; y++)
        {
            if ((y == pp._y && x == pp._x)) continue;

            pion = game.getBoard()[y][x];

            if (!pion) pawns.push_back(pion);
        }

        if (x == pp._x) left = false;
        (left) ? radius++ : radius--;
    }

    return pawns;
}

/**
 * @brief Player::addPawn : Ajoute un pion à la liste des pions du jeu
 * @param p : Pion à ajouter
 */
void Player::addPawn(std::shared_ptr<Pawn> p)
{
    this->_listPawns.push_back(std::move(p));
}

/**
 * @brief Player::removePawn :
 * @param p : Pion à effacer
 */
void Player::removePawn(std::shared_ptr<Pawn> p)
{
    for(auto i = _listPawns.begin() ; i != _listPawns.end() ; ++i){
        if((*i) == p){
            _listPawns.erase(i);
            return;
        }
    }
}

/**
 * @brief Player::ViewRejected : Vide la liste des pions du jeu
 */
void Player::viewRejected()
{
    this->_listPawns.clear();
}

/**
 * @brief Player::getPawns
 * @return la liste des pions du joueur
 */
QVector<std::shared_ptr<Pawn>> Player::getPawns() const
{
    return this->_listPawns;
}

/**
 * @brief Player::getPawn : Récupère un pion à un certain index
 * @param index
 * @return le pion à l'index index
 */
std::shared_ptr<Pawn> Player::getPawn(int index) const
{
    return this->_listPawns.at(index);
}

/**
 * @brief Player::isValid
 * @return si un joueur à joué.
 */
bool Player::isValid() const
{
    return this->_isValid;
}

/**
 * @brief Player::setValid
 * @param valid
 */
void Player::setValid(bool valid)
{
    this->_isValid = valid;
}

/**
 * @brief Player::setPosPawn : Mets à jour la structure PositionPawn
 * @param p
 */
void Player::setPosPawn(PositionPawn p)
{
    _posPawn = p;
}

