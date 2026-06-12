#include "_game.h"

auto lastTime = chrono::steady_clock::now();

static _game *gameInstance = nullptr;

static void onLevelSelected(int level)
{
    if(gameInstance)
        gameInstance->setLevel(level);
}

_game::_game()
{
    gameInstance = this;

    mouse.x = 0.0;
    mouse.y = 0.0;
    mouse.z = -6.0;

    isPaused = false;

    menu->setLevelSelectCallback(onLevelSelected);
    lvl1->setLevelSelectCallback(onLevelSelected);
    lvl2->setLevelSelectCallback(onLevelSelected);

    showLevelIntro = false;
    pendingLevel = 0;
    currentScene = menu;
}

_game::~_game()
{
}

void _game::setLevel(int n)
{
    isPaused = false;

    if(n == 0)
    {
        if(lvl1 && lvl1->snd && lvl1->snd->sndEng)
            lvl1->snd->sndEng->stopAllSounds();

        if(lvl2 && lvl2->snd && lvl2->snd->sndEng)
            lvl2->snd->sndEng->stopAllSounds();

        if(lvl3 && lvl3->snd && lvl3->snd->sndEng)
            lvl3->snd->sndEng->stopAllSounds();

        currentScene = menu;
        menu->showMainMenu();
        return;
    }

    pendingLevel = n;

    if(n == 1)
        levelIntro.initQuad((char*)"images/cutlevel1.png");

    if(n == 2)
        levelIntro.initQuad((char*)"images/cutlevel2.png");

    if(n == 3)
        levelIntro.initQuad((char*)"images/cutlevel3.png");

    levelIntro.scale.x = 4.0f;
    levelIntro.scale.y = 2.68f;
    levelIntro.scale.z = 1.0f;

    levelIntro.pos.x = 0.0f;
    levelIntro.pos.y = 0.0f;
    levelIntro.pos.z = -7.0f;

    showLevelIntro = true;
}

void _game::init()
{
    _textureLoader::textureCache.clear();

    _scene* previousScene = currentScene;

    menu->init();

    if(previousScene == lvl1)
        lvl1->init();
    else if(previousScene == lvl2)
        lvl2->init();
    else if(previousScene == lvl3)
        lvl3->init();

    currentScene = previousScene;

    pauseHelp.initQuad((char*)"images/pausehelp.png");

    pauseHelp.scale.x = 4.0f;
    pauseHelp.scale.y = 2.68f;
    pauseHelp.scale.z = 1.0f;

    pauseHelp.pos.x = 0.0f;
    pauseHelp.pos.y = 0.0f;
    pauseHelp.pos.z = -7.0f;
}

float _game::deltaTime = 0;

void _game::render()
{
    auto currentTime = chrono::steady_clock::now();
    chrono::duration<float> elapsed = currentTime - lastTime;
    _game::deltaTime = elapsed.count();
    lastTime = currentTime;

    if(_game::deltaTime > 0.033f)
        _game::deltaTime = 0.033f;

    if(isPaused)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glColor3f(1.0f, 1.0f, 1.0f);

        pauseHelp.drawQuad();
        return;
    }

    if(currentScene == lvl3 && lvl3->returnToMenu)
    {
        lvl3->returnToMenu = false;
        setLevel(0);
        return;
    }

    if(showLevelIntro)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);

        glColor3f(1.0f, 1.0f, 1.0f);

        levelIntro.drawQuad();
        return;
    }

    currentScene->update(deltaTime, false);
    currentScene->draw(deltaTime, false, dim);
}

void _game::reSize(GLint width, GLint height)
{
    if(height == 0)
        height = 1;

    const float GAME_W = 1920.0f;
    const float GAME_H = 1080.0f;
    const float GAME_ASPECT = GAME_W / GAME_H;

    float windowAspect = (float)width / (float)height;

    int viewX = 0;
    int viewY = 0;
    int viewW = width;
    int viewH = height;

    if(windowAspect > GAME_ASPECT)
    {
        viewH = height;
        viewW = (int)(height * GAME_ASPECT);
        viewX = (width - viewW) / 2;
        viewY = 0;
    }
    else if(windowAspect < GAME_ASPECT)
    {
        viewW = width;
        viewH = (int)(width / GAME_ASPECT);
        viewX = 0;
        viewY = (height - viewH) / 2;
    }

    glViewport(viewX, viewY, viewW, viewH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, GAME_ASPECT, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    dim.x = GAME_W;
    dim.y = GAME_H;
}

void _game::mouseMapping(int x, int y)
{
    GLint viewPort[4];
    GLdouble modelViewM[16];
    GLdouble projectionM[16];
    GLfloat winX, winY, winZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewM);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionM);
    glGetIntegerv(GL_VIEWPORT, viewPort);

    winX = (GLfloat)x;
    winY = (GLfloat)(viewPort[3] - y);

    glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ,
                 modelViewM,
                 projectionM,
                 viewPort,
                 &mouse.x,
                 &mouse.y,
                 &mouse.z);
}

int _game::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(uMsg == WM_KEYDOWN)
    {
        if(showLevelIntro)
        {
            if(wParam == VK_RETURN || wParam == VK_SPACE)
            {
                showLevelIntro = false;

                if(pendingLevel == 1)
                    currentScene = lvl1;

                if(pendingLevel == 2)
                    currentScene = lvl2;

                if(pendingLevel == 3)
                    currentScene = lvl3;

                currentScene->init();
            }

            return true;
        }

        if(isPaused)
        {
            if(wParam == VK_RETURN)
            {
                isPaused = false;
                return true;
            }

            if(wParam == 'M')
            {
                isPaused = false;
                setLevel(0);
                return true;
            }

            return true;
        }

        if((currentScene == lvl1 || currentScene == lvl2 || currentScene == lvl3) && wParam == VK_ESCAPE)
        {
            isPaused = true;
            return true;
        }
    }

    currentScene->winMsg(hWnd, uMsg, wParam, lParam);

    return 0;
}
