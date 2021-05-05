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
Position Player_PHYSICAL::search_next_shot(Game game, Position & p)
{
    std::cout << "Un tour qui se joue !" << std::endl << "Voici vos joueurs disponibles :" << std::endl;
     for (int i(0); i < _ListPionsGame.size(); i++)
     {
         std::cout << i+1 << " - " << _ListPionsGame[i] << std::endl;
     }

     setPlayed();

     int c(1);

     /*do {
         std::cout << "Quel est votre choix ?" << std::endl;
         std::cin >> c;
     } while (c <= 0 || c > _ListPionsGame.size());
    */

     // POur tester, la position est la position du premier pion de la liste
    p = {(_ListPionsGame[c-1])->getX(), (_ListPionsGame[c-1])->getY()};

    // Coups possibles à partir de ce pion
    QVector<Position> pawns = pawnsPossibles(game, game.getBoard()[p._y][p._x]);

    std::cout << "Voici les pawns disponibles : " << std::endl;

    for (unsigned int i(0); i < pawns.size(); i++)
    {
        std::cout << i+1 << " - Case (" << pawns[i]._x << ", " << pawns[i]._y << ")" << std::endl;
    }

    int i(1);
    /*do {
        std::cout << "Veuillez choisir le pawn à play : ";
        std::cin >> i;
    } while (i <= 0 || i > pawns.size());
    */
    Position pos = pawns.at(i-1);


    return pos;
}
