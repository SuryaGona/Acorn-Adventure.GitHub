#ifndef _PARALLAX_H
#define _PARALLAX_H

#include<_common.h>
#include<_textureloader.h>


class _parallax
{
    public:
        _parallax();
        virtual ~_parallax();

        void initPrlx(char *);
        void scroll(bool,int,float);
        void drawBckGrnd(float,float);

        _textureLoader *bckGrnd = new _textureLoader();
        enum{LEFT,RIGHT,UP,DOWN};

        float xMax,xMin,yMax,yMin;
        vec3 scale;
    protected:

    private:
};

#endif
