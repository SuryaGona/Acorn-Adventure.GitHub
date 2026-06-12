#include "_level3.h"

_level3::_level3()
{
}

_level3::~_level3()
{
    delete ply;
    delete prlx;
    delete light;
    delete kbm;
    delete hit;
    delete snd;
}

void _level3::init()
{
    glewInit();

    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHT0);

    light->setLight(GL_LIGHT0);
    snd->initSounds();

    prlx->initPrlx((char*)"images/tree1.png");
    prlx->scale.x = 1.0f;
    prlx->scale.y = 1.0f;
    prlx->scale.z = 1.0f;
    lastLoadedTree = 1;

    ply->plyInit(4,4,(char*)"images/squirrel.png");
    ply->scale.x = 0.50f;
    ply->scale.y = 0.50f;
    ply->scale.z = 1.0f;
    ply->pos.x = -2.80f;
    ply->pos.y = -1.75f;
    ply->pos.z = -7.0f;
    ply->facingLeft = false;
    ply->actionTrigger = ply->STAND;

    plyIdle.initQuad((char*)"images/squirrel_idle.png");
    plyThrow.initQuad((char*)"images/squirrel_throw.png");
    plyHit.initQuad((char*)"images/squirrel_hit.png");

    plyIdle.pos.z = -7.0f;
    plyThrow.pos.z = -7.0f;
    plyHit.pos.z = -7.0f;

    acorn.initQuad((char*)"images/acorn.png");
    acorn.scale.x = 0.28f;
    acorn.scale.y = 0.28f;
    acorn.scale.z = 1.0f;
    acorn.pos.z = -7.0f;

    goldenAcorn.initQuad((char*)"images/golden_acorn.png");
    goldenAcorn.scale.x = 1.10f;
    goldenAcorn.scale.y = 0.75f;
    goldenAcorn.scale.z = 1.0f;
    goldenAcorn.pos.x = 0.0f;
    goldenAcorn.pos.y = 2.65f;
    goldenAcorn.pos.z = -7.0f;

    gameCompleted.initQuad((char*)"images/game_completed.png");
    gameCompleted.scale.x = 2.0f;
    gameCompleted.scale.y = 2.0f;
    gameCompleted.scale.z = 1.0f;
    gameCompleted.pos.x = 0.0f;
    gameCompleted.pos.y = 0.0f;
    gameCompleted.pos.z = -6.5f;

    endCredits.initQuad((char*)"images/end_credits.png");
    endCredits.scale.x = 4.0f;
    endCredits.scale.y = 2.68f;
    endCredits.scale.z = 1.0f;
    endCredits.pos.x = 0.0f;
    endCredits.pos.y = 0.0f;
    endCredits.pos.z = -6.4f;

    nutHudBox.initQuad((char*)"images/hud_box.png");
    nutHudBox.scale.x = 0.62f;
    nutHudBox.scale.y = 0.13f;
    nutHudBox.scale.z = 1.0f;
    nutHudBox.pos.x = -0.91f;
    nutHudBox.pos.y = -2.55f;
    nutHudBox.pos.z = -6.90f;

    nutHud.initQuad((char*)"images/acorn.png");
    nutHud.scale.x = 0.11f;
    nutHud.scale.y = 0.11f;
    nutHud.scale.z = 1.0f;
    nutHud.pos.x = -4.35f;
    nutHud.pos.y = -2.55f;
    nutHud.pos.z = -6.80f;

    for(int i=0; i<10; i++)
    {
        nutMeter[i].initQuad((char*)"images/acorn.png");
        nutMeter[i].scale.x = 0.12f;
        nutMeter[i].scale.y = 0.12f;
        nutMeter[i].scale.z = 1.0f;
        nutMeter[i].pos.z = -7.0f;
    }

    for(int i=0; i<2; i++)
    {
        bird[i].initQuad((char*)"images/bird.png");
        bird[i].scale.x = 0.45f;
        bird[i].scale.y = 0.45f;
        bird[i].scale.z = 1.0f;
        bird[i].pos.z = -7.0f;

        birdHit[i].initQuad((char*)"images/bird_hit.png");
        birdHit[i].scale.x = 0.60f;
        birdHit[i].scale.y = 0.60f;
        birdHit[i].scale.z = 1.0f;
        birdHit[i].pos.z = -7.0f;

        birdLive[i] = false;
        birdDead[i] = false;
        birdFalling[i] = false;
        birdSpeed[i] = 3.2f;
        birdDir[i] = 1.0f;
        birdFallSpeed[i] = 2.0f;
    }

    for(int i=0; i<6; i++)
    {
        branch[i].initQuad((char*)"images/branch.png");
        branch[i].scale.x = 1.78f;
        branch[i].scale.y = 1.18f;
        branch[i].scale.z = 1.0f;
        branch[i].pos.z = -7.0f;

        nuts[i].initQuad((char*)"images/nut.png");
        nuts[i].scale.x = 0.26f;
        nuts[i].scale.y = 0.26f;
        nuts[i].scale.z = 1.0f;
        nuts[i].pos.z = -7.0f;
    }
    branch[0].scale.x = -1.78f;

    for(int i=0; i<2; i++)
    {
        rocks[i].initQuad((char*)"images/rock.png");
        rocks[i].scale.x = 0.20f;
        rocks[i].scale.y = 0.20f;
        rocks[i].scale.z = 1.0f;
        rocks[i].pos.z = -7.0f;
    }

    for(int i=0; i<5; i++)
    {
        snakes[i].enmsInit(1,1,(char*)"images/snake.png");

        snakeHit[i].initQuad((char*)"images/snake_hit.png");
        snakeHit[i].scale.x = 0.75f;
        snakeHit[i].scale.y = 0.75f;
        snakeHit[i].scale.z = 1.0f;
        snakeHit[i].pos.z = -7.0f;
    }

    srand((unsigned int)time(NULL));

    reset();
}

