#ifndef ENDGAMEVIEW_HPP
#define ENDGAMEVIEW_HPP

#include <QDialog>
#include <QtMath>
#include "Models/game.h"
#include <QDialogButtonBox>

namespace Ui {
class EndGameView;
}

class EndGameView : public QDialog
{
    Q_OBJECT

public:
    explicit EndGameView(int nbMonster, int nbTour, const QString &time, const STATE_GAME &val, const QString &name, QWidget *parent = nullptr);
    ~EndGameView();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EndGameView *ui;
};

#endif // ENDGAMEVIEW_HPP
