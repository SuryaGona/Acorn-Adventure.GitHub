#ifndef _TIMER_H
#define _TIMER_H

#include<_common.h>
#include<stdio.h>

class _timer
{
    public:
        _timer();
        virtual ~_timer();

        void start(float duration);
        void stop();
        void reset();
        void update(float dt);
        void draw(float x, float y, float r, float g, float b);
        void drawText(const char* text, float x, float y, float r, float g, float b);

        float getTimeLeft();
        bool  isRunning();
        bool  isFinished();

    private:
        float timeLeft;
        float duration;
        bool  running;
        bool  finished;
};

#endif // _TIMER_H