void _level3::reset()
{
    climbStage = 0;
    nutsCollected = 0;
    gameWon = false;
    creditStage = 0;
    returnToMenu = false;

    kbm->isLeftPressed = false;
    kbm->isRightPressed = false;
    kbm->isUpPressed = false;
    kbm->isSpacePressed = false;

    throwPressed = false;
    jumpPressed = false;
    jumpBufferTimer = 0.0f;
    coyoteTimer = 0.0f;

    inputLockedAfterHit = false;
    inputUnlockTimer = 0.0f;


    lastLoadedTree = -1;

    loadStage();
}

void _level3::loadStage()
{
    int treeId;

    if(climbStage == 3)
        treeId = 4;
    else if(climbStage == 2)
        treeId = 3;
    else if(climbStage % 2 == 0)
        treeId = 1;
    else
        treeId = 2;


    if(treeId != lastLoadedTree)
    {
        if(treeId == 4)
            prlx->initPrlx((char*)"images/tree4.png");
        else if(treeId == 3)
            prlx->initPrlx((char*)"images/tree3.png");
        else if(treeId == 2)
            prlx->initPrlx((char*)"images/tree2.png");
        else
            prlx->initPrlx((char*)"images/tree1.png");

        snd->sndEng->stopAllSounds();

        if(treeId == 3 || treeId == 4)
            snd->playMusic((char*)"sounds/level34_music.mp3");
        else
            snd->playMusic((char*)"sounds/level12_music.mp3");

        lastLoadedTree = treeId;
    }

    setBranches();

    ply->pos.z = -7.0f;
    ply->actionTrigger = ply->STAND;
    ply->facingLeft = false;

    isJump = false;
    isThrow = false;
    isHit = false;

    inputLockedAfterHit = true;
    inputUnlockTimer = 0.18f;

    acornLive = false;
    acornFalling = false;

    kbm->isLeftPressed = false;
    kbm->isRightPressed = false;
    kbm->isUpPressed = false;
    kbm->isSpacePressed = false;

    throwPressed = false;
    jumpPressed = false;
    jumpBufferTimer = 0.0f;
    coyoteTimer = 0.0f;

    birdReady = false;
    secondBirdSpawn = false;
    bird2Timer = 0.0f;

    for(int i=0; i<2; i++)
    {
        birdLive[i] = false;
        birdDead[i] = false;
        birdFalling[i] = false;
        birdFallSpeed[i] = 2.0f;
    }

    jumpVel = 0.0f;
    throwTimer = 0.0f;
    hitTimer = 0.0f;
    acornT = 0.0f;
    acornTimer = 0.0f;
    acornFallSpeed = 0.0f;

    if(climbStage == 0)
    {
        ply->pos.x = -2.80f;
        ply->pos.y = -1.75f;
        onBranch = true;
    }
    else
    {
        int startBranch = 0;

        for(int i=1; i<6; i++)
        {
            if(branch[i].pos.y < branch[startBranch].pos.y)
                startBranch = i;
        }

        ply->pos.x = branch[startBranch].pos.x;
        ply->pos.y = branch[startBranch].pos.y + 0.60f;
        onBranch = true;
    }

    goldenAcorn.pos.x = 0.0f;
    goldenAcorn.pos.y = 2.65f;
    goldenAcorn.pos.z = -7.0f;

    setNuts();
    setRocks();
    setSnakes();
    setBird();
}

