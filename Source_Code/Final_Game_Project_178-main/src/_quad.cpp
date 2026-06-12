#include "_quad.h"

_quad::_quad()
{
    rot.x = rot.y = rot.z = 0;
    pos.x = pos.y = 0;
    pos.z = -8;
    scale.x = scale.y = scale.z = 1;
    vboPos = 0;
    vboTex = 0;
}

_quad::~_quad()
{
    if(vboPos)
    {
        glDeleteBuffers(1, &vboPos);
        vboPos = 0;
    }

    if(vboTex)
    {
        glDeleteBuffers(1, &vboTex);
        vboTex = 0;
    }
}

void _quad::initQuad(char* fileName)
{
    if(vboPos)
    {
        glDeleteBuffers(1, &vboPos);
        vboPos = 0;
    }

    if(vboTex)
    {
        glDeleteBuffers(1, &vboTex);
        vboTex = 0;
    }

    glGenBuffers(1, &vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glGenBuffers(1, &vboTex);
    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);

    myTex->loadTexture(fileName);
}

void _quad::drawQuad()
{
    glPushMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);

    myTex->BindTexture();

    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rot.x, 1, 0, 0);
    glRotatef(rot.y, 0, 1, 0);
    glRotatef(rot.z, 0, 0, 1);
    glScalef(scale.x, scale.y, scale.z);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glTexCoordPointer(2, GL_FLOAT, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}

void _quad::updateQuad()
{
    float left = xMin;
    float right = xMax;

    if(facingLeft)
    {
        left = xMax;
        right = xMin;
    }

    float newTexCoord[8] =
    {
        right, yMin,
        right, yMax,
        left, yMax,
        left, yMin
    };

    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newTexCoord), newTexCoord);
}
