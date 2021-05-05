#ifndef PLAYER_H
#define PLAYER_H

#include <mutex>
#include <cstdlib>
#include <thread>
#include <cmath>
#include <map>
#include <QVector>

#include "Models/Game.h"

/**
 * @brief Class Player
 * Classe mère des joueurs
 * Chaque joueur doit implémenter la méthode play et search_next_shot
 */
class Player
{
private:
    bool _player;
    static bool _played;

public:

    Player();
    Player(const bool &player);

    virtual void play(Game, Position &pawn, std::mutex & pawn_mutex, Position &position);
    virtual Position search_next_shot(Game, Position &) = 0;

    bool player() const;
    void setPlayer(const bool &player);

    bool hasPlayed() const;
    void setPlayed();

    QVector<std::shared_ptr<Pawn>> getListPionsGame() const;
    void addListPionGame(std::shared_ptr<Pawn> p);
    void removeListPionGame(std::shared_ptr<Pawn> p);
    void ViewRejected();
    std::shared_ptr<Pawn> getPion(int index) const;

    QVector<std::shared_ptr<Pawn>> pawnsPlayer(Game);
    QVector<Position> pawnsPossibles(Game, std::shared_ptr<Pawn>);

protected:
    QVector<std::shared_ptr<Pawn>> _ListPionsGame;


};

#endif // Player_H
