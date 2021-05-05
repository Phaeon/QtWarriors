#ifndef Monster_WARRIOR__H
#define Monster_WARRIOR__H

#include "Models/Pawns/pawn.h"

/**
 * @brief The Monster_WARRIOR_ class
 */
class Monster_WARRIOR_ : public Pawn
{
public:
    Monster_WARRIOR_();
    Monster_WARRIOR_(const Monster_WARRIOR_ &monstre);
    Monster_WARRIOR_(const int &X, const int &Y, const bool &good);
    ~Monster_WARRIOR_();

    /**
     * @brief clone
     * @return l'objet clôné
     */
    std::shared_ptr<Pawn> clone() const override
    {
        return std::make_shared<Monster_WARRIOR_>(*this);
    }

    unsigned int getType() const override;
};

#endif // Monster_WARRIOR__H
