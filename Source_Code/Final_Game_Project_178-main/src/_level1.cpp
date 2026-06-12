#include "_level1.h"

static const float BACKGROUND_SYNC = 1.0f / 11.3f;

_level1::_level1()
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

    currentLane = 0;
    laneY[0] = -2.75f;
    laneY[1] = -2.20f;

    laneDownPressed = false;
    targetLaneY = laneY[0];
    laneMoveSpeed = 9.0f;
    isChangingLane = false;

    inputLocked = false;
    inputLockTimer = 0.0f;

    isHit = false;
    hitTimer = 0.0f;

    cameraX = 22.0f;
    cameraLeftEdge = -3.5f;
    cameraRightEdge = 3.0f;

    onLevelSelect = NULL;

    for(int i = 0; i < 30; i++)
        isAA[i] = false;
}

_level1::~_level1()
{
    delete ply;
    delete prlx;
    delete light;
    delete kbm;
    delete col;
    delete snd;
}

void _level1::setLevelSelectCallback(LevelSelectCallback cb)
{
    onLevelSelect = cb;
}

void _level1::init()
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
    snd->playMusicAdj("sounds/level12_music.mp3", 0.75f);

    prlx->initPrlx("images/citybackground.png");

    introImage.initQuad("images/intro_sign.png");
    introImage.pos.x = 19.5f;
    introImage.pos.y = 0.0f;
    introImage.pos.z = -7.7f;
    introImage.scale.x = 1.5f;
    introImage.scale.y = 1.0f;
    introImage.scale.z = 1.0f;

    ply->plyInit(4, 4, "images/sqrl1.png");
    ply->scale.x = 0.40f;
    ply->scale.y = 0.40f;
    ply->scale.z = 1.0f;
    ply->facingLeft = false;
    ply->actionTrigger = ply->STAND;

    ply->xMin = 0.0f;
    ply->xMax = 0.25f;
    ply->yMin = 0.0f;
    ply->yMax = 0.25f;
    ply->updateQuad();

    plyHit.initQuad("images/squirrel_hit.png");
    plyHit.scale.x = 0.40f;
    plyHit.scale.y = 0.40f;
    plyHit.scale.z = 1.0f;
    plyHit.pos.z = -7.9f;

    for(int i = 0; i < 500; i++)
    {
        floor[i].pos.x = -5.0f + i * 0.5f;
        floor[i].pos.y = -3.35f;
        floor[i].pos.z = -8.0f;

        floor[i].scale.x = 0.25f;
        floor[i].scale.y = 0.25f;
        floor[i].scale.z = 1.0f;
    }

    for(int i = 0; i < 10; i++)
    {
        float baseX;

        if(i == 9)
            baseX = 195.0f;
        else
            baseX = 25.0f + i * 16.0f;

        float treeOffset = ((rand() % 100) / 100.0f - 0.5f) * 0.4f;
        float treeX = baseX + treeOffset;
        float secondTreeX = treeX + 7.4f;

        trees[0][i].initQuad("images/tree.png");
        trees[0][i].pos.x = treeX;
        trees[0][i].pos.y = 1.30f;
        trees[0][i].pos.z = -8.0f;
        trees[0][i].scale.x = 1.30f;
        trees[0][i].scale.y = 3.40f;
        trees[0][i].scale.z = 1.0f;

        trees[1][i].initQuad("images/tree.png");
        trees[1][i].pos.x = secondTreeX;
        trees[1][i].pos.y = 0.30f;
        trees[1][i].pos.z = -8.05f;
        trees[1][i].scale.x = 1.15f;
        trees[1][i].scale.y = 2.40f;
        trees[1][i].scale.z = 1.0f;

        branches[0][i].initQuad("images/pbranch.png");
        branches[0][i].pos.x = treeX + 0.78f;
        branches[0][i].pos.y = -0.35f;
        branches[0][i].pos.z = -8.0f;
        branches[0][i].scale.x = 0.95f;
        branches[0][i].scale.y = 0.60f;
        branches[0][i].scale.z = 1.0f;

        branches[1][i].initQuad("images/pbranch.png");
        branches[1][i].pos.x = treeX - 0.78f;
        branches[1][i].pos.y = 0.45f;
        branches[1][i].pos.z = -8.0f;
        branches[1][i].scale.x = -0.95f;
        branches[1][i].scale.y = 0.60f;
        branches[1][i].scale.z = 1.0f;

        branches[2][i].initQuad("images/pbranch.png");
        branches[2][i].pos.x = secondTreeX - 0.68f;
        branches[2][i].pos.y = -1.25f;
        branches[2][i].pos.z = -8.0f;
        branches[2][i].scale.x = -0.85f;
        branches[2][i].scale.y = 0.55f;
        branches[2][i].scale.z = 1.0f;

        branches[3][i].initQuad("images/pbranch.png");
        branches[3][i].pos.x = secondTreeX + 0.68f;
        branches[3][i].pos.y = -0.45f;
        branches[3][i].pos.z = -8.0f;
        branches[3][i].scale.x = 0.85f;
        branches[3][i].scale.y = 0.55f;
        branches[3][i].scale.z = 1.0f;
    }

    for(int i = 0; i < 30; i++)
    {
        acorns[i].initQuad("images/acorn.png");
        acorns[i].pos.x = 0.0f;
        acorns[i].pos.y = -20.0f;
        acorns[i].pos.z = -7.95f;
        acorns[i].scale.x = 0.15f;
        acorns[i].scale.y = 0.15f;
        acorns[i].scale.z = 1.0f;
        isAA[i] = i < 20;
    }

    for(int i = 0; i < 30; i++)
    {
        if(i < 20)
        {
            int branchGroup = i % 4;
            int branchNum = i / 4;

            acorns[i].pos.x = branches[branchGroup][branchNum].pos.x +
                              ((rand() % 100) / 100.0f - 0.5f) * 0.35f;
            acorns[i].pos.y = branches[branchGroup][branchNum].pos.y + 0.45f;
            acorns[i].pos.z = -7.85f;
        }
        else
        {
            acorns[i].pos.x = 0.0f;
            acorns[i].pos.y = -20.0f;
            acorns[i].pos.z = -7.85f;
        }

        isAA[i] = i < 20;
    }

    acornUI.initQuad("images/acorn.png");
    acornUI.pos.x = -5.0f;
    acornUI.pos.y = 3.13f;
    acornUI.pos.z = -8.0f;
    acornUI.scale.x = 0.25f;
    acornUI.scale.y = 0.25f;
    acornUI.scale.z = 1.0f;

    wildernessSign.initQuad("images/welcome_wilderness.png");
    wildernessSign.pos.x = 175.0f;
    wildernessSign.pos.y = -1.70f;
    wildernessSign.pos.z = -8.0f;
    wildernessSign.scale.x = 1.25f;
    wildernessSign.scale.y = 1.00f;
    wildernessSign.scale.z = 1.0f;

    setCars();
    reset();
}

