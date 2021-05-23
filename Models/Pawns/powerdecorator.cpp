#include "powerdecorator.h"

/**
 * @brief Power_Decorator::Power_Decorator : Constructeur par défaut
 */
Power_Decorator::Power_Decorator()
{}

/**
 * @brief Power_Decorator::Power_Decorator : Décore un pion
 * @param pion : Pion à décorer
 */
Power_Decorator::Power_Decorator(std::shared_ptr<Pawn> pion)
    : _pawn(std::move(pion))
{}

/**
 * @brief Power_Decorator::Power_Decorator : Constructeur par recopie
 * @param pow : Instance à copier
 */
Power_Decorator::Power_Decorator(const Power_Decorator &pow)
    : _pawn(pow._pawn)
{}

/**
 * @brief Power_Decorator::~Power_Decorator : Destructeur
 */
Power_Decorator::~Power_Decorator()
{}

/**
 * @brief Power_Decorator::clone : Clône une instance de Power_Decorator
 * @return un clône
 */
std::shared_ptr<Pawn> Power_Decorator::clone() const
{
    return std::make_shared<Power_Decorator>(*this);
}

/**
 * @brief Power_Decorator::getType
 * @return le type du pion
 */
unsigned int Power_Decorator::getType() const
{
    return _pawn->getType();
}
