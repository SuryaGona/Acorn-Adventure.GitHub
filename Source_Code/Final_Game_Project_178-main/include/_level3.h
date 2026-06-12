#ifndef _LEVEL3_H
#define _LEVEL3_H

#include<_common.h>
#include<_scene.h>
#include<_sounds.h>

class _level3 : public _scene
{
public:
    _level3();
    virtual ~_level3();

    _player *ply = new _player();
    _parallax *prlx = new _parallax();
    _lightSettings *light = new _lightSettings();
    _inputs *kbm = new _inputs();
    _collisionCheck *hit = new _collisionCheck();
    _sounds *snd = new _sounds();

    _quad branch[6];
    _quad nuts[6];
    _quad rocks[2];
    _quad acorn;
    _quad bird[2];
    _quad birdHit[2];
    _quad goldenAcorn;
    _quad gameCompleted;
    _quad endCredits;
    _quad nutMeter[10];
    _quad nutHud;
    _quad nutHudBox;

    _quad plyIdle;
    _quad plyThrow;
    _quad plyHit;

    _enms snakes[5];
    _quad snakeHit[5];

    bool nutLive[6];
    bool onBranch = false;
    bool isJump = false;
    bool isThrow = false;
    bool isHit = false;
    bool acornLive = false;
    bool acornFalling = false;
    bool gameWon = false;
    int creditStage = 0;
    bool returnToMenu = false;

    bool inputLockedAfterHit = false;
    bool jumpPressed = false;
    float inputUnlockTimer = 0.0f;

    // Smooth jump helpers
    float jumpBufferTimer = 0.0f;
    float jumpBufferMax = 0.12f;
    float coyoteTimer = 0.0f;
    float coyoteMax = 0.08f;

    // Prevent expensive reloads every reset/load
    int lastLoadedTree = -1;

    bool birdLive[2];
    bool birdReady = false;
    bool birdDead[2];
    bool birdFalling[2];
    bool secondBirdSpawn = false;

    float birdSpeed[2];
    float birdDir[2];
    float birdFallSpeed[2];
    float bird2Timer = 0.0f;

    bool throwPressed = false;
    float acornVelX = 0.0f;
    float acornVelY = 0.0f;
    float acornGravity = 7.0f;
    float acornStraightDist = 1.2f;

    float jumpVel = 0.0f;
    float gravityY = 8.8f;
    float fallSpeed[2];

    float throwTimer = 0.0f;
    float hitTimer = 0.0f;

    float acornT = 0.0f;
    float acornTimer = 0.0f;
    float acornFallSpeed = 0.0f;

    vec3 acornStart;

    int snakeBranch[5];
    float snakeSpeed[5];
    float snakeDir[5];
    float snakeRange[5];
    float snakeFallSpeed[5];

    bool snakeLive = false;
    bool snakeDead[5];
    bool snakeFalling[5];

    int climbStage = 0;
    int nutsCollected = 0;
    int goalStage = 4;

    void init();
    void reset();
    void update(float,bool);
    void draw(float,bool,vec2);
    int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:

private:
    void loadStage();
    void setBranches();
    void setNuts();
    void setRocks();
    void setSnakes();
    void setBird();

    bool checkBranchLand();

    void setPlayerPic(_quad*);
    void setPicFace(_quad*, float);

    void startHit();
    void startThrow();

    void updateHit(float);
    void updateThrow(float);
    void updatePlayer(float);
    void updateAcorn(float);
    void updateNuts();
    void updateRocks(float);
    void updateSnakes(float);
    void updateBird(float);

    void drawPlayer();
    void drawSnakes();
    void drawBirds();

    vec3 getSnakeHead(int);
};

#endif