void _level1::setCars()
{
    for(int i = 0; i < 8; i++)
    {
        int type = rand() % 3;

        if(type == 0)
        {
            cars[i].initQuad("images/blackcar.png");
            cars[i].scale.x = 1.350f;
            cars[i].scale.y = 0.48f;
        }
        else if(type == 1)
        {
            cars[i].initQuad("images/redcar.png");
            cars[i].scale.x = 1.350f;
            cars[i].scale.y = 0.45f;
        }
        else
        {
            cars[i].initQuad("images/bluepickup.png");
            cars[i].scale.x = 1.350f;
            cars[i].scale.y = 0.52f;
        }

        cars[i].scale.z = 1.0f;
        cars[i].pos.z = -7.8f;
        carLive[i] = false;

        if(i < 4)
        {
            carLane[i] = 0;
            carDir[i] = 1.0f;
            cars[i].scale.x = -fabs(cars[i].scale.x);
            cars[i].pos.x = ply->pos.x - 28.0f - i * 17.0f;
            cars[i].pos.y = laneY[0];
            carSpeed[i] = 8.0f + (rand() % 8) * 0.10f;
        }
        else
        {
            carLane[i] = 1;
            carDir[i] = -1.0f;
            cars[i].scale.x = fabs(cars[i].scale.x);
            cars[i].pos.x = ply->pos.x + 28.0f + (i - 4) * 18.0f;
            cars[i].pos.y = laneY[1];
            carSpeed[i] = 5.4f + (rand() % 8) * 0.10f;
        }
    }
}

