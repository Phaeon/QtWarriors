#include "player_ia.h"

std::shared_ptr<Node> Player_IA::_tree(std::make_shared<Node>());

/**
 * @brief Player_IA::Player_IA : Instancie le joueur IA et place ses pions
 * @param player : true (premier), false (deuxième)
 */
Player_IA::Player_IA(const bool &player)
    : Player(player)
{
    _ListPionsGame.push_back(std::make_shared<Monster_ROGUE_>(0, 9, false));
    _ListPionsGame.push_back(std::make_shared<Monster_ROGUE_>(2, 9, false));
    _ListPionsGame.push_back(std::make_shared<Monster_WARRIOR_>(4, 9, false));
    _ListPionsGame.push_back(std::make_shared<Monster_WIZARD_>(6, 9, false));
}

Player_IA::~Player_IA()
{}

/**
 * @brief Player_IA::search_next_shot : Recherche le prochain coup à jouer
 * @param game : Jeu courant
 * @param p : Pion choisi par le joueur
 * @return la position du prochain coup à jouer
 */
Position Player_IA::search_next_shot(Game game, Position& p)
{

    int r = rand()%_ListPionsGame.size();

    p = {(_ListPionsGame[r])->getX(), (_ListPionsGame[r])->getY()};

    QVector<Position> pawns = pawnsPossibles(game, game.getBoard()[p._y][p._x]);

    Position pos = (pawns.at(rand()%pawns.size()));

    /*std::cout << game << std::endl;
    float value = -9999;
    float a = -9999, b = 9999;

    for (auto pawn : _ListPionsGame)
    {
        for (Position position : pawnsPossibles(game, pawn))
        {
            Game game_temp = game;
            game_temp.play(_existentiel, pawn, position);

            float eval = al_bet_(game_temp, 3, a, b, !_existentiel);
            value = std::max(value, eval);
            if (b <= value)
                return position;
            a = std::max(a, value);
        }
    }*/

    return pos;
}

/**
 * @brief Player_IA::al_bet_ : Lance un Alpha-Beta sur tout le jeu
 * @param game : Jeu courant
 * @param alpha : Borne alpha
 * @param beta : Borne beta
 * @param existenciel : Joueur qui commence (true : Physique, false : IA)
 * @return la valeur de la feuille
 */
