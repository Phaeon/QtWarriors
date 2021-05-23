#ifndef OPENGLWIDGET_HPP
#define OPENGLWIDGET_HPP

#include <QGLWidget>
#include <QObject>
#include <QKeyEvent>
#include <memory>
#include "Models/Pawns/pawn.h"
#include "library.hpp"
#include "Models/Objects/tableau.h"
#include "Models/Monsters/warrior_3d_.h"
#include <QTimer>
#include "Models/Objects/fleche.h"

/**
 * @brief The OpenGLWidget class
 * Cette classe gère l'affichage du plateau ainsi que des monstres
 */
class OpenGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    void setMoveBoard();
    void chargePawns(QVector<std::shared_ptr<Pawn> >, QVector<std::shared_ptr<Pawn> >);
    void changeGameStatus();
    void updateArrow(qreal x, qreal z);
    void setPrintArrow();
    void setSelected();

signals:
    void boardHasMoved();

private:
    void rotateBy(int x, int y, int z);

    bool turn;
    GLuint size_tex;
    bool _printArrow;

    qreal x_rot;
    qreal y_rot;
    qreal z_rot;
    float x_distance;
    float z_distance;
    qreal xtransObj;
    qreal ztransObj;
    qreal _x;
    qreal _z;
    bool _seleted;

    GLuint textures[50];

    QVector<std::shared_ptr<Pawn>> _pawns, _pawnsAdv;

    QPoint last_pos;
    QTimer timer;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void chargeTexture(QString file_name);
};

#endif // OPENGLWIDGET_HPP
