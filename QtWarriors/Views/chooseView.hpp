#ifndef VIEWCHOOSE_HPP
#define VIEWCHOOSE_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Models/start.hpp"
#include "Models/choose.hpp"
#include "Models/Players/player.h"
#include "Views/view.hpp"
#include "Views/choosegl.h"

namespace Ui {
  class ViewChoose;
}

/**
 * @brief The ViewChoose class
 * Cette interface gère la fenêtre où l'on va choisir les monstres
 */
class ViewChoose : public QDialog, View
{
  Q_OBJECT

public:
    explicit ViewChoose(Controller * controller, Start start, Choose choose, std::shared_ptr<Player> player , QWidget * parent = nullptr);
    ~ViewChoose();

    void setPlayer(std::shared_ptr<Player>);

private slots:
    void addPawn(std::shared_ptr<Pawn>);
    void delPawn(QHBoxLayout * _layout);
    void delPawnSignal(std::shared_ptr<Pawn>);

signals :
    void updatePawns(std::shared_ptr<Pawn>);
    void updateDeletedPawns(std::shared_ptr<Pawn>);

private:
    Ui::ViewChoose * ui;
    Choose _choose;
    Start _start;
    std::shared_ptr<Player> _player;
    ChooseGL * _gl;

    QVBoxLayout * _addedPawns;
    QHBoxLayout * _mainLayout;
    QVBoxLayout * _rightLayout;

};

#endif // VIEWCHOOSE_HPP
