#include "choosegl.h"

ChooseGL::ChooseGL(std::shared_ptr<PawnGL> pawn, QWidget *parent) : QGLWidget(parent), _pawn(pawn), timer(new QTimer()), size_tex_(0)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(16);
}

ChooseGL::~ChooseGL()
{
    delete timer;
}

void ChooseGL::initializeGL()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glClearColor(0.0, 0.0, 0.0, 1);
    glEnable(GL_DEPTH_TEST);

    x_rot = 0;
    y_rot = 0;
    z_rot = 0;
    z_distance = -2;

    // Tank
    chargeTexture(":/img/tank_3.jpg"); // Corps (0)
    chargeTexture(":/img/tank_2.jpg"); // Jambes (1)

    // Wizard
    chargeTexture(":/img/wizard_1.jpg"); // Boules (2)
    chargeTexture(":/img/wizard_2.jpg"); // Bout bras (3)
    chargeTexture(":/img/wizard_3.jpg"); // Bout bras_2 (4)
    chargeTexture(":/img/wizard_4.jpg"); // Bras (5)
    chargeTexture(":/img/wizard_5.jpg"); // Robe (6)

    // Warrior
    chargeTexture(":/img/warrior_1.jpg"); // Cornes (7)

    // Rogue
    // Cornes + dos : ID 7

    chargeTexture(":/img/tile.jpg"); // Cases (8)
}

/**
 * @brief OpenGLWidget::paintGL : Dessine sur la scène
 */
void ChooseGL::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    makeCurrent();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, 1.0 * width() / height(), 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(3, 5, 3, -100, -50, -100, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    glTranslatef(0.0, 0.0, z_distance);

    glPushMatrix();
    {
       glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
       glScalef(0.15f, 0.20f, 0.15f);
       _pawn->create_monster(textures);
    }
    glPopMatrix();
    y_rot+= 10;

}

/**
 * @brief OpenGLWidget::resizeGL : Cette fonction virtuelle est appelée chaque fois que le widget a été redimensionné.
 * @param width : Largeur du QWidget
 * @param height : Hauteur du QWidget
 */
void ChooseGL::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void ChooseGL::chargeTexture(QString file_name)
{
    // GESTION TEXTURES (https://openclassrooms.com/forum/sujet/textures-opengl-et-qt)
    QImage qim_Texture;
    QImage qim_TempTexture;

    if (!qim_TempTexture.load(file_name)) // FICHIER A CHARGER (ENREGISTRÉ DANS RESSOURCES.QRC)
    {
        throw std::bad_alloc();
    }
    qim_Texture = QGLWidget::convertToGLFormat( qim_TempTexture );

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textures[size_tex_]); // Argument 1 : Nombre de textures différentes
    glBindTexture(GL_TEXTURE_2D, textures[size_tex_]);

    // NE PAS MODIFIER
    glTexImage2D( GL_TEXTURE_2D, 0, 4, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glDisable(GL_TEXTURE_2D);

    size_tex_++;
}
