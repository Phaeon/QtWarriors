#include "player_ia.h"

std::shared_ptr<Node> Player_IA::_tree(std::make_shared<Node>());

/**
 * @brief Player_IA::Player_IA : Instancie le joueur IA et place ses pions
 * @param player : true (premier), false (deuxième)
 */
Player_IA::Player_IA(const bool &player)
    : Player(player)
{
    _listPionsGame.push_back(std::make_shared<Monster_ROGUE_>(0, 9, false));
    _listPionsGame.push_back(std::make_shared<Monster_TANK_>(2, 9, false));
    _listPionsGame.push_back(std::make_shared<Monster_WARRIOR_>(4, 9, false));
    _listPionsGame.push_back(std::make_shared<Monster_WIZARD_>(6, 9, false));
}

/**
 * @brief Player_IA::search_next_shot : Recherche le prochain coup à jouer
 * @param game : Jeu courant
 * @param p : Pion choisi par le joueur
 * @return la position du prochain coup à jouer
 */
Position Player_IA::search_next_shot(Game game, Position & p, Difficulty _difficulty)
{
    unsigned int diff = 2;

    std::random_device rd;
    std::mt19937 gen(rd());

    QVector<std::shared_ptr<Pawn>> targets; // Pions
    QVector<Position> pawns;

    // FACILE
    if (_difficulty == Difficulty::Easy)
    {
        std::uniform_int_distribution<> d_choix(0, _listPionsGame.size() - 1);

        // Choix du pion à jouer
        int r = d_choix(gen);
        p._x = _listPionsGame[r]->getX();
        p._y = _listPionsGame[r]->getY();

        std::cout << p._x << " " << p._y << std::endl;

        targets = getTargets(game, game.getBoard()[p._y][p._x]);
        pawns = pawnsPossibles(game, game.getBoard()[p._y][p._x]);

        // Dans le cas ou aucun pion est dans le périmètre, on choisit un pion au hasard
        if (targets.size() == 0) {
            std::uniform_int_distribution<> d_pawn(0, pawns.size() - 1);
            int pos_r;

            do {
                pos_r = d_pawn(gen);
                std::cout << pawns[pos_r]._x << " " << pawns[pos_r]._y << std::endl;
            } while (pawns[pos_r]._x == p._x && pawns[pos_r]._y == p._y);

            return pawns[pos_r];
        }
        else
        {
            std::uniform_int_distribution<> d_target(0, targets.size() - 1);
            std::shared_ptr<Pawn> target = targets[d_target(gen)];

            int deb_X, fin_X;
            int deb_Y, fin_Y;

            if ((target->getX() <= p._x)) {
                deb_X = target->getX();
                fin_X = p._x;
            } else {
                deb_X = p._x;
                fin_X = target->getX();
            }

            if ((target->getY() <= p._y)) {
                deb_Y = target->getY();
                fin_Y = p._y;
            } else {
                deb_Y = p._y;
                fin_Y = target->getY();
            }

            int rand_x, rand_y;

            std::uniform_int_distribution<> d_pawn_x(deb_X, fin_X), d_pawn_y(deb_Y, fin_Y);
            // Tant que les coordonnées correspondent à notre pion, on continue de chercher.
            do {
                rand_x = d_pawn_x(gen);
                rand_y = d_pawn_y(gen);
            } while (rand_y == p._y && rand_x == p._x);

            return {rand_x, rand_y};
        }

    }
    // INTERMÉDIAIRE
    else if (_difficulty == Difficulty::Medium)
    {
        /* CHOIX DU PION :
         *  1 - Enregistrer l'ensemble des pions avec moins de vies que la moyenne de l'ensemble des attaques dans un vecteur ;
         *  2 - Taille du vecteur :
         *      2.1 - Non-vide : Choisir le pion avec la défense et les vies les plus basses selon des coefficients ;
         *      2.2 - Vide : Choisir un pion proche d'une cible tel que celui-ci est assez éloigné des autres adversaires
         */

        /* CHOIX DE LA CIBLE :
         *  3 - Dans le cas où le vecteur de pions "faibles" n'est pas vide et qu'il faut en extraire un :
         *          > Eloigner le pion là où il y a le moins d'adversaires (Stocker dans un tableau la position de la case avec le moins d'adversaires)
         *  4 - Sinon après avoir choisi le pion, attaquer la cible la plus proche
         *
         */

        // 1
        QVector<std::shared_ptr<Pawn> > low;
        int m_att(0), total_att(0);
        Position pos;

        QVector<std::shared_ptr<Pawn> > lp = pawnsPlayer(game, true);

        // Calculer la moyenne de l'ensemble des attaques
        for (auto p2 : lp)
            total_att += p2->getAttack();

        m_att = total_att / lp.size();

        // Enregistrer les pions avec les vies inférieures à la moyenne de attaques
        for (auto p2 : _listPionsGame)
            if (p2->getLife() <= m_att) low.push_back(p2);

        // 2.1 et 3
        if (low.size() != 0)
        {
            int score(0);

            for (auto p2 : low)
            {
                if ((p2->getLife() * 2 + p2->getDefence()) >= score)
                {
                    p = {p2->getX(), p2->getY()};
                    score = p2->getLife() * 2 + p2->getDefence();
                }
            }

            std::shared_ptr<Pawn> pawn = game.getBoard()[p._y][p._x];
            int aux(9999);

            // Choix du pion
            // Pour chaque position possible du pion choisi, on chercher à voir quelle case à le moins d'adversaires dans son périmètre
            for (auto p2 : pawnsPossibles(game, pawn))
            {
                int s = getTargets(game, game.getBoard()[p2._y][p2._x]).size();
                if (s < aux)
                {
                    pos = p2;
                    aux = s;
                }
            }

            std::cout << pawn << std::endl;
            std::cout << "Position 1" << pos._x << " " << pos._y << std::endl;

            return pos;
        }
        else // 2.2 et 4
        {
            // Calculer la distance la plus minime avec un adversaire
            double dist(9999);

            for (auto p2 : _listPionsGame)
            {
                double x_p = static_cast<double>(p2->getX());
                double y_p = static_cast<double>(p2->getY());

                for (auto p3 : lp)
                {
                    double x_p2 = static_cast<double>(p3->getX());
                    double y_p2 = static_cast<double>(p3->getY());

                    double n_dist = calcul_distance(x_p, y_p, x_p2, y_p2);

                    if (n_dist <= dist) // Retrouver le vecteur directeur réduit
                    {
                        p = {p2->getX(), p2->getY()};
                        pos = {p3->getX(), p3->getY()};
                        dist = n_dist;
                    }
                }
            }

            // Idée : Aller du pion adverse vers notre pion et dès qu'on entre dans le périmètre on arrête

            std::cout << game.getBoard()[p._y][p._x] << std::endl;
            std::cout << "Position 2 - " << pos._x << " " << pos._y << std::endl;

            return pos;

        }
    }
    // DIFFICILE
    else
    {


        return {};
    }
}

