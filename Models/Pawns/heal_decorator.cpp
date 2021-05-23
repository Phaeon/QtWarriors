#include "heal_decorator.h"

/**
 * @brief Heal_Decorator::Heal_Decorator : Constructeur par recopie
 */
Heal_Decorator::Heal_Decorator()
    : Power_Decorator()
{}

/**
 * @brief Heal_Decorator::Heal_Decorator : Décore un pion
 * @param pawn : Pion à décorer
 */
Heal_Decorator::Heal_Decorator(std::shared_ptr<Pawn> pawn)
    : Power_Decorator(pawn)
{}

/**
 * @brief Heal_Decorator::Heal_Decorator : Constructeur par recopie
 * @param dec : Instance à copier
 */
Heal_Decorator::Heal_Decorator(const Heal_Decorator &dec)
    : Heal_Decorator(dec._pawn)
{}

/**
 * @brief Heal_Decorator::~Heal_Decorator : Destructeur
 */
Heal_Decorator::~Heal_Decorator()
{}

/**
 * @brief Heal_Decorator::heal : Appliquer des soins
 */
void Heal_Decorator::heal()
{
    _pawn->setLife((_pawn->getLife() + HEAL_POWER) >= _pawn->getMaxLife() ? _pawn->getMaxLife() : _pawn->getLife() + HEAL_POWER); // A modifier
}
