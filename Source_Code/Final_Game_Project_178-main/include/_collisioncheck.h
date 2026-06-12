#ifndef _COLLISIONCHECK_H
#define _COLLISIONCHECK_H

#include<_common.h>
#include<_quad.h>

class _collisionCheck
{
    public:
        _collisionCheck();
        virtual ~_collisionCheck();

        bool isLinearCol(vec3,vec3); // check only xy
        bool isRadialCol(vec3,vec3,float,float,float);
         //positions, radius, threshold
        bool isPlanoCol(vec3,vec3);
        bool isAABBCol(vec3,vec3,vec3,vec3);

    protected:

    private:
};

#endif // _COLLISIONCHECK_H
