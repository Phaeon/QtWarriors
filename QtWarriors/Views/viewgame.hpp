#ifndef VIEWGAME_HPP
#define VIEWGAME_HPP

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QSpinBox>
#include <QTimer>
#include "Models/Players/player.h"
#include "Models/Game.h"
#include "Views/view.hpp"
#include "Models/Game.h"

namespace Ui {
  class ViewGame;
}

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
    void deleteTimer();

private slots:
    void updatePositionPawnSignal();
    void youCanPlay();
    void playerPlay();
    void moveBoard();


signals :
    void updatePositionPawn(PositionPawn);

private:
    void updateDetailPawn(int index);
    void clearDetailLayout() const;
    void choosePosition();
    void clearChoosePositionLayout() const;
    void chooseMovementAttack();
    void detailTarget();
    void clearDetailTarget() const;

    Ui::ViewGame * ui;
    std::shared_ptr<Player> _player;
    std::shared_ptr<Player> _playerEnemy;
    Game _game;

    int _pawnChosen;
    bool _isSelected;
    bool _allArePositioned;
    QSpinBox * _spinBoxY;
    QSpinBox * _spinBoxX;
    int _x;
    int _y;
    bool _play;
    QTimer * time;
    QPushButton * _buttonValidate;


protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // VIEWGAME_HPP
