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
  explicit ViewChoose(Controller *controller, Start start, Choose choose, std::shared_ptr<Player> player , QWidget *parent = nullptr);
  ~ViewChoose();

  void setPlayer(std::shared_ptr<Player> player);

private slots:
  void addPion(std::shared_ptr<Pawn>);
  void delPion(QHBoxLayout *_layout);
  void delPionSignal(std::shared_ptr<Pawn>);

signals :
    void UpdateListPionsGame(std::shared_ptr<Pawn>);
    void UpdateListPionsGameDel(std::shared_ptr<Pawn>);

private:
  Ui::ViewChoose *ui;
  Choose _Choose;
  Start _Start;
  std::shared_ptr<Player> _Player;

  QVBoxLayout *_ListPionAdd;
  QHBoxLayout *_MainLayout;
  QVBoxLayout *_RightLayout;

};

#endif // VIEWCHOOSE_HPP
