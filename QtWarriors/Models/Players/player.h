#ifndef PLAYER_H
#define PLAYER_H

#include <mutex>
#include <cstdlib>
#include <thread>
#include <cmath>
#include <map>
#include <QVector>
#include <random>

#include "Models/game.h"
#include "Models/start.hpp"

/**
 * @brief The PositionPawn struct
 * Cette structure permet de mettre transporter les informations dans un signal nécessaire à la modification de la position d'un pion
 */
struct PositionPawn{
    int _x;
    int _y;
    int _pawn;
    bool _specialUse;
};

/**
 * @brief Class Player
 * Classe mère des joueurs
 * Chaque joueur doit implémenter la méthode play et search_next_shot
 */
class Player
{
private:
    bool _player;

public:

    Player();
    Player(const bool &player);

    virtual void play(Game &, Difficulty) = 0;

    bool player() const;
    void setPlayer(const bool &player);

    QVector<std::shared_ptr<Pawn>> getPawns() const;
    void addPawn(std::shared_ptr<Pawn> p);
    void removePawn(std::shared_ptr<Pawn> p);
    void viewRejected();
    std::shared_ptr<Pawn> getPawn(int index) const;

    QVector<std::shared_ptr<Pawn>> pawnsPlayer(Game, const bool &);
    QVector<Position> pawnsPossibles(Game, std::shared_ptr<Pawn>);
    QVector<std::shared_ptr<Pawn> > getTargets(Game, std::shared_ptr<Pawn>);
    QVector<std::shared_ptr<Pawn> > getTargetsNull(Game, Position, int radius);

    bool isValid() const;
    void setValid(bool valid);
    void setPosPawn(PositionPawn p);

protected:
    QVector<std::shared_ptr<Pawn>> _listPawns;
    PositionPawn _posPawn;
    bool _isValid;

};

#endif // Player_H
