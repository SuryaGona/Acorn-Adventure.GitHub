#ifndef _COMMON_H
#define _COMMON_H

#include<GL/glew.h>
#include<windows.h>
#include<iostream>
#include<gl/gl.h>
#include<GL/glut.h>
#include<time.h>
#include<cmath>
#include <stdlib.h>
#include<chrono>
#include<string>
#include<map>

#define PI 3.14159
#define GLEW_STATIC
#define GRAVITY 9.81


using namespace std;

typedef struct{

     double x;
     double y;
     double z;
}vec3;


typedef struct
{
    float x;
    float y;
}vec2;


#endif // _COMMON_H
