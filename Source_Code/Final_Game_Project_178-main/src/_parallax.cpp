#include "_parallax.h"

_parallax::_parallax()
{
    //ctor
    xMax = yMax =1.0;
    xMin = yMin =0.0;

    scale.x=0.3;
    scale.y=0.3;
    scale.z=1.0;
}

_parallax::~_parallax()
{
    //dtor
}
void _parallax::initPrlx(char* filename)
{
    bckGrnd->loadTexture(filename);
}

void _parallax::scroll(bool Auto, int dir, float speed)
{
    if(Auto)
    {
        switch(dir)
        {
        case LEFT:
            xMin -=speed;
            xMax -=speed;
            break;

        case RIGHT:
            xMax +=speed;
            xMin +=speed;
            break;

        case UP:
             yMin +=speed;
             yMax +=speed;
            break;

        case DOWN:
             yMin -=speed;
             yMax -=speed;
            break;
         default: break;
        }//end case
    }// end if
}

void _parallax::drawBckGrnd(float width, float height)
{
    int closeToScreen=-8;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    bckGrnd->BindTexture();

    glScalef(scale.x,scale.y,scale.z);
    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
      glTexCoord2f(xMin,yMax);
      glVertex3f(-width/height,-1,closeToScreen);

      glTexCoord2f(xMax,yMax);
      glVertex3f(width/height,-1,closeToScreen);

      glTexCoord2f(xMax,yMin);
      glVertex3f(width/height,1,closeToScreen);

      glTexCoord2f(xMin,yMin);
      glVertex3f(-width/height,1,closeToScreen);

    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();

}
