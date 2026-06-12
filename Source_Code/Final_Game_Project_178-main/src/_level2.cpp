#include "_level2.h"

static float level2CameraX = 22.0f;

_level2::_level2()
{
    velocity.x = 0.0f;
    velocity.y = 0.0f;

    jumpStrength = 7.5f;
    isGrounded = false;

    acornScore = 0;
    lives = 3;

    levelComplete = false;
    levelCompleteTimer = 0.0f;

    stepTimer = 0.0f;

    inputLocked = false;
    inputLockTimer = 0.0f;

    treeCut = false;
    treeChopping = false;
    chopCount = 0;
    chopTimer = 0.0f;

    onLog = false;

    rainY = 0.0f;

    thrownAcornLive = false;
    throwPressed = false;
    isThrow = false;
    throwTimer = 0.0f;
    acornVelX = 0.0f;
    acornVelY = 0.0f;
    acornGravity = 7.0f;

    isHit = false;
    hitTimer = 0.0f;

    logCount = 0;
    logPlaced = false;
    riverStage = false;
    riverLoaded = false;
    isKicking = false;
    kickTimer = 0.0f;

    onLevelSelect = NULL;

    for(int i = 0; i < 20; i++)
        isAA[i] = false;

    for(int i = 0; i < 10; i++)
    {
        logAlive[i] = false;
        logFalling[i] = false;
        logVelY[i] = 0.0f;
        weakTreeAlive[i] = true;
        weakTreeBreaking[i] = false;
        weakTreeTimer[i] = 0.0f;
    }

    for(int i = 0; i < 3; i++)
        foxDeadTimer[i] = 0.0f;
}

_level2::~_level2()
{
    delete ply;
    delete prlx;
    delete light;
    delete kbm;
    delete col;
    delete snd;
}

void _level2::setLevelSelectCallback(Level2SelectCallback cb)
{
    onLevelSelect = cb;
}

void _level2::init()
{
    glewInit();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LIGHT0);

    light->setLight(GL_LIGHT0);

    snd->initSounds();
    snd->playMusicAdj((char*)"sounds/level34_music.mp3", 0.75f);

    prlx->initPrlx((char*)"images/level2_forest.png");

    ply->plyInit(4, 4, (char*)"images/sqrl1.png");
    ply->scale.x = 0.40f;
    ply->scale.y = 0.40f;
    ply->scale.z = 1.0f;
    ply->facingLeft = false;
    ply->actionTrigger = ply->STAND;

    plyHit.initQuad((char*)"images/squirrel_hit.png");
    plyHit.scale.x = 0.40f;
    plyHit.scale.y = 0.40f;
    plyHit.scale.z = 1.0f;
    plyHit.pos.z = -7.9f;

    plyThrow.initQuad((char*)"images/squirrel_throw.png");
    plyThrow.scale.x = 0.40f;
    plyThrow.scale.y = 0.40f;
    plyThrow.scale.z = 1.0f;
    plyThrow.pos.z = -7.9f;

    acornUI.initQuad((char*)"images/acorn.png");
    acornUI.pos.x = -4.20f;
    acornUI.pos.y = 3.05f;
    acornUI.pos.z = -8.0f;
    acornUI.scale.x = 0.25f;
    acornUI.scale.y = 0.25f;
    acornUI.scale.z = 1.0f;

    woodUI.initQuad((char*)"images/log_item.png");
    woodUI.pos.x = -1.35f;
    woodUI.pos.y = 3.05f;
    woodUI.pos.z = -8.0f;
    woodUI.scale.x = 0.25f;
    woodUI.scale.y = 0.18f;
    woodUI.scale.z = 1.0f;

    kickSprite.initQuad((char*)"images/squirrel-kick.png");
    kickSprite.scale.x = 0.30f;
    kickSprite.scale.y = 0.30f;
    kickSprite.scale.z = 1.0f;
    kickSprite.pos.z = -7.9f;

    rain[0].initQuad((char*)"images/rain.png");
    rain[0].pos.x = 0.0f;
    rain[0].pos.y = 0.0f;
    rain[0].pos.z = -6.4f;
    rain[0].scale.x = 5.8f;
    rain[0].scale.y = 3.4f;
    rain[0].scale.z = 1.0f;

    rain[1].initQuad((char*)"images/rain.png");
    rain[1].pos.x = 0.0f;
    rain[1].pos.y = 3.4f;
    rain[1].pos.z = -6.4f;
    rain[1].scale.x = 5.8f;
    rain[1].scale.y = 3.4f;
    rain[1].scale.z = 1.0f;

    chopPrompt.initQuad((char*)"images/chop_prompt.png");
    chopPrompt.pos.x = -100.0f;
    chopPrompt.pos.y = -100.0f;
    chopPrompt.pos.z = -7.7f;
    chopPrompt.scale.x = 0.75f;
    chopPrompt.scale.y = 0.35f;
    chopPrompt.scale.z = 1.0f;

    greatTreeSign.initQuad((char*)"images/great_tree_sign.png");
    greatTreeSign.pos.x = 170.0f;
    greatTreeSign.pos.y = -2.00f;
    greatTreeSign.pos.z = -7.85f;
    greatTreeSign.scale.x = 1.25f;
    greatTreeSign.scale.y = 1.00f;
    greatTreeSign.scale.z = 1.0f;

    introSign2.initQuad((char*)"images/intro_sign2.png");
    introSign2.pos.x = 22.0f;
    introSign2.pos.y = 0.0f;
    introSign2.pos.z = -7.7f;
    introSign2.scale.x = 1.5f;
    introSign2.scale.y = 1.0f;
    introSign2.scale.z = 1.0f;

    thrownAcorn.initQuad((char*)"images/acorn.png");
    thrownAcorn.scale.x = 0.16f;
    thrownAcorn.scale.y = 0.16f;
    thrownAcorn.scale.z = 1.0f;
    thrownAcorn.pos.z = -7.65f;

    for(int i = 0; i < 2; i++)
    {
        bird[i].initQuad((char*)"images/bird.png");
        bird[i].scale.x = 0.45f;
        bird[i].scale.y = 0.45f;
        bird[i].scale.z = 1.0f;
        bird[i].pos.z = -7.65f;

        birdHit[i].initQuad((char*)"images/bird_hit.png");
        birdHit[i].scale.x = 0.60f;
        birdHit[i].scale.y = 0.60f;
        birdHit[i].scale.z = 1.0f;
        birdHit[i].pos.z = -7.65f;

        birdLive[i] = false;
        birdFalling[i] = false;
        birdSpeed[i] = 5.0f;
        birdDir[i] = 1.0f;
        birdFallSpeed[i] = 2.0f;
    }

    wasOnBranch = false;
    showIntroSign2 = true;

    setTrees();
    setBranches();
    setAcorns();
    setFoxes();
    setSnakes();
    setLogs();

    reset();
}

