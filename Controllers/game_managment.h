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
#include <QDateTime>

#include "config.h"
#include "Models/Game.h"
#include "Models/Pawns/pawn.h"
#include "Models/Players/player.h"
#include "Models/Players/player_ia.h"
#include "Models/Players/player_physical.h"
#include "Views/gameView.hpp"
#include "Models/start.hpp"


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
    Position _pTemp;
    static int _tours;

    Difficulty _difficulty;

    QString _timeStart;

public:
    GameManagment();
    ~GameManagment();

    void startGame();
    void initialisation();

    std::shared_ptr<Player> getPlayer() const;
    std::shared_ptr<Player> getPlayerEnemy() const;
    int getTour() const;
    QString getTime() const;

    Game getGame() const;
    void viewGameRejected();
    void setDifficulte(Difficulty _diff);
    int maxX(std::shared_ptr<Pawn> p) const;
    int minX(std::shared_ptr<Pawn> p) const;
    int maxY(std::shared_ptr<Pawn> p) const;
    int minY(std::shared_ptr<Pawn> p) const;

    bool isInPawnPossible(Position p, std::shared_ptr<Pawn> m) const;
    void endOfTreatment();

public slots:
    void updateBoard(PositionPawn PP);
    void addListPionGame(std::shared_ptr<Pawn>);
    void removeListPionGame(std::shared_ptr<Pawn>);
    void game();

signals:
    void youPlay();
    void nextTurn();
    void endGame(STATE_GAME);
    void boardCanMove();
};

#endif // PARTIE_H