void _level1::reset()
{
    currentLane = 0;
    targetLaneY = laneY[0];
    isChangingLane = false;

    ply->plyInit(4, 4, "images/sqrl1.png");
    ply->scale.x = 0.40f;
    ply->scale.y = 0.40f;
    ply->scale.z = 1.0f;

    ply->pos.x = 22.0f;
    ply->pos.y = laneY[0];
    ply->pos.z = -7.9f;

    cameraX = 22.0f;

    ply->facingLeft = false;
    ply->actionTrigger = ply->STAND;

    ply->xMin = 0.0f;
    ply->xMax = 0.25f;
    ply->yMin = 0.0f;
    ply->yMax = 0.25f;
    ply->updateQuad();

    velocity.x = 0.0f;
    velocity.y = 0.0f;

    isGrounded = false;
    stepTimer = 0.0f;

    for(int i = 0; i < 30; i++)
    {
        if(i < 20)
        {
            int branchGroup = i % 4;
            int branchNum = i / 4;

            acorns[i].pos.x = branches[branchGroup][branchNum].pos.x +
                              ((rand() % 100) / 100.0f - 0.5f) * 0.35f;
            acorns[i].pos.y = branches[branchGroup][branchNum].pos.y + 0.45f;
            acorns[i].pos.z = -7.85f;
        }
        else
        {
            acorns[i].pos.x = 0.0f;
            acorns[i].pos.y = -20.0f;
            acorns[i].pos.z = -7.85f;
        }

        isAA[i] = i < 20;
    }

    showIntroImage = true;

    acornScore = 0;
    lives = 3;

    levelComplete = false;
    levelCompleteTimer = 0.0f;

    inputLocked = false;
    inputLockTimer = 0.0f;

    isHit = false;
    hitTimer = 0.0f;

    trafficStarted = false;
    laneDownPressed = false;

    setCars();
}

void _level1::startHit()
{
    if(isHit)
        return;

    isHit = true;
    hitTimer = 0.18f;

    snd->playSounds("sounds/gameover.mp3");

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
}

void _level1::updateHit(float dt)
{
    if(!isHit)
        return;

    hitTimer -= dt;

    if(hitTimer <= 0.0f)
        resetPlayerAfterHit();
}

void _level1::resetPlayerAfterHit()
{
    lives--;

    isHit = false;
    hitTimer = 0.0f;

    if(lives <= 0)
    {
        reset();
        return;
    }

    currentLane = 0;
    targetLaneY = laneY[0];
    isChangingLane = false;

    ply->plyInit(4, 4, "images/sqrl1.png");
    ply->scale.x = 0.40f;
    ply->scale.y = 0.40f;
    ply->scale.z = 1.0f;

    ply->pos.x = 22.0f;
    ply->pos.y = laneY[0];
    ply->pos.z = -7.9f;

    cameraX = 22.0f;

    ply->facingLeft = false;
    ply->actionTrigger = ply->STAND;

    ply->xMin = 0.0f;
    ply->xMax = 0.25f;
    ply->yMin = 0.0f;
    ply->yMax = 0.25f;
    ply->updateQuad();

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

    laneDownPressed = false;

    trafficStarted = false;
    setCars();

    inputLocked = true;
    inputLockTimer = 0.75f;
}

