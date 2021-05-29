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
void Player_PHYSICAL::play(Game &game, Difficulty _difficulty)
{   
    if((_listPawns[_posPawn._pawn]->getType() &~ 2) != 0 && _posPawn._specialUse){
        // Tank
        if((_listPawns[_posPawn._pawn]->getType() &~ 8) == 0){
            game.playSpecial(1, _listPawns[_posPawn._pawn], _listPawns[_posPawn._pawn]);
        }
        // Rogue
        if((_listPawns[_posPawn._pawn]->getType() &~ 4)  == 0){
            game.playSpecial(1, _listPawns[_posPawn._pawn], {_posPawn._x, _posPawn._y}, getTargets(game, _listPawns[_posPawn._pawn]));
        }
        // Warrior
        if((_listPawns[_posPawn._pawn]->getType() &~ 1) == 0){
            game.playSpecial(1, _listPawns[_posPawn._pawn], game.getBoard()[_posPawn._y][_posPawn._x]);
        }

    }else {
        // Attaque basique
        game.play(1, _listPawns[_posPawn._pawn], {_posPawn._x, _posPawn._y});
    }
    return;
}


