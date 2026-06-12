#ifndef _MENU_H
#define _MENU_H

#include<_common.h>
#include<_scene.h>
#include<_sounds.h>

typedef void (*LevelSelectCallback)(int);

class _menu : public _scene
{
public:
    _menu();
    virtual ~_menu();

    void init();
    void reset();
    void showMainMenu();
    void update(float, bool);
    void draw(float, bool, vec2);
    int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void setLevelSelectCallback(LevelSelectCallback cb);

private:
    LevelSelectCallback onLevelSelect;

    _quad landingPage;
    _quad mainMenuPage;
    _quad howToPlayPage;
    _quad selector;
    _quad howToPlayBackSelector;

    int menuScreen;
    int selectedItem;
    float landingTimer;

_sounds *snd;

void confirmSelection();
};

#endif