void _level2::setGround()
{
    for(int i = 0; i < 80; i++)
    {
        ground[i].initQuad((char*)"images/forest_ground.png");
        ground[i].pos.x = 18.0f + i * 2.0f;
        ground[i].pos.y = -3.35f;
        ground[i].pos.z = -8.0f;
        ground[i].scale.x = 1.0f;
        ground[i].scale.y = 0.35f;
        ground[i].scale.z = 1.0f;
    }
}

void _level2::setTrees()
{
    for(int i = 0; i < 10; i++)
    {
        level2_tree[i].initQuad((char*)"images/level2_tree.png");
        level2_tree[i].pos.x = 25.0f + i * 14.0f;
        level2_tree[i].pos.y = 0.60f;
        level2_tree[i].pos.z = -8.0f;
        level2_tree[i].scale.x = 1.30f;
        level2_tree[i].scale.y = 3.40f;
        level2_tree[i].scale.z = 1.0f;

        weakTree[i].initQuad((char*)"images/weak_tree.png");
        weakTree[i].pos.x = 31.0f + i * 14.0f;
        weakTree[i].pos.y = -1.70f;
        weakTree[i].pos.z = -7.86f;
        weakTree[i].scale.x = 1.05f;
        weakTree[i].scale.y = 1.45f;
        weakTree[i].scale.z = 1.0f;

        weakTreeAlive[i] = true;
        weakTreeBreaking[i] = false;
        weakTreeTimer[i] = 0.0f;
    }
}

void _level2::setBranches()
{
    for(int i = 0; i < 20; i++)
    {
        branches[i].initQuad((char*)"images/pbranch.png");
        branches[i].pos.z = -7.9f;
        branches[i].scale.z = 1.0f;
    }

    for(int i = 0; i < 10; i++)
    {
        branches[i].pos.x = 25.65f + i * 14.0f;
        branches[i].pos.y = -0.75f;
        branches[i].scale.x = 0.95f;
        branches[i].scale.y = 0.80f;
    }

    for(int i = 0; i < 10; i++)
    {
        branches[10 + i].pos.x = 24.22f + i * 14.0f;
        branches[10 + i].pos.y = 0.05f;
        branches[10 + i].scale.x = -0.95f;
        branches[10 + i].scale.y = 0.80f;
    }
}

void _level2::setAcorns()
{
    for(int i = 0; i < 20; i++)
    {
        acorns[i].initQuad((char*)"images/acorn.png");
        acorns[i].scale.x = 0.15f;
        acorns[i].scale.y = 0.15f;
        acorns[i].scale.z = 1.0f;
        acorns[i].pos.z = -7.65f;

        acorns[i].pos.x = branches[i].pos.x +
                          ((rand() % 100) / 100.0f - 0.5f) * 0.6f;

        acorns[i].pos.y = branches[i].pos.y + 0.35f;
        isAA[i] = true;
    }
}

void _level2::setLogs()
{
    for(int i = 0; i < 10; i++)
    {
        logs[i].initQuad((char*)"images/log_item.png");
        logs[i].scale.x = 0.55f;
        logs[i].scale.y = 0.30f;
        logs[i].scale.z = 1.0f;
        logs[i].pos.z = -7.95f;
        logs[i].pos.x = weakTree[i].pos.x + 0.75f;
        logs[i].pos.y = -0.60f;

        logAlive[i] = false;
        logFalling[i] = false;
        logVelY[i] = 0.0f;
    }
}