void _level3::setBranches()
{
    float evenPos[6][2] =
{
    { 3.00f,-1.35f},
    {-3.35f,-0.25f},
    { 3.25f, 0.50f},
    {-3.35f, 1.70f},
    { 20.00f,20.00f},
    {-3.50f, 3.15f}
};
    float oddPos[6][2] =
{
    {-3.10f,-2.55f},
    {-2.70f,-0.25f},
    { 2.40f, 0.65f},
    {-2.80f, 1.95f},
    { 2.45f,-1.50f},
    {-0.20f, 3.15f}
};

    float tree3Pos[6][2] =
    {
        {-3.10f,-2.55f},
        {-2.70f,-0.25f},
        { 2.40f, 0.65f},
        {-2.80f, 1.95f},
        { 2.45f,-1.50f},
        {-0.20f, 3.15f}
    };


    float tree4Pos[6][2] =
    {
        {-3.10f,-2.55f},
        {-2.70f,-0.25f},
        { 2.40f, 0.65f},
        {-2.80f, 1.95f},
        { 2.45f,-1.50f},
        {-0.20f, 3.15f}
    };

    float rot[6] = {-4.0f,3.0f,-3.0f,2.0f,-2.0f,2.0f};
    float (*pos)[2];

    if(climbStage == 3)
        pos = tree4Pos;
    else if(climbStage == 2)
        pos = tree3Pos;
    else
        pos = (climbStage % 2 == 0) ? evenPos : oddPos;

    for(int i=0; i<6; i++)
    {
        branch[i].pos.x = pos[i][0];
        branch[i].pos.y = pos[i][1];
        branch[i].rot.z = rot[i];
    }
}

void _level3::setNuts()
{
    for(int i=0; i<6; i++)
    {
        nutLive[i] = rand() % 10 < 6;
        nuts[i].pos.x = branch[i].pos.x;
        nuts[i].pos.y = branch[i].pos.y + 0.40f;
        nuts[i].pos.z = -7.0f;
    }
}

void _level3::setRocks()
{
    for(int i=0; i<2; i++)
    {
        rocks[i].pos.x = -3.0f + (rand() % 60) / 10.0f;
        rocks[i].pos.y = 3.5f + i;
        rocks[i].pos.z = -7.0f;
        fallSpeed[i] = 1.5f + (rand() % 10) / 10.0f;
    }
}

void _level3::setSnakes()
{
    int snakeTotal = 2;

    if(climbStage == 2)
        snakeTotal = 3;

    if(climbStage == 3)
        snakeTotal = 5;

    for(int i=0; i<5; i++)
    {
        snakes[i].scale.x = 0.55f;
        snakes[i].scale.y = 0.55f;
        snakes[i].scale.z = 1.0f;
        snakes[i].pos.z = -7.0f;

        snakeDead[i] = false;
        snakeFalling[i] = false;
        snakeFallSpeed[i] = 1.8f;

        snakes[i].pos.x = 20.0f;
        snakes[i].pos.y = 20.0f;
    }

    if(climbStage == 0)
    {
        snakeLive = false;
        return;
    }

    snakeLive = true;

    if(climbStage == 3)
    {
        int startBranch = 0;

        for(int i=1; i<6; i++)
        {
            if(branch[i].pos.y < branch[startBranch].pos.y)
                startBranch = i;
        }

        int s = 0;

        for(int i=0; i<6; i++)
        {
            if(i != startBranch)
            {
                snakeBranch[s] = i;
                s++;
            }
        }
    }
    else if(climbStage == 2)
    {
        snakeBranch[0] = 1;
        snakeBranch[1] = 3;
        snakeBranch[2] = 4;
    }
    else
    {
        snakeBranch[0] = 3;
        snakeBranch[1] = 4;
    }

    for(int i=0; i<snakeTotal; i++)
    {
        snakeDir[i] = (rand() % 2 == 0) ? 1.0f : -1.0f;
        snakeSpeed[i] = 0.8f + (rand() % 5) / 10.0f;
        snakeRange[i] = 0.60f + (rand() % 4) / 10.0f;

        snakes[i].pos.x = branch[snakeBranch[i]].pos.x;
        snakes[i].pos.y = branch[snakeBranch[i]].pos.y + 0.55f;

        if(snakeDir[i] > 0.0f)
            snakes[i].scale.x = -0.75f;
        else
            snakes[i].scale.x = 0.75f;
    }
}

