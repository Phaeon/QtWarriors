#include "super_attack_decorator.h"
#include <iostream>
/**
 * @brief Super_Attack_Decorator::Super_Attack_Decorator : Constructeur par défaut
 */
Super_Attack_Decorator::Super_Attack_Decorator()
    : Power_Decorator()
{}

/**
 * @brief Super_Attack_Decorator::Super_Attack_Decorator : Décore le pion
 * @param pawn : Pion à décorer
 */
Super_Attack_Decorator::Super_Attack_Decorator(std::shared_ptr<Pawn> pawn)
    : Power_Decorator(pawn)
{}

/**
 * @brief Super_Attack_Decorator::Super_Attack_Decorator : Constructeur par recopie
 * @param dec : Instance à copier
 */
Super_Attack_Decorator::Super_Attack_Decorator(const Super_Attack_Decorator &dec)
    : Super_Attack_Decorator(dec._pawn)
{}

/**
 * @brief Super_Attack_Decorator::~Super_Attack_Decorator : Destructeur
 */
Super_Attack_Decorator::~Super_Attack_Decorator()
{}

/*
 * EXAMPLE: Attack doubled for the round
 **/
void Super_Attack_Decorator::super_attack(std::shared_ptr<Pawn> target)
{
    target->receiveAttack(_pawn->getAttack() * 2);
}