void _level1::updateCars(float dt)
{
    float LOWER_MIN_GAP = 15.0f;
    float LOWER_RANDOM_GAP = 12.0f;
    float UPPER_MIN_GAP = 16.0f;
    float UPPER_RANDOM_GAP = 13.0f;

    float LEFT_OFFSCREEN = 30.0f;
    float RIGHT_OFFSCREEN = 30.0f;

    if(!trafficStarted)
    {
        if(!((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)))
            return;

        trafficStarted = true;

        float lowerX = ply->pos.x - 18.0f;
        float upperX = ply->pos.x + 18.0f;

        for(int i = 0; i < 8; i++)
        {
            carLive[i] = true;

            if(carLane[i] == 0)
            {
                cars[i].pos.x = lowerX;
                cars[i].pos.y = laneY[0];
                lowerX -= LOWER_MIN_GAP + (rand() % 100) / 100.0f * LOWER_RANDOM_GAP;
                carSpeed[i] = 8.0f + (rand() % 8) * 0.10f;
            }
            else
            {
                cars[i].pos.x = upperX;
                cars[i].pos.y = laneY[1];
                upperX += UPPER_MIN_GAP + (rand() % 100) / 100.0f * UPPER_RANDOM_GAP;
                carSpeed[i] = 6.4f + (rand() % 8) * 0.10f;
            }
        }
    }

    for(int i = 0; i < 8; i++)
    {
        if(!carLive[i])
            continue;

        cars[i].pos.x += carDir[i] * carSpeed[i] * dt;
    }

    for(int pass = 0; pass < 4; pass++)
    {
        for(int i = 0; i < 8; i++)
        {
            if(!carLive[i] || carLane[i] != 0)
                continue;

            for(int j = 0; j < 8; j++)
            {
                if(i == j || !carLive[j] || carLane[j] != 0)
                    continue;

                if(cars[i].pos.x < cars[j].pos.x &&
                        cars[i].pos.x > cars[j].pos.x - LOWER_MIN_GAP)
                {
                    cars[i].pos.x = cars[j].pos.x - LOWER_MIN_GAP;
                    carSpeed[i] = carSpeed[j];
                }
            }
        }

        for(int i = 0; i < 8; i++)
        {
            if(!carLive[i] || carLane[i] != 1)
                continue;

            for(int j = 0; j < 8; j++)
            {
                if(i == j || !carLive[j] || carLane[j] != 1)
                    continue;

                if(cars[i].pos.x > cars[j].pos.x &&
                        cars[i].pos.x < cars[j].pos.x + UPPER_MIN_GAP)
                {
                    cars[i].pos.x = cars[j].pos.x + UPPER_MIN_GAP;
                    carSpeed[i] = carSpeed[j];
                }
            }
        }
    }

    for(int i = 0; i < 8; i++)
    {
        if(!carLive[i])
            continue;

        if(carLane[i] == 0 && cars[i].pos.x > ply->pos.x + RIGHT_OFFSCREEN)
        {
            int type = rand() % 3;

            if(type == 0)
            {
                cars[i].initQuad("images/blackcar.png");
                cars[i].scale.x = -1.350f;
                cars[i].scale.y = 0.48f;
            }
            else if(type == 1)
            {
                cars[i].initQuad("images/redcar.png");
                cars[i].scale.x = -1.28f;
                cars[i].scale.y = 0.45f;
            }
            else
            {
                cars[i].initQuad("images/bluepickup.png");
                cars[i].scale.x = -1.45f;
                cars[i].scale.y = 0.52f;
            }

            float furthestBack = ply->pos.x - LEFT_OFFSCREEN;

            for(int j = 0; j < 8; j++)
            {
                if(j != i && carLane[j] == 0 && cars[j].pos.x < furthestBack)
                    furthestBack = cars[j].pos.x;
            }

            float gap = LOWER_MIN_GAP + (rand() % 100) / 100.0f * LOWER_RANDOM_GAP;

            cars[i].pos.x = furthestBack - gap;
            cars[i].pos.y = laneY[0];
            cars[i].pos.z = -7.8f;
            cars[i].scale.z = 1.0f;
            carSpeed[i] = 8.0f + (rand() % 8) * 0.10f;
        }

        if(carLane[i] == 1 && cars[i].pos.x < ply->pos.x - LEFT_OFFSCREEN)
        {
            int type = rand() % 3;

            if(type == 0)
            {
                cars[i].initQuad("images/blackcar.png");
                cars[i].scale.x = 1.350f;
                cars[i].scale.y = 0.48f;
            }
            else if(type == 1)
            {
                cars[i].initQuad("images/redcar.png");
                cars[i].scale.x = 1.28f;
                cars[i].scale.y = 0.45f;
            }
            else
            {
                cars[i].initQuad("images/bluepickup.png");
                cars[i].scale.x = 1.45f;
                cars[i].scale.y = 0.52f;
            }

            float furthestFront = ply->pos.x + RIGHT_OFFSCREEN;

            for(int j = 0; j < 8; j++)
            {
                if(j != i && carLane[j] == 1 && cars[j].pos.x > furthestFront)
                    furthestFront = cars[j].pos.x;
            }

            float gap = UPPER_MIN_GAP + (rand() % 100) / 100.0f * UPPER_RANDOM_GAP;

            cars[i].pos.x = furthestFront + gap;
            cars[i].pos.y = laneY[1];
            cars[i].pos.z = -7.8f;
            cars[i].scale.z = 1.0f;
            carSpeed[i] = 6.4f + (rand() % 8) * 0.10f;
        }

        if(carLane[i] == currentLane)
        {
            float playerHalfWidth = fabs(ply->scale.x) * 0.30f;
            float playerHalfHeight = fabs(ply->scale.y) * 0.35f;

            float carHalfWidth = fabs(cars[i].scale.x) * 0.62f;
            float carHalfHeight = fabs(cars[i].scale.y) * 0.32f;

            float dx = fabs(ply->pos.x - cars[i].pos.x);
            float dy = fabs(ply->pos.y - cars[i].pos.y);

            if(dx < (playerHalfWidth + carHalfWidth) &&
                    dy < (playerHalfHeight + carHalfHeight))
            {
                startHit();
                return;
            }
        }
    }
}

