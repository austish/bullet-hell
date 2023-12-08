#include "ui.h"
#include "borders.h"

// UI player design
void drawUI(Player p) {
    glColor3f(0.5f, 0.5f, 0.5f); // Set color to gray for background
    glBegin(GL_QUADS);
    glVertex2f(borderLeft, borderTop + UIheight);
    glVertex2f(borderRight, borderTop + UIheight); // Account for UI height
    glVertex2f(borderRight, borderTop);
    glVertex2f(borderLeft, borderTop);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white for text
    std::string h = "Health: " + std::to_string(p.getHealth());
    drawText(h, borderLeft + 10, borderTop + UIheight - 30);
    std::string s = "Score: " + std::to_string(p.getScore());
    drawText(s, borderRight - 100, borderTop + UIheight - 30);
}

// UI text design
void drawText(const std::string &text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
