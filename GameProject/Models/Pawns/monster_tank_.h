#ifndef MONSTRE_TANK__H
#define MONSTRE_TANK__H

#include "Models/Pawns/pawn.h"

/**
 * @brief The Monster_TANK_ class
 */
class Monster_TANK_ : public Pawn
{
public:
    Monster_TANK_();
    Monster_TANK_(const Monster_TANK_ &monstre);
    Monster_TANK_(const int &X, const int &Y, const bool &good);
    ~Monster_TANK_();

    /**
     * @brief clone
     * @return l'objet clôné
     */
    std::shared_ptr<Pawn> clone() const override
    {
        return std::make_shared<Monster_TANK_>(*this);
    }

    unsigned int getType() const override;
};

#endif // MONSTRE_TANK__H
