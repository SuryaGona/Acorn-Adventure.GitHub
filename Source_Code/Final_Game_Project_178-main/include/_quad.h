#ifndef _QUAD_H
#define _QUAD_H

#include<_common.h>
#include<_textureloader.h>

class _quad
{
    public:
        _quad();
        virtual ~_quad();

        vec3 rot;
        vec3 pos;
        vec3 scale;

        void initQuad(char *);
        void drawQuad();
        void updateQuad();

        GLuint vboPos, vboTex;
        _textureLoader *myTex = new _textureLoader();

        float xMin =0;
        float xMax =1;
        float yMin =0;
        float yMax =1;

        float verticies[12]={1.0,1.0,0,  //top right
                             1.0,-1.0,0, //bottom right
                             -1.0,-1.0,0,//bottom left
                             -1.0,1.0,0  // top left
                              };

        float texCoord[8] = {xMax,yMin,
                             xMax,yMax,
                             xMin,yMax,
                             xMin,yMin};

        bool facingLeft = false;


    protected:

    private:
};

#endif // _QUAD_H