void _level3::setBird()
{
    for(int i=0; i<2; i++)
        birdLive[i] = false;

    if((climbStage != 2 && climbStage != 3) || !birdReady)
        return;

    birdLive[0] = true;
    birdDead[0] = false;
    birdFalling[0] = false;
    birdFallSpeed[0] = 2.0f;

    bird[0].pos.y = ply->pos.y;
    bird[0].pos.z = -7.0f;
    birdSpeed[0] = 3.0f + (rand() % 8) / 10.0f;

    if(rand() % 2 == 0)
    {
        bird[0].pos.x = -5.2f;
        birdDir[0] = 1.0f;
        bird[0].scale.x = -0.45f;
    }
    else
    {
        bird[0].pos.x = 5.2f;
        birdDir[0] = -1.0f;
        bird[0].scale.x = 0.45f;
    }

    bird[0].scale.y = 0.45f;

    if(climbStage == 3)
    {
        secondBirdSpawn = false;
        bird2Timer = 0.0f;
    }
}

bool _level3::checkBranchLand()
{
    for(int i=0; i<6; i++)
    {
        if(ply->pos.y <= branch[i].pos.y + 0.60f &&
                ply->pos.y >= branch[i].pos.y + 0.10f &&
                fabs(ply->pos.x - branch[i].pos.x) < 1.45f &&
                jumpVel <= 0.0f)
        {
            ply->pos.y = branch[i].pos.y + 0.60f;
            onBranch = true;
            isJump = false;
            jumpVel = 0.0f;
            coyoteTimer = coyoteMax;
            return true;
        }
    }

    if(climbStage == 0)
    {
        if(ply->pos.y <= -1.75f && jumpVel <= 0.0f)
        {
            ply->pos.y = -1.75f;
            onBranch = true;
            isJump = false;
            jumpVel = 0.0f;
            coyoteTimer = coyoteMax;
            return true;
        }
    }
    else
    {
        if(ply->pos.y <= -2.8f)
        {
            kbm->isLeftPressed = false;
            kbm->isRightPressed = false;
            kbm->isUpPressed = false;
            kbm->isSpacePressed = false;
            throwPressed = false;
            jumpPressed = false;
            jumpBufferTimer = 0.0f;

            loadStage();

            inputLockedAfterHit = true;
            inputUnlockTimer = 0.18f;
            return true;
        }
    }

    return false;
}

void _level3::setPlayerPic(_quad *pic)
{
    pic->pos.x = ply->pos.x;
    pic->pos.y = ply->pos.y;
    pic->pos.z = ply->pos.z;
}

void _level3::setPicFace(_quad *pic, float size)
{
    pic->scale.y = size;
    pic->scale.z = 1.0f;

    if(ply->facingLeft)
        pic->scale.x = -size;
    else
        pic->scale.x = size;
}

vec3 _level3::getSnakeHead(int i)
{
    vec3 snakeHead;

    if(snakes[i].scale.x < 0.0f)
        snakeHead.x = snakes[i].pos.x + 0.36f;
    else
        snakeHead.x = snakes[i].pos.x - 0.36f;

    snakeHead.y = snakes[i].pos.y + 0.06f;
    snakeHead.z = snakes[i].pos.z;

    return snakeHead;
}

void _level3::startHit()
{
    if(isHit)
        return;

    snd->playSounds((char*)"sounds/gameover.mp3");

    kbm->isLeftPressed = false;
    kbm->isRightPressed = false;
    kbm->isUpPressed = false;
    kbm->isSpacePressed = false;

    throwPressed = false;
    jumpPressed = false;
    jumpBufferTimer = 0.0f;
    coyoteTimer = 0.0f;

    isJump = false;
    jumpVel = 0.0f;
    inputLockedAfterHit = true;

    isHit = true;
    hitTimer = 0.45f;
}

