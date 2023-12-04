#ifdef __APPLE__ // Check if the target OS is macOS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
#endif

#ifndef MY_VARIABLES_H
#define MY_VARIABLES_H

const extern float borderLeft;
const extern float borderRight;
const extern float borderTop;
const extern float borderBottom;

#endif