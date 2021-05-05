#ifndef Monster_WIZARD__H
#define Monster_WIZARD__H

#include "Models/Pawns/pawn.h"

/**
 * @brief The Monster_WIZARD_ class
 */
class Monster_WIZARD_ : public Pawn
{
public:
    Monster_WIZARD_();
    Monster_WIZARD_(const Monster_WIZARD_ &);
    Monster_WIZARD_(const int &X, const int &Y,
                     const bool &good);
    ~Monster_WIZARD_();

    /**
     * @brief clone
     * @return l'objet clôné
     */
    std::shared_ptr<Pawn> clone() const override
    {
        return std::make_shared<Monster_WIZARD_>(*this);
    }

    unsigned int getType() const override;

};

#endif // Monster_WIZARD__H
