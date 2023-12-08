// Border variables and functions
#ifdef __APPLE__ // Check os
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
#endif
#ifndef BORDERS_H
#define BORDERS_H

const extern float borderLeft;
const extern float borderRight;
const extern float borderTop;
const extern float borderBottom;
const extern float UIheight;

void drawBorders();

#endif
