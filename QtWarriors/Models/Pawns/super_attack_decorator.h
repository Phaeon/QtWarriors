#ifndef SUPER_ATTACK_DECORATOR_H
#define SUPER_ATTACK_DECORATOR_H

#include "powerdecorator.h"

/**
 * @brief The Super_Attack_Decorator class
 */
class Super_Attack_Decorator : public Power_Decorator
{
public:
    Super_Attack_Decorator();
    Super_Attack_Decorator(std::shared_ptr<Pawn>);
    Super_Attack_Decorator(const Super_Attack_Decorator &);
    ~Super_Attack_Decorator();

    void super_attack(std::shared_ptr<Pawn> target);
};

#endif // SUPER_ATTACK_DECORATOR_H
