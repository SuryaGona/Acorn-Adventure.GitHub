#include "_menu.h"
#include "_sounds.h"
_menu::_menu()
{
    onLevelSelect = nullptr;
    menuScreen = 0;
    selectedItem = 0;
    landingTimer = 0.0f;

    snd = new _sounds();
}

_menu::~_menu()
{
    delete snd;
}

void _menu::setLevelSelectCallback(LevelSelectCallback cb)
{
    onLevelSelect = cb;
}

void _menu::init()
{
    glewInit();

snd->initSounds();
snd->playMusicAdj((char*)"sounds/level12_music.mp3", 0.75f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    landingPage.initQuad((char*)"images/landing.png");
    landingPage.scale.x = 4.75f;
    landingPage.scale.y = 2.68f;
    landingPage.scale.z = 1.0f;
    landingPage.pos.x = 0.0f;
    landingPage.pos.y = 0.0f;
    landingPage.pos.z = -7.0f;

    mainMenuPage.initQuad((char*)"images/mainmenu.png");
    mainMenuPage.scale.x = 4.0f;
    mainMenuPage.scale.y = 2.68f;
    mainMenuPage.scale.z = 1.0f;
    mainMenuPage.pos.x = 0.0f;
    mainMenuPage.pos.y = 0.0f;
    mainMenuPage.pos.z = -7.0f;

    howToPlayPage.initQuad((char*)"images/howtoplay.png");
    howToPlayPage.scale.x = 4.0f;
    howToPlayPage.scale.y = 2.68f;
    howToPlayPage.scale.z = 1.0f;
    howToPlayPage.pos.x = 0.0f;
    howToPlayPage.pos.y = 0.0f;
    howToPlayPage.pos.z = -7.0f;

    selector.initQuad((char*)"images/selector.png");

    selector.scale.x = 0.35f;
    selector.scale.y = 0.35f;
    selector.scale.z = 1.0f;

    selector.pos.x = -1.40f;
    selector.pos.y = -0.35f;
    selector.pos.z = -6.8f;

    howToPlayBackSelector.initQuad((char*)"images/selector.png");

    howToPlayBackSelector.scale.x = 0.35f;
    howToPlayBackSelector.scale.y = 0.35f;
    howToPlayBackSelector.scale.z = 1.0f;

    howToPlayBackSelector.pos.x = -1.45f;
    howToPlayBackSelector.pos.y = -1.86f;
    howToPlayBackSelector.pos.z = -6.8f;

}

void _menu::reset()
{
    menuScreen = 0;
    selectedItem = 0;
    landingTimer = 0.0f;
}

void _menu::showMainMenu()
{
    menuScreen = 1;
    selectedItem = 0;
    landingTimer = 2.0f;
}

void _menu::update(float dt, bool isPaused)
{
    if(isPaused)
        return;

    if(menuScreen == 0)
    {
        landingTimer += dt;

        if(landingTimer >= 0.7f)
            menuScreen = 1;
    }
}

void _menu::confirmSelection()
{
    if(selectedItem == 0)
    {
        snd->sndEng->stopAllSounds();

        if(onLevelSelect)
            onLevelSelect(1);
    }
    else if(selectedItem == 1)
    {
        menuScreen = 2;
    }
    else if(selectedItem == 2)
    {
        snd->sndEng->stopAllSounds();
        PostQuitMessage(0);
    }
}

void _menu::draw(float dt, bool isPaused, vec2 dim)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);

    if(menuScreen == 0)
    {
        landingPage.drawQuad();
    }

    if(menuScreen == 1)
    {
        mainMenuPage.drawQuad();

        if(selectedItem == 0)
            selector.pos.y = -0.35f;

        if(selectedItem == 1)
            selector.pos.y = -0.88f;

        if(selectedItem == 2)
            selector.pos.y = -1.4f;

        selector.drawQuad();
    }

    if(menuScreen == 2)
    {
        howToPlayPage.drawQuad();
        howToPlayBackSelector.drawQuad();
    }
}

int _menu::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(uMsg != WM_KEYDOWN)
        return 0;

    if(menuScreen == 0)
        return true;

    if(menuScreen == 2)
    {
        if(wParam == VK_ESCAPE || wParam == VK_RETURN || wParam == VK_SPACE)
            menuScreen = 1;

        return true;
    }

    if(menuScreen == 1)
    {
        if(wParam == VK_UP)
        {
            selectedItem--;

            if(selectedItem < 0)
                selectedItem = 2;
        }

        if(wParam == VK_DOWN)
        {
            selectedItem++;

            if(selectedItem > 2)
                selectedItem = 0;
        }

        if(wParam == VK_RETURN || wParam == VK_SPACE)
            confirmSelection();

        return true;
    }

    return 0;
}
