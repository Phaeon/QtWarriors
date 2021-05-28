#ifndef SUPER_DEFENSE_DECORATOR_H
#define SUPER_DEFENSE_DECORATOR_H

#include "powerdecorator.h"

/**
 * @brief The Super_Defence_Decorator class
 */
class Super_Defence_Decorator : public Power_Decorator
{

public:
    Super_Defence_Decorator();
    Super_Defence_Decorator(std::shared_ptr<Pawn>);
    Super_Defence_Decorator(const Super_Defence_Decorator &);
    ~Super_Defence_Decorator();

    void super_defence(const bool &hasBeen);
};

#endif // SUPER_DEFENSE_DECORATOR_H
