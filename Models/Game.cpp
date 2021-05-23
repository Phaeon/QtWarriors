#include "Game.h"

/**
 * @brief Game::Game : Constructeur par défaut
 */
Game::Game()
{}

/**
 * @brief Game::~Game : Destructeur
 */
Game::~Game()
{}


/**
 * @brief Game::reset : Remet à plat un jeu
 */
void Game::reset()
{
    assert(MAX_PAWNS <= WIDTH_BOARD);

    for (int i(0); i < HEIGHT_BOARD; i++)
    {
        QVector<std::shared_ptr<Pawn>> pi;
        for (int j(0); j < WIDTH_BOARD; j++)
            pi.push_back(nullptr);

        _board.push_back(pi);
    }


    _state = STATE_GAME::IN_GAME;
    _nb_rounds = 0;
}

/**
 * @brief Game::validSlot
 * @param p : Pion à analyser
 * @return si le pion est à une position valide
 */
bool Game::validSlot(std::shared_ptr<Pawn> p) const
{
    return ((p->getX() >= 0 && p->getY() >= 0) &&
            (p->getX() < WIDTH_BOARD && p->getY() < HEIGHT_BOARD));
}

/**
 * @brief Game::roundsPlayed
 * @return le nombre de tours joués
 */
int Game::roundsPlayed() const
{
    return _nb_rounds;
}

/**
 * @brief Game::allPawnsPlayed
 * @param player : Joueur à analyser
 * @return si le joueur n'a plus de pions
 */
bool Game::allPawnsPlayed(const int &player)
{

    if (player)
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

/**
 * @brief Game::play
 * @param player : Joueur courant
 * @param playing : Pion que le joueur joue
 * @param p : Position où le joueur jouera
 *  - Dans le cas d'une case occupé par un adversaire, infliger les dégâts sans bouger
 *  - Dans le cas d'une case occupé par un coéquipuer, lui donner les effets voulus (healing...)
 *  - Dans le cas d'une case vide, déplacer le pawn
 */
void Game::play(const int &player, std::shared_ptr<Pawn> playing, Position p)
{
    _nb_rounds++;
    std::shared_ptr<Pawn> pawn = _board[p._y][p._x];

    // Dans le cas d'une case non-occupé...
    if (!pawn)
    {
        // Aucun dégât donc aucun mort donc aucune défaite. CQFD.
        _board[playing->getY()][playing->getX()] = nullptr;
        playing->setX(p._x);
        playing->setY(p._y);
        _board[p._y][p._x] = std::move(playing);

    }



    // Dans le cas d'une case occupé par un adversaire...
    else if ((player && !pawn->isGood()) || (!player && pawn->isGood()))
    {
        playing->sendAttack(pawn);
        std::cout << "Dégâts infligés : " << playing->getAttack() << ", " << pawn->getLife() << " life restantes." << std::endl;
        if (pawn->isDead()) // Si le pawn adverse meurt, il disparait du plateau
            _board[p._y][p._x] = nullptr;
    }
    else
    {
        if ((playing->getType() &~ 2) == 0) // Wizard (Soins)
        {
            std::shared_ptr<Heal_Decorator> healing = std::make_shared<Heal_Decorator>(pawn);
            healing->heal();
            std::cout << "Soins !" << std::endl;
        }
    }
    // Si le Player opposé n'a plus de pièces, alors la game est terminée.
    if (allPawnsPlayed(!player))
        _state = (player) ? STATE_GAME::END_1 : STATE_GAME::END_2;

}

void Game::playSpecial(const int &player, std::shared_ptr<Pawn> playing, Position position)
{
    _nb_rounds++;
    std::shared_ptr<Pawn> pawn = _board[position._y][position._x];


    // Vérifier si le joueur est un TANK. Si oui, alors vérifier s'il a déjà été boosté
    if ((playing->getType() &~ 8) == 0)
    {
        std::shared_ptr<Super_Defence_Decorator> s_defence = std::make_shared<Super_Defence_Decorator>(playing);
        auto temp_pawn = std::dynamic_pointer_cast<Monster_TANK_>(playing);

        s_defence->super_defence(temp_pawn->isBoosted());
        temp_pawn->setBoosted();

    }
    else if ((playing->getType() &~ 4) == 0) // Rogue (Attaque sur tout le monde)
    {

    }
    else if ((playing->getType() &~ 2) == 0) // Wizard (Soins)
    {
        std::shared_ptr<Heal_Decorator> healing = std::make_shared<Heal_Decorator>(pawn);
        healing->heal();
    }
    else if (((playing->getType() &~ 1) == 0) && pawn) // Warrior (Meilleure attaque)
    {
        std::shared_ptr<Super_Attack_Decorator> s_attack = std::make_shared<Super_Attack_Decorator>(pawn);
        s_attack->super_attack(pawn);
    }

    // Si le Player opposé n'a plus de pièces, alors la game est terminée.
    if (allPawnsPlayed(!player))
        _state = (player) ? STATE_GAME::END_1 : STATE_GAME::END_2;
}

/**
 * @brief Game::gameEnded
 * @return si la partie est terminée
 */
bool Game::gameEnded() const
{
    return (_state != STATE_GAME::IN_GAME);
}

/**
 * @brief Game::getGameState
 * @return l'état du jeu
 */
STATE_GAME Game::getGameState() const
{
    return _state;
}

/**
 * @brief Game::setSlot : Place un pion à une coordonnée
 * @param posX : Position X
 * @param posY : Position Y
 * @param p : Nouveau pion
 */
void Game::setSlot(int posX, int posY, std::shared_ptr<Pawn> p)
{
    _board[posY][posX] = std::move(p);
}

Game& Game::operator=(const Game &game)
{
    this->reset();
    _nb_rounds = game._nb_rounds;
    _state = game._state;

    for (const auto &ligne : game._board)
        for (const auto &bloc : ligne)
            if (bloc) _board[bloc->getY()][bloc->getX()] = bloc->clone();

    return *this;
}

/**
 * @brief operator <<
 * @param flux : Type de flux
 * @param game : Jeu courant
 * @return le flux
 */
std::ostream& operator<<(std::ostream &flux, Game &game)
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

