#ifndef MONSTRE_ROGUE__H
#define MONSTRE_ROGUE__H

#include "Models/Pawns/pawn.h"

/**
 * @brief The Monster_ROGUE_ class
 */
class Monster_ROGUE_ : public Pawn
{
public:
    Monster_ROGUE_();
    Monster_ROGUE_(const Monster_ROGUE_ &monstre);
    Monster_ROGUE_(const int &X, const int &Y, const bool &good);
    ~Monster_ROGUE_();

    /**
     * @brief clone
     * @return l'objet clôné
     */
    std::shared_ptr<Pawn> clone() const override
    {
        return std::make_shared<Monster_ROGUE_>(*this);
    }

    unsigned int getType() const override;
};

#endif // MONSTRE_ROGUE__H
