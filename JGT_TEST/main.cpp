#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <vector>

#include "Objects/torus.h"
#include "Objects/fleche.h"
#include "initwindow.h"
#include "axes.h"
#include "displaylist.h"
#include "Objects/tile.h"
#include "tableau.h"
#include "Monsters/guerrier.h"
#include "Monsters/tank.h"
#include "Monsters/rogue.h"
#include "Monsters/wizard.h"

#include <X11/Xlib.h>
#include <GL/glx.h>

GLfloat x_rot =  0.0f;
GLfloat y_rot =  0.0f;
GLfloat z_rot =  0.0f;
GLfloat z = -15.0f;

float distance_case = 10.0f;

// PARAMS GUERRIER
GLfloat angle_attaque_guerrier = 0.0f;
GLfloat angle_queue_guerrier = 0.0f;

// PARAMS TANK
GLfloat angle_jambe = 0.0f;
GLfloat angle_bras_attaque = 0.0f;
GLfloat translation_jambe = 0.0f;
float saut_longueur = 0.0f;
float saut_hauteur = 0.0f;

// PARAMS ROGUE
GLfloat torus_rogue = 0.0f;
GLfloat translation_attaque_rogue = 0.0f;
GLfloat angle_pattes_rogue = 0.0f;

// PARAMS WIZARD
GLfloat angle_right_meca_arm = 0.0;
GLfloat angle_left_meca_arm = 0.0;
GLint compt_right_meca_arm = 0;
GLint debut_attaque = 1;

// GÉNÉRAL
int direction = 1; // 1 (z), 2 (-x), 3 (-z), 4 (x)
int saut = 0;
int attaque = 1;
int bouger_monstre = 1;
int bouger_jambes = 1;

/*
 *  A FAIRE : se mettre d'accord pour les textures des cases (et le fond aussi) et voir pour les mouvements : warrior mouvements et attaque, rogue mouvements a revoir,
 *  capacite : tous a faire (surement attaque queue pour warrior va devenir attaque spe)
 */

