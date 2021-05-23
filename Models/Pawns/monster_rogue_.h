#ifndef MONSTRE_ROGUE_H
#define MONSTRE_ROGUE_H

#include "Models/Pawns/pawn.h"
#include "Models/Monsters/warrior_3d_.h"
#include "Models/Monsters/rogue_3d_.h"

/**
 * @brief The Monster_ROGUE_ class
 */
class Monster_ROGUE_ : public Pawn
{
public:
    Monster_ROGUE_();
    Monster_ROGUE_(const Monster_ROGUE_ &monstre);
    Monster_ROGUE_(const int &X, const int &Y, const bool &good);

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
