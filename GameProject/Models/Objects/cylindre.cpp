#include "cylindre.h"

void Cylindre::createCylindre(float radius,float height,int stacks)
{
  float *cs =(float *) calloc(stacks,sizeof(float));
  float *sn =(float *) calloc(stacks,sizeof(float));
  int i;
  for( i = 0 ; i < stacks ; i++ )
  {
    float a = (2*M_PI*i)/stacks;
    sn[i] = sin(a);
    cs[i] = cos(a);
  }
  glPushMatrix();
  glBegin(GL_QUAD_STRIP);
  for( i = 0 ; i <= stacks ; i++ )
  {
    float x = radius*cs[i%stacks];
    float z = -radius*sn[i%stacks];
    glNormal3f(cs[i%stacks],0.0F,-sn[i%stacks]);
    glVertex3f(x,height/2,z);
    glVertex3f(x,-height/2,z);
  }
  glEnd();
  glBegin(GL_POLYGON);
  glNormal3f(0.0F,1.0F,0.0F);
  for( i = 0 ; i < stacks ; i++ )
  {
    float si = -sn[i];
    float ci = cs[i];
    glVertex3f(radius*ci,height/2,radius*si);
  }
  glEnd();
  glBegin(GL_POLYGON);
  glNormal3f(0.0F,-1.0F,0.0F);
  for( i = 0 ; i < stacks ; i++ )
  {
    float si = sn[i];
    float ci = cs[i];
    glVertex3f(radius*ci,-height/2,radius*si);
  }
  glEnd();
  free(cs);
  free(sn);
  glPopMatrix();
}