void _level2::setFoxes()
{
    const float FOX_Y = -2.50f;
    const float FOX_W = 0.10f;
    const float FOX_H = 1.55f;

    for(int i = 0; i < 3; i++)
    {
        fox[i].enmsInit(4, 1, (char*)"images/fox_run_fixed.png");

        fox[i].scale.x = FOX_W;
        fox[i].scale.y = FOX_H;
        fox[i].scale.z = 1.0f;

        fox[i].pos.x = -100.0f;
        fox[i].pos.y = -20.0f;
        fox[i].pos.z = -7.8f;

        foxLive[i] = false;
        foxDead[i] = false;
        foxFalling[i] = false;
        foxFallSpeed[i] = 2.0f;
        foxDeadTimer[i] = 0.0f;

        foxSpeed[i] = 3.8f + (rand() % 8) * 0.10f;
        foxDir[i] = -1.0f;
        foxAnimTimer[i] = 0.0f;
        foxFrame[i] = 0;
    }
}

void _level2::setSnakes()
{
    for(int i = 0; i < 3; i++)
    {
        snakes[i].enmsInit(1, 1, (char*)"images/snake.png");
        snakeHit[i].initQuad((char*)"images/snake_hit.png");

        snakes[i].scale.x = 0.50f;
        snakes[i].scale.y = 0.50f;
        snakes[i].scale.z = 1.0f;

        snakeHit[i].scale.x = 0.60f;
        snakeHit[i].scale.y = 0.60f;
        snakeHit[i].scale.z = 1.0f;

        snakes[i].pos.z = -7.65f;
        snakeHit[i].pos.z = -7.65f;

        snakeLive[i] = true;
        snakeDead[i] = false;
        snakeFalling[i] = false;

        snakeSpeed[i] = 0.8f + (rand() % 5) / 10.0f;
        snakeDir[i] = (rand() % 2 == 0) ? 1.0f : -1.0f;
        snakeRange[i] = 0.55f;
        snakeFallSpeed[i] = 1.8f;
    }

    snakeStartX[0] = branches[1].pos.x;
    snakeStartX[1] = branches[2].pos.x;
    snakeStartX[2] = branches[6].pos.x;

    snakes[0].pos.x = branches[1].pos.x;
    snakes[0].pos.y = branches[1].pos.y + 0.18f;

    snakes[1].pos.x = branches[2].pos.x;
    snakes[1].pos.y = branches[2].pos.y + 0.18f;

    snakes[2].pos.x = branches[6].pos.x;
    snakes[2].pos.y = branches[6].pos.y + 0.18f;
}

