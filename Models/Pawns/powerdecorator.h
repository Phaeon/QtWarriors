#ifndef POWERDECORATOR_H
#define POWERDECORATOR_H

#include "Models/Pawns/pawn.h"
#include "config.h"

/**
 * @brief The Power_Decorator class
 */
class Power_Decorator : public Pawn
{
protected:
    std::shared_ptr<Pawn> _pawn; // Pion à décorer
public:
    Power_Decorator();
    Power_Decorator(std::shared_ptr<Pawn>);
    Power_Decorator(const Power_Decorator &);
    ~Power_Decorator();

    std::shared_ptr<Pawn> clone() const override;

    unsigned int getType() const override;
};

#endif // POWERDECORATOR_H
