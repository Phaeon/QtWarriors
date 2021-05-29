#include "player_ia.h"

/**
 * @brief Player_IA::Player_IA : Instancie le joueur IA et place ses pions
 * @param player : true (premier), false (deuxième)
 */
Player_IA::Player_IA(const bool &player)
    : Player(player)
{
    _listPawns.push_back(std::make_shared<Monster_ROGUE_>(0, 9, false));
    _listPawns.push_back(std::make_shared<Monster_TANK_>(2, 9, false));
    _listPawns.push_back(std::make_shared<Monster_WARRIOR_>(4, 9, false));
    _listPawns.push_back(std::make_shared<Monster_WIZARD_>(6, 9, false));
}

/**
 * @brief Player_IA::search_next_shot : Recherche le prochain coup à jouer
 * @param game : Jeu courant
 * @param p : Pion choisi par le joueur
 * @return la position du prochain coup à jouer
 */
void Player_IA::play(Game &game, Difficulty _difficulty)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    QVector<std::shared_ptr<Pawn>> targets; // Pions
    QVector<Position> pawns;
    Position p;

    // FACILE
    if (_difficulty == Difficulty::Easy)
    {
        std::uniform_int_distribution<> d_choix(0, _listPawns.size() - 1);

        // Choix du pion à jouer
        int r = d_choix(gen);
        p._x = _listPawns[r]->getX();
        p._y = _listPawns[r]->getY();

        targets = getTargets(game, game.getBoard()[p._y][p._x]);
        pawns = pawnsPossibles(game, game.getBoard()[p._y][p._x]);

        // Dans le cas ou aucun pion est dans le périmètre, on choisit un pion au hasard
        if (targets.size() == 0) {
            std::uniform_int_distribution<> d_pawn(0, pawns.size() - 1);
            int pos_r;

            do {
                pos_r = d_pawn(gen);
            } while (pawns[pos_r]._x == p._x && pawns[pos_r]._y == p._y);

            game.play(0, game.getBoard()[p._y][p._x], pawns[pos_r]);
            return;
        }
        else
        {
            std::uniform_int_distribution<> d_target(0, targets.size() - 1);
            std::shared_ptr<Pawn> target = targets[d_target(gen)];

            game.play(0, game.getBoard()[p._y][p._x], {target->getX(), target->getY()});
            return;
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
            total_att += p2->getAttack(); // Modifier : Prendre en compte l'attaque des pions dans le périmètre

        // Calculer l'attaque moyenne
        m_att = total_att / lp.size();

        // Enregistrer les pions avec les vies inférieures à la moyenne de attaques et qui ont des adversaires autour
        for (auto p2 : _listPawns)
            if (p2->getLife() <= m_att && getTargets(game, p2).size() != 0) low.push_back(p2);

        // 2.1 et 3
        if (low.size() != 0)
        {
            int score(9999);

            // Récupérer le pion le plus vulnérable (prendre aussi en compte le nombre de pions adverses ?)
            for (auto p2 : low)
            {
                if ((p2->getLife() * 2 + p2->getDefence()) < score)
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
                // Targets à partir d'une case nulle
                int s = getTargetsNull(game, p2, pawn->getMoveRadius()).size();
                if (s < aux)
                {
                    pos = p2;
                    aux = s;
                }
            }

            // SI AUCUNE CASE N'EST SURE, DÉCLENCHER LE COUP SPÉCIAL DE DÉFENSE SI POSSIBLE SINON ATTAQUER
            /*  S'il y a un pion qui a moins de vies que d'attaque du pion utilisé, alors attaquer ce pion
             *  Sinon utiliser la super defense
             */
            if (aux != 0)
            {
                QVector<std::shared_ptr<Pawn> > targets = getTargets(game, pawn);
                // Attaquer si les vies sont inférieures
                for (auto p2 : targets) {
                    if (p2->getLife() < pawn->getAttack())
                    {
                        game.play(0, pawn, {p2->getX(), p2->getY()});
                        return;
                    }
                    else if ((pawn->getType() &~ 1) == 0
                             && p2->getLife() < pawn->getAttack() * 2
                             && !pawn->specialAttackUsed())
                    {
                        game.playSpecial(0, pawn, p2);
                        return;
                    }
                }

                // Utiliser super défense si c'est un tank
                if ((pawn->getType() &~ 8) == 0
                        && !pawn->specialAttackUsed())
                {
                    game.playSpecial(0, pawn, {});
                    return;
                }
                else if ((pawn->getType() &~ 4) == 0
                         && !pawn->specialAttackUsed()
                         && targets.size() > 1)
                {
                    game.playSpecial(0, pawn, {}, targets);
                    return;
                }
                else // Attaquer sur le pion avec le moins de vies
                {
                    int vies(9999);
                    for (auto p2 : getTargets(game, pawn))
                    {
                        if (p2->getLife() < vies)
                        {
                            vies = p2->getLife();
                            pos = {p2->getX(), p2->getY()};
                        }
                    }

                    game.play(0, pawn, pos);
                    return;
                }
            }
            else
            {
                game.play(0, pawn, pos);
                return;
            }
        }
        else // 2.2 et 4
        {
            // Calculer la distance la plus minime avec un adversaire
            double dist(9999);

            for (auto p2 : _listPawns)
            {
                double x_p = static_cast<double>(p2->getX());
                double y_p = static_cast<double>(p2->getY());

                for (auto p3 : lp)
                {
                    double x_p2 = static_cast<double>(p3->getX());
                    double y_p2 = static_cast<double>(p3->getY());

                    double n_dist = calcul_distance(x_p, y_p, x_p2, y_p2);

                    if (n_dist <= dist)
                    {
                        p = {p2->getX(), p2->getY()};
                        pos = {p3->getX(), p3->getY()};
                        dist = n_dist;
                    }
                }
            }

            int x = pos._x - p._x;
            int y = pos._y - p._y;
            QVector<Position> pions_jouables = pawnsPossibles(game, game.getBoard()[p._y][p._x]);

            // Si le pion est dans le périmètre, on l'attaque
            if (pions_jouables.contains(pos))
            {
                game.play(0, game.getBoard()[p._y][p._x], pos);
                return;
            }

            // Récupérer le coefficient directeur le plus simplifié
            int i = PPDC(abs(x), abs(y));

            while (abs(x) > 1 && abs(y) > 1) {
                x = x / i;
                y = y / i;
            }

            // Se diriger vers la cible
            int x_a, y_a;
            bool x_b(false), y_b(false);
            Position aux = p;

            do {

                if (x < 0) // Analyse à gauche
                {
                    x_a = -1;

                    // Rechercher la limite du x dans les coups possibles
                    do {
                        aux = {aux._x - 1, aux._y};
                        if (!pions_jouables.contains(aux))
                        {
                            pos._x = (aux._x + 1);
                            x_b = true;
                            break;
                        }
                        else x_a--;
                    } while (x_a >= x);

                }
                else if (x > 0) // Analyse à droite
                {
                    x_a = 1;

                    // Rechercher la limite du x dans les coups possibles
                    do {
                        aux = {aux._x + 1, aux._y};
                        if (!pions_jouables.contains(aux))
                        {
                            pos._x = (aux._x - 1);
                            x_b = true;
                            break;
                        }
                        else x_a++;
                    } while (x_a <= x);
                }
                else x_b = true; // Pas de travail sur x (pion adverse sur l'axe des y du pion)

                if (y < 0) // Analyse en-dessous
                {
                    y_a = -1;

                    // Rechercher la limite du y dans les coups possibles
                    do {
                        aux = {aux._x, aux._y - 1};
                        if (!pions_jouables.contains(aux))
                        {
                            pos._y = (aux._y + 1);
                            y_b = true;
                            break;
                        }
                        else y_a--;
                    } while (y_a >= y);

                }
                else if (y > 0) // Analyse au-dessus
                {
                    y_a = 1;

                    // Rechercher la limite du y dans les coups possibles
                    do {
                        aux = {aux._x, aux._y + 1};
                        if (!pions_jouables.contains(aux))
                        {
                            pos._y = (aux._y - 1);
                            y_b = true;
                            break;
                        }
                        else y_a++;
                    } while (y_a <= y);
                }
                else y_b = true; // Pas de travail sur y (pion adverse sur l'axe des x du pion)
            } while (!x_b || !y_b); // On continue tant que la limite sur chaque axe n'a été atteint

            game.play(0, game.getBoard()[p._y][p._x], pos);
            return;
        }
    }
}

double Player_IA::calcul_distance(double x_1, double y_1, double x_2, double y_2)
{
    return sqrt(pow((x_2 - x_1), 2) + pow((y_2 - y_1), 2));
}

int Player_IA::PPDC(int a, int b)
{
    int i = 2;
    while (a%i != 0 && b%i != 0)
        i++;

    return i;
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