void _level3::startThrow()
{
    if(acornLive || isThrow || nutsCollected <= 0)
        return;

    isThrow = true;
    throwTimer = 0.25f;
    nutsCollected--;

    snd->playSounds((char*)"sounds/jump.mp3");

    acornLive = true;

    acornStart.x = ply->pos.x;
    acornStart.y = ply->pos.y - 0.08f;
    acornStart.z = -7.0f;

    acorn.pos.x = acornStart.x;
    acorn.pos.y = acornStart.y;
    acorn.pos.z = acornStart.z;

    if(ply->facingLeft)
        acornVelX = -6.0f;
    else
        acornVelX = 6.0f;

    acornVelY = 0.0f;
}

void _level3::updateHit(float dt)
{
    hitTimer -= dt;

    if(hitTimer <= 0.0f)
    {
        nutsCollected = 0;

        kbm->isLeftPressed = false;
        kbm->isRightPressed = false;
        kbm->isUpPressed = false;
        kbm->isSpacePressed = false;

        throwPressed = false;
        jumpPressed = false;
        jumpBufferTimer = 0.0f;

        isHit = false;
        loadStage();

        inputLockedAfterHit = true;
        inputUnlockTimer = 0.18f;
    }
}

void _level3::updateThrow(float dt)
{
    if(isThrow)
    {
        throwTimer -= dt;

        if(throwTimer <= 0.0f)
            isThrow = false;
    }

    if(throwPressed && !isHit)
        startThrow();
}

void _level3::updatePlayer(float dt)
{
    if(inputLockedAfterHit)
    {
        inputUnlockTimer -= dt;

        kbm->isLeftPressed = false;
        kbm->isRightPressed = false;
        kbm->isUpPressed = false;
        kbm->isSpacePressed = false;

        throwPressed = false;
        jumpPressed = false;
        jumpBufferTimer = 0.0f;

        ply->actionTrigger = ply->STAND;

        if(inputUnlockTimer <= 0.0f)
            inputLockedAfterHit = false;

        return;
    }

    float moveSpeed = 4.0f;

    if(jumpBufferTimer > 0.0f)
        jumpBufferTimer -= dt;

    if(onBranch)
        coyoteTimer = coyoteMax;
    else
        coyoteTimer -= dt;

    if(onBranch)
    {
        bool stillOnSomething = false;


        if(climbStage == 0 && fabs(ply->pos.y - (-1.75f)) < 0.08f)
            stillOnSomething = true;

        for(int i=0; i<6; i++)
        {
            if(fabs(ply->pos.y - (branch[i].pos.y + 0.60f)) < 0.08f &&
                    fabs(ply->pos.x - branch[i].pos.x) < 1.45f)
            {
                stillOnSomething = true;
                break;
            }
        }

        if(!stillOnSomething)
        {
            onBranch = false;
            isJump = false;
        }
    }

    if(kbm->isLeftPressed && !isThrow)
    {
        birdReady = true;
        ply->pos.x -= moveSpeed * dt;

        if(!isJump && onBranch)
            ply->actionTrigger = ply->LEFTWALK;

        ply->facingLeft = true;
    }
    else if(kbm->isRightPressed && !isThrow)
    {
        birdReady = true;
        ply->pos.x += moveSpeed * dt;

        if(!isJump && onBranch)
            ply->actionTrigger = ply->RIGHTWALK;

        ply->facingLeft = false;
    }
    else if(!isJump && !isThrow)
        ply->actionTrigger = ply->STAND;


    bool canJump = !isThrow && coyoteTimer > 0.0f;

    if(climbStage == 0 && ply->pos.y <= -1.74f && jumpVel <= 0.0f)
    {
        ply->pos.y = -1.75f;
        onBranch = true;
        canJump = !isThrow;
    }

    if(jumpBufferTimer > 0.0f && canJump)
    {
        snd->playSounds((char*)"sounds/jump.mp3");

        birdReady = true;
        isJump = true;
        onBranch = false;
        jumpVel = 5.0f;
        coyoteTimer = 0.0f;
        jumpBufferTimer = 0.0f;

        ply->actionTrigger = ply->JUMP;
    }

    jumpPressed = false;

    if(!onBranch || isJump)
    {
        ply->pos.y += jumpVel * dt;
        jumpVel -= gravityY * dt;
        checkBranchLand();
    }

    if(ply->pos.x < -4.75f) ply->pos.x = -4.75f;
    if(ply->pos.x >  4.75f) ply->pos.x =  4.75f;

    if(ply->pos.y > 2.95f)
    {
        climbStage++;

        if(climbStage >= goalStage)
        {
            reset();
        }
        else
        {
            loadStage();
            inputLockedAfterHit = true;
            inputUnlockTimer = 0.18f;
        }
    }
}

