#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <memory>
#include "Models/start.hpp"
#include "Models/choose.hpp"
#include "Views/startView.hpp"
#include "Views/chooseView.hpp"
#include "Views/gameView.hpp"
#include "Controllers/game_managment.h"
#include "Views/endgameview.hpp"

/**
 * @brief The Controller class
 */
class Controller : public QObject
{
  Q_OBJECT
public:
    Controller();
    ~Controller();

    Start getStart() const;
    Choose getChoose() const;
    GameManagment * getGameManagement() const;

public slots :
    void setUserName(const QString &);
    void setDifficulty(Difficulty);
    void play();
    void updateGame();
    void loadGame();
    void playCanceled();
    void treatmentOfGame();
    void treatmentOfEndGame(STATE_GAME);

private:
    Start _start;
    Choose _choose;
    ViewStart * _viewStart;
    ViewChoose * _viewChoose;
    ViewGame * _viewGame;
    EndGameView *_endGameView;
    GameManagment * _gameManagment;

};

#endif // CONTROLLER_HPP