void _level2::updateTree(float dt)
{
    bool kickDown = (GetAsyncKeyState('E') & 0x8000);

    chopPrompt.pos.x = -100.0f;
    chopPrompt.pos.y = -100.0f;

    if(isKicking)
    {
        kickTimer -= dt;

        if(kickTimer <= 0.0f)
        {
            isKicking = false;
            kickTimer = 0.0f;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        if(weakTreeBreaking[i])
        {
            weakTreeTimer[i] -= dt;

            if(weakTreeTimer[i] <= 0.0f)
            {
                weakTreeBreaking[i] = false;
                weakTreeAlive[i] = false;

                logAlive[i] = true;
                logFalling[i] = true;
                logVelY[i] = 1.5f;

                logs[i].pos.x = weakTree[i].pos.x + 0.75f;
                logs[i].pos.y = -0.60f;
            }
        }

        if(weakTreeAlive[i] && !weakTreeBreaking[i])
        {
            if(fabs(ply->pos.x - weakTree[i].pos.x) < 1.0f &&
                    fabs(ply->pos.y + 2.50f) < 0.8f)
            {
                chopPrompt.pos.x = weakTree[i].pos.x;
                chopPrompt.pos.y = -1.05f;

                if(kickDown)
                {
                    weakTreeBreaking[i] = true;
                    weakTreeTimer[i] = 0.35f;

                    snd->playSounds((char*)"sounds/broketree.mp3");

                    isKicking = true;
                    kickTimer = 0.25f;

                    kickSprite.pos.x = ply->pos.x;
                    kickSprite.pos.y = ply->pos.y;
                    kickSprite.pos.z = ply->pos.z;
                    kickSprite.scale.x = ply->facingLeft ? -0.40f : 0.40f;
                    kickSprite.scale.y = 0.40f;
                    kickSprite.scale.z = 1.0f;
                }
            }
        }
    }
}

void _level2::updateLog(float dt)
{
    for(int i = 0; i < 10; i++)
    {
        if(logAlive[i] && logFalling[i])
        {
            logs[i].pos.y += logVelY[i] * dt;
            logVelY[i] -= 7.0f * dt;

            if(logs[i].pos.y <= -2.55f)
            {
                logs[i].pos.y = -2.55f;
                logFalling[i] = false;
                logVelY[i] = 0.0f;
            }
        }

        if(logAlive[i] && !logFalling[i] &&
                col->isAABBCol(ply->pos, ply->scale, logs[i].pos, logs[i].scale))
        {
            logAlive[i] = false;
            logCount++;

            snd->playSounds((char*)"sounds/item_pickup.mp3");
        }
    }
}

void _level2::reset()
{
    ply->plyInit(4, 4, (char*)"images/sqrl1.png");
    ply->scale.x = 0.40f;
    ply->scale.y = 0.40f;
    ply->scale.z = 1.0f;

    ply->pos.x = 22.0f;
    ply->pos.y = -2.50f;
    ply->pos.z = -7.9f;

    level2CameraX = 22.0f;

    ply->facingLeft = false;
    ply->actionTrigger = ply->STAND;

    velocity.x = 0.0f;
    velocity.y = 0.0f;

    isGrounded = false;
    stepTimer = 0.0f;

    for(int i = 0; i < 20; i++)
        isAA[i] = true;

    acornScore = 0;
    lives = 3;

    levelComplete = false;
    levelCompleteTimer = 0.0f;

    inputLocked = false;
    inputLockTimer = 0.0f;

    isHit = false;
    hitTimer = 0.0f;

    treeCut = false;
    treeChopping = false;
    chopCount = 0;
    chopTimer = 0.0f;

    logCount = 0;
    logPlaced = false;
    onLog = false;
    riverStage = false;
    riverLoaded = false;

    prlx->initPrlx((char*)"images/level2_forest.png");

    for(int i = 0; i < 10; i++)
    {
        weakTreeAlive[i] = true;
        weakTreeBreaking[i] = false;
        weakTreeTimer[i] = 0.0f;
        logAlive[i] = false;
        logFalling[i] = false;
        logVelY[i] = 0.0f;
    }

    isKicking = false;
    kickTimer = 0.0f;

    rainY = 0.0f;

    thrownAcornLive = false;
    throwPressed = false;
    isThrow = false;
    throwTimer = 0.0f;

    wasOnBranch = false;
    showIntroSign2 = true;

    for(int i = 0; i < 2; i++)
    {
        birdLive[i] = false;
        birdFalling[i] = false;
        birdFallSpeed[i] = 2.0f;
    }

    setTrees();
    setBranches();
    setFoxes();
    setSnakes();
    setLogs();
}

void _level2::startHit()
{
    if(isHit)
        return;

    isHit = true;
    hitTimer = 0.18f;

    snd->playSounds((char*)"sounds/gameover.mp3");

    velocity.x = 0.0f;
    velocity.y = 0.0f;

    thrownAcornLive = false;
    isThrow = false;
    throwPressed = false;
}

void _level2::updateHit(float dt)
{
    if(!isHit)
        return;

    hitTimer -= dt;

    if(hitTimer <= 0.0f)
        resetPlayerAfterHit();
}

void _level2::resetPlayerAfterHit()
{
    lives--;

    isHit = false;
    hitTimer = 0.0f;

    if(lives <= 0)
    {
        lives = 3;
        acornScore = 0;
        logCount = 0;

        for(int i = 0; i < 20; i++)
            isAA[i] = true;

        ply->pos.x = 22.0f;
        ply->pos.y = -2.50f;
        ply->pos.z = -7.9f;

        level2CameraX = 22.0f;

        velocity.x = 0.0f;
        velocity.y = 0.0f;

        isGrounded = false;
        isHit = false;
        hitTimer = 0.0f;

        thrownAcornLive = false;
        isThrow = false;
        throwPressed = false;

        setFoxes();

        return;
    }

    ply->scale.x = 0.40f;
    ply->scale.y = 0.40f;
    ply->scale.z = 1.0f;

    ply->facingLeft = false;
    ply->actionTrigger = ply->STAND;

    ply->pos.x = 22.0f;
    ply->pos.y = -2.50f;
    ply->pos.z = -7.9f;

    level2CameraX = 22.0f;

    velocity.x = 0.0f;
    velocity.y = 0.0f;

    kbm->isLeftPressed = false;
    kbm->isRightPressed = false;
    kbm->isAPressed = false;
    kbm->isDPressed = false;
    kbm->isWPressed = false;
    kbm->isSpacePressed = false;
    kbm->isUpPressed = false;
    kbm->isShiftPressed = false;

    setFoxes();

    thrownAcornLive = false;
    isThrow = false;
    throwPressed = false;
    wasOnBranch = false;

    for(int i = 0; i < 2; i++)
    {
        birdLive[i] = false;
        birdFalling[i] = false;
        birdFallSpeed[i] = 2.0f;
    }

    inputLocked = false;
    inputLockTimer = 0.0f;
}

void _level2::startThrow()
{
    if(thrownAcornLive || isThrow || acornScore <= 0)
        return;

    isThrow = true;
    throwTimer = 0.25f;
    acornScore--;

    snd->playSounds((char*)"sounds/jump.mp3");

    thrownAcornLive = true;

    acornStart.x = ply->pos.x;
    acornStart.y = ply->pos.y + 0.15f;
    acornStart.z = -7.65f;

    thrownAcorn.pos.x = acornStart.x;
    thrownAcorn.pos.y = acornStart.y;
    thrownAcorn.pos.z = acornStart.z;

    if(ply->facingLeft)
        acornVelX = -6.0f;
    else
        acornVelX = 6.0f;

    acornVelY = 0.0f;
}

void _level2::updateRain(float dt)
{
    rainY -= 3.5f * dt;

    if(rainY < -3.4f)
        rainY = 0.0f;

    rain[0].pos.y = rainY;
    rain[1].pos.y = rainY + 3.4f;
}

void _level2::updatePlayer(float dt)
{
    const float MOVE_SPEED = 5.8f;
    const float GROUND_Y = -2.50f;

    bool leftDown  = (GetAsyncKeyState('A') & 0x8000) ||
                     (GetAsyncKeyState(VK_LEFT) & 0x8000);
    bool rightDown = (GetAsyncKeyState('D') & 0x8000) ||
                     (GetAsyncKeyState(VK_RIGHT) & 0x8000);
    bool jumpDown  = (GetAsyncKeyState(VK_SPACE) & 0x8000) ||
                     (GetAsyncKeyState(VK_UP) & 0x8000) ||
                     (GetAsyncKeyState('W') & 0x8000);

    velocity.y -= 14.0f * dt;
    velocity.x = 0.0f;

    if(!isThrow)
        ply->actionTrigger = ply->STAND;

    if(leftDown && !isThrow)
    {
        ply->facingLeft = true;
        velocity.x = -MOVE_SPEED;
        ply->actionTrigger = ply->RUN;
    }
    else if(rightDown && !isThrow)
    {
        ply->facingLeft = false;
        velocity.x = MOVE_SPEED;
        ply->actionTrigger = ply->RUN;
    }

    if(jumpDown && isGrounded && !isThrow)
    {
        snd->playSounds((char*)"sounds/jump.mp3");
        velocity.y = jumpStrength;
        isGrounded = false;
        ply->actionTrigger = ply->JUMP;
    }

    ply->pos.x += velocity.x * dt;
    ply->pos.y += velocity.y * dt;

    isGrounded = false;
    bool landedOnBranch = false;

    if(ply->pos.y <= GROUND_Y && velocity.y <= 0.0f)
    {
        ply->pos.y = GROUND_Y;
        velocity.y = 0.0f;
        isGrounded = true;
    }

    for(int i = 0; i < 20; i++)
    {
        float top = branches[i].pos.y + 0.37f;
        float halfWidth = fabs(branches[i].scale.x) * 1.00f;

        if(ply->pos.y <= top &&
                ply->pos.y >= branches[i].pos.y - 0.12f &&
                fabs(ply->pos.x - branches[i].pos.x) < halfWidth &&
                velocity.y <= 0.0f)
        {
            ply->pos.y = top;
            velocity.y = 0.0f;
            isGrounded = true;
            landedOnBranch = true;

            if(!wasOnBranch && rand() % 2 == 0)
                spawnBird();

            wasOnBranch = true;
        }
    }

    if(!landedOnBranch)
        wasOnBranch = false;

    if(ply->pos.x < 18.0f)
        ply->pos.x = 18.0f;

    if(acornScore < 15 || logCount < 4)
    {
        if(ply->pos.x > greatTreeSign.pos.x - 0.25f)
        {
            ply->pos.x = greatTreeSign.pos.x - 0.25f;
            velocity.x = 0.0f;
        }
    }

    if(ply->pos.y < -4.2f)
    {
        startHit();
        return;
    }
}

void _level2::updateAcorns()
{
    for(int i = 0; i < 20; i++)
    {
        if(isAA[i] && col->isAABBCol(ply->pos, ply->scale, acorns[i].pos, acorns[i].scale))
        {
            snd->playSounds((char*)"sounds/item_pickup.mp3");
            isAA[i] = false;
            acornScore++;
        }
    }
}

void _level2::updateThrownAcorn(float dt)
{
    if(isThrow)
    {
        throwTimer -= dt;

        if(throwTimer <= 0.0f)
            isThrow = false;
    }

    if(throwPressed)
    {
        startThrow();
        throwPressed = false;
    }

    if(!thrownAcornLive)
        return;

    thrownAcorn.pos.x += acornVelX * dt;

    if(fabs(thrownAcorn.pos.x - acornStart.x) > 1.2f)
    {
        thrownAcorn.pos.y += acornVelY * dt;
        acornVelY -= acornGravity * dt;
    }

    if(thrownAcorn.pos.x < ply->pos.x - 8.0f ||
            thrownAcorn.pos.x > ply->pos.x + 8.0f ||
            thrownAcorn.pos.y < -4.0f)
    {
        thrownAcornLive = false;
    }
}

void _level2::updateFoxes(float dt)
{
    const float FOX_Y = -2.50f;
    const float FOX_W = 0.80f;
    const float FOX_H = 1.55f;

    const float FOX_MIN_GAP = 3.0f;
    const float FOX_RANDOM_GAP = 4.0f;
    const float LEFT_OFFSCREEN = 30.0f;

    bool rightDown = (GetAsyncKeyState('D') & 0x8000) ||
                     (GetAsyncKeyState(VK_RIGHT) & 0x8000);

    bool anyFoxLive = false;

    for(int i = 0; i < 3; i++)
    {
        if(foxLive[i] && !foxDead[i])
            anyFoxLive = true;
    }

    if(!anyFoxLive)
    {
        if(!rightDown)
            return;

        int packSize = 1 + rand() % 3;
        float foxX = ply->pos.x + 18.0f;

        for(int i = 0; i < packSize; i++)
        {
            foxLive[i] = true;
            foxDead[i] = false;
            foxFalling[i] = false;

            fox[i].pos.x = foxX;
            fox[i].pos.y = FOX_Y;
            fox[i].pos.z = -7.8f;

            fox[i].scale.x = FOX_W;
            fox[i].scale.y = FOX_H;
            fox[i].scale.z = 1.0f;

            foxSpeed[i] = 3.8f + (rand() % 6) * 0.10f;

            foxX += FOX_MIN_GAP + (rand() % 100) / 100.0f * FOX_RANDOM_GAP;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        if(foxFalling[i])
        {
            fox[i].pos.y -= foxFallSpeed[i] * dt;
            foxFallSpeed[i] += 4.0f * dt;

            if(fox[i].pos.y <= FOX_Y)
            {
                fox[i].pos.y = FOX_Y;
                foxFalling[i] = false;
                foxDead[i] = true;
                foxDeadTimer[i] = 2.0f;
            }

            continue;
        }

        if(foxDead[i])
        {
            foxDeadTimer[i] -= dt;

            if(foxDeadTimer[i] <= 0.0f)
            {
                foxDead[i] = false;
                foxLive[i] = false;
                fox[i].pos.x = -100.0f;
                fox[i].pos.y = -20.0f;
            }

            continue;
        }

        if(!foxLive[i])
            continue;

        fox[i].pos.x -= foxSpeed[i] * dt;
        fox[i].pos.y = FOX_Y;

        foxAnimTimer[i] += dt;

        if(foxAnimTimer[i] >= 0.12f)
        {
            foxAnimTimer[i] = 0.0f;
            foxFrame[i]++;

            if(foxFrame[i] > 2)
                foxFrame[i] = 0;
        }

        fox[i].xMin = foxFrame[i] * 0.25f;
        fox[i].xMax = fox[i].xMin + 0.25f;
        fox[i].updateQuad();

        if(fox[i].pos.x < ply->pos.x - LEFT_OFFSCREEN)
        {
            foxLive[i] = false;
            foxDead[i] = false;
            fox[i].pos.x = -100.0f;
            fox[i].pos.y = -20.0f;
            continue;
        }

        float foxHitWidth = fabs(fox[i].scale.x) * 0.55f;
        float foxHitHeight = fabs(fox[i].scale.y) * 0.28f;

        if(fabs(ply->pos.x - fox[i].pos.x) < foxHitWidth &&
                fabs(ply->pos.y - fox[i].pos.y) < foxHitHeight)
        {
            startHit();
            return;
        }

        float foxAcornHitWidth = 0.65f;
        float foxAcornHitHeight = 0.65f;

        if(thrownAcornLive &&
                fabs(thrownAcorn.pos.x - fox[i].pos.x) < foxAcornHitWidth &&
                fabs(thrownAcorn.pos.y - fox[i].pos.y) < foxAcornHitHeight)
        {
            thrownAcornLive = false;

            foxLive[i] = true;
            foxDead[i] = false;
            foxFalling[i] = true;
            foxFallSpeed[i] = 2.0f;
            foxDeadTimer[i] = 0.0f;

            foxFrame[i] = 3;
            fox[i].xMin = 0.75f;
            fox[i].xMax = 1.0f;
            fox[i].updateQuad();

            snd->playSounds((char*)"sounds/enemy_hit.wav");
            continue;
        }
    }
}

void _level2::updateSnakes(float dt)
{
    for(int i = 0; i < 3; i++)
    {
        if(snakeFalling[i])
        {
            snakeHit[i].pos.y -= snakeFallSpeed[i] * dt;
            snakeFallSpeed[i] += 4.0f * dt;

            if(snakeHit[i].pos.y < -4.0f)
            {
                snakeFalling[i] = false;
                snakeDead[i] = true;
                snakeLive[i] = false;
            }

            continue;
        }

        if(!snakeLive[i] || snakeDead[i])
            continue;

        snakes[i].pos.x += snakeDir[i] * snakeSpeed[i] * dt;

        float leftLimit = snakeStartX[i] - snakeRange[i];
        float rightLimit = snakeStartX[i] + snakeRange[i];

        if(snakes[i].pos.x > rightLimit)
        {
            snakes[i].pos.x = rightLimit;
            snakeDir[i] = -1.0f;
        }

        if(snakes[i].pos.x < leftLimit)
        {
            snakes[i].pos.x = leftLimit;
            snakeDir[i] = 1.0f;
        }

        if(snakeDir[i] > 0.0f)
            snakes[i].scale.x = -0.50f;
        else
            snakes[i].scale.x = 0.50f;

        snakes[i].updateQuad();

        vec3 snakeHead;

        if(snakes[i].scale.x < 0.0f)
            snakeHead.x = snakes[i].pos.x + 0.28f;
        else
            snakeHead.x = snakes[i].pos.x - 0.28f;

        snakeHead.y = snakes[i].pos.y + 0.05f;
        snakeHead.z = snakes[i].pos.z;

        float snakeAcornHitWidth = 0.45f;
        float snakeAcornHitHeight = 0.35f;

        if(thrownAcornLive &&
                fabs(thrownAcorn.pos.x - snakes[i].pos.x) < snakeAcornHitWidth &&
                fabs(thrownAcorn.pos.y - snakes[i].pos.y) < snakeAcornHitHeight)
        {
            thrownAcornLive = false;
            snakeLive[i] = false;
            snakeFalling[i] = true;

            snakeHit[i].pos.x = snakes[i].pos.x;
            snakeHit[i].pos.y = snakes[i].pos.y;
            snakeHit[i].pos.z = snakes[i].pos.z;

            snd->playSounds((char*)"sounds/enemy_hit.wav");
            continue;
        }

        if(fabs(ply->pos.x - snakeHead.x) < 0.22f &&
                fabs(ply->pos.y - snakeHead.y) < 0.22f)
        {
            startHit();
            return;
        }
    }
}

void _level2::spawnBird()
{
    for(int i = 0; i < 2; i++)
    {
        if(!birdLive[i] && !birdFalling[i])
        {
            birdLive[i] = true;

            bird[i].pos.y = ply->pos.y + 0.10f;
            bird[i].pos.z = -7.65f;

            birdSpeed[i] = 5.0f + (rand() % 8) / 10.0f;

            if(rand() % 2 == 0)
            {
                bird[i].pos.x = ply->pos.x - 7.0f;
                birdDir[i] = 1.0f;
                bird[i].scale.x = -0.45f;
            }
            else
            {
                bird[i].pos.x = ply->pos.x + 7.0f;
                birdDir[i] = -1.0f;
                bird[i].scale.x = 0.45f;
            }

            bird[i].scale.y = 0.45f;
            break;
        }
    }
}

void _level2::updateBirds(float dt)
{
    for(int i = 0; i < 2; i++)
    {
        if(birdFalling[i])
        {
            birdHit[i].pos.y -= birdFallSpeed[i] * dt;
            birdFallSpeed[i] += 4.0f * dt;

            if(birdHit[i].pos.y < -4.0f)
            {
                birdFalling[i] = false;
                birdLive[i] = false;
            }

            continue;
        }

        if(!birdLive[i])
            continue;

        bird[i].pos.x += birdDir[i] * birdSpeed[i] * dt;

        if(bird[i].pos.x < ply->pos.x - 9.0f ||
                bird[i].pos.x > ply->pos.x + 9.0f)
        {
            birdLive[i] = false;
            continue;
        }

        float birdHitWidth = 0.45f;
        float birdHitHeight = 0.32f;
        float acornHitWidth = 0.22f;
        float acornHitHeight = 0.22f;

        if(thrownAcornLive &&
                fabs(thrownAcorn.pos.x - bird[i].pos.x) < birdHitWidth + acornHitWidth &&
                fabs(thrownAcorn.pos.y - bird[i].pos.y) < birdHitHeight + acornHitHeight)
        {
            thrownAcornLive = false;
            birdLive[i] = false;
            birdFalling[i] = true;
            birdFallSpeed[i] = 2.0f;

            birdHit[i].pos.x = bird[i].pos.x;
            birdHit[i].pos.y = bird[i].pos.y;
            birdHit[i].pos.z = bird[i].pos.z;

            birdHit[i].scale.x = bird[i].scale.x;
            birdHit[i].scale.y = 0.60f;
            birdHit[i].scale.z = 1.0f;

            snd->playSounds((char*)"sounds/enemy_hit.wav");
            continue;
        }

        if(fabs(ply->pos.x - bird[i].pos.x) < 0.35f &&
                fabs(ply->pos.y - bird[i].pos.y) < 0.30f)
        {
            startHit();
            return;
        }
    }
}

void _level2::drawPlayer()
{
    if(isHit)
    {
        plyHit.pos.x = ply->pos.x;
        plyHit.pos.y = ply->pos.y;
        plyHit.pos.z = ply->pos.z;

        float zoom = 1.4f;

        if(ply->facingLeft)
            plyHit.scale.x = -fabs(ply->scale.x) * zoom;
        else
            plyHit.scale.x = fabs(ply->scale.x) * zoom;

        plyHit.scale.y = ply->scale.y * zoom;
        plyHit.scale.z = ply->scale.z;

        plyHit.drawQuad();
    }
    else if(isThrow)
{
    plyThrow.pos.x = ply->pos.x;
    plyThrow.pos.y = ply->pos.y;
    plyThrow.pos.z = ply->pos.z;

    float throwSize = 1.60f;

    if(ply->facingLeft)
        plyThrow.scale.x = -fabs(ply->scale.x) * throwSize;
    else
        plyThrow.scale.x = fabs(ply->scale.x) * throwSize;

    plyThrow.scale.y = fabs(ply->scale.y) * throwSize;
    plyThrow.scale.z = ply->scale.z;

    plyThrow.drawQuad();
}
    else
    {
        ply->drawQuad();
    }
}

void _level2::drawFoxes()
{
    for(int i = 0; i < 3; i++)
    {
        if(foxFalling[i])
            fox[i].drawQuad();
        else if(foxDead[i])
            fox[i].drawQuad();
        else if(foxLive[i])
            fox[i].drawQuad();
    }
}

void _level2::drawSnakes()
{
    for(int i = 0; i < 3; i++)
    {
        if(snakeFalling[i])
            snakeHit[i].drawQuad();
        else if(snakeLive[i] && !snakeDead[i])
            snakes[i].drawQuad();
    }
}

void _level2::drawBirds()
{
    for(int i = 0; i < 2; i++)
    {
        if(birdFalling[i])
            birdHit[i].drawQuad();
        else if(birdLive[i])
            bird[i].drawQuad();
    }
}

void _level2::update(float dt, bool isPaused)
{
    if(isPaused)
        return;

    if(dt <= 0.0f)
        return;

    if(dt > 0.025f)
        dt = 0.025f;

    if(levelComplete)
    {
        levelCompleteTimer -= dt;

        if(levelCompleteTimer <= 0.0f && onLevelSelect != NULL)
            onLevelSelect(3);

        return;
    }

    if(isHit)
    {
        updateHit(dt);
        return;
    }

    updateRain(dt);
    updateThrownAcorn(dt);
    updateTree(dt);
    updateLog(dt);
    updatePlayer(dt);

    float targetCameraX = ply->pos.x - 0.75f;

    if(targetCameraX < 22.0f)
        targetCameraX = 22.0f;

    float cameraDiff = targetCameraX - level2CameraX;
    float cameraStep = 10.0f * dt;

    if(cameraStep > 1.0f)
        cameraStep = 1.0f;

    level2CameraX += cameraDiff * cameraStep;

    if(fabs(cameraDiff) < 0.001f)
        level2CameraX = targetCameraX;

    updateAcorns();

    bool hasRequiredItems = (acornScore >= 15 && logCount >= 4);
    bool touchedSign = (ply->pos.x >= greatTreeSign.pos.x - 1.0f);

    if(hasRequiredItems && touchedSign)
    {
        levelComplete = true;
        levelCompleteTimer = 0.1f;

        snd->sndEng->stopAllSounds();

        return;
    }

    if(showIntroSign2 && introSign2.pos.x < ply->pos.x - 8.0f)
        showIntroSign2 = false;

    updateFoxes(dt);
    updateSnakes(dt);
    updateBirds(dt);

    if(isThrow)
        ply->actionTrigger = ply->STAND;

    ply->playerActions(dt);
    ply->updateQuad();
}

void _level2::draw(float dt, bool isPaused, vec2 dim)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);

    prlx->xMin = 0.0f;
    prlx->xMax = 1.0f;
    prlx->yMin = 0.0f;
    prlx->yMax = 1.0f;

    glPushMatrix();
    glTranslatef(-level2CameraX, 0.0f, 0.0f);

    float bgScale = 11.3f;
    float bgWidth = (dim.x / dim.y) * 2.0f * bgScale * prlx->scale.x;

    if(bgWidth <= 0.0f)
        bgWidth = 12.0f;

    float firstBgX = floor((level2CameraX - bgWidth) / bgWidth) * bgWidth;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    for(int i = 0; i < 3; i++)
    {
        glPushMatrix();
        glTranslatef(firstBgX + bgWidth * i, 0.0f, 0.0f);
        glScalef(bgScale, bgScale, 1.0f);
        prlx->drawBckGrnd(dim.x, dim.y);
        glPopMatrix();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    if(showIntroSign2)
        introSign2.drawQuad();

    for(int i = 0; i < 10; i++)
        level2_tree[i].drawQuad();

    for(int i = 0; i < 10; i++)
    {
        if(weakTreeAlive[i] || weakTreeBreaking[i])
            weakTree[i].drawQuad();
    }

    for(int i = 0; i < 20; i++)
        branches[i].drawQuad();

    for(int i = 0; i < 20; i++)
    {
        if(isAA[i])
            acorns[i].drawQuad();
    }

    for(int i = 0; i < 10; i++)
    {
        if(logAlive[i])
            logs[i].drawQuad();
    }

    chopPrompt.drawQuad();

    if(acornScore >= 15 && logCount >= 4)
        greatTreeSign.drawQuad();

    drawFoxes();
    drawSnakes();
    drawBirds();

    if(thrownAcornLive)
        thrownAcorn.drawQuad();

    glDisable(GL_DEPTH_TEST);

    if(isKicking)
        kickSprite.drawQuad();
    else
        drawPlayer();

    glEnable(GL_DEPTH_TEST);

    glPopMatrix();

    acornUI.drawQuad();
    woodUI.drawQuad();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos3f(-3.95f, 2.98f, -8.0f);
    std::string scoreText = "x " + std::to_string(acornScore) + "/15";

    for(char c : scoreText)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glRasterPos3f(-1.05f, 2.98f, -8.0f);
    std::string logText = "x " + std::to_string(logCount) + "/4";

    for(char c : logText)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glRasterPos3f(3.20f, 2.98f, -8.0f);
    std::string livesText = "Lives: " + std::to_string(lives);

    for(char c : livesText)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);

    rain[0].drawQuad();
    rain[1].drawQuad();

    glEnable(GL_LIGHTING);
}
int _level2::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        if(wParam == VK_SHIFT)
            throwPressed = true;
        break;

    case WM_KEYUP:
        if(wParam == VK_SHIFT)
            throwPressed = false;
        break;

    default:
        break;
    }

    return 0;
}
