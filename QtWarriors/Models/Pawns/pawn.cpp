#include "pawn.h"

/**
 * @brief Pawn::Pawn : Constructeur par défaut
 */
Pawn::Pawn()
    : _posX(0), _posY(0), _state(STATE_PAWN::DEAD), _life(0)
{}

/**
 * @brief Pawn::Pawn : Instancie un pion
 * @param X : Position X
 * @param Y : Position Y
 * @param good : Gentil
 * @param maxlife : Vies maximales
 * @param attack : Attaque
 * @param defence : Défense
 * @param moveRadius : Périmètre de déplacement
 * @param attackRadius : Périmètre d'attaque
 */
Pawn::Pawn(const int &X, const int &Y, const bool &good,
           const int &maxlife,
           const int &attack, const int &defence,
           const int &moveRadius, const int &attackRadius,
           const std::shared_ptr<PawnGL> &pawn3D)
    : _posX(X), _posY(Y), _good(good), _state(STATE_PAWN::ALIVE),
      _maxLife(maxlife), _life(maxlife),
      _attack(attack), _defence(defence), _moveRadius(moveRadius), _attackRadius(attackRadius),
      _3d(std::move(pawn3D)),
      _specialUsed(false)
{}

/**
 * @brief Pawn::Pawn : Constructeur par recopie
 * @param p : Instance à copier
 */
Pawn::Pawn(const Pawn &p)
    : _posX(p._posX), _posY(p._posY), _good(p._good), _state(p._state), _3d(p._3d)
{}

/**
 * @brief Pawn::~Pawn : Destructeur
 */
Pawn::~Pawn()
{}

/**
 * @brief Pawn::getX
 * @return la position X
 */
int Pawn::getX() const
{
    return _posX;
}

/**
 * @brief Pawn::getY
 * @return la position Y
 */
int Pawn::getY() const
{
    return _posY;
}

/**
 * @brief Pawn::getLife
 * @return le nombre de vies en cours
 */
int Pawn::getLife() const
{
    return _life;
}

/**
 * @brief Pawn::setX : Redéfinit la position X
 * @param X : Nouvelle coordonnée
 */
void Pawn::setX(const int &X)
{
    _posX = X;
}

/**
 * @brief Pawn::setY : Redéfinit la position Y
 * @param Y : Nouvelle coordonnée
 */
void Pawn::setY(const int &Y)
{
    _posY = Y;
}

/**
 * @brief Pawn::setLife : Redéfinit les vies
 * @param life : Nouvelle valeur
 */
void Pawn::setLife(const float &life) {
    _life = life;
}

/**
 * @brief Pawn::setDefence : Redéfinit la défence
 * @param defence : Nouvelle valeur
 */
void Pawn::setDefence(const int &defence)
{
    _defence = defence;
}

/**
 * @brief Pawn::getMaxLife
 * @return le nombre maximal de vies
 */
int Pawn::getMaxLife() const
{
    return _maxLife;
}

/**
 * @brief Pawn::getAttackRadius
 * @return le périmètre d'attaque
 */
int Pawn::getAttackRadius() const
{
    return _attackRadius;
}

/**
 * @brief Pawn::getMoveRadius
 * @return le périmètre de déplacement
 */
int Pawn::getMoveRadius() const
{
    return _moveRadius;
}

/**
 * @brief Pawn::getAttack
 * @return l'attaque
 */
int Pawn::getAttack() const
{
    return _attack;
}

/**
 * @brief Pawn::getDefence
 * @return la défense
 */
int Pawn::getDefence() const
{
    return _defence;
}

// Modifier pour prendre en compte la défense
/**game.getBoard()[_posPawn._y][_posPawn._x]
 * @brief Pawn::receiveAttack : Reçoit une attaque
 * @param damages : Attaque reçue
 */
void Pawn::receiveAttack(const float &damages) {
    if (_defence > damages)
        _life = (_life - damages + (_defence/damages) <= 0) ? 0 : _life - damages + (_defence/damages);
    else
        _life = (_life - damages + (damages/_defence) <= 0) ? 0 : _life - damages + (damages/_defence);
}

/**
 * @brief Pawn::sendAttack : Infliger une attaque
 * @param p : Pion attaqué
 */
void Pawn::sendAttack(std::shared_ptr<Pawn> p) {
    p->receiveAttack(getAttack());
}

/**
 * @brief Pawn::isDead
 * @return si le pion est mort
 */
bool Pawn::isDead() const {
    return (getLife() == 0);
}

bool Pawn::isAttacking() const
{
    return _attacking;
}

void Pawn::attacking()
{
    _attacking = (_attacking) ? false : true;
}

bool Pawn::specialAttackUsed() const
{
    return _specialUsed;
}

void Pawn::hasBeenUsed()
{
    _specialUsed = true;
}

/**
 * @brief Pawn::getState
 * @return l'état du pion
 */
STATE_PAWN Pawn::getState() const
{
    return _state;
}

/**
 * @brief Pawn::setState : Redéfinit l'état du pion
 * @param state : Nouvel état
 */
void Pawn::setState(const STATE_PAWN &state)
{
    _state = state;
}

/**
 * @brief Pawn::isGood
 * @return si le pion est de notre côté ou pas
 */
bool Pawn::isGood() const {
    return _good;
}

std::shared_ptr<PawnGL> Pawn::get3DPawn() const
{
    return _3d;
}


/**
 * @brief Pawn::getName
 * @return le nom du pion sous forme de texte
 */
QString Pawn::getName() const
{
  switch (this->getType()) {
    case WARRIOR:
        return "Warrior";
    case WIZARD:
        return "Wizard";
    case ROGUE:
        return "Rogue";
    case TANK:
        return "Tank";
    default:
        break;
  }

  return "";
}

/**
 * @brief operator <<
 * @param flux : Type de flux
 * @param p : Pion à afficher
 * @return un stream
 */
std::ostream& operator<<(std::ostream &flux, std::shared_ptr<Pawn> p) {
    switch (p->getType()) {
    case WARRIOR:
        flux << "Guerrier";
        break;
    case WIZARD:
        flux << "Sorcier";
        break;
    case ROGUE:
        flux << "Assassin";
        break;
    case TANK:
        flux << "Tank";
        break;
    default:
        break;
    }

    flux << " : (" << p->getX() << ", " << p->getY() << ") - " << p->getLife() << " life";
    return flux;
}
