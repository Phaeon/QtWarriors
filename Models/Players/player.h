#ifndef PLAYER_H
#define PLAYER_H

#include <mutex>
#include <cstdlib>
#include <thread>
#include <cmath>
#include <map>
#include <QVector>
#include <random>

#include "Models/Game.h"
#include "Models/start.hpp"

/**
 * @brief The PositionPawn struct
 * Cette structure permet de mettre transporter les informations dans un signal nécessaire à la modification de la position d'un pion
 */
struct PositionPawn{
    int _x;
    int _y;
    int _pawn;
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

    virtual void play(Game, Position &pawn, std::mutex & pawn_mutex, Position &position, Difficulty _difficulty);
    virtual Position search_next_shot(Game, Position &, Difficulty _difficulty) = 0;

    bool player() const;
    void setPlayer(const bool &player);

    QVector<std::shared_ptr<Pawn>> getListPionsGame() const;
    void addListPionGame(std::shared_ptr<Pawn> p);
    void removeListPionGame(std::shared_ptr<Pawn> p);
    void viewRejected();
    std::shared_ptr<Pawn> getPion(int index) const;

    QVector<std::shared_ptr<Pawn>> pawnsPlayer(Game, const bool &);
    QVector<Position> pawnsPossibles(Game, std::shared_ptr<Pawn>);
    QVector<std::shared_ptr<Pawn> > getTargets(Game game, std::shared_ptr<Pawn> p);

    bool getValid() const;
    void setValid(bool valid);
    void setPosPawn(PositionPawn p);

protected:
    QVector<std::shared_ptr<Pawn>> _listPionsGame;
    PositionPawn _posPawn;
    bool _isValid;

};

#endif // Player_H
