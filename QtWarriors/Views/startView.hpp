#ifndef VIEWSTART_HPP
#define VIEWSTART_HPP

#include <QMainWindow>
#include <QMessageBox>
#include "Models/start.hpp"
#include "Views/view.hpp"

namespace Ui {
  class ViewStart;
}

/**
 * @brief The ViewStart class
 * Cette interface gère l'affichage de la première fenêtre où l'on indique le nom du joueur ainsi que la difficulté
 */
class ViewStart : public QMainWindow, View
{
  Q_OBJECT

public:
  explicit ViewStart(Controller * controller, QWidget * parent = nullptr);
  ~ViewStart();

private slots :
  void about();
  void help();
  void on_PlayButton_clicked();

signals :
  void updateUserName(const QString &);
  void updateDifficulty(Difficulty);
  void play();

private:
  void createActions();
  void createMenu();

  Ui::ViewStart * ui;
  QAction * _aboutAction;
  QAction * _helpAction;
};

#endif // VIEWSTART_HPP
