#include "openglwidget.hpp"
#include <iostream>
#include <QImage>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/**
 * @brief OpenGLWidget::OpenGLWidget : Créer un widget OpenGL
 * @param parent :Objet QWidget
 */
OpenGLWidget::OpenGLWidget(QWidget *parent) :  QGLWidget(parent)
{
  //setFocusPolicy(Qt::StrongFocus);
  //Mets à jour le widget toutes les 16 millisecondes
  connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
  timer.start(16);
}

/**
 * @brief OpenGLWidget::initializeGL : initialise la scène
 */
void OpenGLWidget::initializeGL()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glClearColor(0.0, 0.0, 255.0, 1);
    glEnable(GL_DEPTH_TEST);

    turn = false;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;
    z_distance = 0.5;
    x_distance = 0.5;

    // GESTION TEXTURES (A MODIFIER: FAIRE UNE FONCTION ANNEXE POUR CHARGER UNE TEXTURE À LA FOIS: https://openclassrooms.com/forum/sujet/textures-opengl-et-qt)
    QImage qim_Texture;
    QImage qim_TempTexture;
    if (!qim_TempTexture.load(":/img/texture.jpg")) // FICHIER A CHARGER (ENREGISTRÉ DANS RESSOURCES.QRC)
    {
        throw std::bad_alloc();
    }
    qim_Texture = QGLWidget::convertToGLFormat( qim_TempTexture );

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, textures); // Argument 1 : Nombre de textures différentes
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    // NE PAS MODIFIER
    glTexImage2D( GL_TEXTURE_2D, 0, 4, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

}

/**
 * @brief OpenGLWidget::paintGL : Dessine sur la scène
 */
void OpenGLWidget::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    makeCurrent();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, 1.0 * width() / height(), 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 5, 3, -100, -50, -100, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(x_distance, 0.0, z_distance);


      glPushMatrix();
      {
          create_table();
          glTranslatef(0.0, 2.0, 0.0);
          glColor3f(0.0, 0.0, 0.0);
          glutSolidCube(1.0);
      }
      glPopMatrix();

      //Guerrier G;
      //G.displayGuerrier();
      //Tank T;
      //T.displayTank();

      glEnable(GL_TEXTURE_2D); // TOUJOURS ENABLE EN DÉBUT D'APPLICATION DE TEXTURE
      glTranslatef(0.0, 3.0, 0.0);
      glBindTexture(GL_TEXTURE_2D, textures[0]); // L'indice c'est l'ID de la texture enregistrée dans le chargement
      glBegin(GL_QUADS); // PETIT SOUCIS... COORDONNEES DE LA TEXTURE POUR UN POLYGONE ?
      {
          glColor3f(255, 255, 255);

          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(1.0, 1.0, 0.0);

          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(1.0, -1.0, 0.0);

          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(-1.0, -1.0, 0.0);

          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-1.0, 1.0, 0.0);
      }
      glEnd();
      glDisable(GL_TEXTURE_2D); // TOUJOURS DISABLE APRÈS AVOIR APPLIQUÉ UNE TEXTURE


    if(turn){

        if(z_distance < 11.0f) z_distance += 0.15f;
        if(x_distance < 10.0f) x_distance += 0.15f;
        if(y_rot < 3000) rotateBy(0, 40, 0);

    }
    else {
        if(z_distance > 0.5f) z_distance -= 0.15f;
        if(x_distance > 0.5f) x_distance -= 0.15f;
        if(y_rot > 0) rotateBy(0, -40, 0);
    }

}

/**
 * @brief OpenGLWidget::resizeGL : Cette fonction virtuelle est appelée chaque fois que le widget a été redimensionné.
 * @param width : Largeur du QWidget
 * @param height : Hauteur du QWidget
 */
void OpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * @brief OpenGLWidget::keyPressEvent : Permet avec différent touche du clavier de bouger un objet
 * @param event : Capture les évènements clavier
 */
void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_A:
            if(turn) turn = false;
            else turn = true;
            break;
    case Qt::Key_B:
            std::cout << y_rot;
        break;
      }
}

/**
 * @brief OpenGLWidget::mousePressEvent : Mets à jour last_pos
 * @param event : Capture les évènements du clique de la souris
 */
void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

/**
 * @brief OpenGLWidget::mouseMoveEvent : Mets à jour last_pos, fait une rotation de la scène
 * @param event : Capture les évènements du déplacement de la souris
 */
void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
     int dx = event->x() - last_pos.x();
     int dy = event->y() - last_pos.y();

     if (event->buttons() & Qt::RightButton)
     {
         rotateBy(dy*8, 0, 0);
         rotateBy(0, dx*8, 0);
     }
     last_pos = event->pos();
}

/**
 * @brief OpenGLWidget::wheelEvent : Mets à jour distance
 * @param event : Capture les évènements de la molette de la souris
 */
void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    z_distance *= 1.0 + (1.0 * event->delta() / 1200.0);
}

/**
 * @brief OpenGLWidget::rotateBy : Mets à jour x_rot, y_rot et z_rot
 * @param x
 * @param y
 * @param z
 */
void OpenGLWidget::rotateBy(int x, int y, int z)
{
    x_rot += x;
    y_rot += y;
    z_rot += z;
}