GLvoid Modelisation()
{
    InitializeScene();
    {
        //create_table();

        //fleche f(distance_case, 0, 0, 0);

        glScalef(0.5, 0.5, 0.5);

//WARRIOR
        /*glPushMatrix();
        {
            // ATTAQUE : TOUR PUIS COUP DE QUEUE
            if (attaque == 1)
            {
                if (angle_attaque_guerrier <= 360.f) angle_attaque_guerrier += 3.0f;
                else
                {
                    angle_attaque_guerrier = 0;
                    attaque = 0;
                }
                // Positionner la queue pour l'attaque
                if (angle_attaque_guerrier <= 180.0f)
                {
                    angle_queue_guerrier += 0.4f;
                } // A FAIRE : PIVOTER LA QUEUE POUR ALLER VERS L'ADVERSAIRE LORS DE L'ATTAQUE
            }
            if (saut) // Passer à la case d'après
            {
                if (saut_longueur < distance_case/2)
                {
                    saut_longueur += 0.03f;
                    saut_hauteur += 0.01f;
                }
                else if (saut_longueur >= distance_case/2 && saut_longueur < distance_case)
                {
                    saut_longueur += 0.03f;
                    saut_hauteur -= 0.01f;
                }
            }
            glRotatef(angle_attaque_guerrier, 0, 1, 0);

            if (direction == 1)
                glTranslatef(0.0, saut_hauteur, saut_longueur);
            else if (direction == 2)
                glTranslatef(-saut_longueur, saut_hauteur, 0.0f);
            else if (direction == 3)
                glTranslatef(0.0, saut_hauteur, -saut_longueur);
            else if (direction == 4)
                glTranslatef(saut_longueur, saut_hauteur, 0.0f);

            Guerrier G;
            G.displayGuerrier(angle_queue_guerrier);
        }
        glPopMatrix();*/

//TANK
        /*glPushMatrix();
        {
            //glTranslatef(8.5, -4.7, 0.0);
            // ATTAQUE : LEVER BRAS PUIS FRAPPER PUIS REVENIR COMME AVANT
            if (attaque == 1)
            {
                if (angle_bras_attaque <= 150.0f)
                {
                    angle_bras_attaque += 0.3f;
                } else attaque = 2;
            }
            else if (attaque == 2)
            { // A MODIFIER : LAISSER UN TEMPS AVANT DE REPOSER LE BRAS
                if (angle_bras_attaque >= 120.0f)
                {
                    angle_bras_attaque -= 0.3f;
                } else attaque = 0;
            }
            else
            {
                if (angle_bras_attaque >= 0.0f)
                {
                    angle_bras_attaque -= 0.3f;
                }
            }
            // MOUVEMENTS
            if (direction == 1)
            {
                glTranslatef(0.0, saut_hauteur, saut_longueur);
                glTranslatef(0.0, 0.0, translation_jambe);
            }
            else if (direction == 2)
            {
                glTranslatef(-saut_longueur, saut_hauteur, 0.0f);
                glTranslatef(-translation_jambe, 0.0, 0.0f);
            }
            else if (direction == 3)
            {
                glTranslatef(0.0, saut_hauteur, -saut_longueur);
                glTranslatef(0.0, 0.0, -translation_jambe);
            }
            else if (direction == 4)
            {
                glTranslatef(saut_longueur, saut_hauteur, 0.0f);
                glTranslatef(translation_jambe, 0.0, 0.0f);
            }
            if (saut) // Passer à la case d'après
            {
                if (saut_longueur < distance_case/2)
                {
                    saut_longueur += 0.03f;
                    saut_hauteur += 0.01f;
                }
                else if (saut_longueur >= distance_case/2 && saut_longueur < distance_case)
                {
                    saut_longueur += 0.03f;
                    saut_hauteur -= 0.01f;
                }
            }
            else
            {
                if (bouger_jambes)
                {
                    if (angle_jambe <= 20.0f)
                    {
                        angle_jambe += 0.5f;
                    } else bouger_jambes = 0;
                }
                else
                {
                    if (angle_jambe >= 0.0f)
                    {
                        angle_jambe -= 0.5f;
                    } else bouger_jambes = 1;
                }
                if (bouger_monstre)
                {
                    translation_jambe += 0.01f;
                }
            }
            glScalef(0.7, 1.5, 1.0);
            Tank k;
            k.displayTank(angle_jambe, angle_bras_attaque);
        }
        glPopMatrix();*/

//ROGUE
        /*glPushMatrix();
        {
            // ATTAQUE : RAYON
            if (attaque == 1)
            {
                glPushMatrix();
                {
                    if (direction == 1)
                        glTranslatef(0.0f, 0.0f, translation_attaque_rogue);
                    else if (direction == 2)
                        glTranslatef(-translation_attaque_rogue, 0.0f, 0.0f);
                    else if (direction == 3)
                        glTranslatef(0.0f, 0.0f, -translation_attaque_rogue);
                    else if (direction == 4)
                        glTranslatef(translation_attaque_rogue, 0.0f, 0.0f);

                    glutSolidSphere(0.4, 20, 20);
                    translation_attaque_rogue += 0.3f;
                }
                glPopMatrix();

                if (translation_attaque_rogue >= 20.0f) attaque = 0;
            }
            // MOUVEMENTS : BONDIR
            if (saut)
            { // A MODIFIER : ROTATION DES PATTES PEUT ETRE PLUS SMOOTH
                if (saut_longueur < distance_case/2)
                {
                    saut_longueur += 0.03f;
                    saut_hauteur += 0.01f;
                    angle_pattes_rogue -= 0.08f;
                }
                else if (saut_longueur >= distance_case/2 && saut_longueur < distance_case)
                {
                    saut_longueur += 0.03f;
                    saut_hauteur -= 0.01f;
                    angle_pattes_rogue += 0.08f;
                }
            }
            else // PRÉPARER LE SAUT (A MODIFIER)
            {
                if (true) ;
                else saut = 1;
            }
            if (direction == 1)
                glTranslatef(0.0, saut_hauteur, saut_longueur);
            else if (direction == 2)
                glTranslatef(-saut_longueur, saut_hauteur, 0.0f);
            else if (direction == 3)
                glTranslatef(0.0, saut_hauteur, -saut_longueur);
            else if (direction == 4)
                glTranslatef(saut_longueur, saut_hauteur, 0.0f);

            Rogue r;
            r.displayRogue(angle_pattes_rogue);
        }
        glPopMatrix();*/

//WIZARD
        glPushMatrix();
        {
            // MOUVEMENTS : TÉLÉPORTATION
            if (saut)
            {
                saut_longueur += distance_case;
                saut = 0;
            }
            else if (saut == 0) // ATTAQUE
            {
                // AJOUTER ATTAQUE
                if ((angle_right_meca_arm > -45) && (debut_attaque))
                {
                    angle_right_meca_arm -= 1.0;

                }
                else if (compt_right_meca_arm != 40)
                {
                    compt_right_meca_arm += 1;
                }
                else if ((compt_right_meca_arm = 40) && (angle_right_meca_arm < 0))
                {
                    debut_attaque = 0;
                    angle_right_meca_arm += 1.0;
                }

                // RETOUR
                saut_longueur -= distance_case;
                saut = 2;
            }
            /*if (direction == 1)
                glTranslatef(0.0f, 0.0f, saut_longueur);
            //else if (direction == 2)
                glTranslatef(-saut_longueur, 0.0f, 0.0f);
            //else if (direction == 3)
                glTranslatef(0.0, 0.0f, -saut_longueur);
            //else if (direction == 4)
                glTranslatef(saut_longueur, 0.0f, 0.0f);*/

            Wizard w;
            w.displayWizard(angle_right_meca_arm, angle_left_meca_arm);
        }
        glPopMatrix();
    }
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    return InitWindow(argc, argv, &Modelisation);
}
