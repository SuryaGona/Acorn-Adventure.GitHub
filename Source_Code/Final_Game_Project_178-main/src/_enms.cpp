#include "_enms.h"

_enms::_enms()
{
    //ctor
    pos.x =0;
    pos.y =-0.4;
    pos.z =-7;

    rot.x =0;
    rot.y =0;
    rot.z =0;

    scale.x =0.5;
    scale.y =0.5;
    scale.z =1.0;

    actionTrigger =2;

    velocity=30.0;
    t=0.1;
    theta=0.0;
}

_enms::~_enms()
{
    //dtor
}

void _enms::enmsInit(int x, int y, char *fileName)
{
    initQuad(fileName);
    xFrames =x;
    yFrames =y;

    xMin =0;
    xMax =1.0/(float)xFrames;
    yMax =1.0/(float)yFrames;
    yMin =0;
}

void _enms::enmsActions(float deltaT)
{
    timer += deltaT;
    switch(actionTrigger)
    {
        case STAND:
            xMin =0;
            xMax =1.0/(float)xFrames;
            yMax = 1.0/(float)yFrames;
            yMin = yMax-(1.0/(float)yFrames);
            break;

        case RIGHTWALK:

            if(timer>0.08)
             {

            xMax<xMin?(xMin =0,xMax = 1.0/(float)xFrames):NULL;
            xMin +=1.0/(float)xFrames;;
            xMax +=1.0/(float)xFrames;

            pos.x <=4.5?pos.x +=2*deltaT+0.2:actionTrigger=LEFTWALK;
            pos.y=-1.4;

              timer =0;
             }
             break;

        case LEFTWALK:
            if(timer>0.08)
             {
             xMax>xMin?(xMax =0,xMin = 1.0/(float)xFrames):NULL;
             xMin +=1.0/(float)xFrames;
             xMax +=1.0/(float)xFrames;

             pos.x >= -4.5?pos.x -= 2*deltaT+0.2:actionTrigger=RIGHTWALK;
             pos.y=-1.4;
             timer =0;
             }
             break;

        case ROLLEFT:
            if(timer>0.08)
            {
                theta=30.0*PI/180.0;
                rot.z-=(float)rand()/(float)(RAND_MAX)*100;
                pos.x-=velocity*t*cos(theta)/1500.0;
                pos.y+=(velocity*t*sin(theta)-0.5*GRAVITY*t*t)/300.0;

                pos.y>-1.5?t+=0.3:(t=0.1,pos.y=-1.4);
                pos.x<-4.5?(actionTrigger=RIGHTWALK,rot.z=0):NULL;

                timer=0;
            }
             break;

        case ROLRIGHT:
            if(timer>0.08)
            {
                theta=30.0*PI/180.0;
                rot.z+=(float)rand()/(float)(RAND_MAX)*100;
                pos.x+=velocity*t*cos(theta)/1500.0;
                pos.y+=(velocity*t*sin(theta)-0.5*GRAVITY*t*t)/300.0;

                pos.y>-1.5?t+=0.3:(t=0.1,pos.y=-1.4);
                pos.x>4.5?(actionTrigger=LEFTWALK,rot.z=0):NULL;

                timer=0;
            }
            break;

        default: break;
    }
}

void _enms::placeEmns(vec3 Epos, float timer)
{
    pos.x = Epos.x;
    pos.y = Epos.y;
    pos.z = Epos.z;
}

void _enms::drawEnms()
{
   updateQuad();
   drawQuad();
}