void _level3::updateAcorn(float dt)
{
    if(!acornLive)
        return;

    acorn.pos.x += acornVelX * dt;

    if(fabs(acorn.pos.x - acornStart.x) > acornStraightDist)
    {
        acorn.pos.y += acornVelY * dt;
        acornVelY -= acornGravity * dt;
    }

    if(acorn.pos.x < -5.2f || acorn.pos.x > 5.2f || acorn.pos.y < -3.5f)
        acornLive = false;
}

void _level3::updateNuts()
{
    for(int i=0; i<6; i++)
    {
        if(nutLive[i] && hit->isRadialCol(nuts[i].pos,ply->pos,0.05f,0.11f,0.08f))
        {
            nutLive[i] = false;
            nutsCollected++;

            snd->playSounds((char*)"sounds/acorncollected.mp3");
        }
    }
}

void _level3::updateRocks(float dt)
{
    for(int i=0; i<2; i++)
    {
        rocks[i].pos.y -= fallSpeed[i] * dt;

        if(rocks[i].pos.y < -2.8f)
        {
            rocks[i].pos.y = 3.5f + (rand() % 3);
            rocks[i].pos.x = -3.0f + (rand() % 60) / 10.0f;
        }

        if(hit->isRadialCol(rocks[i].pos,ply->pos,0.08f,0.11f,0.04f))
        {
            startHit();
            return;
        }
    }
}

void _level3::updateSnakes(float dt)
{
    if(!snakeLive)
        return;

    int snakeTotal = 2;

    if(climbStage == 2)
        snakeTotal = 3;

    if(climbStage == 3)
        snakeTotal = 5;

    for(int i=0; i<snakeTotal; i++)
    {
        if(snakeFalling[i])
        {
            snakeHit[i].pos.y -= snakeFallSpeed[i] * dt;
            snakeFallSpeed[i] += 4.0f * dt;

            if(snakeHit[i].pos.y < -3.2f)
            {
                snakeFalling[i] = false;
                snakeDead[i] = true;
                snakes[i].pos.x = 20.0f;
                snakes[i].pos.y = 20.0f;
            }

            continue;
        }

        if(snakeDead[i])
            continue;

        snakes[i].pos.x += snakeDir[i] * snakeSpeed[i] * dt;

        float leftLimit = branch[snakeBranch[i]].pos.x - snakeRange[i];
        float rightLimit = branch[snakeBranch[i]].pos.x + snakeRange[i];

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

        snakes[i].pos.y = branch[snakeBranch[i]].pos.y + 0.30f;

        if(snakeDir[i] > 0.0f)
            snakes[i].scale.x = -0.75f;
        else
            snakes[i].scale.x = 0.75f;

        snakes[i].updateQuad();

        vec3 snakeHead = getSnakeHead(i);

        if(acornLive && hit->isRadialCol(acorn.pos, snakeHead, 0.12f, 0.10f, 0.08f))
        {
            acornLive = false;
            snakeFalling[i] = true;

            snakeHit[i].pos.x = snakes[i].pos.x;
            snakeHit[i].pos.y = snakes[i].pos.y;
            snakeHit[i].pos.z = snakes[i].pos.z;
            snakeHit[i].scale.y = 0.75f;

            if(snakes[i].scale.x < 0.0f)
                snakeHit[i].scale.x = -0.75f;
            else
                snakeHit[i].scale.x = 0.75f;
        }

        if(hit->isRadialCol(snakeHead, ply->pos, 0.14f, 0.10f, 0.08f))
        {
            startHit();
            return;
        }
    }
}

