#ifndef _SCENE_H
#define _SCENE_H

#include<_common.h>
#include<_lightsettings.h>
#include<_model.h>
#include<_inputs.h>
#include<_modelvbo.h>
#include<_parallax.h>
#include<_quad.h>
#include<_player.h>
#include<_sounds.h>
#include<_enms.h>
#include<_collisioncheck.h>

class _scene
{
    public:
        _scene();
        virtual ~_scene();

        virtual void init();
        virtual void reset();
        virtual void draw(float,bool,vec2);
        virtual void update(float, bool);
        virtual int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    protected:

    private:
};

#endif // _SCENE_H
