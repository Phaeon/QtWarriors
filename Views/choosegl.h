#ifndef CHOOSEGL_H
#define CHOOSEGL_H

#include <QGLWidget>
#include "library.hpp"
#include <QTimer>
#include "Models/Monsters/pawngl.h"
#include <memory>

class ChooseGL : public QGLWidget
{
        Q_OBJECT
public:
    explicit ChooseGL(std::shared_ptr<PawnGL>pawn, QWidget *parent = nullptr);
    ~ChooseGL();

private:
    std::shared_ptr<PawnGL> _pawn;

    qreal x_rot;
    qreal y_rot;
    qreal z_rot;
    float z_distance;
    QTimer *timer;

    GLuint size_tex_;
    GLuint textures[50];

    void chargeTexture(QString file_name);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif // CHOOSEGL_H