void _level1::update(float dt, bool isPaused)
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
            onLevelSelect(2);

        return;
    }

    if(isHit)
    {
        updateHit(dt);
        return;
    }

    if(inputLocked)
    {
        inputLockTimer -= dt;

        if(inputLockTimer <= 0.0f)
            inputLocked = false;

        return;
    }

    const float MOVE_SPEED = 5.2f;
    const float RUN_MULT = 1.35f;
    const float TREE_RUN_MULT = 1.12f;

    bool leftDown  = (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000);
    bool rightDown = (GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000);
    bool runDown   = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ||
                     (GetAsyncKeyState(VK_LSHIFT) & 0x8000) ||
                     (GetAsyncKeyState(VK_RSHIFT) & 0x8000);
    bool jumpDown  = (GetAsyncKeyState(VK_SPACE) & 0x8000) ||
                     (GetAsyncKeyState(VK_UP) & 0x8000) ||
                     (GetAsyncKeyState('W') & 0x8000);

    bool upperLaneAir = currentLane == 1 && !isGrounded;
    bool canRun = runDown && !upperLaneAir;
    float activeRunMult = (currentLane == 1) ? TREE_RUN_MULT : RUN_MULT;

    playerOnBranch = false;

    if(currentLane == 1)
    {
        for(int k = 0; k < 4; k++)
        {
            for(int j = 0; j < 10; j++)
            {
                float branchTop = branches[k][j].pos.y + 0.35f;
                float branchHalfWidth = fabs(branches[k][j].scale.x) * 0.75f;

                if(fabs(ply->pos.x - branches[k][j].pos.x) < branchHalfWidth &&
                        fabs(ply->pos.y - branchTop) < 0.08f)
                {
                    playerOnBranch = true;
                }
            }
        }
    }

    if(!isGrounded && !isChangingLane)
        velocity.y -= 14.0f * dt;

    velocity.x = 0.0f;

    if(!isChangingLane)
        ply->actionTrigger = ply->STAND;

    if(leftDown)
    {
        ply->facingLeft = true;
        velocity.x = -MOVE_SPEED;

        if(canRun)
        {
            velocity.x *= activeRunMult;

            if(!isChangingLane)
                ply->actionTrigger = ply->RUN;
        }
        else if(!isChangingLane)
        {
            ply->actionTrigger = ply->LEFTWALK;
        }
    }
    else if(rightDown)
    {
        ply->facingLeft = false;
        velocity.x = MOVE_SPEED;

        if(canRun)
        {
            velocity.x *= activeRunMult;

            if(!isChangingLane)
                ply->actionTrigger = ply->RUN;
        }
        else if(!isChangingLane)
        {
            ply->actionTrigger = ply->RIGHTWALK;
        }
    }
    else if(isGrounded && !isChangingLane)
    {
        ply->actionTrigger = ply->STAND;
    }

    if(laneDownPressed && isGrounded && !isChangingLane && !playerOnBranch)
    {
        currentLane = 1 - currentLane;
        targetLaneY = laneY[currentLane];
        isChangingLane = true;
        laneDownPressed = false;
    }

    if(isChangingLane)
    {
        float diff = targetLaneY - ply->pos.y;

        if(fabs(diff) <= laneMoveSpeed * dt)
        {
            ply->pos.y = targetLaneY;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            isGrounded = true;
            isChangingLane = false;
        }
        else
        {
            if(diff > 0.0f)
                ply->pos.y += laneMoveSpeed * dt;
            else
                ply->pos.y -= laneMoveSpeed * dt;

            velocity.y = 0.0f;
            isGrounded = true;
        }
    }

    if(jumpDown && isGrounded && !isChangingLane)
    {
        snd->playSounds("sounds/jump.mp3");

        if(currentLane == 1 && runDown)
        {
            if(velocity.x > MOVE_SPEED)
                velocity.x = MOVE_SPEED;

            if(velocity.x < -MOVE_SPEED)
                velocity.x = -MOVE_SPEED;
        }

        velocity.y = jumpStrength;
        isGrounded = false;

        ply->actionTrigger = ply->JUMP;
    }

    ply->pos.x += velocity.x * dt;

    if(!isChangingLane)
        ply->pos.y += velocity.y * dt;

    if(!isChangingLane)
        isGrounded = false;

    if(!isChangingLane)
    {
        if(ply->pos.y <= laneY[currentLane] && velocity.y <= 0.0f)
        {
            ply->pos.y = laneY[currentLane];
            velocity.y = 0.0f;
            isGrounded = true;
        }
    }

    if(!isChangingLane && currentLane == 1)
    {
        for(int k = 0; k < 4; k++)
        {
            for(int j = 0; j < 10; j++)
            {
                float branchTop = branches[k][j].pos.y + 0.35f;
                float branchHalfWidth = fabs(branches[k][j].scale.x) * 0.75f;

                if(ply->pos.y <= branchTop &&
                        ply->pos.y >= branches[k][j].pos.y + 0.05f &&
                        fabs(ply->pos.x - branches[k][j].pos.x) < branchHalfWidth &&
                        velocity.y <= 0.0f)
                {
                    ply->pos.y = branchTop;
                    velocity.y = 0.0f;
                    isGrounded = true;
                    playerOnBranch = true;
                }
            }
        }
    }

    if(velocity.x != 0.0f && isGrounded && !playerOnBranch)
    {
        stepTimer += dt;

        if(stepTimer > 0.18f)
        {
            stepTimer = 0.0f;
        }
    }

    updateCars(dt);

    if(currentLane == 1 && playerOnBranch)
    {
        for(int k = 0; k < 30; k++)
        {
            if(isAA[k] && col->isAABBCol(ply->pos, ply->scale, acorns[k].pos, acorns[k].scale))
            {
                isAA[k] = false;
                acornScore++;
            }
        }
    }

    if(acornScore < 10 && ply->pos.x > wildernessSign.pos.x - 2.0f)
        ply->pos.x = wildernessSign.pos.x - 2.0f;

    if(acornScore >= 10 && ply->pos.x > wildernessSign.pos.x + 8.0f)
    {
        levelComplete = true;
        levelCompleteTimer = 1.0f;

        snd->sndEng->stopAllSounds();
    }

    ply->playerActions(dt);

    if(!isGrounded)
    {
        ply->xMin = 0.0f;
        ply->xMax = 0.25f;
        ply->yMin = 0.50f;
        ply->yMax = 0.75f;
    }

    ply->updateQuad();

    if(ply->pos.y < -3.5f)
    {
        startHit();
        return;
    }

    if(showIntroImage && introImage.pos.x < ply->pos.x - 8.0f)
        showIntroImage = false;

    if(ply->pos.x < 18.0f)
        ply->pos.x = 18.0f;

    float targetCameraX = ply->pos.x - 0.75f;

    if(targetCameraX < 22.0f)
        targetCameraX = 22.0f;

    float cameraDiff = targetCameraX - cameraX;
    float cameraStep = 14.0f * dt;

    if(cameraStep > 1.0f)
        cameraStep = 1.0f;

    cameraX += cameraDiff * cameraStep;

    if(fabs(cameraDiff) < 0.001f)
        cameraX = targetCameraX;
}