double Player_IA::calcul_distance(double x_1, double y_1, double x_2, double y_2)
{
    return sqrt(pow((x_2 - x_1), 2) + pow((y_2 - y_1), 2));
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

        for (auto pawn : pawnsPlayer(game, false))
        {
            for (Position position : pawnsPossibles(game, pawn))
            {
                Game game_temp;
                game_temp = game;

                game_temp.play(1, pawn, position);

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
        for (auto pawn : pawnsPlayer(game, true))
        {
            for (Position position : pawnsPossibles(game, pawn))
            {
                Game game_temp;
                game_temp = game;

                game_temp.play(0, pawn, position);

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
    Game game_temp;
    game_temp = game;

    if (game_temp.gameEnded() || profondeur == 0)
        return evaluation();

    if (existenciel)
    {
        float maxEval = -9999;

        for (auto pawn : pawnsPlayer(game_temp, false))
        {
            for (Position position : pawnsPossibles(game_temp, pawn))
            {
                game_temp.play(0, pawn, position);

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

        for (auto pawn : pawnsPlayer(game_temp, true))
        {
            for (Position position : pawnsPossibles(game_temp, pawn))
            {
                game_temp.play(1, pawn, position);

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
    for (auto i : pawnsPlayer(game, false))
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
        for (auto i : pawnsPlayer(game, false))
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

