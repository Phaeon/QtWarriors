#include "monster_warrior_.h"

/**
 * @brief Monster_WARRIOR_::Monster_WARRIOR_ : Constructeur par défaut
 */
Monster_WARRIOR_::Monster_WARRIOR_()
{}

/**
 * @brief Monster_WARRIOR_::Monster_WARRIOR_ : Instancie un guerrier
 * @param X : Position X
 * @param Y : Position y
 * @param good : Gentil
 */
Monster_WARRIOR_::Monster_WARRIOR_(const int &X, const int &Y, const bool &good)
    : Pawn(X, Y, good,
           LIFE_WARRIOR, ATTACK_WARRIOR, DEFENCE_WARRIOR, MOVE_RADIUS_WARRIOR, ATTACK_RADIUS_WARRIOR,
           std::make_shared<Warrior_3D_>(X, 0, Y, (good) ? 1 : 2, 0, (good) ? 180 : 0, 0))
{}

/**
 * @brief Monster_WARRIOR_::Monster_WARRIOR_ : Constructeur par recopie
 * @param monstre : Instance à copier
 */
Monster_WARRIOR_::Monster_WARRIOR_(const Monster_WARRIOR_ &monstre)
    : Pawn(monstre.getX(), monstre.getY(), monstre.isGood(),
           monstre.getMaxLife(),
           monstre.getAttack(), monstre.getDefence(),
           monstre.getMoveRadius(), monstre.getAttackRadius(),
           monstre.get3DPawn())
{}

/**
 * @brief Monster_WARRIOR_::~Monster_WARRIOR_ : Destructeur
 */
Monster_WARRIOR_::~Monster_WARRIOR_()
{}

/**
 * @brief Monster_WARRIOR_::getType
 * @return le type du monstre
 */
unsigned int Monster_WARRIOR_::getType() const
{
    return WARRIOR;
}
