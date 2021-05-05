#ifndef GAME_HPP
#define GAME_HPP

#include <QVector>
#include <QString>

class Game
{
public:
  Game();
  Game(const Game &g);
  ~Game();

  QVector<QString> getListPionsGame() const;
  void setListPionGame(const QString &name);
  void setListPionGameDel(const QString &name);
  void ViewRejected();
  QString getPion(int index) const;

private:
    QVector<QString> _ListPionsGame;

};

#endif // GAME_HPP
