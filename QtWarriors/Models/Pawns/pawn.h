#ifndef Pawn_H
#define Pawn_H

#include <ostream>
#include <vector>
#include <memory>
#include <QString>

#include "config.h"

#include "Models/Monsters/pawngl.h"

/**
 * @brief The STATE_PAWN enum
 */
enum class STATE_PAWN {ALIVE, DEAD};

const unsigned int WARRIOR = 1;
const unsigned int WIZARD = 2;
const unsigned int ROGUE = 4;
const unsigned int TANK = 8;

/**
 * @brief The Pawn class
 */
class Pawn
{

private:

    int _posX, _posY; // Coordonnées du pion
    bool _good; // Si le pion est gentil

    STATE_PAWN _state; // Etat du pion

    int _maxLife, _life; // Vies du pion
    int _attack, _defence, _moveRadius, _attackRadius;

    std::shared_ptr<PawnGL> _3d;

    bool _specialUsed, _attacking;

public:

    Pawn();
    Pawn(const int &X, const int &Y, const bool &good,
         const int &maxlife,
         const int &attack, const int &defence,
         const int &moveRadius, const int &attackRadius,
         const std::shared_ptr<PawnGL> &pawn3D);
    Pawn(const Pawn &);
    virtual ~Pawn();

    // Clonage
    virtual std::shared_ptr<Pawn> clone() const = 0;

    // Getters et setters
    int getX() const;
    int getY() const;
    int getLife() const;
    QString getName() const;

    int getMaxLife() const;
    int getAttackRadius() const;
    int getMoveRadius() const;
    int getAttack() const;
    int getDefence() const;

    void setX(const int &X);
    void setY(const int &Y);
    void setLife(const float &life);
    void setDefence(const int &defence);

    // Gestion des attaques
    void receiveAttack(const float &damages);
    void sendAttack(std::shared_ptr<Pawn>);
    bool isDead() const;

    bool isAttacking() const;
    void attacking();
    bool specialAttackUsed() const;
    void hasBeenUsed();

    // Vérifier son état
    STATE_PAWN getState() const;
    void setState(const STATE_PAWN &);

    // Type
    virtual unsigned int getType() const = 0;

    // Gentil ou méchant
    bool isGood() const;

    std::shared_ptr<PawnGL> get3DPawn() const;
};

std::ostream& operator<<(std::ostream &flux, std::shared_ptr<Pawn>);

#endif // Pawn_H
