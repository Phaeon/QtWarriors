#ifndef PLAYER_IA_H
#define PLAYER_IA_H

#include "player.h"

/**
 * @brief The Node struct
 */
struct Node {
    Node()
        : parent_node(nullptr), children(), average_score(0), times_used(0), playing(nullptr), pawn_after()
    {}

    Node(std::shared_ptr<Node> parent, std::shared_ptr<Pawn> pion, Position pos)
        : parent_node(parent), children(), average_score(0), times_used(0), playing(pion), pawn_after(pos)
    {}

    std::shared_ptr<Node> parent_node;
    QVector<std::shared_ptr<Node> > children;

    float average_score;
    unsigned int times_used;

    std::shared_ptr<Pawn> playing; // Pawn qui a servi à en arriver là
    Position pawn_after; // Position de la position après l'attaque
};


/**
 * @brief The Player_IA class
 */
class Player_IA : public Player
{
private:
    // Gestion alpha-beta
    bool _existentiel;

    // Gestion mcts
    static std::shared_ptr<Node> _tree;

public:
    Player_IA();
    Player_IA(const bool &player);

    Position search_next_shot(Game, Position &, Difficulty _difficulty) override;

    double calcul_distance(double x_1, double y_1, double x_2, double y_2);


    // ALPHA_BETA tout modifier : retour + calcul évaluation
    float al_bet_(Game, float alpha, float beta, bool existenciel);
    float al_bet_(Game, unsigned int depth, float alpha, float beta, bool existenciel);

    float evaluation();

    // MCTS
    void mcts_(Game);

    std::shared_ptr<Node> simulation(Game, std::shared_ptr<Node>);
    int rollout(Game &, std::shared_ptr<Node>);
    void callback(std::shared_ptr<Node>, int value);

    float ubc(double w, double n, double N);

};

#endif // Player_IA_H
