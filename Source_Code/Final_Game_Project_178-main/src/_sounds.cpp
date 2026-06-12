#include "_sounds.h"

_sounds::_sounds()
{
}

_sounds::~_sounds()
{
    if(sndEng)
    {
        sndEng->drop();
        sndEng = nullptr;
    }
}

void _sounds::playMusicAdj(char* FN, float ADJ)
{
    if(!sndEng || !FN)
        return;

    if(ADJ < 0.0f)
        ADJ = 0.0f;

    if(ADJ > 1.0f)
        ADJ = 1.0f;

    ISound* adjSND = sndEng->play2D(FN, true, false, true);

    if(adjSND)
    {
        adjSND->setVolume(ADJ);
        adjSND->drop();
    }
}

void _sounds::playMusic(char* fileName)
{
    if(!sndEng || !fileName)
        return;

    sndEng->play2D(fileName, true, false, true);
}

void _sounds::playSounds(char* fileName)
{
    if(!sndEng || !fileName)
        return;

    sndEng->play2D(fileName, false, false);
}

void _sounds::pauseSound(char* fileName)
{
    if(!sndEng || !fileName)
        return;

    sndEng->play2D(fileName, true, false);
}

void _sounds::initSounds()
{
    if(!sndEng)
        cout << "ERROR** Sound Engine did not Start " << endl;
}
