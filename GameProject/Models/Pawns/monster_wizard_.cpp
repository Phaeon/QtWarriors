#include "monster_wizard_.h"

/**
 * @brief Monster_WIZARD_::Monster_WIZARD_ : Constructeur par défaut
 */
Monster_WIZARD_::Monster_WIZARD_()
{}

/**
 * @brief Monster_WIZARD_::Monster_WIZARD_ : Instancie un sorcier
 * @param X : Position X
 * @param Y : Position Y
 * @param good : Gentil
 */
Monster_WIZARD_::Monster_WIZARD_(const int &X, const int &Y,const bool &good)
    : Pawn(X, Y, good, LIFE_WIZARD, ATTACK_WIZARD, DEFENCE_WIZARD, MOVE_RADIUS_WIZARD, ATTACK_RADIUS_WIZARD)
{}

/**
 * @brief Monster_WIZARD_::Monster_WIZARD_ : Constructeur par recopie
 * @param monstre : Instance à copier
 */
Monster_WIZARD_::Monster_WIZARD_(const Monster_WIZARD_ &monstre)
    : Pawn(monstre.getX(), monstre.getY(), monstre.isGood(),
           monstre.getMaxLife(),
           monstre.getAttack(), monstre.getDefence(),
           monstre.getMoveRadius(), monstre.getAttackRadius())
{}

/**
 * @brief Monster_WIZARD_::~Monster_WIZARD_ : Destructeur
 */
Monster_WIZARD_::~Monster_WIZARD_()
{}

/**
 * @brief Monster_WIZARD_::getType
 * @return le type du monstre
 */
unsigned int Monster_WIZARD_::getType() const {
    return WIZARD;
}

