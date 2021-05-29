#ifndef Game_H
#define Game_H

#include <iostream>
#include <QVector>
#include <cassert>
#include <array>
#include <memory>

#include "Models/Pawns/pawn.h"
#include "config.h"

#include "Models/Pawns/monster_warrior_.h"
#include "Models/Pawns/monster_wizard_.h"
#include "Models/Pawns/monster_rogue_.h"
#include "Models/Pawns/monster_tank_.h"

#include "Models/Pawns/heal_decorator.h"
#include "Models/Pawns/super_attack_decorator.h"
#include "Models/Pawns/super_defence_decorator.h"

/**
 * @brief The STATE_GAME enum
 */
enum class STATE_GAME {IN_GAME, END_1, END_2, DRAW, ERROR};

/**
 * @brief The Position struct
 */
struct Position {
    int _x;
    int _y;
};

bool operator==(Position const & p1, Position const & p2);

/**
 * @brief The Game class
 */
class Game
{
private:
    // Etat de la game
    STATE_GAME _state;

    // Plateau de game
    QVector<QVector<std::shared_ptr<Pawn>> > _board;

public:
    Game();
    ~Game();

    // Initialisation du plateau ainsi que l'état de la game
    void reset();

    // Coups
    bool validSlot(std::shared_ptr<Pawn>) const;
    bool validPawn(std::shared_ptr<Pawn> playing, std::shared_ptr<Pawn> target) const;

    // Vérifie l'état de game du Player, A MODIFIER : Utiliser une classe Player et non plus un entier
    bool allPawnsPlayed(const int &player);

    // Jouer le pawn p
    void play(const int &player, std::shared_ptr<Pawn> playing, Position position);
    void playSpecial(const int &player, std::shared_ptr<Pawn> playing, Position position, QVector<std::shared_ptr<Pawn>> positions);
    void playSpecial(const int &player, std::shared_ptr<Pawn> playing, std::shared_ptr<Pawn> target);

    // Etat de la game
    bool gameEnded() const;
    STATE_GAME getGameState() const;

    /**
     * @brief getBoard
     * @return le plateau du jeu
     */
    QVector<QVector<std::shared_ptr<Pawn>> > const & getBoard()
    {
        return _board;
    }

    void setSlot(int X, int Y, std::shared_ptr<Pawn> p);

    Game& operator=(const Game &game);


};

std::ostream& operator<<(std::ostream &flux, Game &);

#endif // Game_H
