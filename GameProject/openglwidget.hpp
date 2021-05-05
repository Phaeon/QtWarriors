#ifndef OPENGLWIDGET_HPP
#define OPENGLWIDGET_HPP

#include <QGLWidget>
#include <QObject>
#include <QKeyEvent>
#include "library.hpp"
#include "Models/Objects/tableau.h"
#include "Models/Objects/guerrier.h"
#include "Models/Objects/tank.h"
#include <QTimer>

/**
 * @brief The OpenGLWidget class
 * Cette classe gère l'affichage du plateau ainsi que des monstres
 */
class OpenGLWidget : public QGLWidget
{
    Q_OBJECT
public:
  explicit OpenGLWidget(QWidget *parent = nullptr);

private:
    void rotateBy(int x, int y, int z);

    bool turn;

    qreal x_rot;
    qreal y_rot;
    qreal z_rot;
    float x_distance;
    float z_distance;

    GLuint textures[1];

    QPoint last_pos;
    QTimer timer;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // OPENGLWIDGET_HPP
