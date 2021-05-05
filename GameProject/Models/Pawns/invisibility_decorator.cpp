#include "invisibility_decorator.h"

/**
 * @brief Invisibility_Decorator::Invisibility_Decorator : Constructeur par défaut
 */
Invisibility_Decorator::Invisibility_Decorator()
    : Power_Decorator()
{}

/**
 * @brief Invisibility_Decorator::Invisibility_Decorator : Décore un pion
 * @param pawn : Pion à décorer
 */
Invisibility_Decorator::Invisibility_Decorator(std::shared_ptr<Pawn> pawn)
    : Power_Decorator(pawn), _invisible(true)
{}

/**
 * @brief Invisibility_Decorator::Invisibility_Decorator : Constructeur par recopie
 * @param monstre : Instance à copier
 */
Invisibility_Decorator::Invisibility_Decorator(const Invisibility_Decorator &monstre)
    : Invisibility_Decorator(monstre._pawn)
{}

/**
 * @brief Invisibility_Decorator::~Invisibility_Decorator : Destructeur
 */
Invisibility_Decorator::~Invisibility_Decorator()
{}
