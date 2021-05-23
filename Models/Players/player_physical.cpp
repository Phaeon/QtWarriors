#include "player_physical.h"

/**
 * @brief Player_PHYSICAL::Player_PHYSICAL : Instancie le joueur physique
 * @param player : true (premier), false (deuxième)
 */
Player_PHYSICAL::Player_PHYSICAL(const bool &player)
    : Player(player)
{}

/**
 * @brief Player_PHYSIQUE::search_next_shot : Recherche le prochain coup à jouer
 * @param game : Jeu courant
 * @param p : Pion choisi par le joueur
 * @return la position du prochain coup à jouer
 */
Position Player_PHYSICAL::search_next_shot(Game game, Position & p, Difficulty _difficulty)
{
    Position pos;

    p = {(_listPionsGame[_posPawn._pawn])->getX(), (_listPionsGame[_posPawn._pawn])->getY()};
    pos = {_posPawn._x, _posPawn._y};

    return pos;
}


