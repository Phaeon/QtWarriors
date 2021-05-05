#ifndef INVISIBILITY_DECORATOR_H
#define INVISIBILITY_DECORATOR_H

#include "powerdecorator.h"

/**
 * @brief The Invisibility_Decorator class
 */
class Invisibility_Decorator : public Power_Decorator
{
private:
    bool _invisible; // Est invisible ou non

public:
    Invisibility_Decorator();
    Invisibility_Decorator(std::shared_ptr<Pawn>);
    Invisibility_Decorator(const Invisibility_Decorator &);
    ~Invisibility_Decorator();
};

#endif // INVISIBILITY_DECORATOR_H
