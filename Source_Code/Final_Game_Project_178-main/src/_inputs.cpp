#include "_inputs.h"

_inputs::_inputs()
{
    //ctor

    isRotate =  false;
    isTranslate= false;
    isWPressed = false;
    isAPressed = false;
    isSPressed = false;
    isDPressed= false;
    isUpPressed=false;
    isDownPressed=false;
    isLeftPressed=false;
    isRightPressed=false;
    isSpacePressed=false;
    isShiftPressed=false;
}

_inputs::~_inputs()
{
    //dtor
}
void _inputs::keyPressed(_model *mdl)
{
    switch(wParam)
    {
        // Toggle flags up
        case VK_UP:    isUpPressed = true; break;   // Up arrow
        case 87:    isWPressed = true; break;       // W
        case VK_DOWN:  isDownPressed = true; break; // Down arrow
        case 83:  isSPressed = true; break;         // S
        case VK_LEFT:  isLeftPressed = true; break; // Left arrow
        case 65:  isAPressed = true; break;         // A
        case VK_RIGHT: isRightPressed = true; break;// Right Arrow
        case 68: isDPressed = true; break;          // D
        default: break;
    }
}

void _inputs::keyPressed(_player* qD)
{
    switch(wParam)
    {
        case VK_LEFT:   isLeftPressed=true; qD->facingLeft=true;    qD->actionTrigger = qD->LEFTWALK;  break;
        case 65:  isAPressed = true; break; qD->facingLeft=true;    qD->actionTrigger = qD->LEFTWALK;  break;         // A
        case VK_RIGHT:  isRightPressed=true; qD->facingLeft=false;   qD->actionTrigger = qD->RIGHTWALK; break;
        case 68: isDPressed = true; break;  qD->facingLeft=false;   qD->actionTrigger = qD->RIGHTWALK; break;         // D
        case VK_UP:     isUpPressed=true; qD->actionTrigger = qD->JUMP;     break;
        case 87:    isWPressed = true; break;  qD->actionTrigger = qD->JUMP;     break;      // W
        case VK_SPACE:  isSpacePressed=true; qD->actionTrigger = qD->JUMP;     break;
        case VK_SHIFT:  isShiftPressed=true; break;
        default:break;
    }
}


void _inputs::keyUp(_player* qD)
{
    switch(wParam)
    {
        // Toggle flags down
        case VK_UP:    isUpPressed = false; qD->actionTrigger = qD->STAND; break;   // Up arrow
        case 87:    isWPressed = false; qD->actionTrigger = qD->STAND; break;       // W
        case VK_DOWN:  isDownPressed = false; qD->actionTrigger = qD->STAND; break; // Down arrow
        case 83:  isSPressed = false; qD->actionTrigger = qD->STAND; break;         // S
        case VK_LEFT:  isLeftPressed = false; qD->actionTrigger = qD->STAND; break; // Left arrow
        case 65:  isAPressed = false; qD->actionTrigger = qD->STAND; break;         // A
        case VK_RIGHT: isRightPressed = false; qD->actionTrigger = qD->STAND; break;// Right Arrow
        case 68: isDPressed = false; qD->actionTrigger = qD->STAND; break;          // D
        case VK_SPACE: isSpacePressed = false; break;//space
        case VK_SHIFT: isShiftPressed=false; break;
        default: break;
    }
}

void _inputs::mouseEventDown(_model* mdl,double x, double y)
{
    prevMx =x;
    prevMy =y;

    switch(wParam)
    {
    case MK_LBUTTON:
        isRotate = true;
        break;
    case MK_RBUTTON:
        isTranslate=true;
        break;
    case MK_MBUTTON: break;
    default: break;

    }
}

void _inputs::mouseEventUp()
{
    isRotate = false;
    isTranslate= false;
}

void _inputs::mouseMove(_model *mdl,double x, double y)
{
    if(isRotate)
    {
        mdl->rotation.x+=(x-prevMx)/3.0;
        mdl->rotation.y+=(y-prevMy)/3.0;
    }
    if(isTranslate)
    {
        mdl->pos.x+=(x-prevMx)/100.0;
        mdl->pos.y+=(y-prevMy)/100.0;
    }

    prevMx =x;
    prevMy =y;
}

void _inputs::mouseWheel(_model *mdl,double delta)
{
    mdl->pos.z +=delta/100.0;
}

void _inputs::keyPressed(_modelVBO* mdlv)
{
     switch(wParam)
    {

        case 65:
            mdlv->rot.y -=1.0;
        break;

        case 68:
            mdlv->rot.y +=1.0;
        break;

        case 87:
            mdlv->rot.x -=1.0;
        break;

        case 83:
            mdlv->rot.x +=1.0;
        break;
    }

}

void _inputs::mouseEventDown(_modelVBO* mdlv, double x, double y)
{

}

void _inputs::mouseMove(_modelVBO* mdlv, double x, double y)
{

}

void _inputs::mouseWheel(_modelVBO* mdlv, double delta)
{

}

