#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <memory>
#include "Models/start.hpp"
#include "Models/choose.hpp"
#include "Views/viewstart.hpp"
#include "Views/viewchoose.hpp"
#include "Views/viewgame.hpp"
#include "Controllers/game_managment.h"

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
   GameManagment *getGameManagement() const;

public slots :
  void setUserName(const QString &);
  void setDifficulty(Difficulty);
  void Play();
  void UpdateGame();
  void LoadGame();
  void PlayCanceled();

private:
  Start _Start;
  Choose _Choose;
  ViewStart *_ViewStart;
  ViewChoose *_ViewChoose;
  ViewGame *_ViewGame;
  GameManagment *_GameManagment;

};

#endif // CONTROLLER_HPP