void _level1::drawPlayer()
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
    else
    {
        ply->drawQuad();
    }
}

void _level1::draw(float dt, bool isPaused, vec2 dim)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);

    prlx->xMin = 0.0f;
    prlx->xMax = 1.0f;
    prlx->yMin = 0.0f;
    prlx->yMax = 1.0f;

    glPushMatrix();
    glTranslatef(-cameraX, 0.0f, 0.0f);

    float bgScale = 11.3f;
    float bgWidth = (dim.x / dim.y) * 2.0f * bgScale * prlx->scale.x;

    if(bgWidth <= 0.0f)
        bgWidth = 12.0f;

    int firstBgIndex = (int)((cameraX - bgWidth) / bgWidth);
    float firstBgX = firstBgIndex * bgWidth;

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

    if(showIntroImage)
        introImage.drawQuad();

    for(int i = 0; i < 500; i++)
        floor[i].drawQuad();

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 10; j++)
            trees[i][j].drawQuad();
    }

    if(currentLane == 1)
    {
        glDisable(GL_DEPTH_TEST);
        drawPlayer();
        glEnable(GL_DEPTH_TEST);
    }

    glDepthMask(GL_FALSE);

    for(int i = 0; i < 8; i++)
    {
        if(carLive[i] && carLane[i] == 1)
            cars[i].drawQuad();
    }

    for(int i = 0; i < 8; i++)
    {
        if(carLive[i] && carLane[i] == 0)
            cars[i].drawQuad();
    }

    glDepthMask(GL_TRUE);

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 10; j++)
            branches[i][j].drawQuad();
    }

    for(int i = 0; i < 30; i++)
    {
        if(isAA[i])
            acorns[i].drawQuad();
    }

    wildernessSign.drawQuad();

    if(currentLane == 0)
    {
        glDisable(GL_DEPTH_TEST);
        drawPlayer();
        glEnable(GL_DEPTH_TEST);
    }

    glPopMatrix();

    acornUI.pos.x = -4.20f;
    acornUI.pos.y = 3.05f;
    acornUI.pos.z = -8.0f;
    acornUI.drawQuad();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos3f(-3.95f, 2.98f, -8.0f);
    std::string scoreText = "x " + std::to_string(acornScore);

    for(char c : scoreText)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glRasterPos3f(3.20f, 2.98f, -8.0f);
    std::string livesText = "Lives: " + std::to_string(lives);

    for(char c : livesText)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

int _level1::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        if(wParam == VK_DOWN)
        {
            bool wasDown = (lParam & (1 << 30)) != 0;

            if(!wasDown && !isChangingLane)
                laneDownPressed = true;
        }
        break;

    case WM_KEYUP:
        if(wParam == VK_DOWN)
            laneDownPressed = false;
        break;

    default:
        break;
    }

    return 0;
}
