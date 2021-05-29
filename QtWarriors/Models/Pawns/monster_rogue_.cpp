#include "monster_rogue_.h"

/**
 * @brief Monster_ROGUE_::Monster_ROGUE_ : Constructeur par défaut
 */
Monster_ROGUE_::Monster_ROGUE_()
{}

/**
 * @brief Monster_ROGUE_::Monster_ROGUE_ : Instancie un assassin
 * @param X : Position X
 * @param Y : Position Y
 * @param good : Gentil
 */
Monster_ROGUE_::Monster_ROGUE_(const int &X, const int &Y, const bool &good)
    : Pawn(X, Y, good,
           LIFE_ROGUE, ATTACK_ROGUE, DEFENCE_ROGUE, MOVE_RADIUS_ROGUE, ATTACK_RADIUS_ROGUE,
           std::make_shared<Rogue_3D_>(X, 0, Y, (good) ? 1 : 2, 0, (good) ? 180 : 0, 0, good))
{}

/**
 * @brief Monster_ROGUE_::Monster_ROGUE_ : Constructeur par recopie
 * @param monstre : Instance à copier
 */
Monster_ROGUE_::Monster_ROGUE_(const Monster_ROGUE_ &monstre)
    : Pawn(monstre.getX(), monstre.getY(), monstre.isGood(),
           monstre.getMaxLife(),
           monstre.getAttack(), monstre.getDefence(),
           monstre.getMoveRadius(), monstre.getAttackRadius(),
           monstre.get3DPawn())
{}

/**
 * @brief Monster_ROGUE_::getType
 * @return le type du monstre
 */
unsigned int Monster_ROGUE_::getType() const
{
    return ROGUE;
}
