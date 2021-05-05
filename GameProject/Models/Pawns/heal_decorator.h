#ifndef HEALDECORATOR_H
#define HEALDECORATOR_H

#include "Models/Pawns/powerdecorator.h"
#include "config.h"

/**
 * @brief The Heal_Decorator class
 */
class Heal_Decorator : public Power_Decorator
{
public:
    Heal_Decorator();
    Heal_Decorator(std::shared_ptr<Pawn>);
    Heal_Decorator(const Heal_Decorator &);
    ~Heal_Decorator();

    void heal();
};

#endif // HEALDECORATOR_H
