#ifndef _LEVEL2_H
#define _LEVEL2_H

#include<_common.h>
#include<_scene.h>
#include<_sounds.h>

typedef void (*Level2SelectCallback)(int);

class _level2 : public _scene
{
public:
    _level2();
    virtual ~_level2();

    void setLevelSelectCallback(Level2SelectCallback cb);

    _player *ply = new _player();
    _parallax *prlx = new _parallax();
    _lightSettings *light = new _lightSettings();
    _inputs *kbm = new _inputs();
    _collisionCheck *col = new _collisionCheck();
    _sounds *snd = new _sounds();

    _quad ground[80];
    _quad branches[20];

    _quad acornUI;
    _quad woodUI;
    _quad kickSprite;
    _quad plyHit;
    _quad introSign2;
    _quad plyThrow;
bool showIntroSign2;

    bool isKicking;
    float kickTimer;
    bool isHit;
    float hitTimer;

    _quad acorns[20];
    bool isAA[20];
    int acornScore;

    _quad rain[2];

    _quad level2_tree[10];
    _quad weakTree[10];
    bool weakTreeAlive[10];
    bool weakTreeBreaking[10];
    float weakTreeTimer[10];

    _quad chopPrompt;
    _quad greatTreeSign;

    _quad logs[10];
    bool logAlive[10];
    bool logFalling[10];
    float logVelY[10];
    int logCount;

    _quad placedLog;
    bool logPlaced;

    bool riverStage;
    bool riverLoaded;

    _enms fox[3];
    _quad foxHit[3];
    bool foxLive[3];
    bool foxDead[3];
    bool foxFalling[3];
    float foxSpeed[3];
    float foxDir[3];
    float foxRange[3];
    float foxStartX[3];
    float foxFallSpeed[3];
    float foxAnimTimer[3];
    float foxDeadTimer[3];
    int foxFrame[3];


    _enms snakes[3];
    _quad snakeHit[3];
    bool snakeLive[3];
    bool snakeDead[3];
    bool snakeFalling[3];
    float snakeSpeed[3];
    float snakeDir[3];
    float snakeRange[3];
    float snakeStartX[3];
    float snakeFallSpeed[3];


    _quad bird[2];
    _quad birdHit[2];
    bool birdLive[2];
    bool birdFalling[2];
    float birdSpeed[2];
    float birdDir[2];
    float birdFallSpeed[2];

    bool wasOnBranch;

    _quad thrownAcorn;
    bool thrownAcornLive;
    bool throwPressed;
    bool isThrow;
    float throwTimer;
    float acornVelX;
    float acornVelY;
    float acornGravity;
    vec3 acornStart;

    int lives;

    bool levelComplete;
    float levelCompleteTimer;

    vec2 velocity;
    float jumpStrength;
    bool isGrounded;
    float stepTimer;

    bool inputLocked;
    float inputLockTimer;

    bool treeCut;
    bool treeChopping;
    int chopCount;
    float chopTimer;

    bool onLog;

    float rainY;

    void init();
    void reset();
    void update(float, bool);
    void draw(float, bool, vec2);
    int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    Level2SelectCallback onLevelSelect;

    void setGround();
    void setTrees();
    void setBranches();
    void setAcorns();
    void setFoxes();
    void setSnakes();
    void setLogs();

    void updatePlayer(float);
    void updateAcorns();
    void updateFoxes(float);
    void updateSnakes(float);
    void updateThrownAcorn(float);
    void updateRain(float);
    void updateTree(float);
    void updateLog(float);
    void updateHit(float dt);

    void drawPlayer();
    void drawFoxes();
    void drawSnakes();
    void spawnBird();
    void updateBirds(float);
    void drawBirds();

    void startThrow();
    void startHit();
    void resetPlayerAfterHit();

};

#endif
