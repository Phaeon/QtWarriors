#include "GameCopie.h"

GameCopie::GameCopie()
{}

GameCopie::~GameCopie()
{}

void GameCopie::reset()
{
    assert(MAX_PAWNS <= WIDTH_BOARD);

    for (int i(0); i < HEIGHT_BOARD; i++)
    {
        std::vector<std::shared_ptr<Pawn>> pi;
        for (int j(0); j < WIDTH_BOARD; j++)
            pi.push_back(nullptr);

        _board.push_back(pi);
    }


    _state = STATE_GAME::IN_GAME;
    _nb_rounds = 0;
}

bool GameCopie::validSlot(std::shared_ptr<Pawn> p) const
{
    return ((p->getX() >= 0 && p->getY() >= 0) &&
            (p->getX() < WIDTH_BOARD && p->getY() < HEIGHT_BOARD));
}


int GameCopie::roundsPlayed() const
{
    return _nb_rounds;
}

bool GameCopie::allPawnsPlayed(const int &Player)
{

    if (Player == 1)
    {
        for (auto & ligne : _board)
            for (auto & colonne : ligne)
                if (colonne && colonne->isGood()) return false;
    }
    else
    {
        for (auto & ligne : _board)
            for (auto & colonne : ligne)
                if (colonne && !colonne->isGood()) return false;
    }

    return true;
}

/*
 * ON CONSIDERE QUE LE COUP EST VALABLE
 * Jouer :
 *  - Dans le cas d'une case occupé par un adversaire, infliger les dégâts sans bouger
 *  - Dans le cas d'une case occupé par un coéquipuer, lui donner les effets voulus (healing...)
 *  - Dans le cas d'une case vide, déplacer le pawn
 **/
void GameCopie::play(const int &player, std::shared_ptr<Pawn> playing, Position p)
{
    _nb_rounds++;
    std::shared_ptr<Pawn> pawn = _board[p._y][p._x];
    int x = p._x;
    int y = p._y;

    // Dans le cas d'une case non-occupé...
    if (!pawn)
    {
        // Aucun dégât donc aucun mort donc aucune défaite. CQFD.
        _board[playing->getY()][playing->getX()] = nullptr;
        _board[p._y][p._x] = std::move(playing);
        _board[p._y][p._x]->setX(x);
        _board[p._y][p._x]->setY(y);
    }

    // Dans le cas d'une case occupé par un adversaire...
    else if ((player && !pawn->isGood()) || (!player && pawn->isGood()))
    {
        playing->sendAttack(_board[p._y][p._x]);
        std::cout << "Dégâts infligés : " << playing->getAttack() << ", " << pawn->getLife() << " life restantes." << std::endl;
        if (pawn->isDead()) // Si le pawn adverse meurt, il disparait du plateau
            _board[p._y][p._x] = nullptr;


    }

    // Dans le cas d'une case occupé par un coéquipier...
    else
    {
        // Vérifier que c'est un sorcier
        if ((playing->getType() &~ 2) == 0)
        {
            std::shared_ptr<Heal_Decorator> healing = std::make_shared<Heal_Decorator>(pawn);
            healing->heal();
        }
    }

    // Si le Player opposé n'a plus de pièces, alors la game est terminée.
    if (allPawnsPlayed(!player))
        _state = (player) ? STATE_GAME::END_1 : STATE_GAME::END_2;

}

bool GameCopie::gameEnded() const
{
    return (_state != STATE_GAME::IN_GAME);
}

STATE_GAME GameCopie::getGameState() const
{
    return _state;
}

void GameCopie::setSlot(int posX, int posY, std::shared_ptr<Pawn> p)
{
    _board[posY][posX] = p;
}

std::ostream& operator<<(std::ostream &flux, GameCopie &game)
{
    for (int i(0); i < HEIGHT_BOARD; i++)
    {
        flux << "|";
        auto ligne = game.getBoard()[i];
        for (auto bloc : ligne)
        {
            if (!bloc) flux << " |";
            else if (!bloc->isGood()) flux << "X|";
            else flux << "O|";
        }

        flux << " " << i << std::endl;

    }

    flux << std::endl << "|";

    for (int j(0); j < WIDTH_BOARD; j++)
    {
        flux << j << "|";
    }

    flux << std::endl;

    return flux;
}

