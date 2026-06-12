#include "_scene.h"

_scene::_scene()
{
    //ctor
}

_scene::~_scene()
{
    //dtor
}

void _scene::init()
{
    glewInit();
    glClearColor(0.0,0.0,0.0,1.0); // background color
    glClearDepth(1.0);             // depth test value;
    glEnable(GL_DEPTH_TEST);       // Enable depth test
    glDepthFunc(GL_LEQUAL);        // True for less or Equal

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void _scene::reset()
{
    return;
}

void _scene::draw(float, bool, vec2)
{
    return;
}

void _scene::update(float, bool)
{
    return;
}

int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}
