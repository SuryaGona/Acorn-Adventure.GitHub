#ifndef _MODEL_H
#define _MODEL_H

#include<_common.h>

class _model
{
    public:
        _model();
        virtual ~_model();

        vec3 rotation;
        vec3 pos;
        vec3 scale;

        void initModel();
        void drawModel();


    protected:

    private:
};

#endif // _MODEL_H
