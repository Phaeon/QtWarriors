#ifndef PLAYER_IA_H
#define PLAYER_IA_H

#include "player.h"

/**
 * @brief The Player_IA class
 */
class Player_IA : public Player
{
private:
    // Gestion alpha-beta
    bool _existentiel;

public:
    Player_IA();
    Player_IA(const bool &player);

    void play(Game &, Difficulty _difficulty) override;

    double calcul_distance(double x_1, double y_1, double x_2, double y_2);
    int PPDC(int a, int b);

    // ALPHA_BETA tout modifier : retour + calcul évaluation
    float al_bet_(Game, float alpha, float beta, bool existenciel);
    float al_bet_(Game, unsigned int depth, float alpha, float beta, bool existenciel);

    float evaluation();

};

#endif // Player_IA_H
