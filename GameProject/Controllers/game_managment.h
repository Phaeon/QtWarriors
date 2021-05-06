#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include <utility>
#include <functional>
#include <random>
#include <QObject>

#include "config.h"
#include "Models/Game.h"
#include "Models/Pawns/pawn.h"
#include "Models/Players/player.h"
#include "Models/Players/player_ia.h"
#include "Models/Players/player_physical.h"
#include "Views/viewgame.hpp"


/**
 * @brief The GameManagment class
 */
class GameManagment : public QObject
{
    Q_OBJECT
private:
    // Players
    std::shared_ptr<Player> _player, _player2;
    static bool _firstPlayer;

    // Game
    Game _game;
    std::shared_ptr<Pawn> _pawn;
    Position _pos;
    std::mutex _mutex;

    static int _tours;

public:
    GameManagment();
    ~GameManagment();

    void startGame();
    void initialisation();

    std::shared_ptr<Player> getPlayer() const;
    std::shared_ptr<Player> getPlayerEnemy() const;
    Game getGame() const;
    void ViewGameRejected();
    int MaxX(std::shared_ptr<Pawn> p) const;
    int MinX(std::shared_ptr<Pawn> p) const;
    int MaxY(std::shared_ptr<Pawn> p) const;
    int MinY(std::shared_ptr<Pawn> p) const;
    bool IsInPawnPossible(Position p, std::shared_ptr<Pawn> m) const;



public slots:
    void UpdateBoard(PositionPawn PP);
    void addListPionGame(std::shared_ptr<Pawn>);
    void removeListPionGame(std::shared_ptr<Pawn>);
    void game();

signals:
    void YouPlay();
};
#endif // PARTIE_H
