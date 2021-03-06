#include "openglwidget.hpp"
/**
 * @brief OpenGLWidget::OpenGLWidget : Créer un widget OpenGL
 * @param parent :Objet QWidget
 */
OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QGLWidget(parent), size_tex(0), _printArrow(false), _seleted(false), _mouvArrow(true), _title(""), _pawns(), _pawnsAdv()
{
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
    qglClearColor(QColor(32, 178, 170, 1));
    //glClearColor(32.0, 178.0, 170.0, 1);
    glEnable(GL_DEPTH_TEST);

    x_rot = 0;
    y_rot = 0;
    z_rot = 0;
    z_distance = 0.5;
    x_distance = 0.5;
    _zTransArrow = 0.0;
    _x = 0;
    _z = 0;

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
    gluLookAt(-5, 9, 4, -5, 0, -5, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(x_distance, 0.0, z_distance);


    glPushMatrix();
    {
        create_table(textures[8]);
    }
    glPopMatrix();

    for(auto i = _pawns.begin() ; i != _pawns.end() ; ++i){
        if((*i)->isDead()){
            _pawns.erase(i);
            break;
        }
    }

    for(auto i = _pawnsAdv.begin() ; i != _pawnsAdv.end() ; ++i){
        if((*i)->isDead()){
            _pawnsAdv.erase(i);
            break;
        }
    }

    for (auto i : _pawns)
    {

        glPushMatrix();
        {
            if (i->getType() == 1) glTranslatef(0.0f - i->getX() * 1.3f, 1.7f, -1.3f - i->getY() * 1.3f);
            else if (i->getType() == 2) glTranslatef(0.0f - i->getX() * 1.3f, 1.1f, -1.3f - i->getY() * 1.3f);
            else if (i->getType() == 4) glTranslatef(0.0f - i->getX() * 1.3f, 1.1f, -1.3f - i->getY() * 1.3f);
            else if (i->getType() == 8) glTranslatef(0.0f - i->getX() * 1.3f, 0.6f, -1.3f - i->getY() * 1.3f);

            glRotatef(i->get3DPawn()->getRotX(), 1, 0, 0);
            glRotatef(i->get3DPawn()->getRotY(), 0, 1, 0);
            glRotatef(i->get3DPawn()->getRotZ(), 0, 0, 1);

            glScalef(0.15f, 0.20f, 0.15f);
            i->get3DPawn()->create_monster(textures);
        }
        glPopMatrix();
    }

    for (auto i : _pawnsAdv)
    {

        glPushMatrix();
        {        
            if (i->getType() == 1) glTranslatef(0.0f - i->getX() * 1.3f, 1.7f, -1.3f - i->getY() * 1.3f);
            else if (i->getType() == 2) glTranslatef(0.0f - i->getX() * 1.3f, 1.1f, -1.3f - i->getY() * 1.3f);
            else if (i->getType() == 4) glTranslatef(0.0f - i->getX() * 1.3f, 1.1f, -1.3f - i->getY() * 1.3f);
            else if (i->getType() == 8) glTranslatef(0.0f - i->getX() * 1.3f, 0.6f, -1.3f - i->getY() * 1.3f);

            glRotatef(i->get3DPawn()->getRotX(), 1, 0, 0);
            glRotatef(i->get3DPawn()->getRotY(), 0, 1, 0);
            glRotatef(i->get3DPawn()->getRotZ(), 0, 0, 1);

            glScalef(0.15f, 0.20f, 0.15f);
            i->get3DPawn()->create_monster(textures);
        }
        glPopMatrix();
    }

    glPushMatrix();
    {
        if(_printArrow){
            if(_seleted)
                glColor3f(0.0f, 0.0f, 0.0f);
            else
                glColor3f(255.0f, 0.0f, 0.0f);

            glTranslatef(0.0f - _x * 1.3f, 2.0f + _zTransArrow, -1.3f - _z * 1.3f);
            fleche _arrow(1, 0, 0, 0);
            _arrow.creer_fleche(textures);

            if (_mouvArrow)
            {
              if(_zTransArrow <= 0.3f) _zTransArrow += 0.005f;
              else _mouvArrow = false;
            }
            else
            {
              if (_zTransArrow >= 0.0f) _zTransArrow -= 0.005f;
              else _mouvArrow = true;
            }
        }
    }
    glPopMatrix();

    glPopMatrix();
    {
        qglColor(Qt::white);
        renderText(width()/2, 40, _title, QFont("Accanthis ADF Std", 25));
    }
    glPopMatrix();

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
 * @brief OpenGLWidget::chargeTexture
 * @param file_name
 */
void OpenGLWidget::chargeTexture(QString file_name)
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
    glGenTextures(1, &textures[size_tex]); // Argument 1 : Nombre de textures différentes
    glBindTexture(GL_TEXTURE_2D, textures[size_tex]);

    // NE PAS MODIFIER
    glTexImage2D( GL_TEXTURE_2D, 0, 4, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glDisable(GL_TEXTURE_2D);

    size_tex++;
}

/**
 * @brief OpenGLWidget::chargePawns
 * @param pawns
 * @param enemyPawns
 */
void OpenGLWidget::chargePawns(QVector<std::shared_ptr<Pawn> > pawns, QVector<std::shared_ptr<Pawn> > enemyPawns)
{
    _pawns = pawns;
    _pawnsAdv = enemyPawns;
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

/**
 * @brief OpenGLWidget::updateArrow
 * @param x
 * @param z
 */
void OpenGLWidget::updateArrow(qreal x, qreal z)
{
    _x = x;
    _z = z;
}

/**
 * @brief OpenGLWidget::setPrintArrow
 */
void OpenGLWidget::setPrintArrow()
{
    this->_printArrow = (_printArrow) ? false : true;
}

/**
 * @brief OpenGLWidget::setSelected
 */
void OpenGLWidget::setSelected()
{
    this->_seleted = (_seleted) ? false : true;
}

/**
 * @brief OpenGLWidget::updateTitle
 * @param title
 */
void OpenGLWidget::updateTitle(const QString &title)
{
    _title = title;
}

