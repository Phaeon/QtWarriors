#ifndef VIEWGAME_HPP
#define VIEWGAME_HPP

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QSpinBox>
#include "Models/Players/player.h"
#include "Models/Game.h"
#include "Views/view.hpp"
#include "Models/Game.h"

namespace Ui {
  class ViewGame;
}

/**
 * @brief The PositionPawn struct
 * Cette structure permet de mettre transporter les informations dans un signal nécessaire à la modification de la position d'un pion
 */
struct PositionPawn{
    int _x;
    int _y;
    int _Pawn;
};

/**
 * @brief The ViewGame class
 * Cette interface gère tout l'affichage d'une partie
 */
class ViewGame : public QDialog, View
{
  Q_OBJECT

public:
  explicit ViewGame(Controller *controller, std::shared_ptr<Player> player, std::shared_ptr<Player> playerEnemy, Game game, QWidget *parent = nullptr);
  ~ViewGame() override;

private slots:
  void UpdatePositionPawnSignal();
  void YouCanPlay();

signals :
    void UpdatePositionPawn(PositionPawn);

private:
  void UpdateDetailPawn(int index);
  void ClearDetailLayout() const;
  void ChoosePosition();
  void ClearChoosePositionLayout() const;
  void ChooseMovementAttack();

  Ui::ViewGame *ui;
  std::shared_ptr<Player> _Player;
  std::shared_ptr<Player> _PlayerEnemy;
  Game _Game;

  int _PawnChoose;
  bool _IsSelected;
  bool _AllIsPositioned;
  QSpinBox *_SpinBoxY;
  QSpinBox *_SpinBoxX;
  int _X;
  int _Y;
  bool _play;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // VIEWGAME_HPP
