#include "_modelvbo.h"

_modelVBO::_modelVBO()
{
    //ctor
    rot.x =rot.y=rot.z =0;
    scale.x=scale.y= scale.z =1;
    pos.x =0;
    pos.y =0;
    pos.z =-4.0;

}

_modelVBO::~_modelVBO()
{
    //dtor
}

void _modelVBO::drawmodel()
{
   glPushMatrix();  // start groupiong
   glColor3f(0,1,0);
   glTranslatef(pos.x,pos.y,pos.z);
   glRotatef(rot.x, 1,0,0);
   glRotatef(rot.y, 0,1,0);
   glRotatef(rot.z, 0,0,1);

   glScalef(scale.x,scale.y,scale.z);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);

   glBindBuffer(GL_ARRAY_BUFFER,vboVerticies);
   glVertexPointer(3,GL_FLOAT,0,0);

   glBindBuffer(GL_ARRAY_BUFFER,vboNormals);
   glNormalPointer(GL_FLOAT,0,0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,eboID);
   myTex->BindTexture();
   glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);

   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);

   glPopMatrix();  //End grouping
}

void _modelVBO::modelInit(char *fileName)
{
    // setup VBO
    glGenBuffers(1,&vboVerticies);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticies);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glGenBuffers(1,&vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER,vboNormals);
    glBufferData(GL_ARRAY_BUFFER,sizeof(normals),normals,GL_STATIC_DRAW);

    //set faces (index)
    glGenBuffers(1,&eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    myTex->loadTexture(fileName);
}
