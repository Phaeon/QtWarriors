#include "super_defence_decorator.h"

/**
 * @brief Super_Defence_Decorator::Super_Defence_Decorator : Constructeur par défaut
 */
Super_Defence_Decorator::Super_Defence_Decorator()
    : Power_Decorator()
{}

/**
 * @brief Super_Defence_Decorator::Super_Defence_Decorator : Décore le pion
 * @param pawn : Pion à décorer
 */
Super_Defence_Decorator::Super_Defence_Decorator(std::shared_ptr<Pawn> pawn)
    : Power_Decorator(pawn)
{}

/**
 * @brief Super_Defence_Decorator::Super_Defence_Decorator : Constructeur par recopie
 * @param dec : Instance à copier
 */
Super_Defence_Decorator::Super_Defence_Decorator(const Super_Defence_Decorator &dec)
    : Super_Defence_Decorator(dec._pawn)
{}

/**
 * @brief Super_Defence_Decorator::~Super_Defence_Decorator : Destructeur
 */
Super_Defence_Decorator::~Super_Defence_Decorator()
{}

/**
 * @brief Super_Defence_Decorator::super_defence : Augmente temporairement la défense du pion
 */
void Super_Defence_Decorator::super_defence(const bool &hasBeen)
{
    (hasBeen) ? _pawn->setDefence(_pawn->getDefence() / DEFENSE_AMPLIFIER) :
                _pawn->setDefence(_pawn->getDefence() * DEFENSE_AMPLIFIER);
}
