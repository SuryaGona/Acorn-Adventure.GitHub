#ifndef _LEVEL1_H
#define _LEVEL1_H

#include<_common.h>
#include<_scene.h>
#include<_sounds.h>

typedef void (*LevelSelectCallback)(int);

class _level1 : public _scene
{
public:
    _level1();
    virtual ~_level1();

    void setLevelSelectCallback(LevelSelectCallback cb);

    _player *ply = new _player();

    _quad plyHit;
    bool isHit;
    float hitTimer;

    _parallax *prlx = new _parallax();
    _lightSettings *light = new _lightSettings();
    _inputs *kbm = new _inputs();
    _collisionCheck *col = new _collisionCheck();
    _sounds *snd = new _sounds();

    _quad trees[2][10];
    _quad branches[4][10];
    _quad floor[1000];

    _quad wildernessSign;

    _quad introImage;
    bool showIntroImage;

    _quad acornUI;
    _quad acorns[30];
    bool isAA[30];
    int acornScore;

    _quad cars[8];
    float carSpeed[8];
    float carDir[8];
    int carLane[8];
    bool carLive[8];
    bool trafficStarted;

    int currentLane;
    float laneY[2];
    bool laneDownPressed;
    float targetLaneY;
    float laneMoveSpeed;
    bool isChangingLane;

    bool playerOnBranch = false;

    int lives;

    bool levelComplete;
    float levelCompleteTimer;

    vec2 velocity;
    float jumpStrength;
    bool isGrounded;
    float stepTimer;

    bool inputLocked;
    float inputLockTimer;

    float cameraX;
    float cameraLeftEdge;
    float cameraRightEdge;

    void init();
    void reset();
    void update(float,bool);
    void draw(float,bool,vec2);
    int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    LevelSelectCallback onLevelSelect;

    void setCars();
    void updateCars(float dt);

    void startHit();
    void updateHit(float dt);
    void drawPlayer();

    void resetPlayerAfterHit();
};

#endif
