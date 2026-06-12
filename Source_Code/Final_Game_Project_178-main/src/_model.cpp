#include "_model.h"

_model::_model()
{
    //ctor
}

_model::~_model()
{
    //dtor
}
void _model::initModel()
{
    rotation.x = rotation.y=rotation.z =0;
    pos.x=pos.y =0;
    pos.z =-8;
    scale.x =scale.y=scale.z =1;
}

void _model::drawModel()
{
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);           // set base color

    glTranslatef(pos.x,pos.y,pos.z);  // place the object
    glRotatef(rotation.x, 1,0,0);     // rotation around x
    glRotatef(rotation.y, 0,1,0);     // rotation around y
    glRotatef(rotation.z, 0,0,1);     // rotation around z
    glScalef(scale.x,scale.y,scale.z);// resize object

    glutSolidTeapot(1.5);

    glPopMatrix();
}
