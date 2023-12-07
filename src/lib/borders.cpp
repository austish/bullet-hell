#include "borders.h"

// Initialize borders
const extern float borderLeft = -400.0f;
const extern float borderRight = 400.0f;
const extern float borderTop = 250.0f;
const extern float borderBottom = -300.0f;
const extern float UIheight = 50.0f;

// Draw borders (white)
void drawBorders() {
   glColor3f(1.0f, 1.0f, 1.0f); // Set border color to red
   glBegin(GL_LINES);
   // Top border
   glVertex2f(borderLeft, borderTop);
   glVertex2f(borderRight, borderTop);
   // Bottom border
   glVertex2f(borderLeft, borderBottom);
   glVertex2f(borderRight, borderBottom);
   // Left border
   glVertex2f(borderLeft, borderBottom);
   glVertex2f(borderLeft, borderTop);
   // Right border
   glVertex2f(borderRight, borderBottom);
   glVertex2f(borderRight, borderTop);
   glEnd();
}