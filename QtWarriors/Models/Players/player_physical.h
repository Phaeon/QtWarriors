#ifndef PLAYER_PHYSIQUE_H
#define PLAYER_PHYSIQUE_H

#include "player.h"

/**
 * @brief The Player_PHYSICAL class
 */
class Player_PHYSICAL : public Player
{
public:
    Player_PHYSICAL();
    Player_PHYSICAL(const bool &player);

    void play(Game &, Difficulty _difficulty) override;
};

#endif // Player_PHYSICAL_H
