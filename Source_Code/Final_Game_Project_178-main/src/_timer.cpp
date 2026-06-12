#include "_timer.h"

_timer::_timer()
{
    timeLeft = 0.0f;
    duration = 0.0f;
    running  = false;
    finished = false;
}

_timer::~_timer()
{
    //dtor
}

void _timer::start(float dur)
{
    duration = dur;
    timeLeft = dur;
    running  = true;
    finished = false;
}

void _timer::stop()
{
    running = false;
}

void _timer::reset()
{
    timeLeft = duration;
    running  = false;
    finished = false;
}

void _timer::update(float dt)
{
    if (!running || finished) return;
    timeLeft -= dt;
    if (timeLeft <= 0.0f)
    {
        timeLeft = 0.0f;
        running  = false;
        finished = true;
    }
}

float _timer::getTimeLeft() { return timeLeft; }
bool  _timer::isRunning()   { return running;   }
bool  _timer::isFinished()  { return finished;  }

void _timer::drawText(const char* text, float x, float y, float r, float g, float b)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}

void _timer::draw(float x, float y, float r, float g, float b)
{
    int totalSecs = (int)timeLeft;
    int mins      = totalSecs / 60;
    int secs      = totalSecs % 60;

    char buf[16];
    sprintf(buf, "Time: %02d:%02d", mins, secs);

    drawText(buf, x, y, r, g, b);
}