void _level3::updateBird(float dt)
{
    if(climbStage == 2 && !birdLive[0] && !birdFalling[0] && birdReady)
        setBird();

    if(climbStage == 3 &&
            !birdLive[0] &&
            !birdFalling[0] &&
            !birdLive[1] &&
            !birdFalling[1] &&
            birdReady)
        setBird();

    if(climbStage == 3 && birdLive[0] && !secondBirdSpawn)
    {
        bird2Timer += dt;

        if(bird2Timer > 0.45f)
        {
            birdLive[1] = true;
            birdDead[1] = false;
            birdFalling[1] = false;
            birdFallSpeed[1] = 2.0f;

            secondBirdSpawn = true;

            bird[1].pos.y = ply->pos.y;
            bird[1].pos.z = -7.0f;

            birdSpeed[1] = 3.0f + (rand() % 8) / 10.0f;

            if(birdDir[0] > 0.0f)
            {
                bird[1].pos.x = 5.2f;
                birdDir[1] = -1.0f;
                bird[1].scale.x = 0.45f;
            }
            else
            {
                bird[1].pos.x = -5.2f;
                birdDir[1] = 1.0f;
                bird[1].scale.x = -0.45f;
            }

            bird[1].scale.y = 0.45f;
        }
    }

    int birdTotal = (climbStage == 3) ? 2 : 1;

    for(int i=0; i<birdTotal; i++)
    {
        if(birdFalling[i])
        {
            birdHit[i].pos.y -= birdFallSpeed[i] * dt;
            birdFallSpeed[i] += 4.0f * dt;

            if(birdHit[i].pos.y < -3.2f)
            {
                birdFalling[i] = false;
                birdDead[i] = true;
                birdLive[i] = false;
            }

            continue;
        }

        if(!birdLive[i])
            continue;

        bird[i].pos.x += birdDir[i] * birdSpeed[i] * dt;

        if(bird[i].pos.x < -5.4f || bird[i].pos.x > 5.4f)
        {
            birdLive[i] = false;

            if(climbStage == 2)
                setBird();

            if(climbStage == 3 && i == 0)
                secondBirdSpawn = true;

            continue;
        }

        if(acornLive && hit->isRadialCol(acorn.pos,bird[i].pos,0.12f,0.12f,0.08f))
        {
            acornLive = false;
            birdLive[i] = false;
            birdFalling[i] = true;
            birdHit[i].pos.x = bird[i].pos.x;
            birdHit[i].pos.y = bird[i].pos.y;
            birdHit[i].pos.z = bird[i].pos.z;
            birdHit[i].scale.y = 0.60f;
            birdHit[i].scale.x = bird[i].scale.x;
            continue;
        }

        if(hit->isRadialCol(bird[i].pos,ply->pos,0.12f,0.11f,0.08f))
        {
            startHit();
            return;
        }
    }
}

void _level3::update(float dt, bool isPaused)
{
    if(isPaused || gameWon)
        return;

    if(isHit)
    {
        updateHit(dt);
        return;
    }

    updateThrow(dt);
    updatePlayer(dt);
    updateAcorn(dt);
    updateNuts();
    updateRocks(dt);

    if(isHit)
        return;

    ply->playerActions(dt);
    ply->updateQuad();

    updateSnakes(dt);
    updateBird(dt);

    if(climbStage == 3 &&
            hit->isRadialCol(goldenAcorn.pos, ply->pos, 0.30f, 0.25f, 0.18f))
    {
        snd->sndEng->stopAllSounds();
        snd->playSounds((char*)"sounds/finalmusic.mp3");
        gameWon = true;
    }
}

void _level3::drawSnakes()
{
    if(!snakeLive)
        return;

    int snakeTotal = 2;

    if(climbStage == 2)
        snakeTotal = 3;

    if(climbStage == 3)
        snakeTotal = 5;

    for(int i=0; i<snakeTotal; i++)
    {
        if(snakeFalling[i])
            snakeHit[i].drawQuad();
        else if(!snakeDead[i])
            snakes[i].drawQuad();
    }
}

void _level3::drawBirds()
{
    int birdTotal = (climbStage == 3) ? 2 : 1;

    for(int i=0; i<birdTotal; i++)
    {
        if(birdFalling[i])
            birdHit[i].drawQuad();
        else if(birdLive[i])
            bird[i].drawQuad();
    }
}

