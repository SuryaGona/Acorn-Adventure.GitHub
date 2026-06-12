#ifndef _GAME_H
#define _GAME_H

#include<_common.h>
#include<_scene.h>
#include<_menu.h>
#include<_level1.h>
#include<_level2.h>
#include<_level3.h>


class _game
{
public:
    _game();
    virtual ~_game();

    void init();
    void render();
    void reSize(GLint, GLint);
    int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void mouseMapping(int, int);
    void setLevel(int n);

    vec2 dim;
    vec3 mouse;
    static float deltaTime;

    _menu   *menu = new _menu();
    _level1 *lvl1 = new _level1();
    _level2 *lvl2 = new _level2();
    _level3 *lvl3 = new _level3();

    _scene *currentScene;

    bool isPaused;
    _quad pauseHelp;
    bool showLevelIntro;
int pendingLevel;

_quad levelIntro;

protected:

private:
};

#endif
