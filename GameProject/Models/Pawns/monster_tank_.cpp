#include "monster_tank_.h"

/**
 * @brief Monster_TANK_::Monster_TANK_ : Constructeur par recopie
 */
Monster_TANK_::Monster_TANK_()
{}

/**
 * @brief Monster_TANK_::Monster_TANK_ : Instancie un tank
 * @param X : Position X
 * @param Y : Position Y
 * @param good : Gentil
 */
Monster_TANK_::Monster_TANK_(const int &X, const int &Y, const bool &good)
    : Pawn(X, Y, good, LIFE_TANK, ATTACK_TANK, DEFENCE_TANK, MOVE_RADIUS_TANK, ATTACK_RADIUS_TANK)
{}

/**
 * @brief Monster_TANK_::Monster_TANK_ : Constructeur par recopie
 * @param monstre : Instance à copier
 */
Monster_TANK_::Monster_TANK_(const Monster_TANK_ &monstre)
    : Pawn(monstre.getX(), monstre.getY(), monstre.isGood(),
           monstre.getMaxLife(),
           monstre.getAttack(), monstre.getDefence(),
           monstre.getMoveRadius(), monstre.getAttackRadius())
{}

/**
 * @brief Monster_TANK_::~Monster_TANK_ : Destructeur
 */
Monster_TANK_::~Monster_TANK_()
{}

/**
 * @brief Monster_TANK_::getType
 * @return le type du monstre
 */
unsigned int Monster_TANK_::getType() const
{
    return TANK;
}