void _level3::drawPlayer()
{
    if(isHit)
    {
        setPlayerPic(&plyHit);
        plyHit.pos.y -= 0.10f;
        setPicFace(&plyHit,0.75f);
        plyHit.drawQuad();
    }
    else if(isThrow)
    {
        setPlayerPic(&plyThrow);
        plyThrow.pos.y -= 0.18f;
        setPicFace(&plyThrow,0.75f);
        plyThrow.drawQuad();
    }
    else if(!isJump && !kbm->isLeftPressed && !kbm->isRightPressed)
    {
        setPlayerPic(&plyIdle);
        plyIdle.pos.y -= 0.18f;
        setPicFace(&plyIdle,0.75f);
        plyIdle.drawQuad();
    }
    else
        ply->drawQuad();
}

void _level3::draw(float dt, bool isPaused, vec2 dim)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0,0,1.0);

    if(gameWon && creditStage == 1)
    {
        endCredits.drawQuad();
        return;
    }

    glPushMatrix();


    const float DESIGN_W = 1366.0f;
    const float DESIGN_H = 768.0f;

    glScalef(4.2f,4.2f,1.0f);
    prlx->drawBckGrnd(DESIGN_W,DESIGN_H);
    glPopMatrix();

    for(int i=0; i<6; i++)
        branch[i].drawQuad();

    for(int i=0; i<6; i++)
    {
        if(nutLive[i])
            nuts[i].drawQuad();
    }

    for(int i=0; i<2; i++)
        rocks[i].drawQuad();

    drawSnakes();
    drawBirds();

    if(climbStage == 3)
        goldenAcorn.drawQuad();

    if(gameWon && creditStage == 0)
    {
        gameCompleted.drawQuad();
        return;
    }

    if(acornLive)
        acorn.drawQuad();

    nutHudBox.scale.x = 0.95f;
    nutHudBox.scale.y = 0.18f;
    nutHudBox.pos.x = -3.15f;
    nutHudBox.pos.y = -2.62f;
    nutHudBox.pos.z = -6.90f;
    nutHudBox.drawQuad();

    for(int i = 0; i < nutsCollected && i < 10; i++)
    {
        nutMeter[i].pos.x = -3.72f + (i * 0.12f);
        nutMeter[i].pos.y = -2.52f;
        nutMeter[i].pos.z = -6.70f;

        nutMeter[i].scale.x = 0.10f;
        nutMeter[i].scale.y = 0.10f;
        nutMeter[i].scale.z = 1.0f;

        nutMeter[i].drawQuad();
    }

    drawPlayer();
}

int _level3::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_SETCURSOR:
        SetCursor(LoadCursor(NULL, IDC_CROSS));
        return true;

    case WM_KEYDOWN:
        if((wParam == VK_RETURN || wParam == VK_SPACE) && gameWon)
        {
            if(creditStage == 0)
            {
                creditStage = 1;
                snd->sndEng->stopAllSounds();
                snd->playMusic((char*)"sounds/creditsmusic.mp3");
            }
            else
            {
                returnToMenu = true;
            }

            return true;
        }

        if(isHit)
            break;

        if(inputLockedAfterHit)
            break;

        kbm->wParam = wParam;
        kbm->keyPressed(ply);

        if(wParam == VK_LEFT)  kbm->isLeftPressed = true;
        if(wParam == VK_RIGHT) kbm->isRightPressed = true;

        if(wParam == VK_UP)
        {
            kbm->isUpPressed = true;
            jumpPressed = true;
            jumpBufferTimer = jumpBufferMax;
        }

        if(wParam == VK_SPACE)
        {
            kbm->isSpacePressed = true;
            jumpPressed = true;
            jumpBufferTimer = jumpBufferMax;
        }

        if(wParam == VK_SHIFT)
            throwPressed = true;

        break;

    case WM_KEYUP:
        kbm->wParam = wParam;
        kbm->keyUp(ply);

        if(wParam == VK_LEFT)  kbm->isLeftPressed = false;
        if(wParam == VK_RIGHT) kbm->isRightPressed = false;
        if(wParam == VK_UP)    kbm->isUpPressed = false;
        if(wParam == VK_SPACE) kbm->isSpacePressed = false;
        if(wParam == VK_SHIFT) throwPressed = false;

        break;

    default:
        break;
    }

    return 0;
}