float Player_IA::al_bet_(Game game, float alpha, float beta, bool existenciel)
{
    if (game.gameEnded())
        return evaluation();

    if (existenciel)
    {
        float maxEval = -9999;

        for (auto pawn : _ListPionsGame)
        {
            for (Position position : pawnsPossibles(game, pawn))
            {
                Game game_temp = game;
                game_temp.play(1, pawn, position);
                setPlayer(false);
                float eval = al_bet_(game_temp, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                if (beta <= maxEval)
                    return maxEval;
                alpha = std::max(maxEval, alpha);
            }
        }

        return maxEval;
    }
    else
    {
        float minEval = 9999;
        std::cout << "Partie terminée ? " << game.gameEnded() << std::endl;
        for (auto pawn : pawnsPlayer(game))
        {
            for (Position position : pawnsPossibles(game, pawn))
            {
                Game game_temp = game;
                game_temp.play(0, pawn, position);
                setPlayer(true);
                float eval = al_bet_(game_temp, alpha, beta, true);
                minEval = std::min(minEval, eval);
                if (minEval <= alpha)
                    return minEval;
                beta = std::min(minEval, beta);
            }
        }

        return minEval;
    }
}

/**
 * @brief Player_IA::al_bet_ : Lance un Alpha-Beta sur une partie du jeu
 * @param game : Jeu courant
 * @param profondeur : Profondeur de la recherche
 * @param alpha : Borne alpha
 * @param beta : Borne beta
 * @param existenciel : Joueur qui commence (true : Physique, false : IA)
 * @return la valeur de la feuille
 */
float Player_IA::al_bet_(Game game, unsigned int profondeur, float alpha, float beta, bool existenciel)
{
    if (game.gameEnded() || profondeur == 0)
        return evaluation();

    if (existenciel)
    {
        float maxEval = -9999;
        std::cout << "Joueur : " << std::endl << game << std::endl;
        for (auto pawn : _ListPionsGame)
        {
            for (Position position : pawnsPossibles(game, pawn))
            {
                Game game_temp = game;
                game_temp.play(0, pawn, position);
                //setPlayer(true);
                float eval = al_bet_(game_temp, profondeur - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                if (beta <= maxEval)
                    return maxEval;
                alpha = std::max(maxEval, alpha);
            }
        }

        return maxEval;
    }
    else
    {
        float minEval = 9999;
        std::cout << "Adversaire : " << std::endl << game << std::endl;
        std::cout << "Taille des pions du joueur : " << pawnsPlayer(game).size() << std::endl;

        for (auto pawn : pawnsPlayer(game))
        {

            for (Position position : pawnsPossibles(game, pawn))
            {
                Game game_temp = game;
                game_temp.play(1, pawn, position);
                //setPlayer(false);

                float eval = al_bet_(game_temp, profondeur - 1, alpha, beta, true);
                minEval = std::min(minEval, eval);
                if (minEval <= alpha)
                    return minEval;
                beta = std::min(minEval, beta);
            }
        }

        return minEval;
    }
}

/**
 * @brief Player_IA::evaluation
 * @return l'évaluation d'un noeud
 */
float Player_IA::evaluation() // A revoir
{
    if (_existentiel) return 1;
    else return -1;
}

/**
 * @brief Player_IA::mcts_ : Lance un MCTS sur tout le jeu
 * @param game : Jeu courant
 */
void Player_IA::mcts_(Game game)
{
    std::shared_ptr<Node> N = _tree;

    simulation(game, N);

    int value = rollout(game, N);

    callback(N, value);
}

/**
 * @brief Player_IA::simulation : Etape de la simulation
 * @param game : Jeu courant
 * @param node : Noeud courant
 * @return le noeud sur lequel va être effectué un rollout et/ou callback
 */
std::shared_ptr<Node> Player_IA::simulation(Game game, std::shared_ptr<Node> node)
{
    // On récupère tous les pawns possibles
    std::map<std::shared_ptr<Pawn>, QVector<Position>> all_pawns;
    for (auto i : pawnsPlayer(game))
    {
        QVector<Position> tab_pos;
        for (Position p : pawnsPossibles(game, i))
            tab_pos.push_back(p);

        all_pawns.insert({i, tab_pos});
    }

    // Dans le cas d'un node non exploré...
    if (node->children.size() != all_pawns.size())
    {
    // GROWTH
        // Dans le cas où nous ne sommes pas à une feuille
        if (all_pawns.size() != 0)
        {
            std::shared_ptr<Node> N = std::make_shared<Node>(node->parent_node,  all_pawns.begin()->first,  all_pawns.begin()->second[0]); // A MODIFIER
            node->children.push_back(N);

            return node;

        } else return node;
    // END GROWTH
    }
    else // Lorsque tous les nodes fils ont été explorés
    {
        std::shared_ptr<Node> max_node;
        float max_value = -9999;

        for (auto n : node->children)
        {
            float local = ubc(n->average_score, n->times_used, n->parent_node->times_used);
            if (local > max_value)
            {
                max_value = local;
                max_node = n;
            }
        }

        game.play(player(), node->playing, max_node->pawn_after);
        return simulation(game, max_node);
    }
}

/**
 * @brief Player_IA::rollout : Simule une partie à partir d'un état de jeu et d'un noeud
 * @param game : Jeu courant
 * @param node : Noeud courant
 * @return la valeur de la simulation
 */
int Player_IA::rollout(Game &game, std::shared_ptr<Node> node)
{
    while (!game.gameEnded())
    {
        QVector<Position> all_pawns;
        for (auto i : pawnsPlayer(game))
            for (Position p : pawnsPossibles(game, i))
                all_pawns.push_back(p);

        game.play(player(), node->playing, all_pawns[rand()%all_pawns.size()]);
    }

    if (game.getGameState() == STATE_GAME::DRAW) return 0;
    else if (game.getGameState() == STATE_GAME::END_1) return 1;
    else return -1;
}

/**
 * @brief Player_IA::callback : Remonte une valeur jusqu'à la racine
 * @param node : Noeud courant
 * @param value : Valeur remontée
 */
void Player_IA::callback(std::shared_ptr<Node> node, int value)
{
    node->times_used++;
    node->average_score += value;

    if (!node->parent_node) callback(node->parent_node, value);
}

/**
 * @brief Player_IA::ubc : Détermine l'ubc d'un noeud
 * @param w : Gain moyen
 * @param n : Itérations du noeud courant
 * @param N : Itérations du parent
 * @return l'ubc du noeud courant
 */
float Player_IA::ubc(double w, double n, double N)
{
    // Retourne la valeur de pawn
    return (w/n) + CONSTANT * sqrt(log(N)/n);
}

